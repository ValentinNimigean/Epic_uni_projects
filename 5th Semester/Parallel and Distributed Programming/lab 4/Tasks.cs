using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.IO;
using System.Threading.Tasks;

class ClientTasks
{
    public static Task Run(string[] urls)
    {
        Console.WriteLine("Running Task/ContinueWith client...");

        Task[] all = new Task[urls.Length];
        for (int i = 0; i < urls.Length; i++)
        {
            all[i] = DownloadOne(urls[i]);
        }

        return Task.WhenAll(all);
    }

    private static Task DownloadOne(string urlStr)
    {
        Uri uri = new Uri(urlStr);

        IPAddress ip = Array.Find(
            Dns.GetHostEntry(uri.Host).AddressList,
            a => a.AddressFamily == AddressFamily.InterNetwork
        );

        if (ip == null)
            throw new Exception("No IPv4 address found for " + uri.Host);

        IPEndPoint ep = new IPEndPoint(ip, uri.Port == -1 ? 80 : uri.Port);

        Socket sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

        byte[] buf = new byte[4096];
        var headerBuilder = new StringBuilder();
        bool headersDone = false;
        int contentLength = -1;
        int bodyReceived = 0;

        string fileName = Path.GetFileName(uri.LocalPath);
        if (string.IsNullOrEmpty(fileName))
            fileName = "download_" + Guid.NewGuid().ToString("N") + ".bin";
        string outPath = Path.Combine("downloads", fileName);

        FileStream fs = new FileStream(outPath, FileMode.Create, FileAccess.Write);

        return SocketHelpers.ConnectAsync(sock, ep)
            .ContinueWith(_ =>
            {
                string req =
                    $"GET {uri.PathAndQuery} HTTP/1.1\r\nHost: {uri.Host}\r\nConnection: close\r\n\r\n";

                byte[] reqBytes = Encoding.ASCII.GetBytes(req);
                return SocketHelpers.SendAsync(sock, reqBytes);
            }).Unwrap()
            .ContinueWith(_ =>
                ReceiveLoop(sock, buf, headerBuilder, fs, uri,
                    headersDone, contentLength, bodyReceived)
            ).Unwrap();
    }

    private static Task ReceiveLoop(
        Socket sock, byte[] buf, StringBuilder headerBuilder,
        FileStream fs, Uri uri, bool headersDone,
        int contentLength, int bodyReceived)
    {
        return SocketHelpers.ReceiveAsync(sock, buf).ContinueWith(t =>
        {
            int n = t.Result;

            if (n <= 0)
            {
                fs.Close();
                sock.Close();
                Console.WriteLine($"[TASKS] Finished {uri} (body {bodyReceived} bytes)");
                return Task.CompletedTask;
            }

            int offset = 0;

            if (!headersDone)
            {
                string chunk = Encoding.ASCII.GetString(buf, 0, n);
                headerBuilder.Append(chunk);

                string all = headerBuilder.ToString();
                int idx = all.IndexOf("\r\n\r\n", StringComparison.Ordinal);

                if (idx >= 0)
                {
                    headersDone = true;
                    string headerText = all.Substring(0, idx);
                    contentLength = HttpParser.GetContentLength(headerText);

                    string bodyStr = all.Substring(idx + 4);
                    byte[] bodyBytes = Encoding.ASCII.GetBytes(bodyStr);

                    fs.Write(bodyBytes, 0, bodyBytes.Length);
                    bodyReceived += bodyBytes.Length;

                    if (contentLength > 0 && bodyReceived >= contentLength)
                    {
                        fs.Close();
                        sock.Close();
                        Console.WriteLine($"[TASKS] Finished {uri} → {bodyReceived} bytes to {fs.Name}");
                        return Task.CompletedTask;
                    }

                    return ReceiveLoop(sock, buf, headerBuilder, fs, uri,
                        headersDone, contentLength, bodyReceived);
                }
                else
                {
                    return ReceiveLoop(sock, buf, headerBuilder, fs, uri,
                        headersDone, contentLength, bodyReceived);
                }
            }
            else
            {
                fs.Write(buf, offset, n - offset);
                bodyReceived += (n - offset);

                if (contentLength > 0 && bodyReceived >= contentLength)
                {
                    fs.Close();
                    sock.Close();
                    Console.WriteLine($"[TASKS] Finished {uri} → {bodyReceived} bytes to {fs.Name}");
                    return Task.CompletedTask;
                }

                return ReceiveLoop(sock, buf, headerBuilder, fs, uri,
                    headersDone, contentLength, bodyReceived);
            }
        }).Unwrap();
    }
}

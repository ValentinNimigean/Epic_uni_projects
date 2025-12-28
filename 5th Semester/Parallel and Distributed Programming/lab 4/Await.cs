using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.IO;
using System.Threading.Tasks;

class ClientAwait
{
    public static Task Run(string[] urls)
    {
        Console.WriteLine("Running async/await client...");

        Task[] tasks = new Task[urls.Length];
        for (int i = 0; i < urls.Length; i++)
        {
            tasks[i] = DownloadOneAsync(urls[i]);
        }

        return Task.WhenAll(tasks);
    }

    private static async Task DownloadOneAsync(string urlStr)
    {
        Uri uri = new Uri(urlStr);

        IPAddress ip = null;
        foreach (var addr in Dns.GetHostEntry(uri.Host).AddressList)
        {
            if (addr.AddressFamily == AddressFamily.InterNetwork)
            {
                ip = addr;
                break;
            }
        }
        if (ip == null)
            throw new Exception("No IPv4 address found for host: " + uri.Host);

        IPEndPoint ep = new IPEndPoint(ip, uri.Port == -1 ? 80 : uri.Port);

        using Socket sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

        await SocketHelpers.ConnectAsync(sock, ep);

        string req =
            $"GET {uri.PathAndQuery} HTTP/1.1\r\nHost: {uri.Host}\r\nConnection: close\r\n\r\n";
        byte[] reqBytes = Encoding.ASCII.GetBytes(req);
        await SocketHelpers.SendAsync(sock, reqBytes);

        byte[] buf = new byte[4096];
        StringBuilder headerBuilder = new StringBuilder();
        bool headersDone = false;
        int contentLength = -1;
        int bodyReceived = 0;

        string fileName = Path.GetFileName(uri.LocalPath);
        if (string.IsNullOrEmpty(fileName))
            fileName = "download_" + Guid.NewGuid().ToString("N") + ".bin";
        string outPath = Path.Combine("downloads", fileName);

        using FileStream fs = new FileStream(outPath, FileMode.Create, FileAccess.Write);

        while (true)
        {
            int n = await SocketHelpers.ReceiveAsync(sock, buf);
            if (n <= 0)
                break;

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
                        break;

                    continue;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                fs.Write(buf, offset, n - offset);
                bodyReceived += (n - offset);

                if (contentLength > 0 && bodyReceived >= contentLength)
                    break;
            }
        }

        Console.WriteLine($"[AWAIT] Finished {uri} → {bodyReceived} bytes to {outPath}");
    }
}

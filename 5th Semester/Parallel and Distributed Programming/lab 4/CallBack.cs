using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.IO;
using System.Threading;

class ClientCallBack
{
    private static CountdownEvent _latch;
    private static object _lockObj = new object();

    public static void Run(string[] urls)
    {
        Console.WriteLine("Running callbacks (Begin/End) client...");

        _latch = new CountdownEvent(urls.Length);

        foreach (var urlStr in urls)
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

            Socket sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            string fileName = Path.GetFileName(uri.LocalPath);
            if (string.IsNullOrEmpty(fileName))
                fileName = "download_" + Guid.NewGuid().ToString("N") + ".bin";
            string outPath = Path.Combine("downloads", fileName);

            Session sess = new Session(sock, uri, outPath);
            sock.BeginConnect(ep, ar => sess.OnConnected(ar), null);
        }

        _latch.Wait();
        Console.WriteLine("All downloads complete (BeginEnd).");
    }

    class Session
    {
        enum ParseState { ReadingHeaders, ReadingBody }

        private Socket _conn;
        private Uri _uri;
        private string _outPath;

        private byte[] _buffer;
        private int _pos;
        private int _size;

        private ParseState _state;
        private bool _headersDone;
        private int _contentLength;
        private int _bodyReceived;

        private MemoryStream _headerBytes;
        private FileStream _fs;

        private bool _done;

        public Session(Socket conn, Uri uri, string outPath)
        {
            _conn = conn;
            _uri = uri;
            _outPath = outPath;
            _buffer = new byte[4096];
            _pos = 0;
            _size = 0;
            _state = ParseState.ReadingHeaders;
            _headersDone = false;
            _contentLength = -1;
            _bodyReceived = 0;
            _headerBytes = new MemoryStream();
            _fs = new FileStream(outPath, FileMode.Create, FileAccess.Write);
            _done = false;
        }

        public void OnConnected(IAsyncResult ar)
        {
            try
            {
                _conn.EndConnect(ar);

                string req =
                    $"GET {_uri.PathAndQuery} HTTP/1.1\r\n" +
                    $"Host: {_uri.Host}\r\n" +
                    "Connection: close\r\n\r\n";

                byte[] reqBytes = Encoding.ASCII.GetBytes(req);
                _conn.BeginSend(reqBytes, 0, reqBytes.Length, SocketFlags.None, OnSent, null);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"[CB] Connect error: {ex.Message}");
                Finish();
            }
        }

        private void OnSent(IAsyncResult ar)
        {
            try
            {
                _conn.EndSend(ar);
                _conn.BeginReceive(_buffer, 0, _buffer.Length, SocketFlags.None, OnBytesReceived, null);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"[CB] Send error: {ex.Message}");
                Finish();
            }
        }

        private void OnBytesReceived(IAsyncResult ar)
        {
            try
            {
                _size = _conn.EndReceive(ar);
                _pos = 0;
                ProcessBuffer();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"[CB] Receive error: {ex.Message}");
                Finish();
            }
        }

        private void ProcessBuffer()
        {
            if (_size == 0)
            {
                Finish();
                return;
            }

            while (_pos < _size)
            {
                byte b = _buffer[_pos];
                _pos++;

                if (_state == ParseState.ReadingHeaders)
                {
                    _headerBytes.WriteByte(b);
                    if (_headerBytes.Length >= 4)
                    {
                        byte[] hb = _headerBytes.GetBuffer();
                        int n = (int)_headerBytes.Length;
                        if (hb[n - 4] == (byte)'\r' &&
                            hb[n - 3] == (byte)'\n' &&
                            hb[n - 2] == (byte)'\r' &&
                            hb[n - 1] == (byte)'\n')
                        {
                            _headersDone = true;
                            _state = ParseState.ReadingBody;

                            string headerText = Encoding.ASCII.GetString(hb, 0, n - 4);
                            _contentLength = HttpParser.GetContentLength(headerText);

                            continue;
                        }
                    }
                }
                else
                {
                    _fs.WriteByte(b);
                    _bodyReceived++;

                    if (_contentLength > 0 && _bodyReceived >= _contentLength)
                    {
                        Finish();
                        return;
                    }
                }
            }

            _conn.BeginReceive(_buffer, 0, _buffer.Length, SocketFlags.None, OnBytesReceived, null);
        }

        private void Finish()
        {
            if (_done) return;
            _done = true;

            try { _conn.Close(); } catch { }
            try { _fs.Close(); } catch { }

            Console.WriteLine($"[CB] Finished {_outPath} ({_bodyReceived} bytes)");

            ClientCallBack._latch.Signal();
        }
    }
}

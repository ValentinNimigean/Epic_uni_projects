using System;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;

static class SocketHelpers
{
    public static Task ConnectAsync(Socket s, EndPoint ep)
    {
        var tcs = new TaskCompletionSource<bool>();

        s.BeginConnect(ep, ar =>
        {
            try
            {
                s.EndConnect(ar);
                tcs.SetResult(true);
            }
            catch (Exception ex)
            {3
                tcs.SetException(ex);
            }
        }, null);

        return tcs.Task;
    }

    public static Task<int> SendAsync(Socket s, byte[] buf)
    {
        var tcs = new TaskCompletionSource<int>();

        s.BeginSend(buf, 0, buf.Length, SocketFlags.None, ar =>
        {
            try
            {
                int sent = s.EndSend(ar);
                tcs.SetResult(sent);
            }
            catch (Exception ex)
            {
                tcs.SetException(ex);
            }
        }, null);

        return tcs.Task;
    }

    public static Task<int> ReceiveAsync(Socket s, byte[] buf)
    {
        var tcs = new TaskCompletionSource<int>();

        s.BeginReceive(buf, 0, buf.Length, SocketFlags.None, ar =>
        {
            try
            {
                int received = s.EndReceive(ar);
                tcs.SetResult(received);
            }
            catch (Exception ex)
            {
                tcs.SetException(ex);
            }
        }, null);

        return tcs.Task;
    }
}

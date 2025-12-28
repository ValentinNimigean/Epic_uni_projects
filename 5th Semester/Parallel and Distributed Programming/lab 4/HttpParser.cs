using System;

class HttpParser
{
    public static int GetContentLength(string headers)
    {
        int len = -1;

        var lines = headers.Split(new[] { "\r\n" }, StringSplitOptions.None);
        foreach (var line in lines)
        {
            if (line.StartsWith("Content-Length:", StringComparison.OrdinalIgnoreCase))
            {
                var parts = line.Split(':');
                if (parts.Length >= 2 && int.TryParse(parts[1].Trim(), out int v))
                    len = v;
            }
        }

        return len;
    }
}

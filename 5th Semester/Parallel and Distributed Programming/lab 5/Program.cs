using System;
using System.Numerics;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

class Program
{
    static void Main(string[] args)
    {
        string logFile = "results.txt";

        File.AppendAllText(logFile,
            $"\n===========================\n" +
            $"RUN AT {DateTime.Now}\n" +
            $"===========================\n\n");

        RunSmallNumbers(logFile);
        RunBigNumbers(logFile);

        Console.WriteLine("All runs completed. Results saved to results.txt");
    }

    static void RunSmallNumbers(string logFile)
    {
        File.AppendAllText(logFile, "--- SMALL NUMBER RUN ---\n\n");

        int[] sizes = { 64, 128,500,1300,10000 };

        foreach (int n in sizes)
        {
            var a = GenerateRandomSmallPolynomial(n);
            var b = GenerateRandomSmallPolynomial(n);

            File.AppendAllText(logFile, $"Small-number polynomial size: {n}\n");

            var t1 = Measure(() => NaiveSequential(a, b));
            var t2 = Measure(() => NaiveParallel(a, b));
            var t3 = Measure(() => KaratsubaSequential(a, b));
            var t4 = Measure(() => KaratsubaParallel(a, b));

            File.AppendAllText(logFile,
                $"Naive sequential:     {t1.TotalMilliseconds:F2} ms\n" +
                $"Naive parallel:       {t2.TotalMilliseconds:F2} ms\n" +
                $"Karatsuba sequential: {t3.TotalMilliseconds:F2} ms\n" +
                $"Karatsuba parallel:   {t4.TotalMilliseconds:F2} ms\n\n");

            Console.WriteLine($"Small {n}: done.");
        }
    }

    static void RunBigNumbers(string logFile)
    {
        File.AppendAllText(logFile, "--- BIG NUMBER RUN ---\n\n");

        int[] sizes = { 64, 120, 300, 1000};

        foreach (int n in sizes)
        {
            var a = GenerateRandomBigPolynomial(n, 256);
            var b = GenerateRandomBigPolynomial(n, 256);

            File.AppendAllText(logFile, $"Big-number polynomial size: {n}\n");

            var t1 = Measure(() => NaiveSequential(a, b));
            var t2 = Measure(() => NaiveParallel(a, b));
            var t3 = Measure(() => KaratsubaSequential(a, b));
            var t4 = Measure(() => KaratsubaParallel(a, b));

            File.AppendAllText(logFile,
                $"Naive sequential:     {t1.TotalMilliseconds:F2} ms\n" +
                $"Naive parallel:       {t2.TotalMilliseconds:F2} ms\n" +
                $"Karatsuba sequential: {t3.TotalMilliseconds:F2} ms\n" +
                $"Karatsuba parallel:   {t4.TotalMilliseconds:F2} ms\n\n");

            Console.WriteLine($"Big {n}: done.");
        }
    }

    // ALGORITHMS

    // 1. Naive Sequential O(n²)
    public static BigInteger[] NaiveSequential(BigInteger[] a, BigInteger[] b)
    {
        int n = a.Length, m = b.Length;
        BigInteger[] result = new BigInteger[n + m - 1];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                result[i + j] += a[i] * b[j];

        return result;
    }

    // 2. Naive Parallel (with per-index locks)
    public static BigInteger[] NaiveParallel(BigInteger[] a, BigInteger[] b)
    {
        int n = a.Length, m = b.Length;
        BigInteger[] result = new BigInteger[n + m - 1];

        object[] locks = new object[result.Length];
        for (int i = 0; i < locks.Length; i++)
            locks[i] = new object();

        Parallel.For(0, n, i =>
        {
            for (int j = 0; j < m; j++)
            {
                int k = i + j;
                BigInteger product = a[i] * b[j];

                lock (locks[k])
                {
                    result[k] += product;
                }
            }
        });

        return result;
    }

    // 3. Karatsuba Sequential

    public static BigInteger[] KaratsubaSequential(BigInteger[] a, BigInteger[] b)
    {
        int n = NextPow2(Math.Max(a.Length, b.Length));
        a = Pad(a, n);
        b = Pad(b, n);
        return KarSeq(a, b, n);
    }

    private static BigInteger[] KarSeq(BigInteger[] a, BigInteger[] b, int n)
    {
        BigInteger[] result = new BigInteger[2 * n];

        if (n <= 32)
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    result[i + j] += a[i] * b[j];

            return result;
        }

        int m = n / 2;

        var a0 = Slice(a, 0, m);
        var a1 = Slice(a, m, m);
        var b0 = Slice(b, 0, m);
        var b1 = Slice(b, m, m);

        var z0 = KarSeq(a0, b0, m);
        var z2 = KarSeq(a1, b1, m);
        var z1star = KarSeq(Add(a0, a1), Add(b0, b1), m);

        var z1 = Sub(Sub(z1star, z0), z2);

        Combine(result, z0, z1, z2, m);
        return result;
    }

    // 4. Karatsuba Parallel 

    public static BigInteger[] KaratsubaParallel(BigInteger[] a, BigInteger[] b)
    {
        int n = NextPow2(Math.Max(a.Length, b.Length));
        a = Pad(a, n);
        b = Pad(b, n);
        return KarPar(a, b, n, 0);
    }

    private static BigInteger[] KarPar(BigInteger[] a, BigInteger[] b, int n, int depth)
    {
        BigInteger[] result = new BigInteger[2 * n];

  
        if (n <= 32)
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    result[i + j] += a[i] * b[j];

            return result;
        }

        int m = n / 2;

        var a0 = Slice(a, 0, m);
        var a1 = Slice(a, m, m);
        var b0 = Slice(b, 0, m);
        var b1 = Slice(b, m, m);

        BigInteger[] z0 = null!, z1star = null!, z2 = null!;

        if (depth < 4) 
        {
            var t0 = Task.Run(() => z0 = KarPar(a0, b0, m, depth + 1));
            var t1 = Task.Run(() => z2 = KarPar(a1, b1, m, depth + 1));
            var t2 = Task.Run(() => z1star = KarPar(Add(a0, a1), Add(b0, b1), m, depth + 1));

            Task.WaitAll(t0, t1, t2);
        }
        else 
        {
            z0 = KarSeq(a0, b0, m);
            z2 = KarSeq(a1, b1, m);
            z1star = KarSeq(Add(a0, a1), Add(b0, b1), m);
        }

        var z1 = Sub(Sub(z1star, z0), z2);

        Combine(result, z0, z1, z2, m);
        return result;
    }

    // HELPER METHODS


    static BigInteger[] Slice(BigInteger[] arr, int start, int length)
    {
        BigInteger[] res = new BigInteger[length];
        Array.Copy(arr, start, res, 0, length);
        return res;
    }

    static BigInteger[] Pad(BigInteger[] arr, int size)
    {
        BigInteger[] res = new BigInteger[size];
        Array.Copy(arr, res, arr.Length);
        return res;
    }

    static int NextPow2(int x)
    {
        int p = 1;
        while (p < x) p <<= 1;
        return p;
    }

    static BigInteger[] Add(BigInteger[] a, BigInteger[] b)
    {
        BigInteger[] r = new BigInteger[a.Length];
        for (int i = 0; i < a.Length; i++)
            r[i] = a[i] + b[i];
        return r;
    }

    static BigInteger[] Sub(BigInteger[] a, BigInteger[] b)
    {
        BigInteger[] r = new BigInteger[a.Length];
        for (int i = 0; i < a.Length; i++)
            r[i] = a[i] - b[i];
        return r;
    }

    static void Combine(BigInteger[] result, BigInteger[] z0, BigInteger[] z1, BigInteger[] z2, int m)
    {
        for (int i = 0; i < 2 * m; i++)
        {
            result[i] += z0[i];
            result[i + m] += z1[i];
            result[i + 2 * m] += z2[i];
        }
    }

    // GENERATORS


    static BigInteger[] GenerateRandomSmallPolynomial(int n)
    {
        var rnd = new Random();
        BigInteger[] arr = new BigInteger[n];
        for (int i = 0; i < n; i++)
            arr[i] = rnd.Next(-50, 51);
        return arr;
    }

    static BigInteger[] GenerateRandomBigPolynomial(int n, int bitLength)
    {
        var rnd = new Random();
        BigInteger[] arr = new BigInteger[n];

        int byteLen = bitLength / 8;
        for (int i = 0; i < n; i++)
        {
            byte[] bytes = new byte[byteLen];
            rnd.NextBytes(bytes);
            arr[i] = new BigInteger(bytes, isUnsigned: true, isBigEndian: false);
        }

        return arr;
    }

    

    static TimeSpan Measure(Action action, int runs = 3)
    {
        long total = 0;
        Stopwatch sw = new Stopwatch();

        for (int i = 0; i < runs; i++)
        {
            sw.Restart();
            action();
            sw.Stop();
            total += sw.ElapsedTicks;
        }

        return new TimeSpan(total / runs);
    }
}

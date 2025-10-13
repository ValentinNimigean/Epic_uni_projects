using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace WarehouseSimulation
{
    public class Warehouse
    {
        public int[] Products;
        public readonly object Lock = new();

        public Warehouse(int productCount, int initialQuantity)
        {
            Products = Enumerable.Repeat(initialQuantity, productCount).ToArray();
        }
    }

    public enum LockMode
    {
        Global,
        Warehouse,
        Product
    }

    public class Program
    {
        static Warehouse[] warehouses = null!;
        static object globalLock = new();
        static object[]? productLocks;
        static int[] initialTotals = null!;
        static bool running = true;
        static LockMode mode;
        static readonly object logLock = new();
        static StreamWriter? logWriter;

        public static void Main()
        {
            // Create Logs folder in the same directory as Program.cs
            string projectDir = Directory.GetParent(AppContext.BaseDirectory)!.Parent!.Parent!.Parent!.FullName;
            string logDir = Path.Combine(projectDir, "Logs");
            Directory.CreateDirectory(logDir);

            string logFile = Path.Combine(logDir, $"log_{DateTime.Now:yyyy-MM-dd_HH-mm-ss}.txt");
            logWriter = new StreamWriter(logFile) { AutoFlush = true };

            Log($"=== Warehouse Simulation Started ({DateTime.Now}) ===");
            Log($"Log file: {logFile}\n");

            // Gather inputs
            Console.Write("Number of warehouses: ");
            int totalWarehouses = int.Parse(Console.ReadLine() ?? "10");

            Console.Write("Number of products: ");
            int totalProducts = int.Parse(Console.ReadLine() ?? "5");

            Console.Write("Initial quantity per product per warehouse: ");
            int initialQuantity = int.Parse(Console.ReadLine() ?? "1000");

            Console.Write("Total operations: ");
            int totalOperations = int.Parse(Console.ReadLine() ?? "1000000");

            Console.Write("Number of worker threads: ");
            int totalThreads = int.Parse(Console.ReadLine() ?? "8");

            Console.Write("Locking mode (global / warehouse / product): ");
            string lockModeInput = (Console.ReadLine() ?? "warehouse").ToLower();
            mode = lockModeInput switch
            {
                "global" => LockMode.Global,
                "product" => LockMode.Product,
                _ => LockMode.Warehouse
            };

            Log($"[CONFIG] Warehouses={totalWarehouses}, Products={totalProducts}, Threads={totalThreads}, Operations={totalOperations}, Mode={mode}");
            Console.WriteLine("\nConfiguration recorded. Starting simulation...\n");

            // Initialize warehouses
            warehouses = new Warehouse[totalWarehouses];
            for (int i = 0; i < totalWarehouses; i++)
                warehouses[i] = new Warehouse(totalProducts, initialQuantity);

            if (mode == LockMode.Product)
                productLocks = Enumerable.Range(0, totalProducts).Select(_ => new object()).ToArray();

            initialTotals = Enumerable.Repeat(totalWarehouses * initialQuantity, totalProducts).ToArray();

            var sw = Stopwatch.StartNew();

            // Background consistency checker
            var checker = Task.Run(() =>
            {
                while (running)
                {
                    CheckConsistency();
                    Thread.Sleep(500);
                }
            });

            // Launch worker threads
            int opsPerThread = totalOperations / totalThreads;
            var threads = new List<Task>();
            for (int t = 0; t < totalThreads; t++)
            {
                int id = t;
                threads.Add(Task.Run(() => Worker(id, opsPerThread, totalWarehouses, totalProducts)));
            }

            Task.WaitAll(threads.ToArray());
            running = false;
            checker.Wait();

            sw.Stop();

            CheckConsistency();
            Log($"\n✅ Simulation complete in {sw.Elapsed.TotalSeconds:F2} seconds.");
            Log($"=== End of Run ({DateTime.Now}) ===");

            Console.WriteLine($"\nRun complete. Log saved to {logFile}");
            logWriter?.Dispose();
        }

        static void Worker(int id, int operations, int totalWarehouses, int totalProducts)
        {
            var rand = new Random(id * Environment.TickCount);
            for (int i = 0; i < operations; i++)
            {
                int from = rand.Next(totalWarehouses);
                int to = rand.Next(totalWarehouses);
                if (from == to) continue;

                int product = rand.Next(totalProducts);
                int amount = rand.Next(1, 50);

                Move(from, to, product, amount);

                if (i % (operations / 10) == 0 && i > 0)
                    Log($"[Thread {id}] Progress: {100 * i / operations}%");
            }
            Log($"[Thread {id}] Finished all {operations} operations.");
        }

        static void Move(int from, int to, int product, int amount)
        {
            switch (mode)
            {
                case LockMode.Global:
                    lock (globalLock) DoMove(from, to, product, amount);
                    break;

                case LockMode.Warehouse:
                    var first = Math.Min(from, to);
                    var second = Math.Max(from, to);
                    lock (warehouses[first].Lock)
                    {
                        lock (warehouses[second].Lock)
                        {
                            DoMove(from, to, product, amount);
                        }
                    }
                    break;

                case LockMode.Product:
                    lock (productLocks![product])
                    {
                        DoMove(from, to, product, amount);
                    }
                    break;
            }
        }

        static void DoMove(int from, int to, int product, int amount)
        {
            if (warehouses[from].Products[product] >= amount)
            {
                warehouses[from].Products[product] -= amount;
                warehouses[to].Products[product] += amount;
            }
        }

        static void CheckConsistency()
        {
            if (mode == LockMode.Global)
                Monitor.Enter(globalLock);
            else
                foreach (var wh in warehouses)
                    Monitor.Enter(wh.Lock);

            try
            {
                for (int p = 0; p < initialTotals.Length; p++)
                {
                    int total = 0;
                    foreach (var wh in warehouses)
                        total += wh.Products[p];

                    if (total != initialTotals[p])
                        Log($"[ERROR] Product {p} total mismatch: {total} vs expected {initialTotals[p]}");
                }
                Log($"[CHECK] Consistency OK at {DateTime.Now:HH:mm:ss}");
            }
            finally
            {
                if (mode == LockMode.Global)
                    Monitor.Exit(globalLock);
                else
                    foreach (var wh in warehouses)
                        Monitor.Exit(wh.Lock);
            }
        }

        static void Log(string message)
        {
            string line = $"[{DateTime.Now:HH:mm:ss.fff}] {message}";
            lock (logLock)
            {
                Console.WriteLine(line);
                logWriter?.WriteLine(line);
            }
        }
    }
}
using System;
using System.IO;
using System.Threading.Tasks;

class Program
{
    static void Main(string[] args)
    {
        if (args.Length != 2)
        {
            Console.WriteLine("Usage:");
            Console.WriteLine("  callbacks urls.txt");
            Console.WriteLine("  tasks     urls.txt");
            Console.WriteLine("  await     urls.txt");
            return;
        }

        string mode = args[0];
        string urlsFile = args[1];

        if (!File.Exists(urlsFile))
        {
            Console.WriteLine($"File not found: {urlsFile}");
            return;
        }

        string[] urls = File.ReadAllLines(urlsFile);
        urls = Array.FindAll(urls, l => !string.IsNullOrWhiteSpace(l));
        if (urls.Length == 0)
        {
            Console.WriteLine("No URLs in file.");
            return;
        }

        Directory.CreateDirectory("downloads");

        switch (mode)
        {
            case "callbacks":
                ClientCallBack.Run(urls);   
                break;

            case "tasks":
                Task tasksAll = ClientTasks.Run(urls);
                tasksAll.Wait();             
                break;

            case "await":
                Task awaitAll = ClientAwait.Run(urls);
                awaitAll.Wait();             
                break;

            default:
                Console.WriteLine("Unknown mode. Use: callbacks | tasks | await");
                break;
        }
    }
}

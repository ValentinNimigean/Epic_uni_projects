# 🏭 Warehouse Concurrency Simulation

## 🧩 What This Program Does

This program simulates a **multi-threaded warehouse system** where several threads perform random transfers (moves) of product quantities between different warehouses. Each warehouse stores a set number of products, each with an initial stock quantity.

The program’s goal is to:

* Test **concurrent access** to shared data (warehouses and products).
* Ensure **data consistency** — no products are lost or created during concurrent moves.
* Explore **performance effects** of different synchronization (locking) granularities.

During execution:

* Several threads execute random move operations.
* Each move transfers random quantities of a randomly chosen product from one warehouse to another.
* A separate background thread periodically performs a **consistency check** to ensure that total stock for each product remains equal to the initial amount.
* At the end, results and timing are logged into a file for analysis.

---

## ⚙️ Parameters and What They Do

When you run the program, it asks for the following parameters:

| Parameter                                                                             | Description                                                                                                                            |
| ------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| **Number of warehouses**                                                              | How many separate warehouses exist in the simulation. Each has its own product inventory.                                              |
| **Number of products**                                                                | How many different product types are tracked across warehouses.                                                                        |
| **Initial quantity per product per warehouse**                                        | The starting stock of each product in each warehouse. This value determines the total initial inventory for each product.              |
| **Total operations**                                                                  | The total number of move operations that all threads together will execute. A higher number increases runtime and concurrency effects. |
| **Number of worker threads**                                                          | How many concurrent threads perform product transfers. Increasing this tests multithreaded performance and locking efficiency.         |
| **Locking mode (global / warehouse / product)**                                       | Determines synchronization granularity:                                                                                                |
| - `global` → one global lock for all operations (simplest, slowest).                  |                                                                                                                                        |
| - `warehouse` → one lock per warehouse (good concurrency for independent warehouses). |                                                                                                                                        |
| - `product` → one lock per product (best when moves target different products).       |                                                                                                                                        |

---

## 🪵 Output and Logs

* Progress updates and consistency checks are printed to the console.
* A detailed **log file** is generated for every run, named:

  ```
  log_YYYY-MM-DD_HH-MM-SS.txt
  ```

  It contains:

  * Configuration parameters
  * Thread progress messages
  * Consistency check results
  * Final summary and runtime

Example log snippet:

```
[15:42:09.004] === Warehouse Simulation Started ===
[CONFIG] Warehouses=10, Products=5, Threads=8, Operations=100000, Mode=Warehouse
[CHECK] Consistency OK at 15:42:10
✅ Simulation complete in 0.45 seconds.
```

---

## 🧠 In Short

The simulation shows how concurrent operations on shared data can remain safe and consistent when proper synchronization is applied — and lets you experiment with **different locking granularities** to observe **performance trade-offs**.
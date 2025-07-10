# Traveling Salesman Problem (TSP) – Brute Force in C

## 📖 Overview

The **Traveling Salesman Problem (TSP)** is a classic optimization problem in computer science and operations research. The goal is to determine the shortest possible route that:

- Starts at a given city,
- Visits each city **exactly once**,
- Returns to the starting city.

This repository provides a simple brute-force solution in C, which checks **all possible permutations** of cities to find the minimum cost tour.

---

## 🚀 How It Works

- The algorithm uses **recursive backtracking** to explore every possible path.
- It always starts from city `0`.
- At each step, it visits all unvisited cities recursively.
- Once all cities are visited, it returns to the starting city and updates the minimum cost if a better tour is found.

### ⏱️ Time Complexity

- **O(N!)** – explores all permutations of the cities.
- Practical only for small `N` (typically `N ≤ 10`).

---

## 🧪 Example

**Input (4 cities, distance matrix):**
```
0  10  15  20
10  0  35  25
15 35   0  30
20 25  30   0
```

**Expected Output:**
```
Minimum TSP cost (brute-force): 80
```

---

## 🛠️ Compilation & Usage

### Compile

```bash
gcc -o tsp tsp.c
```

### Run

Pass the number of cities `N` followed by the `N x N` distance matrix (row-major order):

```bash
./tsp 4 0 10 15 20 10 0 35 25 15 35 0 30 20 25 30 0
```

**Output:**
```
Minimum TSP cost (brute-force): 80
```

---

## 📁 Files

- `tsp.c` – Brute-force TSP implementation (main source file)
- `README.md` – This documentation

---

## 🚫 Limitations

- Not optimized (does **not** use dynamic programming or memoization)
- Not suitable for large `N` due to factorial time complexity

---

## 📚 References

- [Traveling Salesman Problem – Wikipedia](https://en.wikipedia.org/wiki/Travelling_salesman_problem)

---


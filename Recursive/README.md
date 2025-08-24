# RecursiveTraceVisualizer

An educational C++ project that **visualizes recursion step-by-step**.  
Instead of just showing the final answer, this program prints **indented traces** of recursive calls, making the call stack and return values fully transparent.

---

## 🎯 Purpose
- Help students and developers **understand recursion** by exposing the internal process.
- Show **recursive depth** with indentation (like a tree structure).
- Provide a reusable framework to visualize many different recursive algorithms.

---

## 🚀 Features (Implemented & Planned)

### ✅ Implemented
- **Fibonacci Sequence (recursive)**  
  - Shows how each `fib(n)` call expands into `fib(n-1)` and `fib(n-2)`  
  - Displays both *call* and *return* values with indentation  

### 🛠️ Planned Visualizations
1. **Factorial Function (`n!`)**  
   - Trace how recursive multiplication unwinds back to the result.  
   - Example:
     ```
     fact(4)
       fact(3)
         fact(2)
           fact(1)
           return 1
         return 2
       return 6
     return 24
     ```

2. **Tower of Hanoi**  
   - Trace each move step recursively:  
     ```
     move(3, A -> C)
       move(2, A -> B)
         move(1, A -> C)
         ...
     ```

3. **Binary Search (recursive)**  
   - Show how the array interval shrinks at each recursive step.  

4. **Merge Sort (recursive sorting)**  
   - Trace the divide-and-conquer process:  
     ```
     sort([3,1,4,2])
       sort([3,1])
         sort([3])
         sort([1])
         merge([3],[1]) -> [1,3]
       sort([4,2])
         sort([4])
         sort([2])
         merge([4],[2]) -> [2,4]
       merge([1,3],[2,4]) -> [1,2,3,4]
     ```

---

## 🏗️ Project Structure
RecursiveTraceVisualizer/
│
├── main.cpp # Program entry point
├── fibonacci.cpp # Fibonacci recursion + trace
├── fibonacci.h # Header for fibonacci
├── (future) factorial.cpp / factorial.h
├── (future) hanoi.cpp / hanoi.h
├── (future) sorting.cpp / sorting.h
├── .gitignore
└── README.md

yaml
Copy
Edit

---

## ⚙️ Build & Run
### Compile
```bash
g++ -std=c++17 main.cpp fibonacci.cpp -o RecursiveTraceVisualizer
Run
bash
Copy
Edit
./RecursiveTraceVisualizer
📖 Example Output (Fibonacci)
sql
Copy
Edit
Enter a number for Fibonacci: 4

Tracing recursive calls:
fib(4) called
  fib(3) called
    fib(2) called
      fib(1) called
      return 1
      fib(0) called
      return 0
    fib(2) returns 1
    fib(1) called
    return 1
  fib(3) returns 2
  fib(2) called
    fib(1) called
    return 1
    fib(0) called
    return 0
  fib(2) returns 1
fib(4) returns 3

Final Result: fib(4) = 3


🛣️ Roadmap
✅ Add fibonacci visualization

 Add factorial visualization

 Add Tower of Hanoi visualization

 Add binary search visualization

 Add merge sort visualization

 Optional: colorize output per recursion depth

 Optional: export traces to JSON/HTML for graphical visualization
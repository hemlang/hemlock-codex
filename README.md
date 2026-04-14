# Hemlock Translation Dataset (Codex)

Training dataset for fine-tuning LLMs to generate [Hemlock](https://github.com/hemlang/hemlock) code. 120 working, tested examples covering algorithms, systems programming, cross-language translation, and practical programs.

## Why

Benchmark results for `hemlang/Hemlock2-Coder-7B` (Q8_0, zero-shot):

| Level | Score |
|-------|-------|
| L1 Syntax & Basics | 44.4% |
| L2 Stdlib Usage | 60.0% |
| L3 Algorithms | 28.6% |
| L4 Systems Programming | 42.9% |
| L5 Translation | 0.0% |
| L6 Debugging | 60.0% |
| **Overall** | **38.9%** |

L3, L4, and especially L5 need more training data. This dataset targets those gaps.

## Planned Examples (120 total)

### Tier 1: Algorithms (44 examples) — targets L3

**Sorting (8)**
- [x] Bubble sort
- [x] Insertion sort
- [x] Selection sort
- [x] Merge sort (recursive)
- [x] Quicksort
- [x] Heap sort
- [x] Counting sort
- [x] Radix sort

**Search (4)**
- [x] Binary search (iterative)
- [x] Binary search (recursive)
- [x] Linear search with sentinel
- [x] Interpolation search

**Trees (7)**
- [x] BST insert/search/delete
- [x] BST in-order traversal
- [x] BST level-order traversal (BFS)
- [x] AVL tree with rotations
- [x] Trie insert/search/prefix
- [x] Expression tree evaluation
- [x] Lowest common ancestor

**Graphs (9)**
- [x] Dijkstra's shortest path
- [x] BFS shortest path (unweighted)
- [x] DFS traversal
- [x] Topological sort
- [x] Floyd-Warshall
- [x] Prim's MST
- [x] Kruskal's MST (union-find)
- [x] Cycle detection (directed)
- [x] A* pathfinding

**Dynamic Programming (8)**
- [ ] Longest common subsequence
- [ ] Longest increasing subsequence
- [ ] Knapsack (0/1)
- [ ] Edit distance (Levenshtein)
- [ ] Coin change
- [ ] Matrix chain multiplication
- [ ] Fibonacci (memoized)
- [ ] Rod cutting

**Classic Data Structures (8)**
- [ ] Two sum (hashmap)
- [ ] Linked list reversal
- [ ] Stack-based bracket matching
- [ ] Queue with two stacks
- [ ] Priority queue (min-heap)
- [ ] LRU cache
- [ ] Ring buffer
- [ ] String permutations

### Tier 2: Systems Patterns (22 examples) — targets L4

**Memory (8)**
- [ ] Manual linked list (alloc/free)
- [ ] Dynamic array (realloc pattern)
- [ ] Arena allocator
- [ ] Memory pool / slab allocator
- [ ] Double-ended queue with pointers
- [ ] Buffer builder (growing buffer)
- [ ] Struct-of-arrays with ptr arithmetic
- [ ] Reference counting

**Concurrency (10)**
- [ ] Producer-consumer (channels)
- [ ] Fan-out/fan-in worker pool
- [ ] Pipeline (multi-stage channels)
- [ ] Barrier synchronization
- [ ] Lock-free atomic counter
- [ ] Parallel merge sort
- [ ] Dining philosophers
- [ ] Thread-safe queue
- [ ] Map-reduce pattern
- [ ] Async file processing

**Defer Patterns (4)**
- [ ] File open/defer close
- [ ] alloc/defer free
- [ ] Nested resource cleanup
- [ ] Error cleanup with defer

### Tier 3: Cross-Language Translation (42 examples) — targets L5

**From Python (10)**
- [ ] Word frequency counter
- [ ] List comprehension → map/filter
- [ ] Context manager → defer
- [ ] Generator → closure/iterator
- [ ] Class → define + functions
- [ ] Decorator → higher-order fn
- [ ] CSV processing
- [ ] JSON parsing and transformation
- [ ] Regex find-all
- [ ] argparse → @stdlib/args

**From JavaScript (10)**
- [ ] Promise.all → spawn + join
- [ ] async/await → spawn/await
- [ ] Array.map/filter/reduce chain
- [ ] EventEmitter → channels
- [ ] Fetch API → http_get/http_post
- [ ] setTimeout → spawn + sleep
- [ ] Object spread/destructuring
- [ ] Template literals → template strings
- [ ] try/catch/finally
- [ ] Map/Set → HashMap/Set

**From C (10)**
- [ ] malloc/free → alloc/free
- [ ] struct + functions → define + fn
- [ ] Linked list with pointers
- [ ] File I/O (fopen/fread/fwrite)
- [ ] String manipulation
- [ ] Bit manipulation
- [ ] Signal handling
- [ ] Fork/exec → spawn
- [ ] pthread → spawn/join
- [ ] Socket server (basic TCP)

**From Go (6)**
- [ ] Goroutine fan-out → spawn + channels
- [ ] sync.WaitGroup → join
- [ ] select → channel recv patterns
- [ ] defer → defer
- [ ] error handling → try/catch
- [ ] Mutex → atomic ops

**From Rust (6)**
- [ ] Vec operations → array methods
- [ ] Option/Result → null + try/catch
- [ ] Ownership/borrowing → manual alloc/free
- [ ] Arc/Mutex → atomic + spawn
- [ ] Iterator chains → map/filter/reduce
- [ ] Pattern matching → match

### Tier 4: Practical Programs (12 examples)

- [ ] HTTP server (hello world)
- [ ] CLI tool with arg parsing
- [ ] File watcher
- [ ] Simple chat (TCP + channels)
- [ ] JSON config loader
- [ ] Log file parser
- [ ] Markdown to HTML (basic)
- [ ] Base64 encoder/decoder from scratch
- [ ] Simple REPL
- [ ] Unit test runner
- [ ] SQLite CRUD app
- [ ] URL shortener (in-memory)

## Usage

Requires Hemlock 2.0.0+ on PATH.

```bash
# Test all examples
find hemlock -name '*.hml' | while read f; do
  echo -n "$f: "
  timeout 10 hemlock "$f" > /dev/null 2>&1 && echo "PASS" || echo "FAIL"
done
```

## License

Same as Hemlock.

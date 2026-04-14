# Hemlock Translation Dataset

## What This Is

A training dataset of Hemlock code examples for fine-tuning LLMs to generate Hemlock code. Each example is a working, tested `.hml` file that runs on Hemlock 2.0.0.

The goal is to improve code generation quality for `hemlang/Hemlock2-Coder-7B` (and future models). Benchmark results showed the model is weakest at:
- **L3 Algorithms** (14-28%) — data structures, graph algorithms, DP
- **L4 Systems** (42-57%) — memory management, concurrency patterns
- **L5 Translation** (0-20%) — converting C/JS/Python/Go/Rust to Hemlock

## How to Build the Dataset

### Phase 1: Hemlock implementations (current)
Write working Hemlock versions of all 120 examples. Test each with `hemlock` (must be on PATH, version 2.0.0+). Every file must run cleanly with `timeout 10 hemlock <file>`.

### Phase 2: Source language versions
For each Hemlock file, write equivalent implementations in the source languages (Python, JavaScript, C, Go, Rust). These become translation pairs.

### Phase 3: SFT dataset generation
Convert the pairs into instruction-tuning format (JSONL) with prompts like:
- "Translate this Python code to Hemlock: ..."
- "Write a Hemlock implementation of Dijkstra's algorithm"
- "Convert this C linked list to idiomatic Hemlock"

## Directory Structure

```
hemlock/                    # Hemlock implementations (Phase 1)
  algorithms/
    sorting/                # 8 sorting algorithms
    search/                 # 4 search algorithms
    trees/                  # 7 tree data structures
    graphs/                 # 9 graph algorithms
    dp/                     # 8 dynamic programming
    classic/                # 8 classic data structures/problems
  systems/
    memory/                 # 8 memory management patterns
    concurrency/            # 10 async/concurrency patterns
    defer/                  # 4 defer/cleanup patterns
  translation/
    python/                 # 10 Python → Hemlock
    javascript/             # 10 JavaScript → Hemlock
    c/                      # 10 C → Hemlock
    go/                     # 6 Go → Hemlock
    rust/                   # 6 Rust → Hemlock
  practical/                # 12 practical programs
source/                     # Source language versions (Phase 2)
  python/
  javascript/
  c/
  go/
  rust/
```

## Hemlock Quick Reference (for writing examples)

- Semicolons mandatory, `{}` blocks required
- `print()` takes only 1 argument — use template strings `` `text ${expr}` ``
- `write()` outputs without newline
- `/` always returns float — use `import { divi } from "@stdlib/math";` for integer division
- Manual memory: `alloc(n)`, `free(p)`, `buffer(n)` (bounds-checked)
- Pointer ops: `ptr_write_i32(p, val)`, `ptr_deref_i32(p)`, `ptr_offset(p, idx, stride)`
- Objects as structs: `let node = { value: 10, left: null, right: null };`
- No classes — use objects + standalone functions
- `import { HashMap, Queue, Set } from "@stdlib/collections";`
- Async: `spawn(fn, args)`, `await task` / `join(task)`, `channel(cap)`
- Atomics: `atomic_load_i32(p)`, `atomic_store_i32(p, v)`, `atomic_add_i32(p, n)`, `atomic_cas_i32(p, expected, desired)`
- `defer` for cleanup (runs when function returns)
- `typeof(x)` returns string, `typeid(x)` returns integer
- See the main hemlock repo's CLAUDE.md for full language spec

## Testing

```bash
# Test a single file
timeout 10 hemlock hemlock/algorithms/sorting/bubble_sort.hml

# Test all files in a directory
for f in hemlock/algorithms/sorting/*.hml; do
  echo -n "$(basename $f): "
  timeout 10 hemlock "$f" > /dev/null 2>&1 && echo "PASS" || echo "FAIL"
done

# Test everything
find hemlock -name '*.hml' | while read f; do
  echo -n "$f: "
  timeout 10 hemlock "$f" > /dev/null 2>&1 && echo "PASS" || echo "FAIL"
done
```

## Important Notes

- Every `.hml` file MUST run successfully with `timeout 10 hemlock <file>`
- Examples should be idiomatic Hemlock, not just "C with different syntax"
- Use stdlib imports where appropriate (HashMap, math, json, etc.)
- Include comments explaining the algorithm, not just code
- Each file should be self-contained (no external dependencies beyond stdlib)

# Hembot-DPO

Direct Preference Optimization (DPO) training dataset for fine-tuning Hemlock-Apothecary to work optimally as the hembot coding agent.

## Dataset Format

CSV file with three columns:
- **prompt**: The user instruction/request
- **chosen**: The preferred response (concise, code-fenced, Hemlock-focused)
- **rejected**: An undesirable alternative (verbose, includes unnecessary cross-language comparisons)

## What This Trains

The DPO pairs teach the model to prefer:
1. ✅ Code fences around all Hemlock code blocks
2. ✅ Concise responses without excessive explanation
3. ✅ Focusing on Hemlock idioms without unnecessary C/Python comparisons
4. ❌ Verbose preambles and postambles
5. ❌ Cross-language comparisons unless explicitly requested
6. ❌ Over-explanation of straightforward code

## Example

**Prompt:**
```
Implement Bracket Matching (classic algorithm)
```

**Chosen (preferred):**
```
Here's an implementation of Bracket Matching:

```hemlock
fn is_balanced(s) {
    let stack = [];
    // ... concise code with fences
}
```
```

**Rejected (undesirable):**
```
Let me help you with that. Here's what we need to do:

```hemlock
fn is_balanced(s) {
    // ... same code
}
```

This works similarly to how you might do it in C, where you'd use a stack data structure...
```

## Statistics

- **Total examples:** 127
- **Source:** Converted from hemlock-codex SFT dataset
- **File:** `dataset_dpo.csv` (357KB)

## Usage

Load the dataset for DPO fine-tuning:

```python
import pandas as pd

df = pd.read_csv("dataset_dpo.csv")
# Columns: prompt, chosen, rejected
```

Or with datasets library:

```python
from datasets import load_dataset

dataset = load_dataset("csv", data_files={"train": "dataset_dpo.csv"})
```

## Related

- **SFT version:** See `dataset.jsonl` for the instruction-tuning format
- **hembot:** The Hemlock coding agent this trains: https://github.com/hemlang/hembot
- **Hemlock-Apothecary-7B:** Base model to fine-tune: https://huggingface.co/nbeerbower/Hemlock-Apothecary-7B

## License

MIT

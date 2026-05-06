# Hembot-DPO

DPO (Direct Preference Optimization) training dataset for fine-tuning Hemlock-Apothecary to work optimally as the hembot coding agent.

[![Dataset License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Format](https://img.shields.io/badge/Format-JSONL-green.svg)]()
[![Size](https://img.shields.io/badge/Size-127%20examples-purple.svg)]()

## Quick Start

```python
from datasets import load_dataset

# Load the dataset
dataset = load_dataset("hemlang/Hembot-DPO")

# Each example has:
# - prompt: user instruction
# - chosen: preferred response (concise, code-fenced)
# - rejected: undesirable response (verbose, cross-language comparisons)
for example in dataset["train"]:
    print(example["prompt"])
    print(example["chosen"])
    print(example["rejected"])
```

## What This Trains

The DPO pairs teach the model to prefer **concise, focused responses** over verbose ones:

| ✅ Prefer | ❌ Avoid |
|-----------|----------|
| Code fences around all Hemlock code | Bare code without fences |
| Concise responses | Excessive explanation |
| Hemlock-focused output | Unnecessary C/Python comparisons |
| Direct answers | Verbose preambles/postambles |

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
    let chars = s.chars();
    for (let i = 0; i < chars.length; i++) {
        let c = chars[i];
        if (c == '(' || c == '{' || c == '[') {
            stack.push(c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (stack.length == 0) {
                return false;
            }
            let top = stack.pop();
            if (c == ')' && top != '(') { return false; }
            if (c == '}' && top != '{') { return false; }
            if (c == ']' && top != '[') { return false; }
        }
    }
    return stack.length == 0;
}
```
```

**Rejected (undesirable):**
```
Let me help you with that. Here's what we need to do:

```hemlock
// ... same code ...
```

This works similarly to how you might do it in C, where you'd use a stack data structure and iterate through the string checking for matching brackets. The main difference is that Hemlock has built-in array methods like push() and pop() that make this cleaner than manual stack management in C.
```

## Dataset Statistics

- **Total examples:** 127
- **Format:** JSONL (prompt, chosen, rejected fields)
- **File size:** 376 KB
- **Source:** Converted from hemlock-codex SFT dataset

## Files

- `dataset_dpo.jsonl` - Main dataset file (JSONL format)

## Usage for DPO Fine-Tuning

### With Axolotl

```yaml
# config.yaml
dataset_msha: dataset_dpo.jsonl
dataset_train_split: train
dataset_text_field: prompt
dataset_input_field: prompt
dataset_output_field: chosen
```

### With TRL

```python
from trl import DPOTrainer

# Load and format dataset
dataset = load_dataset("hemlang/Hembot-DPO")

trainer = DPOTrainer(
    model=model,
    ref_model=ref_model,
    train_dataset=dataset["train"],
    args=training_args,
    formatting_func=lambda x: {
        "prompt": x["prompt"],
        "chosen": x["chosen"],
        "rejected": x["rejected"]
    }
)
```

## Related Resources

- **hembot**: The Hemlock coding agent — https://github.com/hemlang/hembot
- **Hemlock-Apothecary-7B**: Base model to fine-tune — https://huggingface.co/nbeerbower/Hemlock-Apothecary-7B
- **SFT Dataset**: Instruction-tuning version — https://github.com/hemlang/hemlock-codex/tree/main/hembot-training
- **Hemlock Language**: Documentation — https://github.com/hemlang/hemlock

## License

MIT License — see LICENSE file for details.

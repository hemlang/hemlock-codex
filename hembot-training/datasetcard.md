---
language:
- en
dataset_type: text
license: mit
tags:
- hemlock
- programming
- code-generation
- dpo
- fine-tuning
---

# Hembot-DPO

DPO (Direct Preference Optimization) training dataset for fine-tuning Hemlock-Apothecary to work optimally as the hembot coding agent.

## Dataset Description

This dataset contains 127 DPO training examples with prompt/chosen/rejected triplets designed to teach the model to produce concise, code-fenced Hemlock code without unnecessary verbosity or cross-language comparisons.

### Format

Each example contains:
- `prompt`: User instruction or request
- `chosen`: Preferred response (concise, code-fenced, Hemlock-focused)
- `rejected`: Undesirable alternative (verbose, includes unnecessary C/Python comparisons)

## How to Use

```python
from datasets import load_dataset

# Load the dataset
dataset = load_dataset("hemlang/Hembot-DPO", split="train")

# Access examples
for example in dataset:
    print(example["prompt"])
    print(example["chosen"])
    print(example["rejected"])
```

## Dataset Statistics

- **Total examples:** 127
- **File format:** JSONL
- **File size:** ~220 KB

## Related Resources

- **hembot**: The Hemlock coding agent — https://github.com/hemlang/hembot
- **Hemlock-Apothecary-7B**: Base model — https://huggingface.co/nbeerbower/Hemlock-Apothecary-7B
- **SFT Dataset**: Instruction-tuning version — https://github.com/hemlang/hemlock-codex/tree/main/hembot-training

## License

MIT License

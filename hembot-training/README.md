# Hembot-Specific Training Dataset

Dataset for fine-tuning Hemlock-Apothecary to work optimally with the hembot agent.

## Overview

This dataset teaches the model:
1. **Always use code fences** - Every response wrapped in ```hemlock blocks
2. **Concise output** - No verbose explanations or C equivalents
3. **Error recovery** - How to fix code based on sandbox error messages
4. **Hemlock idioms** - Use the language correctly and idiomatically

## Current Status

- **127 examples** generated from hemlock-codex
- **122 instruction-response pairs** from algorithms, systems, translation, practical examples
- **5 additional simple examples** for basic tasks
- **Error recovery variants** for select examples

## Usage

Generate the dataset:
```bash
python3 generate_dataset.py
```

The output `dataset.jsonl` is in standard SFT format ready for fine-tuning.

## Dataset Format

Each example follows the standard instruction-following format:

```json
{
  "instruction": "User prompt or task description",
  "input": "",
  "output": "Model response with ```hemlock fenced code"
}
```

## Next Steps

1. **Expand error recovery examples** - Add 100+ more error→fix pairs
2. **Add conversational variants** - Follow-up questions and multi-turn examples
3. **Include more simple tasks** - Common programming patterns
4. **Validate all examples** - Ensure code runs successfully
5. **Fine-tune model** - Train Hemlock-Apothecary-7B-Hembot variant

## Files

- `generate_dataset.py` - Script to generate dataset from hemlock-codex
- `dataset.jsonl` - Generated SFT dataset
- `HEMBOT_TRAINING_PLAN.md` - Detailed plan and strategy
- `instructions/` - Organized instruction examples (future)
- `error-recovery/` - Error→fix pairs (future)

## License

Same as Hemlock.

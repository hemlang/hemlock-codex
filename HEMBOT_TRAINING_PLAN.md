# Hembot-Specific Training Data

## Overview

This dataset teaches Hemlock-Apothecary to work optimally with the hembot agent. While the main hemlock-codex dataset teaches Hemlock code generation, this dataset teaches the **interaction patterns** hembot needs:

1. **Always use code fences** - Every code response wrapped in ```hemlock blocks
2. **Concise output** - No verbose explanations or C equivalents unless requested
3. **Error recovery** - How to fix code based on sandbox error messages
4. **Hemlock idioms** - Use the language correctly and idiomatically

## Dataset Structure

```
hembot-training/
├── instructions/           # User prompts → ideal responses
│   ├── simple/            # Basic tasks (print, math, strings)
│   ├── algorithms/        # Sorting, search, trees, graphs
│   ├── systems/           # Memory, concurrency, defer patterns
│   └── translation/       # Convert from other languages
├── error-recovery/         # Error message → fixed code pairs
│   ├── syntax-errors/     # Missing semicolons, wrong syntax
│   ├── runtime-errors/    # Null deref, bounds errors
│   └── logic-errors/      # Wrong output, algorithm bugs
├── dataset.jsonl           # Final SFT dataset in standard format
└── generate.py             # Script to build dataset from examples
```

## Instruction Format

Each training example follows this pattern:

```json
{
  "instruction": "Write a function that reverses a string",
  "input": "",
  "output": "```hemlock\nfn reverse(s: string): string {\n    let chars = s.chars();\n    let i = 0;\n    let j = chars.length - 1;\n    while (i < j) {\n        let tmp = chars[i];\n        chars[i] = chars[j];\n        chars[j] = tmp;\n        i = i + 1;\n        j = j - 1;\n    }\n    return chars.join(\"\");\n}\n\nprint(reverse(\"hello\"));  // \"olleh\"\n```"
}
```

**Key requirements:**
- Output ALWAYS contains ```hemlock fenced code block
- Brief explanation before/after is OK, but code is the focus
- No C equivalents or other language comparisons
- Code must be runnable and correct

## Error Recovery Format

Teaches the model to fix code based on error feedback:

```json
{
  "instruction": "Fix this code that failed with: [line 2] Division by zero",
  "input": "fn divide(a, b) { return a / b; }\nlet result = divide(10, 0);",
  "output": "```hemlock\nfn divide(a, b) {\n    if (b == 0) {\n        print(\"Error: Division by zero\");\n        return null;\n    }\n    return a / b;\n}\n\nlet result = divide(10, 0);\nif (result == null) {\n    print(\"Operation not performed\");\n}\n```"
}
```

## Training Objectives

### Priority 1: Code Fencing (500+ examples)
- Teach model to ALWAYS wrap code in ```hemlock blocks
- Cover all task types: simple, algorithms, systems, translation
- Include varied prompts to generalize the behavior

### Priority 2: Concise Output (300+ examples)
- Show brief, focused responses
- Demonstrate when explanations are helpful vs. verbose
- Teach to avoid C equivalents and cross-language comparisons

### Priority 3: Error Recovery (200+ examples)
- Syntax errors → quick fixes
- Runtime errors → defensive programming
- Logic errors → algorithm corrections
- Show the feedback loop: error → understanding → fix

### Priority 4: Hemlock Idioms (200+ examples)
- Use stdlib modules (collections, math, json, etc.)
- Proper memory management (alloc/free, buffer)
- Correct pointer operations (ptr_deref_*, ptr_offset)
- Template strings for output
- Defer for cleanup

## Building the Dataset

### Phase 1: Extract from hemlock-codex (Week 1)
1. Convert all 120 hemlock-codex examples to instruction-response format
2. Add concise explanations where helpful
3. Ensure all code is wrapped in ```hemlock fences
4. Validate all examples run correctly

### Phase 2: Add Error Recovery (Week 1-2)
1. For each example, create 1-2 common error variants
2. Show the error message and corrected code
3. Cover syntax, runtime, and logic errors
4. Include hembot's build_retry_feedback format

### Phase 3: Augment with Variations (Week 2)
1. Create variations of each example (different parameters, edge cases)
2. Add conversational variants (follow-up questions)
3. Include multi-step tasks
4. Test diversity of prompts

### Phase 4: Validation (Week 2)
1. Run all examples through hembot to verify quality
2. Check that generated code passes sandbox
3. Ensure instruction diversity
4. Validate JSONL format for fine-tuning

## Dataset Size Targets

| Category | Examples | Priority |
|----------|----------|----------|
| Simple tasks | 100 | High |
| Algorithms | 200 | High |
| Systems patterns | 150 | High |
| Translation | 150 | Medium |
| Error recovery | 250 | High |
| Variations | 150 | Medium |
| **Total** | **1000** | |

## Fine-Tuning Strategy

### Model: Hemlock-Apothecary-7B
- Base: Qwen2.5-7B-Instruct
- Current tuning: General Hemlock code generation

### New Tuning: Hemlock-Apothecary-7B-Hembot
- Additional SFT on hembot-training dataset
- Focus: interaction patterns, code fencing, error recovery
- Target: Better hembot performance while maintaining general capabilities

### Training Parameters
- epochs: 2-3
- learning_rate: 2e-5
- batch_size: 4-8
- gradient_accumulation: 4
- max_length: 2048 (for instruction + response)

## Evaluation

### Automated Metrics
1. **Code fence rate**: % of responses with ```hemlock blocks
2. **Sandbox pass rate**: % of generated code that runs successfully
3. **Conciseness**: Average response length
4. **Error recovery success**: % of fixes that resolve the error

### Manual Evaluation
1. Run hembot with 50 diverse prompts
2. Measure: code quality, conciseness, error handling
3. Compare before/after fine-tuning

## Implementation Plan

### Week 1
- [ ] Set up dataset structure
- [ ] Convert 50 hemlock-codex examples to instruction format
- [ ] Create 25 error recovery examples
- [ ] Write generate.py script

### Week 2
- [ ] Complete all 120 hemlock-codex conversions
- [ ] Create 100+ error recovery examples
- [ ] Add variations (150+ examples)
- [ ] Validate all examples

### Week 3
- [ ] Generate final dataset.jsonl
- [ ] Run fine-tuning on Hemlock-Apothecary-7B
- [ ] Evaluate with automated metrics
- [ ] Manual evaluation with hembot

### Week 4
- [ ] Iterate on dataset based on evaluation
- [ ] Retrain with improved dataset
- [ ] Final evaluation and documentation
- [ ] Release Hemlock-Apothecary-7B-Hembot

## Success Criteria

- **Code fence rate**: >95% (currently ~80%)
- **Sandbox pass rate**: >90% on first attempt
- **Conciseness**: 50% reduction in average response length
- **Error recovery**: >80% success on first retry

## Notes

- Maintain compatibility with existing hemlock-codex dataset
- Can be used independently or combined with general tuning
- Focus on quality over quantity - 1000 high-quality examples > 10000 mediocre ones
- Dataset should be extensible - easy to add new examples

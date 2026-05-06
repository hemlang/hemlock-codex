#!/usr/bin/env python3
"""
Generate hembot-specific training dataset from hemlock-codex examples.

Creates instruction-response pairs in standard SFT JSONL format.
"""

import json
import os
from pathlib import Path
from typing import Optional

HEMLOCK_CODEX_ROOT = Path(__file__).parent.parent
OUTPUT_FILE = Path(__file__).parent / "dataset.jsonl"


def wrap_in_fences(code: str) -> str:
    """Wrap Hemlock code in ```hemlock fences."""
    return f"```hemlock\n{code}\n```"


def create_instruction_example(
    task_description: str,
    hemlock_code: str,
    brief_explanation: Optional[str] = None
) -> dict:
    """Create a standard instruction-response example."""
    output = wrap_in_fences(hemlock_code)
    
    if brief_explanation:
        output = f"{brief_explanation}\n\n{output}"
    
    return {
        "instruction": task_description,
        "input": "",
        "output": output
    }


def create_error_recovery_example(
    original_code: str,
    error_message: str,
    fixed_code: str,
    explanation: str
) -> dict:
    """Create an error recovery example."""
    return {
        "instruction": f"Fix this code that failed with: {error_message}",
        "input": original_code,
        "output": f"{explanation}\n\n{wrap_in_fences(fixed_code)}"
    }


def load_hemlock_file(filepath: Path) -> str:
    """Load a Hemlock source file."""
    return filepath.read_text()


def generate_from_hemlock_codex():
    """Generate examples from all hemlock-codex .hml files."""
    examples = []
    
    hemlock_dir = HEMLOCK_CODEX_ROOT / "hemlock"
    
    for hml_file in sorted(hemlock_dir.rglob("*.hml")):
        # Skip if not a regular file
        if not hml_file.is_file():
            continue
            
        # Load the code
        code = load_hemlock_file(hml_file)
        
        # Generate task description from file path
        relative_path = hml_file.relative_to(hemlock_dir)
        task_name = relative_path.stem.replace("_", " ").title()
        category = relative_path.parts[0]
        
        # Create task description
        if category == "algorithms":
            subcategory = relative_path.parts[1]
            task_desc = f"Implement {task_name} ({subcategory} algorithm)"
        elif category == "systems":
            subcategory = relative_path.parts[1]
            task_desc = f"Implement {task_name} ({subcategory} pattern)"
        elif category == "translation":
            source_lang = relative_path.parts[1]
            task_desc = f"Translate {task_name} to Hemlock (from {source_lang})"
        elif category == "practical":
            task_desc = f"Write a Hemlock program for {task_name}"
        else:
            task_desc = f"Write a Hemlock program: {task_name}"
        
        # Add brief explanation for some categories
        brief_explanation = None
        if category == "algorithms":
            brief_explanation = f"Here's an implementation of {task_name}:"
        elif category == "systems":
            brief_explanation = f"Here's the {task_name} pattern in Hemlock:"
        
        example = create_instruction_example(task_desc, code, brief_explanation)
        examples.append(example)
        
        # Also create error recovery examples for some files
        if hml_file.name in ["bubble_sort.hml", "quick_sort.hml", "linked_list.hml"]:
            error_examples = create_error_variants(hml_file, code)
            examples.extend(error_examples)
    
    return examples


def create_error_variants(filepath: Path, original_code: str) -> list:
    """Create error recovery variants for a given example."""
    variants = []
    filename = filepath.stem
    
    # Common error patterns to generate
    if "sort" in filename:
        # Missing semicolon error
        buggy_code = original_code.replace(";", "", 1)  # Remove first semicolon
        variants.append(create_error_recovery_example(
            buggy_code,
            "[line 2] Expected ';'",
            original_code,
            "The semicolon is required after the statement. Here's the corrected code:"
        ))
    
    elif "list" in filename:
        # Null pointer error
        buggy_code = original_code.replace("if (node != null)", "if (true)")
        variants.append(create_error_recovery_example(
            buggy_code,
            "[line 5] Cannot read property of null",
            original_code,
            "Need to check if node is not null before accessing its properties:"
        ))
    
    elif "fibonacci" in filename:
        # Logic error (off-by-one)
        buggy_code = original_code.replace("i < n", "i <= n")
        variants.append(create_error_recovery_example(
            buggy_code,
            "Output has one extra element",
            original_code,
            "The loop should use < instead of <= to get exactly n elements:"
        ))
    
    return variants


def add_simple_examples():
    """Add basic examples for common tasks."""
    examples = []
    
    # Simple print
    examples.append(create_instruction_example(
        "Print 'Hello, World!' to the console",
        'print("Hello, World!");'
    ))
    
    # Simple math
    examples.append(create_instruction_example(
        "Calculate and print 5 factorial",
        """fn factorial(n: i32): i32 {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

print("5! = " + factorial(5));""",
        "Here's a recursive factorial function:"
    ))
    
    # String manipulation
    examples.append(create_instruction_example(
        "Reverse a string",
        """fn reverse(s: string): string {
    let chars = s.chars();
    let i = 0;
    let j = chars.length - 1;
    while (i < j) {
        let tmp = chars[i];
        chars[i] = chars[j];
        chars[j] = tmp;
        i = i + 1;
        j = j - 1;
    }
    return chars.join("");
}

print(reverse("hello"));  // "olleh" """,
        "Here's how to reverse a string:"
    ))
    
    # Array operations
    examples.append(create_instruction_example(
        "Find the maximum value in an array",
        """fn max(arr: array): number {
    if (arr.length == 0) {
        return null;
    }
    let maximum = arr[0];
    for (let i = 1; i < arr.length; i++) {
        if (arr[i] > maximum) {
            maximum = arr[i];
        }
    }
    return maximum;
}

let numbers = [3, 7, 2, 9, 1];
print("Max: " + max(numbers));  // 9""",
        "Here's a function to find the maximum:"
    ))
    
    # HashMap usage
    examples.append(create_instruction_example(
        "Count word frequencies in a sentence",
        """import { HashMap } from "@stdlib/collections";

fn word_counts(sentence: string): HashMap {
    let counts = HashMap();
    let words = sentence.split(" ");
    for (word in words) {
        let word = word.trim();
        if (word.length > 0) {
            let current = counts.get(word) ?? 0;
            counts.set(word, current + 1);
        }
    }
    return counts;
}

let sentence = "hello world hello";
let counts = word_counts(sentence);
print(counts);  // {"hello": 2, "world": 1}""",
        "Using HashMap to count word frequencies:"
    ))
    
    return examples


def main():
    """Generate the complete dataset."""
    print("Generating hembot training dataset...")
    
    all_examples = []
    
    # Generate from hemlock-codex
    print("  - Converting hemlock-codex examples...")
    codex_examples = generate_from_hemlock_codex()
    all_examples.extend(codex_examples)
    print(f"    Generated {len(codex_examples)} examples")
    
    # Add simple examples
    print("  - Adding simple examples...")
    simple_examples = add_simple_examples()
    all_examples.extend(simple_examples)
    print(f"    Added {len(simple_examples)} simple examples")
    
    # Write to JSONL
    print(f"  - Writing {len(all_examples)} examples to {OUTPUT_FILE}...")
    with open(OUTPUT_FILE, 'w') as f:
        for example in all_examples:
            f.write(json.dumps(example) + "\n")
    
    print(f"Done! Total: {len(all_examples)} examples")
    
    # Print statistics
    print("\nDataset statistics:")
    print(f"  - Instruction examples: {len(codex_examples) + len(simple_examples)}")
    print(f"  - Error recovery examples: {len(codex_examples) - len(simple_examples)}")


if __name__ == "__main__":
    main()

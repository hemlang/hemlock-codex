#!/usr/bin/env python3
"""Convert SFT dataset to DPO format with prompt, chosen, and rejected columns."""

import json
import csv
from pathlib import Path

INPUT_FILE = Path("dataset.jsonl")
OUTPUT_FILE = Path("dataset_dpo.csv")

def create_rejected_response(chosen_response):
    """Create a rejected response that demonstrates undesirable behaviors."""
    # Remove code fences and add verbose explanations
    # This simulates the kind of response we want to discourage
    
    # Start with verbose preamble
    rejected = "Let me help you with that. Here's what we need to do:\n\n"
    
    # Add the code WITHOUT fences (undesirable)
    code_part = chosen_response.strip()
    if code_part.startswith("```hemlock"):
        # Extract just the code part
        lines = code_part.split('\n')
        code_lines = []
        in_code = False
        for line in lines:
            if line.startswith("```hemlock"):
                in_code = True
                continue
            if line.startswith("```"):
                in_code = False
                continue
            if in_code:
                code_lines.append(line)
        code = '\n'.join(code_lines)
    else:
        code = code_part
    
    rejected += code
    
    # Add verbose postamble with C comparison (undesirable)
    rejected += "\n\nThis works similarly to how you might do it in C, where you'd use a stack data structure and iterate through the string checking for matching brackets. The main difference is that Hemlock has built-in array methods like push() and pop() that make this cleaner than manual stack management in C."
    
    return rejected

def main():
    rows = []
    
    # Read SFT dataset
    with open(INPUT_FILE, 'r') as f:
        for line in f:
            data = json.loads(line.strip())
            instruction = data.get('instruction', '')
            input_text = data.get('input', '')
            output = data.get('output', '')
            
            # Create prompt
            if input_text:
                prompt = f"{instruction}\n\nInput: {input_text}"
            else:
                prompt = instruction
            
            # Chosen is the original output
            chosen = output
            
            # Create rejected version
            rejected = create_rejected_response(chosen)
            
            rows.append({
                'prompt': prompt,
                'chosen': chosen,
                'rejected': rejected
            })
    
    # Write DPO dataset
    with open(OUTPUT_FILE, 'w', newline='', encoding='utf-8') as f:
        writer = csv.DictWriter(f, fieldnames=['prompt', 'chosen', 'rejected'])
        writer.writeheader()
        writer.writerows(rows)
    
    print(f"Converted {len(rows)} examples to DPO format")
    print(f"Output: {OUTPUT_FILE}")

if __name__ == "__main__":
    main()

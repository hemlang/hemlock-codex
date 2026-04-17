#!/usr/bin/env python3
"""Generate SFT training dataset in JSONL format from Hemlock translation pairs."""

import json
import os
import random
import re
import sys
from pathlib import Path

SEED = 42
random.seed(SEED)

REPO_ROOT = Path(__file__).parent
HEMLOCK_DIR = REPO_ROOT / "hemlock"
SOURCE_DIR = REPO_ROOT / "source"
OUTPUT_FILE = REPO_ROOT / "hemlock_codex_sft.jsonl"

LANGUAGES = {
    "python": {"ext": ".py", "lang_name": "Python", "fence": "python"},
    "javascript": {"ext": ".js", "lang_name": "JavaScript", "fence": "javascript"},
    "c": {"ext": ".c", "lang_name": "C", "fence": "c"},
    "go": {"ext": ".go", "lang_name": "Go", "fence": "go"},
    "rust": {"ext": ".rs", "lang_name": "Rust", "fence": "rust"},
}

TRANSLATION_TEMPLATES = [
    "Translate this {lang} {desc} to Hemlock:\n\n```{fence}\n{code}\n```",
    "Convert the following {lang} code to Hemlock:\n\n```{fence}\n{code}\n```",
    "Rewrite this {lang} program in Hemlock:\n\n```{fence}\n{code}\n```",
    "Port this {lang} implementation to Hemlock:\n\n```{fence}\n{code}\n```",
    "Here is a {lang} program. Write the equivalent in Hemlock:\n\n```{fence}\n{code}\n```",
]

# Acronyms that should stay uppercase in descriptions
ACRONYMS = {
    "bst", "bfs", "dfs", "lcs", "lis", "lru", "avl", "json", "csv", "http",
    "tcp", "cli", "repl", "url", "crud", "ffi", "mst", "io", "dp", "arc",
    "vec", "sql", "sqlite",
}


def filename_to_description(basename: str) -> str:
    """Convert a filename like 'bst_insert_search_delete' to 'BST insert/search/delete'."""
    parts = basename.split("_")
    result = []
    i = 0
    while i < len(parts):
        part = parts[i]
        if part.lower() in ACRONYMS:
            result.append(part.upper())
        elif i == 0 and part.lower() not in ACRONYMS:
            result.append(part.lower())
        else:
            result.append(part.lower())
        i += 1

    # Join with spaces
    desc = " ".join(result)

    # Capitalize first letter
    if desc:
        desc = desc[0].upper() + desc[1:]

    return desc


def build_hemlock_index():
    """Build a mapping from base filename -> (relative_path, full_path) for all .hml files."""
    index = {}
    for hml_path in HEMLOCK_DIR.rglob("*.hml"):
        basename = hml_path.stem
        rel = hml_path.relative_to(HEMLOCK_DIR)
        index[basename] = (str(rel), hml_path)
    return index


def get_hemlock_category(rel_path: str) -> str:
    """Get category from hemlock relative path like 'algorithms/sorting/bubble_sort.hml'."""
    parts = Path(rel_path).parts
    if len(parts) >= 2:
        return "/".join(parts[:-1])
    return parts[0] if parts else "unknown"


def read_file_stripped(path: Path) -> str:
    """Read file and strip trailing whitespace from each line and the whole string."""
    text = path.read_text(encoding="utf-8")
    lines = [line.rstrip() for line in text.splitlines()]
    # Remove trailing empty lines
    while lines and not lines[-1]:
        lines.pop()
    return "\n".join(lines)


def extract_description_from_code(hemlock_code: str, basename: str, category: str) -> str:
    """Extract a meaningful description from Hemlock code comments and structure."""
    lines = hemlock_code.splitlines()

    # Try to get description from leading comments
    comment_lines = []
    for line in lines:
        stripped = line.strip()
        if stripped.startswith("//"):
            comment_text = stripped[2:].strip()
            if comment_text and not comment_text.startswith("Python equivalent") and not comment_text.startswith("Node layout"):
                comment_lines.append(comment_text)
        elif stripped.startswith("/*"):
            continue
        elif stripped == "":
            if comment_lines:
                break
            continue
        else:
            break

    if comment_lines:
        # Use the first meaningful comment line as description
        desc = comment_lines[0]
        # Remove trailing punctuation for use as fragment
        desc = desc.rstrip(".")
        return desc

    # Fall back to filename-based description
    return filename_to_description(basename)


def generate_scratch_instruction(basename: str, category: str, hemlock_code: str) -> str:
    """Generate a 'write from scratch' instruction based on category and code analysis."""
    desc = extract_description_from_code(hemlock_code, basename, category)
    friendly_name = filename_to_description(basename)

    cat_parts = category.split("/")
    cat_type = cat_parts[0] if cat_parts else ""
    cat_sub = cat_parts[1] if len(cat_parts) > 1 else ""

    templates_by_category = {
        "sorting": [
            f"Write a Hemlock program that implements {friendly_name.lower()}. {desc}.",
            f"Implement {friendly_name.lower()} in Hemlock. The program should sort an array and print the result.",
        ],
        "search": [
            f"Write a Hemlock program that implements {friendly_name.lower()}. {desc}.",
            f"Implement {friendly_name.lower()} in Hemlock. Search for elements in a sorted array.",
        ],
        "trees": [
            f"Write a Hemlock program that implements {friendly_name.lower()}. {desc}.",
            f"Implement a {friendly_name.lower()} in Hemlock using pointer-based nodes with alloc/free.",
        ],
        "graphs": [
            f"Write a Hemlock program that implements {friendly_name.lower()}. {desc}.",
            f"Implement {friendly_name.lower()} in Hemlock using adjacency lists.",
        ],
        "dp": [
            f"Write a Hemlock program that solves the {friendly_name.lower()} problem using dynamic programming. {desc}.",
            f"Implement {friendly_name.lower()} in Hemlock using a DP approach.",
        ],
        "classic": [
            f"Write a Hemlock program that implements {friendly_name.lower()}. {desc}.",
        ],
        "memory": [
            f"Write a Hemlock program that demonstrates {friendly_name.lower()} using manual memory management. {desc}.",
            f"Implement {friendly_name.lower()} in Hemlock using alloc/free and pointer operations.",
        ],
        "concurrency": [
            f"Write a Hemlock program that demonstrates the {friendly_name.lower()} pattern using async/channels. {desc}.",
            f"Implement {friendly_name.lower()} in Hemlock using structured concurrency.",
        ],
        "defer": [
            f"Write a Hemlock program that demonstrates {friendly_name.lower()} using defer for cleanup. {desc}.",
        ],
    }

    if cat_type == "practical":
        templates = [
            f"Write a Hemlock program that implements {friendly_name.lower()}. {desc}.",
            f"Build a {friendly_name.lower()} in Hemlock. {desc}.",
        ]
    elif cat_type == "translation":
        # For translation subdirectories, describe what the program does without mentioning source language
        templates = [
            f"Write a Hemlock program that implements {friendly_name.lower()}. {desc}.",
            f"Implement {friendly_name.lower()} in Hemlock. {desc}.",
        ]
    else:
        templates = templates_by_category.get(cat_sub, [
            f"Write a Hemlock program that implements {friendly_name.lower()}. {desc}.",
        ])

    return random.choice(templates)


def main():
    hemlock_index = build_hemlock_index()
    rows = []
    stats = {"translation": {}, "generation": 0, "skipped_no_match": []}

    # Type 1: Translation pairs
    for lang_key, lang_info in LANGUAGES.items():
        lang_dir = SOURCE_DIR / lang_key
        if not lang_dir.exists():
            continue

        ext = lang_info["ext"]
        lang_name = lang_info["lang_name"]
        fence = lang_info["fence"]
        matched = 0

        for source_file in sorted(lang_dir.iterdir()):
            if source_file.suffix != ext:
                continue

            basename = source_file.stem
            if basename not in hemlock_index:
                stats["skipped_no_match"].append(f"{lang_key}/{source_file.name}")
                continue

            rel_path, hml_path = hemlock_index[basename]
            source_code = read_file_stripped(source_file)
            hemlock_code = read_file_stripped(hml_path)
            desc = filename_to_description(basename)

            template = random.choice(TRANSLATION_TEMPLATES)
            instruction = template.format(
                lang=lang_name,
                desc=desc,
                fence=fence,
                code=source_code,
            )

            rows.append({
                "instruction": instruction,
                "output": hemlock_code,
                "category": f"translation/{lang_key}",
                "task": basename,
            })
            matched += 1

        stats["translation"][lang_key] = matched

    # Type 2: Write from scratch pairs
    for basename, (rel_path, hml_path) in sorted(hemlock_index.items()):
        hemlock_code = read_file_stripped(hml_path)
        category = get_hemlock_category(rel_path)
        instruction = generate_scratch_instruction(basename, category, hemlock_code)

        rows.append({
            "instruction": instruction,
            "output": hemlock_code,
            "category": f"generation/{category}",
            "task": basename,
        })
        stats["generation"] += 1

    # Shuffle with deterministic seed for good mixing
    random.shuffle(rows)

    # Write output
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        for row in rows:
            f.write(json.dumps(row, ensure_ascii=False) + "\n")

    # Print summary
    total_translation = sum(stats["translation"].values())
    total = len(rows)

    print(f"Generated {total} training examples -> {OUTPUT_FILE}")
    print(f"\nType 1 - Translation pairs: {total_translation}")
    for lang, count in sorted(stats["translation"].items()):
        print(f"  {lang}: {count}")
    print(f"\nType 2 - Generation (write from scratch): {stats['generation']}")
    print(f"\nTotal rows: {total}")

    if stats["skipped_no_match"]:
        print(f"\nSkipped (no matching .hml): {len(stats['skipped_no_match'])}")
        for s in stats["skipped_no_match"][:10]:
            print(f"  {s}")
        if len(stats["skipped_no_match"]) > 10:
            print(f"  ... and {len(stats['skipped_no_match']) - 10} more")

    # Print a few sample rows
    print("\n--- Sample rows ---")
    # Show one translation and one generation example
    for row in rows:
        if row["category"].startswith("translation/"):
            print(f"\n[Translation example - {row['category']}]")
            print(f"Task: {row['task']}")
            print(f"Instruction: {row['instruction'][:200]}...")
            print(f"Output: {row['output'][:150]}...")
            break

    for row in rows:
        if row["category"].startswith("generation/"):
            print(f"\n[Generation example - {row['category']}]")
            print(f"Task: {row['task']}")
            print(f"Instruction: {row['instruction'][:300]}")
            print(f"Output: {row['output'][:150]}...")
            break


if __name__ == "__main__":
    main()

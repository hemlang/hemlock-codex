import re

def convert_inline(line):
    result = line
    # Bold: **text**
    while "**" in result:
        start = result.find("**")
        rest = result[start + 2:]
        end = rest.find("**")
        if end < 0:
            break
        bold_text = rest[:end]
        before = result[:start]
        after = rest[end + 2:]
        result = f"{before}<strong>{bold_text}</strong>{after}"

    # Italic: *text*
    while "*" in result:
        start = result.find("*")
        rest = result[start + 1:]
        end = rest.find("*")
        if end < 0:
            break
        ital_text = rest[:end]
        before = result[:start]
        after = rest[end + 1:]
        result = f"{before}<em>{ital_text}</em>{after}"

    # Inline code: `text`
    while "`" in result:
        start = result.find("`")
        rest = result[start + 1:]
        end = rest.find("`")
        if end < 0:
            break
        code_text = rest[:end]
        before = result[:start]
        after = rest[end + 1:]
        result = f"{before}<code>{code_text}</code>{after}"

    return result

def md_to_html(text):
    lines = text.split("\n")
    html = []
    for line in lines:
        if line.startswith("### "):
            html.append(f"<h3>{convert_inline(line[4:])}</h3>")
        elif line.startswith("## "):
            html.append(f"<h2>{convert_inline(line[3:])}</h2>")
        elif line.startswith("# "):
            html.append(f"<h1>{convert_inline(line[2:])}</h1>")
        elif line.startswith("- "):
            html.append(f"<li>{convert_inline(line[2:])}</li>")
        elif line.strip() == "":
            html.append("")
        else:
            html.append(f"<p>{convert_inline(line)}</p>")
    return "\n".join(html)

markdown = "# Hello World\n\nThis is **bold** and *italic* text.\n\n## Features\n\n- Item with `code`\n- Another **bold** item\n\n### Details\n\nA paragraph with **mixed** and *styles*."

html = md_to_html(markdown)
print(html)

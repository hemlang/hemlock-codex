fn convert_inline(input: &str) -> String {
    let mut result = input.to_string();

    // Bold: **text**
    loop {
        if let Some(start) = result.find("**") {
            let rest = &result[start + 2..].to_string();
            if let Some(end) = rest.find("**") {
                let bold_text = &rest[..end];
                let before = result[..start].to_string();
                let after = rest[end + 2..].to_string();
                result = format!("{}<strong>{}</strong>{}", before, bold_text, after);
                continue;
            }
        }
        break;
    }

    // Italic: *text*
    loop {
        if let Some(start) = result.find('*') {
            let rest = result[start + 1..].to_string();
            if let Some(end) = rest.find('*') {
                let ital_text = &rest[..end];
                let before = result[..start].to_string();
                let after = rest[end + 1..].to_string();
                result = format!("{}<em>{}</em>{}", before, ital_text, after);
                continue;
            }
        }
        break;
    }

    // Inline code: `text`
    loop {
        if let Some(start) = result.find('`') {
            let rest = result[start + 1..].to_string();
            if let Some(end) = rest.find('`') {
                let code_text = &rest[..end];
                let before = result[..start].to_string();
                let after = rest[end + 1..].to_string();
                result = format!("{}<code>{}</code>{}", before, code_text, after);
                continue;
            }
        }
        break;
    }

    result
}

fn md_to_html(text: &str) -> String {
    let mut html = Vec::new();
    for line in text.split('\n') {
        if line.starts_with("### ") {
            html.push(format!("<h3>{}</h3>", convert_inline(&line[4..])));
        } else if line.starts_with("## ") {
            html.push(format!("<h2>{}</h2>", convert_inline(&line[3..])));
        } else if line.starts_with("# ") {
            html.push(format!("<h1>{}</h1>", convert_inline(&line[2..])));
        } else if line.starts_with("- ") {
            html.push(format!("<li>{}</li>", convert_inline(&line[2..])));
        } else if line.trim().is_empty() {
            html.push(String::new());
        } else {
            html.push(format!("<p>{}</p>", convert_inline(line)));
        }
    }
    html.join("\n")
}

fn main() {
    let markdown = "# Hello World\n\nThis is **bold** and *italic* text.\n\n## Features\n\n- Item with `code`\n- Another **bold** item\n\n### Details\n\nA paragraph with **mixed** and *styles*.";
    println!("{}", md_to_html(markdown));
}

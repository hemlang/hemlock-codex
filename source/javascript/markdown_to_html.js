// Basic markdown to HTML converter
function convertInline(line) {
    let result = line;

    // Bold: **text**
    while (result.includes("**")) {
        const start = result.indexOf("**");
        const rest = result.slice(start + 2);
        const end = rest.indexOf("**");
        if (end < 0) break;
        const boldText = rest.substring(0, end);
        const before = result.substring(0, start);
        const after = rest.slice(end + 2);
        result = `${before}<strong>${boldText}</strong>${after}`;
    }

    // Italic: *text*
    while (result.includes("*")) {
        const start = result.indexOf("*");
        const rest = result.slice(start + 1);
        const end = rest.indexOf("*");
        if (end < 0) break;
        const italText = rest.substring(0, end);
        const before = result.substring(0, start);
        const after = rest.slice(end + 1);
        result = `${before}<em>${italText}</em>${after}`;
    }

    // Inline code: `text`
    while (result.includes("`")) {
        const start = result.indexOf("`");
        const rest = result.slice(start + 1);
        const end = rest.indexOf("`");
        if (end < 0) break;
        const codeText = rest.substring(0, end);
        const before = result.substring(0, start);
        const after = rest.slice(end + 1);
        result = `${before}<code>${codeText}</code>${after}`;
    }

    return result;
}

function mdToHtml(text) {
    const lines = text.split("\n");
    const html = [];
    for (const line of lines) {
        if (line.startsWith("### ")) html.push(`<h3>${convertInline(line.slice(4))}</h3>`);
        else if (line.startsWith("## ")) html.push(`<h2>${convertInline(line.slice(3))}</h2>`);
        else if (line.startsWith("# ")) html.push(`<h1>${convertInline(line.slice(2))}</h1>`);
        else if (line.startsWith("- ")) html.push(`<li>${convertInline(line.slice(2))}</li>`);
        else if (line.trim() === "") html.push("");
        else html.push(`<p>${convertInline(line)}</p>`);
    }
    return html.join("\n");
}

const markdown = "# Hello World\n\nThis is **bold** and *italic* text.\n\n## Features\n\n- Item with `code`\n- Another **bold** item\n\n### Details\n\nA paragraph with **mixed** and *styles*.";
const html = mdToHtml(markdown);
console.log(html);

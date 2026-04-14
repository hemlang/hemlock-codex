package main

import (
	"fmt"
	"strings"
)

func convertInline(line string) string {
	result := line

	// Bold: **text**
	for strings.Contains(result, "**") {
		start := strings.Index(result, "**")
		rest := result[start+2:]
		end := strings.Index(rest, "**")
		if end < 0 {
			break
		}
		boldText := rest[:end]
		before := result[:start]
		after := rest[end+2:]
		result = before + "<strong>" + boldText + "</strong>" + after
	}

	// Italic: *text*
	for strings.Contains(result, "*") {
		start := strings.Index(result, "*")
		rest := result[start+1:]
		end := strings.Index(rest, "*")
		if end < 0 {
			break
		}
		italText := rest[:end]
		before := result[:start]
		after := rest[end+1:]
		result = before + "<em>" + italText + "</em>" + after
	}

	// Inline code: `text`
	for strings.Contains(result, "`") {
		start := strings.Index(result, "`")
		rest := result[start+1:]
		end := strings.Index(rest, "`")
		if end < 0 {
			break
		}
		codeText := rest[:end]
		before := result[:start]
		after := rest[end+1:]
		result = before + "<code>" + codeText + "</code>" + after
	}

	return result
}

func mdToHTML(text string) string {
	lines := strings.Split(text, "\n")
	var html []string

	for _, line := range lines {
		if strings.HasPrefix(line, "### ") {
			content := convertInline(line[4:])
			html = append(html, "<h3>"+content+"</h3>")
		} else if strings.HasPrefix(line, "## ") {
			content := convertInline(line[3:])
			html = append(html, "<h2>"+content+"</h2>")
		} else if strings.HasPrefix(line, "# ") {
			content := convertInline(line[2:])
			html = append(html, "<h1>"+content+"</h1>")
		} else if strings.HasPrefix(line, "- ") {
			content := convertInline(line[2:])
			html = append(html, "<li>"+content+"</li>")
		} else if strings.TrimSpace(line) == "" {
			html = append(html, "")
		} else {
			html = append(html, "<p>"+convertInline(line)+"</p>")
		}
	}

	return strings.Join(html, "\n")
}

func main() {
	markdown := "# Hello World\n\nThis is **bold** and *italic* text.\n\n## Features\n\n- Item with `code`\n- Another **bold** item\n\n### Details\n\nA paragraph with **mixed** and *styles*."
	html := mdToHTML(markdown)
	fmt.Println(html)
}

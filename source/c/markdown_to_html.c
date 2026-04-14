// gcc -o markdown_to_html markdown_to_html.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Replace first occurrence of `from` with `<tag>content</tag>`
// This is a simple implementation matching the Hemlock logic
void convert_inline(const char *in, char *out, int outsz) {
    char tmp[4096];
    strncpy(tmp, in, sizeof(tmp)-1); tmp[sizeof(tmp)-1] = '\0';

    // Bold: **text**
    while (1) {
        char *p1 = strstr(tmp, "**");
        if (!p1) break;
        char *p2 = strstr(p1 + 2, "**");
        if (!p2) break;
        int plen = p1 - tmp;
        int blen = p2 - (p1 + 2);
        char result[4096];
        snprintf(result, sizeof(result), "%.*s<strong>%.*s</strong>%s",
                 plen, tmp, blen, p1+2, p2+2);
        strncpy(tmp, result, sizeof(tmp)-1);
    }

    // Italic: *text*
    while (1) {
        char *p1 = strchr(tmp, '*');
        if (!p1) break;
        char *p2 = strchr(p1 + 1, '*');
        if (!p2) break;
        int plen = p1 - tmp;
        int ilen = p2 - (p1 + 1);
        char result[4096];
        snprintf(result, sizeof(result), "%.*s<em>%.*s</em>%s",
                 plen, tmp, ilen, p1+1, p2+1);
        strncpy(tmp, result, sizeof(tmp)-1);
    }

    // Inline code: `text`
    while (1) {
        char *p1 = strchr(tmp, '`');
        if (!p1) break;
        char *p2 = strchr(p1 + 1, '`');
        if (!p2) break;
        int plen = p1 - tmp;
        int clen = p2 - (p1 + 1);
        char result[4096];
        snprintf(result, sizeof(result), "%.*s<code>%.*s</code>%s",
                 plen, tmp, clen, p1+1, p2+1);
        strncpy(tmp, result, sizeof(tmp)-1);
    }

    strncpy(out, tmp, outsz-1);
    out[outsz-1] = '\0';
}

void process_line(const char *line, char *out, int outsz) {
    char content[2048];
    if (strncmp(line, "### ", 4) == 0) {
        convert_inline(line + 4, content, sizeof(content));
        snprintf(out, outsz, "<h3>%s</h3>", content);
    } else if (strncmp(line, "## ", 3) == 0) {
        convert_inline(line + 3, content, sizeof(content));
        snprintf(out, outsz, "<h2>%s</h2>", content);
    } else if (strncmp(line, "# ", 2) == 0) {
        convert_inline(line + 2, content, sizeof(content));
        snprintf(out, outsz, "<h1>%s</h1>", content);
    } else if (strncmp(line, "- ", 2) == 0) {
        convert_inline(line + 2, content, sizeof(content));
        snprintf(out, outsz, "<li>%s</li>", content);
    } else if (line[0] == '\0') {
        out[0] = '\0';
    } else {
        convert_inline(line, content, sizeof(content));
        snprintf(out, outsz, "<p>%s</p>", content);
    }
}

int main(void) {
    const char *markdown = "# Hello World\n\nThis is **bold** and *italic* text.\n\n## Features\n\n- Item with `code`\n- Another **bold** item\n\n### Details\n\nA paragraph with **mixed** and *styles*.";

    // Split by \n and process
    char md_copy[4096];
    strncpy(md_copy, markdown, sizeof(md_copy)-1);

    // Split preserving empty lines
    char *lines[64];
    int nlines = 0;
    char *p = md_copy;
    while (*p && nlines < 63) {
        lines[nlines++] = p;
        char *nl = strchr(p, '\n');
        if (!nl) break;
        *nl = '\0';
        p = nl + 1;
    }

    char html_lines[64][4096];
    for (int i = 0; i < nlines; i++) {
        process_line(lines[i], html_lines[i], sizeof(html_lines[i]));
    }

    for (int i = 0; i < nlines; i++) {
        if (i > 0) printf("\n");
        printf("%s", html_lines[i]);
    }
    printf("\n");
    return 0;
}

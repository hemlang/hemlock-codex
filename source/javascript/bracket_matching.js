function isBalanced(s) {
    const stack = [];
    for (const c of s) {
        if (c === '(' || c === '{' || c === '[') stack.push(c);
        else if (c === ')' || c === '}' || c === ']') {
            if (stack.length === 0) return false;
            const top = stack.pop();
            if (c === ')' && top !== '(') return false;
            if (c === '}' && top !== '{') return false;
            if (c === ']' && top !== '[') return false;
        }
    }
    return stack.length === 0;
}

const tests = ["({[]})", "({[}])", ""];
for (const t of tests) {
    console.log(`"${t}" -> ${isBalanced(t) ? "balanced" : "not balanced"}`);
}

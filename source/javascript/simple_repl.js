// Simple calculator REPL with predefined inputs
const inputs = ["2 + 3", "10 * 4", "100 / 7", "50 - 18", "2 + 3 * 4"];

function tokenize(expr) {
    const tokens = [];
    let num = "";
    for (const ch of expr) {
        if (ch === ' ') {
            if (num !== "") { tokens.push(num); num = ""; }
        } else if ("+-*/".includes(ch)) {
            if (num !== "") { tokens.push(num); num = ""; }
            tokens.push(ch);
        } else {
            num += ch;
        }
    }
    if (num !== "") tokens.push(num);
    return tokens;
}

function evaluate(expr) {
    const tokens = tokenize(expr);
    if (tokens.length === 0) return 0;
    let result = parseFloat(tokens[0]);
    let i = 1;
    while (i < tokens.length) {
        const op = tokens[i], operand = parseFloat(tokens[i + 1]);
        if (op === "+") result += operand;
        else if (op === "-") result -= operand;
        else if (op === "*") result *= operand;
        else if (op === "/") result /= operand;
        i += 2;
    }
    return result;
}

console.log("=== Simple Calculator ===");
for (const input of inputs) {
    const result = evaluate(input);
    const intResult = Math.trunc(result);
    if (intResult === result) console.log(`> ${input} = ${intResult}`);
    else console.log(`> ${input} = ${result}`);
}
console.log("=== Done ===");

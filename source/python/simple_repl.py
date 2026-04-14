inputs = [
    "2 + 3",
    "10 * 4",
    "100 / 7",
    "50 - 18",
    "2 + 3 * 4",
]

def tokenize(expr):
    tokens = []
    num = ""
    for ch in expr:
        if ch == " ":
            if num:
                tokens.append(num)
                num = ""
        elif ch in "+-*/":
            if num:
                tokens.append(num)
                num = ""
            tokens.append(ch)
        else:
            num += ch
    if num:
        tokens.append(num)
    return tokens

def evaluate(expr):
    tokens = tokenize(expr)
    if not tokens:
        return 0
    result = float(tokens[0])
    i = 1
    while i < len(tokens):
        op = tokens[i]
        operand = float(tokens[i + 1])
        if op == "+": result += operand
        elif op == "-": result -= operand
        elif op == "*": result *= operand
        elif op == "/": result /= operand
        i += 2
    return result

print("=== Simple Calculator ===")
for inp in inputs:
    result = evaluate(inp)
    int_result = int(result)
    if float(int_result) == result:
        print(f"> {inp} = {int_result}")
    else:
        print(f"> {inp} = {result}")
print("=== Done ===")

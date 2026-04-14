def is_balanced(s):
    stack = []
    for c in s:
        if c in "({[":
            stack.append(c)
        elif c in ")}]":
            if not stack:
                return False
            top = stack.pop()
            if c == ")" and top != "(":
                return False
            if c == "}" and top != "{":
                return False
            if c == "]" and top != "[":
                return False
    return len(stack) == 0

tests = ["({[]})", "({[}])", ""]
for t in tests:
    status = "balanced" if is_balanced(t) else "not balanced"
    print(f'"{t}" -> {status}')

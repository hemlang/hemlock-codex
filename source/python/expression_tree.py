class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

def evaluate(node):
    if node.left is None and node.right is None:
        return int(node.value)
    left_val = evaluate(node.left)
    right_val = evaluate(node.right)
    if node.value == "+":
        return left_val + right_val
    if node.value == "-":
        return left_val - right_val
    if node.value == "*":
        return left_val * right_val
    return 0

# Build: (2 + 3) * (4 - 1)
add_node = Node("+", Node("2"), Node("3"))
sub_node = Node("-", Node("4"), Node("1"))
mul_node = Node("*", add_node, sub_node)

result = evaluate(mul_node)
print(f"result: {result}")

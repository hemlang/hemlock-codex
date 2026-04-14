class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def insert(root, value):
    if root is None:
        return Node(value)
    if value < root.value:
        root.left = insert(root.left, value)
    elif value > root.value:
        root.right = insert(root.right, value)
    return root

def lca(root, p, q):
    if root is None:
        return None
    if p < root.value and q < root.value:
        return lca(root.left, p, q)
    if p > root.value and q > root.value:
        return lca(root.right, p, q)
    return root

root = None
for v in [50, 30, 70, 20, 40, 60, 80]:
    root = insert(root, v)

r1 = lca(root, 20, 40)
print(f"lca(20, 40): {r1.value}")

r2 = lca(root, 20, 70)
print(f"lca(20, 70): {r2.value}")

r3 = lca(root, 60, 80)
print(f"lca(60, 80): {r3.value}")

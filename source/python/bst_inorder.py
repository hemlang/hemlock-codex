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

def inorder(root, result):
    if root is None:
        return
    inorder(root.left, result)
    result.append(root.value)
    inorder(root.right, result)

root = None
for v in [50, 30, 70, 20, 40, 60, 80]:
    root = insert(root, v)

result = []
inorder(root, result)
print(f"inorder: {' '.join(str(x) for x in result)}")

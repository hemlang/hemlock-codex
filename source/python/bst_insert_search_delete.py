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

def search(root, value):
    if root is None:
        return False
    if value == root.value:
        return True
    if value < root.value:
        return search(root.left, value)
    return search(root.right, value)

def find_min(root):
    current = root
    while current.left is not None:
        current = current.left
    return current

def delete_node(root, value):
    if root is None:
        return None
    if value < root.value:
        root.left = delete_node(root.left, value)
    elif value > root.value:
        root.right = delete_node(root.right, value)
    else:
        if root.left is None:
            return root.right
        if root.right is None:
            return root.left
        successor = find_min(root.right)
        root.value = successor.value
        root.right = delete_node(root.right, successor.value)
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

print("search 40: found" if search(root, 40) else "search 40: not found")
print("search 25: found" if search(root, 25) else "search 25: not found")

root = delete_node(root, 30)

result = []
inorder(root, result)
print(f"inorder: {' '.join(str(x) for x in result)}")

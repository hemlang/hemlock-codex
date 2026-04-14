class Node:
    def __init__(self, val, next=None):
        self.val = val
        self.next = next

def build_list(arr):
    head = None
    for x in reversed(arr):
        head = Node(x, head)
    return head

def print_list(head, label):
    parts = []
    curr = head
    while curr:
        parts.append(str(curr.val))
        curr = curr.next
    print(f"{label}: {' '.join(parts)}")

def reverse_list(head):
    prev = None
    curr = head
    while curr:
        next_node = curr.next
        curr.next = prev
        prev = curr
        curr = next_node
    return prev

head = build_list([1, 2, 3, 4, 5])
print_list(head, "original")
reversed_head = reverse_list(head)
print_list(reversed_head, "reversed")

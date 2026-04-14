# Simulates a manual linked list using Python objects
# (Python manages memory, but we demonstrate the same structure/output)

head = None

class Node:
    def __init__(self, val, nxt=None):
        self.val = val
        self.next = nxt

def push(val):
    global head
    head = Node(val, head)

def traverse():
    parts = []
    current = head
    while current is not None:
        parts.append(str(current.val))
        current = current.next
    print("list: " + " ".join(parts))

def free_all():
    global head
    current = head
    count = 0
    while current is not None:
        nxt = current.next
        count += 1
        current = nxt
    head = None
    print(f"freed {count} nodes")

push(10)
push(20)
push(30)
traverse()
free_all()

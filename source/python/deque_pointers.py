# Double-ended queue using a doubly-linked list

class Node:
    def __init__(self, val):
        self.val = val
        self.prev = None
        self.next = None

dq_head = None
dq_tail = None
dq_size = 0

def push_front(val):
    global dq_head, dq_tail, dq_size
    node = Node(val)
    if dq_head is None:
        dq_head = node
        dq_tail = node
    else:
        node.next = dq_head
        dq_head.prev = node
        dq_head = node
    dq_size += 1
    print(f"push_front: {val}")

def push_back(val):
    global dq_head, dq_tail, dq_size
    node = Node(val)
    if dq_tail is None:
        dq_head = node
        dq_tail = node
    else:
        node.prev = dq_tail
        dq_tail.next = node
        dq_tail = node
    dq_size += 1
    print(f"push_back: {val}")

def pop_front():
    global dq_head, dq_tail, dq_size
    if dq_head is None:
        print("deque empty")
        return None
    val = dq_head.val
    nxt = dq_head.next
    if nxt is not None:
        nxt.prev = None
    else:
        dq_tail = None
    dq_head = nxt
    dq_size -= 1
    print(f"pop_front: {val}")
    return val

def pop_back():
    global dq_head, dq_tail, dq_size
    if dq_tail is None:
        print("deque empty")
        return None
    val = dq_tail.val
    prv = dq_tail.prev
    if prv is not None:
        prv.next = None
    else:
        dq_head = None
    dq_tail = prv
    dq_size -= 1
    print(f"pop_back: {val}")
    return val

def print_deque():
    parts = []
    cur = dq_head
    while cur is not None:
        parts.append(str(cur.val))
        cur = cur.next
    print("deque: " + " ".join(parts))

push_front(1)
push_front(2)
push_back(3)
push_back(4)
print_deque()
print(f"size: {dq_size}")

pop_front()
pop_back()
print_deque()
print(f"size: {dq_size}")

while dq_head is not None:
    pop_front()
print("deque cleared")

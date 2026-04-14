# Simulates a dynamic array that doubles capacity when full

capacity = 4
data = [None] * capacity
size = 0

def grow():
    global capacity, data
    new_cap = capacity * 2
    new_data = [None] * new_cap
    for i in range(size):
        new_data[i] = data[i]
    data = new_data
    capacity = new_cap

def push(val):
    global size
    if size == capacity:
        grow()
    data[size] = val
    size += 1

def print_all():
    parts = [str(data[i]) for i in range(size)]
    print("values: " + " ".join(parts))

for i in range(1, 11):
    push(i)

print(f"capacity: {capacity}")
print_all()

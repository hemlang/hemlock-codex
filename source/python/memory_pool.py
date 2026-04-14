# Fixed-size slab allocator / object pool simulation

SLOT_SIZE = 8
POOL_SLOTS = 8
used = [False] * POOL_SLOTS
slot_data = [None] * POOL_SLOTS
alloc_count = 0

def pool_alloc():
    global alloc_count
    for i in range(POOL_SLOTS):
        if not used[i]:
            used[i] = True
            alloc_count += 1
            print(f"alloc slot {i}")
            return i
    print("pool exhausted!")
    return None

def pool_free(slot_index):
    global alloc_count
    if used[slot_index]:
        used[slot_index] = False
        alloc_count -= 1
        print(f"freed slot {slot_index}")

def active_count():
    return sum(1 for u in used if u)

s0 = pool_alloc()
s1 = pool_alloc()
s2 = pool_alloc()
s3 = pool_alloc()
s4 = pool_alloc()

slot_data[s0] = 100
slot_data[s1] = 200

print(f"active: {active_count()}")

pool_free(1)
pool_free(3)

print(f"active after free: {active_count()}")

s5 = pool_alloc()
s6 = pool_alloc()
s7 = pool_alloc()

print(f"final active: {active_count()}")
print("pool freed")

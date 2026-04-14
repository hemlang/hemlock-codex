import ctypes

ARENA_SIZE = 1024
arena = (ctypes.c_uint8 * ARENA_SIZE)()
offset = 0

def arena_alloc(size):
    global offset
    if offset + size > ARENA_SIZE:
        print("arena out of memory!")
        return None
    idx = offset
    offset += size
    return idx

def arena_reset():
    global offset
    offset = 0

slots = {}

def write_i32(idx, val):
    slots[idx] = val

def read_i32(idx):
    return slots[idx]

a = arena_alloc(4)
b = arena_alloc(4)
c = arena_alloc(4)
d = arena_alloc(4)
e = arena_alloc(4)

write_i32(a, 100)
write_i32(b, 200)
write_i32(c, 300)
write_i32(d, 400)
write_i32(e, 500)

print(f"slot 0: {read_i32(a)}")
print(f"slot 1: {read_i32(b)}")
print(f"slot 2: {read_i32(c)}")
print(f"slot 3: {read_i32(d)}")
print(f"slot 4: {read_i32(e)}")

print(f"arena used: {offset} bytes")
print("arena freed")

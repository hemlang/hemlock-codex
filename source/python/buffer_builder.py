# Growing buffer that doubles capacity when full

capacity = 4
buf = bytearray(capacity)
size = 0

def buf_grow():
    global capacity, buf
    new_cap = capacity * 2
    new_buf = bytearray(new_cap)
    new_buf[:size] = buf[:size]
    buf = new_buf
    capacity = new_cap

def write_byte(b):
    global size
    if size >= capacity:
        buf_grow()
    buf[size] = b
    size += 1

def read_back():
    return buf[:size].decode("utf-8")

message = "Hello, World!"
for b in message.encode("utf-8"):
    write_byte(b)

print(f"wrote {size} bytes")
print(f"capacity: {capacity}")
reconstructed = read_back()
print(f"reconstructed: {reconstructed}")

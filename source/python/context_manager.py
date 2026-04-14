def write_with_context():
    path = "/tmp/hemlock_ctx.txt"
    with open(path, "w") as f:
        f.write("hello from context manager")

def read_with_context():
    path = "/tmp/hemlock_ctx.txt"
    with open(path, "r") as f:
        content = f.read()
        print(content)

write_with_context()
read_with_context()

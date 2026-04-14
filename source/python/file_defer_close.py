import os

def main():
    path = "/tmp/hemlock_defer_test.txt"
    with open(path, "w") as f:
        f.write("hello from defer")

    with open(path, "r") as f:
        contents = f.read()
        if contents == "hello from defer":
            print("wrote and read back successfully")

main()

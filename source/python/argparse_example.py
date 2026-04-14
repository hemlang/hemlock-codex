import argparse

# Simulate: script.py --name Alice --count 3 --upper
parser = argparse.ArgumentParser(description="Demo CLI tool")
parser.add_argument("--name", default="World", help="Name to greet")
parser.add_argument("--count", type=int, default=3, help="Repeat count")
parser.add_argument("--upper", action="store_true", help="Uppercase output")

# Parse with simulated args
args = parser.parse_args(["--name", "Alice", "--count", "3", "--upper"])

print(f"name: {args.name}")
print(f"count: {args.count}")
print(f"upper: {str(args.upper).lower()}")

for i in range(args.count):
    msg = f"Hello, {args.name}!"
    if args.upper:
        msg = msg.upper()
    print(msg)

import re

text = "Order 42 has 3 items weighing 17 kg at price 99"
numbers = re.findall(r'\d+', text)
print("Numbers found:")
for n in numbers:
    print(n)
print(f"Count: {len(numbers)}")

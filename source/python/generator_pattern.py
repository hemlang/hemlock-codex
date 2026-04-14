def fibonacci():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b

gen = fibonacci()
results = [next(gen) for _ in range(10)]
print(" ".join(str(x) for x in results))

class RingBuffer:
    def __init__(self, capacity):
        self.capacity = capacity
        self.data = [None] * capacity
        self.head = 0
        self.tail = 0
        self.count = 0

    def write(self, val):
        if self.count == self.capacity:
            print(f"ring full, cannot write {val}")
            return False
        self.data[self.tail] = val
        self.tail = (self.tail + 1) % self.capacity
        self.count += 1
        return True

    def read(self):
        if self.count == 0:
            print("ring empty")
            return None
        val = self.data[self.head]
        self.head = (self.head + 1) % self.capacity
        self.count -= 1
        return val

rb = RingBuffer(4)
rb.write(1)
rb.write(2)
rb.write(3)
rb.write(4)

results = []
results.append(rb.read())
results.append(rb.read())

rb.write(5)
rb.write(6)

results.append(rb.read())
results.append(rb.read())
results.append(rb.read())
results.append(rb.read())

print(" ".join(str(x) for x in results))

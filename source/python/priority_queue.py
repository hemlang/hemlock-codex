class MinHeap:
    def __init__(self):
        self.heap = []

    def insert(self, val):
        self.heap.append(val)
        i = len(self.heap) - 1
        while i > 0:
            parent = (i - 1) // 2
            if self.heap[i] < self.heap[parent]:
                self.heap[i], self.heap[parent] = self.heap[parent], self.heap[i]
                i = parent
            else:
                break

    def extract_min(self):
        min_val = self.heap[0]
        last = self.heap.pop()
        if self.heap:
            self.heap[0] = last
            i = 0
            while True:
                left = 2 * i + 1
                right = 2 * i + 2
                smallest = i
                if left < len(self.heap) and self.heap[left] < self.heap[smallest]:
                    smallest = left
                if right < len(self.heap) and self.heap[right] < self.heap[smallest]:
                    smallest = right
                if smallest != i:
                    self.heap[i], self.heap[smallest] = self.heap[smallest], self.heap[i]
                    i = smallest
                else:
                    break
        return min_val

pq = MinHeap()
for v in [5, 3, 7, 1, 4, 2]:
    pq.insert(v)

results = [pq.extract_min() for _ in range(6)]
print(" ".join(str(x) for x in results))

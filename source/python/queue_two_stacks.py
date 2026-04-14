class Queue:
    def __init__(self):
        self.inbox = []
        self.outbox = []

    def enqueue(self, val):
        self.inbox.append(val)

    def dequeue(self):
        if not self.outbox:
            while self.inbox:
                self.outbox.append(self.inbox.pop())
        return self.outbox.pop()

q = Queue()
q.enqueue(1)
q.enqueue(2)
q.enqueue(3)

results = []
results.append(q.dequeue())
results.append(q.dequeue())

q.enqueue(4)
q.enqueue(5)

results.append(q.dequeue())
results.append(q.dequeue())
results.append(q.dequeue())

print(" ".join(str(x) for x in results))

import threading
import queue

work_q = queue.Queue()
result_q = queue.Queue()

def worker():
    while True:
        val = work_q.get()
        if val is None:
            break
        result_q.put(val * val)

for i in range(1, 21):
    work_q.put(i)

workers = []
for _ in range(4):
    t = threading.Thread(target=worker)
    t.start()
    workers.append(t)

for _ in range(4):
    work_q.put(None)

for t in workers:
    t.join()

results = []
while not result_q.empty():
    results.append(result_q.get())

results.sort()
print(f"results: {' '.join(str(x) for x in results)}")

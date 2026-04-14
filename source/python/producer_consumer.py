import threading
import queue

ch = queue.Queue(maxsize=10)

def producer():
    for i in range(1, 11):
        ch.put(i)
    ch.put(None)  # sentinel

def consumer():
    results = []
    while True:
        val = ch.get()
        if val is None:
            break
        results.append(val)
    return results

results_holder = []

def consumer_thread():
    results_holder.extend(consumer())

p = threading.Thread(target=producer)
c = threading.Thread(target=consumer_thread)

p.start()
c.start()
p.join()
c.join()

print(f"received: {' '.join(str(x) for x in results_holder)}")

import threading
import queue

q = queue.Queue(maxsize=100)
num_producers = 3
items_per_producer = 5
total_items = num_producers * items_per_producer
results = []
results_lock = threading.Lock()

def producer(prod_id):
    for i in range(items_per_producer):
        q.put(f"p{prod_id}-{i}")

def consumer():
    received = []
    for _ in range(total_items):
        val = q.get()
        received.append(val)
    with results_lock:
        results.extend(received)

consumer_thread = threading.Thread(target=consumer)
producer_threads = [threading.Thread(target=producer, args=(i,)) for i in range(num_producers)]

consumer_thread.start()
for t in producer_threads:
    t.start()

for t in producer_threads:
    t.join()
consumer_thread.join()

print(f"consumed {len(results)} items")
results.sort()
print(f"values: {' '.join(results)}")

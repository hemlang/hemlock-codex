import threading

counter = 0
lock = threading.Lock()
num_tasks = 10
iterations = 100

def increment_worker():
    global counter
    for _ in range(iterations):
        with lock:
            counter += 1

threads = [threading.Thread(target=increment_worker) for _ in range(num_tasks)]
for t in threads:
    t.start()
for t in threads:
    t.join()

print(f"final: {counter}")

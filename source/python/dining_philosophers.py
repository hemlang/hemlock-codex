import threading

num_phil = 5
forks = [threading.Semaphore(1) for _ in range(num_phil)]
results = []
results_lock = threading.Lock()

def philosopher(phil_id):
    left = phil_id
    right = (phil_id + 1) % num_phil

    first = min(left, right)
    second = max(left, right)

    forks[first].acquire()
    forks[second].acquire()

    print(f"philosopher {phil_id} is eating")

    forks[first].release()
    forks[second].release()

    with results_lock:
        results.append(phil_id)

threads = [threading.Thread(target=philosopher, args=(i,)) for i in range(num_phil)]
for t in threads:
    t.start()
for t in threads:
    t.join()

print("all philosophers ate")

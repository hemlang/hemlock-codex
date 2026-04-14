import threading

num_tasks = 4
barrier = threading.Barrier(num_tasks)
done_count = 0
lock = threading.Lock()

def barrier_task(task_id):
    global done_count
    barrier.wait()
    with lock:
        done_count += 1

threads = []
for i in range(num_tasks):
    t = threading.Thread(target=barrier_task, args=(i,))
    threads.append(t)
    t.start()

for t in threads:
    t.join()

print(f"all {done_count} tasks passed barrier")

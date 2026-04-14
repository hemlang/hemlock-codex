import threading

data = [1, 2, 3, 4, 5, 6, 7, 8]

def map_worker(chunk, result_holder):
    result_holder.extend(x * x for x in chunk)

def reduce_worker(values, result_holder):
    result_holder.append(sum(values))

chunk_size = 2
chunks = [data[i:i + chunk_size] for i in range(0, len(data), chunk_size)]

map_results = [[] for _ in chunks]
map_threads = []
for i, chunk in enumerate(chunks):
    t = threading.Thread(target=map_worker, args=(chunk, map_results[i]))
    t.start()
    map_threads.append(t)

for t in map_threads:
    t.join()

all_squares = []
for r in map_results:
    all_squares.extend(r)

reduce_result = []
reduce_thread = threading.Thread(target=reduce_worker, args=(all_squares, reduce_result))
reduce_thread.start()
reduce_thread.join()

print(f"sum of squares: {reduce_result[0]}")

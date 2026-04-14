import threading

def process_file(name, data, result_holder):
    total = sum(data)
    maximum = max(data)
    result_holder.append({"name": name, "sum": total, "max": maximum, "count": len(data)})

files = [
    {"name": "data_a.csv", "data": [10, 20, 30, 40, 50]},
    {"name": "data_b.csv", "data": [5, 15, 25, 35, 45, 55]},
    {"name": "data_c.csv", "data": [100, 200, 300]},
]

result_holders = [[] for _ in files]
threads = []
for i, f in enumerate(files):
    t = threading.Thread(target=process_file, args=(f["name"], f["data"], result_holders[i]))
    t.start()
    threads.append(t)

for t in threads:
    t.join()

results = [r[0] for r in result_holders]
for r in results:
    print(f"{r['name']}: sum={r['sum']} max={r['max']} count={r['count']}")
print("all files processed")

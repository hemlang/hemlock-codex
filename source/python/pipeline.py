import threading
import queue

gen_q = queue.Queue(maxsize=5)
dbl_q = queue.Queue(maxsize=5)
add_q = queue.Queue(maxsize=5)

def generate(out):
    for i in range(1, 6):
        out.put(i)
    out.put(None)

def double_stage(inp, out):
    while True:
        val = inp.get()
        if val is None:
            out.put(None)
            break
        out.put(val * 2)

def add10_stage(inp, out):
    while True:
        val = inp.get()
        if val is None:
            out.put(None)
            break
        out.put(val + 10)

t1 = threading.Thread(target=generate, args=(gen_q,))
t2 = threading.Thread(target=double_stage, args=(gen_q, dbl_q))
t3 = threading.Thread(target=add10_stage, args=(dbl_q, add_q))

t1.start()
t2.start()
t3.start()

results = []
while True:
    val = add_q.get()
    if val is None:
        break
    results.append(val)

t1.join()
t2.join()
t3.join()

print(" ".join(str(x) for x in results))

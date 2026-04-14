import time
import os

watch_path = "/tmp/hemlock_watch_test.txt"

with open(watch_path, "w") as f:
    f.write("initial content")
t1 = int(time.time() * 1000)
print(f"[watcher] monitoring: {watch_path}")
print(f"[watcher] initial write at t={t1}")

with open(watch_path, "r") as f:
    initial = f.read()
print(f"[watcher] initial content: {initial}")

with open(watch_path, "w") as f:
    f.write("modified content")
t2 = int(time.time() * 1000)
print(f"[watcher] file modified at t={t2}")

with open(watch_path, "r") as f:
    content = f.read()

if content == "modified content":
    print("[watcher] file change detected")
    print(f"[watcher] new content: {content}")
else:
    print("[watcher] no change detected")

if t2 > t1:
    print("[watcher] modification time advanced")

print("[watcher] done")

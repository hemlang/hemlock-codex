import threading
import queue

request_q = queue.Queue(maxsize=10)
response_q = queue.Queue(maxsize=10)

def server():
    for _ in range(3):
        req = request_q.get()
        method = req["method"]
        path = req["path"]
        status = 200
        if path == "/":
            body = "Hello, World!"
        elif path == "/about":
            body = "About Page"
        else:
            status = 404
            body = "Not Found"
        response_q.put({"status": status, "body": body, "method": method, "path": path})

def client():
    requests = [
        {"method": "GET", "path": "/"},
        {"method": "GET", "path": "/about"},
        {"method": "GET", "path": "/missing"},
    ]
    for req in requests:
        request_q.put(req)
        res = response_q.get()
        print(f"[simulated] {res['method']} {res['path']} -> {res['status']} {res['body']}")

srv = threading.Thread(target=server)
cli = threading.Thread(target=client)

srv.start()
cli.start()
cli.join()
srv.join()

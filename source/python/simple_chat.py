import threading
import queue

alice_q = queue.Queue(maxsize=10)
bob_q = queue.Queue(maxsize=10)

def alice(send_q, recv_q):
    send_q.put("Hi Bob! How are you?")
    msg = recv_q.get()
    print(f"Alice received: {msg}")

    send_q.put("I'm working on a Hemlock project!")
    msg = recv_q.get()
    print(f"Alice received: {msg}")

    send_q.put("Thanks! Talk later.")
    msg = recv_q.get()
    print(f"Alice received: {msg}")

def bob(send_q, recv_q):
    msg = recv_q.get()
    print(f"Bob received: {msg}")
    send_q.put("Hey Alice! I'm great, you?")

    msg = recv_q.get()
    print(f"Bob received: {msg}")
    send_q.put("That sounds awesome!")

    msg = recv_q.get()
    print(f"Bob received: {msg}")
    send_q.put("Bye Alice!")

a = threading.Thread(target=alice, args=(bob_q, alice_q))
b = threading.Thread(target=bob, args=(alice_q, bob_q))

a.start()
b.start()
a.join()
b.join()

print("Chat ended.")

# Manual reference counting simulation

class RCObject:
    def __init__(self, data):
        self.refcount = 1
        self.data = data

def rc_new(data):
    obj = RCObject(data)
    print(f"created obj(data={data}, refcount=1)")
    return obj

def rc_retain(obj):
    obj.refcount += 1
    print(f"retain obj(data={obj.data}, refcount={obj.refcount})")
    return obj

def rc_release(obj):
    obj.refcount -= 1
    if obj.refcount == 0:
        print(f"release obj(data={obj.data}, refcount=0) -> freed")
        return None
    print(f"release obj(data={obj.data}, refcount={obj.refcount})")
    return obj

print("--- create object ---")
a = rc_new(42)

print("--- share with b ---")
b = rc_retain(a)

print("--- share with c ---")
c = rc_retain(a)

print(f"data: {a.data}, refcount: {a.refcount}")

print("--- release a ---")
a = rc_release(a)

print("--- release b ---")
b = rc_release(b)

print("--- release c (last ref, should free) ---")
c = rc_release(c)

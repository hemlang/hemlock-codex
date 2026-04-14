import math

COUNT = 5
xs = [0.0] * COUNT
ys = [0.0] * COUNT
zs = [0.0] * COUNT

def set_point(i, x, y, z):
    xs[i] = x
    ys[i] = y
    zs[i] = z

def distance(i):
    x, y, z = xs[i], ys[i], zs[i]
    return math.sqrt(x * x + y * y + z * z)

set_point(0, 1.0, 0.0, 0.0)
set_point(1, 0.0, 2.0, 0.0)
set_point(2, 0.0, 0.0, 3.0)
set_point(3, 1.0, 1.0, 1.0)
set_point(4, 3.0, 4.0, 0.0)

for i in range(COUNT):
    x, y, z = xs[i], ys[i], zs[i]
    d = distance(i)
    # Format floats to match Hemlock output (remove trailing zeros where possible)
    def fmt(v):
        if v == int(v):
            return str(int(v)) + ".0"
        return str(v)
    print(f"point {i}: ({fmt(x)}, {fmt(y)}, {fmt(z)}) distance = {d}")

print("all arrays freed")

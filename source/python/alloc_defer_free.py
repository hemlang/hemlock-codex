import ctypes

def main():
    # Simulate alloc/free with ctypes, defer with try/finally
    a = ctypes.create_string_buffer(8)
    b = ctypes.create_string_buffer(8)
    c = ctypes.create_string_buffer(8)

    try:
        ctypes.cast(a, ctypes.POINTER(ctypes.c_int32))[0] = 10
        ctypes.cast(b, ctypes.POINTER(ctypes.c_int32))[0] = 20
        ctypes.cast(c, ctypes.POINTER(ctypes.c_int32))[0] = 30

        va = ctypes.cast(a, ctypes.POINTER(ctypes.c_int32))[0]
        vb = ctypes.cast(b, ctypes.POINTER(ctypes.c_int32))[0]
        vc = ctypes.cast(c, ctypes.POINTER(ctypes.c_int32))[0]

        print(f"{va} {vb} {vc}")
    finally:
        print("all memory freed")

main()

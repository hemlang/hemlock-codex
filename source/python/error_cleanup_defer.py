cleaned = False

def cleanup():
    global cleaned
    cleaned = True
    print("resource cleaned up")

def risky_operation():
    try:
        raise Exception("something went wrong")
    finally:
        cleanup()

def main():
    try:
        risky_operation()
    except Exception:
        print("error handled")

main()

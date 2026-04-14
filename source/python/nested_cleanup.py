import contextlib

@contextlib.contextmanager
def cleanup_context(msg):
    try:
        yield
    finally:
        print(msg)

def inner():
    with cleanup_context("inner cleanup"):
        print("inner running")

def middle():
    with cleanup_context("middle cleanup"):
        print("middle running")
        inner()

def outer():
    with cleanup_context("outer cleanup"):
        print("outer running")
        middle()

outer()

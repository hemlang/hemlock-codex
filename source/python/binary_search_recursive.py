def binary_search_rec(arr, target, low, high):
    if low > high:
        return None
    mid = low + (high - low) // 2
    if arr[mid] == target:
        return mid
    elif arr[mid] < target:
        return binary_search_rec(arr, target, mid + 1, high)
    else:
        return binary_search_rec(arr, target, low, mid - 1)

def binary_search(arr, target):
    return binary_search_rec(arr, target, 0, len(arr) - 1)

arr = [2, 5, 8, 12, 16, 23, 38, 56, 72, 91]

result1 = binary_search(arr, 23)
if result1 is not None:
    print(f"search 23: found at index {result1}")
else:
    print("search 23: not found")

result2 = binary_search(arr, 50)
if result2 is not None:
    print(f"search 50: found at index {result2}")
else:
    print("search 50: not found")

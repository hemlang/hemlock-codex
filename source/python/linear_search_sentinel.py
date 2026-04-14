def linear_search_sentinel(arr, target):
    n = len(arr)
    last = arr[n - 1]
    arr[n - 1] = target
    i = 0
    while arr[i] != target:
        i += 1
    arr[n - 1] = last
    if i < n - 1:
        return i
    if arr[n - 1] == target:
        return n - 1
    return None

arr = [2, 5, 8, 12, 16, 23, 38, 56, 72, 91]

result1 = linear_search_sentinel(arr, 23)
if result1 is not None:
    print(f"search 23: found at index {result1}")
else:
    print("search 23: not found")

result2 = linear_search_sentinel(arr, 50)
if result2 is not None:
    print(f"search 50: found at index {result2}")
else:
    print("search 50: not found")

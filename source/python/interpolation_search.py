def interpolation_search(arr, target):
    low = 0
    high = len(arr) - 1
    while low <= high and target >= arr[low] and target <= arr[high]:
        if low == high:
            if arr[low] == target:
                return low
            return None
        range_val = arr[high] - arr[low]
        pos = low + ((target - arr[low]) * (high - low)) // range_val
        if arr[pos] == target:
            return pos
        elif arr[pos] < target:
            low = pos + 1
        else:
            high = pos - 1
    return None

arr = [2, 5, 8, 12, 16, 23, 38, 56, 72, 91]

result1 = interpolation_search(arr, 23)
if result1 is not None:
    print(f"search 23: found at index {result1}")
else:
    print("search 23: not found")

result2 = interpolation_search(arr, 50)
if result2 is not None:
    print(f"search 50: found at index {result2}")
else:
    print("search 50: not found")

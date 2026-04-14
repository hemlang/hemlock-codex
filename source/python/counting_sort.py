def counting_sort(arr):
    n = len(arr)
    if n == 0:
        return arr
    max_val = max(arr)
    count = [0] * (max_val + 1)
    for x in arr:
        count[x] += 1
    idx = 0
    for i in range(max_val + 1):
        while count[i] > 0:
            arr[idx] = i
            idx += 1
            count[i] -= 1
    return arr

arr = [64, 34, 25, 12, 22, 11, 90, 1, 45, 78]
counting_sort(arr)
print(" ".join(str(x) for x in arr))

def quicksort(arr, low, high):
    if low < high:
        pivot = arr[high]
        i = low - 1
        for j in range(low, high):
            if arr[j] <= pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]
        arr[i + 1], arr[high] = arr[high], arr[i + 1]
        pi = i + 1
        quicksort(arr, low, pi - 1)
        quicksort(arr, pi + 1, high)

arr = [64, 34, 25, 12, 22, 11, 90, 1, 45, 78]
quicksort(arr, 0, len(arr) - 1)
print(" ".join(str(x) for x in arr))

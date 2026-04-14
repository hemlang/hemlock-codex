import threading

def merge(left, right):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result

def merge_sort(arr, result_holder):
    if len(arr) <= 1:
        result_holder.append(arr)
        return

    mid = len(arr) // 2
    left_result = []
    right_result = []

    left_thread = threading.Thread(target=merge_sort, args=(arr[:mid], left_result))
    right_thread = threading.Thread(target=merge_sort, args=(arr[mid:], right_result))

    left_thread.start()
    right_thread.start()
    left_thread.join()
    right_thread.join()

    result_holder.append(merge(left_result[0], right_result[0]))

arr = [38, 27, 43, 3, 9, 82, 10, 55]
result = []
merge_sort(arr, result)
print(f"sorted: {' '.join(str(x) for x in result[0])}")

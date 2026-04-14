def permutations(s):
    results = []
    chars = list(s)

    def permute(arr, start):
        if start == len(arr) - 1:
            results.append("".join(arr))
            return
        for i in range(start, len(arr)):
            arr[start], arr[i] = arr[i], arr[start]
            permute(arr, start + 1)
            arr[start], arr[i] = arr[i], arr[start]

    permute(chars, 0)
    return results

for p in permutations("abc"):
    print(p)

def two_sum(nums, target):
    seen = {}
    for i, x in enumerate(nums):
        complement = target - x
        if complement in seen:
            return [seen[complement], i]
        seen[x] = i
    return None

nums = [2, 7, 11, 15]
target = 9
result = two_sum(nums, target)
print(f"indices: {result[0]}, {result[1]}")

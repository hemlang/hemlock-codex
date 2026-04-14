// Binary Search (Iterative)
function binarySearch(arr, target) {
    let low = 0, high = arr.length - 1;
    while (low <= high) {
        const mid = low + Math.floor((high - low) / 2);
        if (arr[mid] === target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return null;
}

const arr = [2, 5, 8, 12, 16, 23, 38, 56, 72, 91];

const result1 = binarySearch(arr, 23);
if (result1 !== null) console.log(`search 23: found at index ${result1}`);
else console.log("search 23: not found");

const result2 = binarySearch(arr, 50);
if (result2 !== null) console.log(`search 50: found at index ${result2}`);
else console.log("search 50: not found");

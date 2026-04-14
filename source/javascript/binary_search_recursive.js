// Binary Search (Recursive)
function binarySearchRec(arr, target, low, high) {
    if (low > high) return null;
    const mid = low + Math.floor((high - low) / 2);
    if (arr[mid] === target) return mid;
    else if (arr[mid] < target) return binarySearchRec(arr, target, mid + 1, high);
    else return binarySearchRec(arr, target, low, mid - 1);
}

function binarySearch(arr, target) {
    return binarySearchRec(arr, target, 0, arr.length - 1);
}

const arr = [2, 5, 8, 12, 16, 23, 38, 56, 72, 91];

const result1 = binarySearch(arr, 23);
if (result1 !== null) console.log(`search 23: found at index ${result1}`);
else console.log("search 23: not found");

const result2 = binarySearch(arr, 50);
if (result2 !== null) console.log(`search 50: found at index ${result2}`);
else console.log("search 50: not found");

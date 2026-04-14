// Interpolation Search
function interpolationSearch(arr, target) {
    let low = 0, high = arr.length - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low === high) {
            if (arr[low] === target) return low;
            return null;
        }
        const range = arr[high] - arr[low];
        const pos = low + Math.floor((target - arr[low]) * (high - low) / range);
        if (arr[pos] === target) return pos;
        else if (arr[pos] < target) low = pos + 1;
        else high = pos - 1;
    }
    return null;
}

const arr = [2, 5, 8, 12, 16, 23, 38, 56, 72, 91];

const result1 = interpolationSearch(arr, 23);
if (result1 !== null) console.log(`search 23: found at index ${result1}`);
else console.log("search 23: not found");

const result2 = interpolationSearch(arr, 50);
if (result2 !== null) console.log(`search 50: found at index ${result2}`);
else console.log("search 50: not found");

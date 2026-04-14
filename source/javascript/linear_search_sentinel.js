// Linear Search with Sentinel
function linearSearchSentinel(arr, target) {
    const n = arr.length;
    const last = arr[n - 1];
    arr[n - 1] = target;

    let i = 0;
    while (arr[i] !== target) i++;

    arr[n - 1] = last;

    if (i < n - 1) return i;
    if (arr[n - 1] === target) return n - 1;
    return null;
}

const arr = [2, 5, 8, 12, 16, 23, 38, 56, 72, 91];

const result1 = linearSearchSentinel(arr, 23);
if (result1 !== null) console.log(`search 23: found at index ${result1}`);
else console.log("search 23: not found");

const result2 = linearSearchSentinel(arr, 50);
if (result2 !== null) console.log(`search 50: found at index ${result2}`);
else console.log("search 50: not found");

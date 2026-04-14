// Parallel Merge Sort using Promise.all
function merge(left, right) {
    const result = [];
    let i = 0, j = 0;
    while (i < left.length && j < right.length) {
        if (left[i] <= right[j]) result.push(left[i++]);
        else result.push(right[j++]);
    }
    while (i < left.length) result.push(left[i++]);
    while (j < right.length) result.push(right[j++]);
    return result;
}

async function mergeSort(arr) {
    if (arr.length <= 1) return arr;
    const mid = Math.floor(arr.length / 2);
    const [sortedLeft, sortedRight] = await Promise.all([
        mergeSort(arr.slice(0, mid)),
        mergeSort(arr.slice(mid))
    ]);
    return merge(sortedLeft, sortedRight);
}

async function main() {
    const arr = [38, 27, 43, 3, 9, 82, 10, 55];
    const sorted = await mergeSort(arr);
    console.log(`sorted: ${sorted.join(" ")}`);
}

main();

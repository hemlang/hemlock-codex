function countingSort(arr) {
    const n = arr.length;
    if (n === 0) return arr;

    let maxVal = arr[0];
    for (let i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    const count = new Array(maxVal + 1).fill(0);
    for (let i = 0; i < n; i++) count[arr[i]]++;

    let idx = 0;
    for (let i = 0; i <= maxVal; i++) {
        while (count[i] > 0) {
            arr[idx++] = i;
            count[i]--;
        }
    }
    return arr;
}

const arr = [64, 34, 25, 12, 22, 11, 90, 1, 45, 78];
countingSort(arr);
console.log(arr.join(" "));

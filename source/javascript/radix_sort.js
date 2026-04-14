function countingSortByDigit(arr, exp) {
    const n = arr.length;
    const output = new Array(n).fill(0);
    const count = new Array(10).fill(0);

    for (let i = 0; i < n; i++) {
        const digit = Math.floor(arr[i] / exp) % 10;
        count[digit]++;
    }
    for (let i = 1; i < 10; i++) count[i] += count[i - 1];
    for (let i = n - 1; i >= 0; i--) {
        const digit = Math.floor(arr[i] / exp) % 10;
        count[digit]--;
        output[count[digit]] = arr[i];
    }
    for (let i = 0; i < n; i++) arr[i] = output[i];
}

function radixSort(arr) {
    const n = arr.length;
    if (n === 0) return arr;

    let maxVal = arr[0];
    for (let i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    for (let exp = 1; Math.floor(maxVal / exp) > 0; exp *= 10) {
        countingSortByDigit(arr, exp);
    }
    return arr;
}

const arr = [64, 34, 25, 12, 22, 11, 90, 1, 45, 78];
radixSort(arr);
console.log(arr.join(" "));

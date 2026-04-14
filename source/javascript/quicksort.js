function quicksort(arr, low, high) {
    if (low < high) {
        const pivot = arr[high];
        let i = low - 1;
        for (let j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                const temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        const temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        const pi = i + 1;
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

const arr = [64, 34, 25, 12, 22, 11, 90, 1, 45, 78];
quicksort(arr, 0, arr.length - 1);
console.log(arr.join(" "));

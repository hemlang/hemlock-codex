// Array method chaining: map, filter, reduce
const nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

const result = nums
    .map(x => x * x)
    .filter(x => x > 20)
    .reduce((acc, x) => acc + x, 0);

console.log(`result: ${result}`);

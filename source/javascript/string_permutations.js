function permutations(s) {
    const results = [];
    const chars = s.split("");
    function permute(arr, start) {
        if (start === arr.length - 1) { results.push(arr.join("")); return; }
        for (let i = start; i < arr.length; i++) {
            [arr[start], arr[i]] = [arr[i], arr[start]];
            permute(arr, start + 1);
            [arr[start], arr[i]] = [arr[i], arr[start]];
        }
    }
    permute(chars, 0);
    return results;
}

const perms = permutations("abc");
for (const p of perms) console.log(p);

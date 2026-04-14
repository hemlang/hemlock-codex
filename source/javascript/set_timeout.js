// setTimeout equivalent using actual setTimeout
function main() {
    return new Promise(resolve => {
        let done = 0;
        const total = 3;
        function check() { if (++done === total) resolve(); }

        setTimeout(() => { console.log("fast (0.1s)"); check(); }, 100);
        setTimeout(() => { console.log("medium (0.2s)"); check(); }, 200);
        setTimeout(() => { console.log("slow (0.3s)"); check(); }, 300);

        console.log("all scheduled");
    }).then(() => console.log("all complete"));
}

main();

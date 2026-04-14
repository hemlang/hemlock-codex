// Error cleanup with defer-like pattern
let cleaned = false;

function cleanup() {
    cleaned = true;
    console.log("resource cleaned up");
}

function riskyOperation() {
    try {
        throw new Error("something went wrong");
    } finally {
        cleanup();
    }
}

function main() {
    try {
        riskyOperation();
    } catch (e) {
        console.log("error handled");
    }
}

main();

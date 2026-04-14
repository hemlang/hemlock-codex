// try/catch/finally
function riskyOperation(value) {
    try {
        console.log("try: starting");
        if (value < 0) throw "negative value";
        if (value === 0) throw "zero value";
        console.log(`try: success with ${value}`);
    } catch (e) {
        console.log(`catch: ${e}`);
    } finally {
        console.log("finally: cleanup");
    }
}

riskyOperation(42);
console.log("---");
riskyOperation(-1);
console.log("---");
riskyOperation(0);

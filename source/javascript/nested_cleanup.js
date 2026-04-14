// Nested cleanup (defer-like pattern via try/finally)
function inner() {
    try {
        console.log("inner running");
    } finally {
        console.log("inner cleanup");
    }
}

function middle() {
    try {
        console.log("middle running");
        inner();
    } finally {
        console.log("middle cleanup");
    }
}

function outer() {
    try {
        console.log("outer running");
        middle();
    } finally {
        console.log("outer cleanup");
    }
}

outer();

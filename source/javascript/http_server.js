// Simulated HTTP server using request/response objects
async function handleRequest(req) {
    let body = "", status = 200;
    if (req.path === "/") body = "Hello, World!";
    else if (req.path === "/about") body = "About Page";
    else { status = 404; body = "Not Found"; }
    return { status, body, method: req.method, path: req.path };
}

async function main() {
    const requests = [
        { method: "GET", path: "/" },
        { method: "GET", path: "/about" },
        { method: "GET", path: "/missing" }
    ];

    for (const req of requests) {
        const res = await handleRequest(req);
        console.log(`[simulated] ${res.method} ${res.path} -> ${res.status} ${res.body}`);
    }
}

main();

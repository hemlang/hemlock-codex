// Fetch API simulation (no network dependency)
function simulateFetch(url) {
    // Simulated response
    const raw = '{"name": "hemlock", "version": "2.0.0"}';
    return { status: 200, body: raw };
}

function handleResponse(response) {
    try {
        console.log(`status: ${response.status}`);
        const data = JSON.parse(response.body);
        console.log(`name: ${data.name}`);
        console.log(`version: ${data.version}`);
    } catch (e) {
        console.log(`error: ${e.message}`);
    }
}

const response = simulateFetch("https://api.example.com/data");
handleResponse(response);

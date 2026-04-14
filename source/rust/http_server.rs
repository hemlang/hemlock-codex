use std::sync::mpsc;
use std::thread;

struct Request { method: String, path: String }
struct Response { status: u32, body: String, method: String, path: String }

fn handle(req: Request) -> Response {
    let (status, body) = match req.path.as_str() {
        "/" => (200, "Hello, World!".to_string()),
        "/about" => (200, "About Page".to_string()),
        _ => (404, "Not Found".to_string()),
    };
    Response { status, body, method: req.method, path: req.path }
}

fn main() {
    let (req_tx, req_rx) = mpsc::channel::<Request>();
    let (res_tx, res_rx) = mpsc::channel::<Response>();

    // Server
    let server = thread::spawn(move || {
        for req in req_rx.into_iter().take(3) {
            res_tx.send(handle(req)).unwrap();
        }
    });

    // Client
    let client = thread::spawn(move || {
        let requests = vec![
            Request { method: "GET".to_string(), path: "/".to_string() },
            Request { method: "GET".to_string(), path: "/about".to_string() },
            Request { method: "GET".to_string(), path: "/missing".to_string() },
        ];
        for req in requests {
            req_tx.send(req).unwrap();
            let res = res_rx.recv().unwrap();
            println!("[simulated] {} {} -> {} {}", res.method, res.path, res.status, res.body);
        }
    });

    client.join().unwrap();
    server.join().unwrap();
}

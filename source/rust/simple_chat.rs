use std::sync::mpsc;
use std::thread;

fn main() {
    let (alice_tx, alice_rx) = mpsc::channel::<String>();
    let (bob_tx, bob_rx) = mpsc::channel::<String>();

    let alice_tx2 = alice_tx.clone();
    let bob_tx2 = bob_tx.clone();

    let alice = thread::spawn(move || {
        bob_tx.send("Hi Bob! How are you?".to_string()).unwrap();
        let msg = alice_rx.recv().unwrap();
        println!("Alice received: {}", msg);

        bob_tx.send("I'm working on a Hemlock project!".to_string()).unwrap();
        let msg = alice_rx.recv().unwrap();
        println!("Alice received: {}", msg);

        bob_tx.send("Thanks! Talk later.".to_string()).unwrap();
        let msg = alice_rx.recv().unwrap();
        println!("Alice received: {}", msg);
    });

    let bob = thread::spawn(move || {
        let msg = bob_rx.recv().unwrap();
        println!("Bob received: {}", msg);
        alice_tx2.send("Hey Alice! I'm great, you?".to_string()).unwrap();

        let msg = bob_rx.recv().unwrap();
        println!("Bob received: {}", msg);
        alice_tx2.send("That sounds awesome!".to_string()).unwrap();

        let msg = bob_rx.recv().unwrap();
        println!("Bob received: {}", msg);
        alice_tx2.send("Bye Alice!".to_string()).unwrap();
    });

    alice.join().unwrap();
    bob.join().unwrap();
    println!("Chat ended.");
}

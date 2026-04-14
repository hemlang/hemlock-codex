// Chat pattern: two users exchange messages
async function chat() {
    // Simulate the exchange with arrays
    const aliceMessages = [
        "Hi Bob! How are you?",
        "I'm working on a Hemlock project!",
        "Thanks! Talk later."
    ];
    const bobMessages = [
        "Hey Alice! I'm great, you?",
        "That sounds awesome!",
        "Bye Alice!"
    ];

    for (let i = 0; i < 3; i++) {
        // Alice sends
        const aliceSent = aliceMessages[i];
        // Bob receives and replies
        console.log(`Bob received: ${aliceSent}`);
        const bobSent = bobMessages[i];
        console.log(`Alice received: ${bobSent}`);
    }
    console.log("Chat ended.");
}

chat();

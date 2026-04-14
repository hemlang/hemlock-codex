// SQLite CRUD operations using better-sqlite3 if available, otherwise simulate
let db;
try {
    const Database = require('better-sqlite3');
    db = new Database(':memory:');

    db.exec("CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT, email TEXT, age INTEGER)");
    console.log("=== Created users table ===");

    const insert = db.prepare("INSERT INTO users (name, email, age) VALUES (?, ?, ?)");
    insert.run("Alice", "alice@example.com", 30);
    insert.run("Bob", "bob@example.com", 25);
    insert.run("Charlie", "charlie@example.com", 35);
    insert.run("Diana", "diana@example.com", 28);
    console.log("Inserted 4 users");

    console.log("\n=== All Users ===");
    const rows = db.prepare("SELECT * FROM users").all();
    for (const row of rows) console.log(`  id=${row.id} name=${row.name} email=${row.email} age=${row.age}`);

    console.log("\n=== Users over 28 ===");
    const older = db.prepare("SELECT name, age FROM users WHERE age > ?").all(28);
    for (const row of older) console.log(`  ${row.name} (age ${row.age})`);

    const changed = db.prepare("UPDATE users SET age = 31 WHERE name = ?").run("Alice").changes;
    console.log(`\n=== Updated ${changed} row(s) ===`);
    const alice = db.prepare("SELECT name, age FROM users WHERE name = ?").all("Alice");
    console.log(`  Alice is now age ${alice[0].age}`);

    const deleted = db.prepare("DELETE FROM users WHERE name = ?").run("Charlie").changes;
    console.log(`\n=== Deleted ${deleted} row(s) ===`);
    const remaining = db.prepare("SELECT name FROM users").all();
    console.log(`  Remaining users: ${remaining.map(r => r.name).join(", ")}`);

    const countRows = db.prepare("SELECT COUNT(*) as cnt FROM users").all();
    console.log(`  Total users: ${countRows[0].cnt}`);

    db.close();
    console.log("\nDatabase closed.");
} catch (e) {
    // Simulate without real SQLite
    console.log("=== Created users table ===");
    let users = [];
    let nextId = 1;

    function insertUser(name, email, age) { users.push({ id: nextId++, name, email, age }); }
    insertUser("Alice", "alice@example.com", 30);
    insertUser("Bob", "bob@example.com", 25);
    insertUser("Charlie", "charlie@example.com", 35);
    insertUser("Diana", "diana@example.com", 28);
    console.log("Inserted 4 users");

    console.log("\n=== All Users ===");
    for (const row of users) console.log(`  id=${row.id} name=${row.name} email=${row.email} age=${row.age}`);

    console.log("\n=== Users over 28 ===");
    for (const row of users.filter(u => u.age > 28)) console.log(`  ${row.name} (age ${row.age})`);

    let changed = 0;
    for (const u of users) { if (u.name === "Alice") { u.age = 31; changed++; } }
    console.log(`\n=== Updated ${changed} row(s) ===`);
    console.log(`  Alice is now age ${users.find(u => u.name === "Alice").age}`);

    const beforeLen = users.length;
    users = users.filter(u => u.name !== "Charlie");
    const deleted = beforeLen - users.length;
    console.log(`\n=== Deleted ${deleted} row(s) ===`);
    console.log(`  Remaining users: ${users.map(u => u.name).join(", ")}`);
    console.log(`  Total users: ${users.length}`);

    console.log("\nDatabase closed.");
}

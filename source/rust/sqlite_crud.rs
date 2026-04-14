// SQLite simulation without external crates
use std::collections::HashMap;

#[derive(Clone, Debug)]
struct Row {
    id: i32,
    name: String,
    email: String,
    age: i32,
}

struct Table {
    rows: Vec<Row>,
    next_id: i32,
}

impl Table {
    fn new() -> Self { Table { rows: Vec::new(), next_id: 1 } }

    fn insert(&mut self, name: &str, email: &str, age: i32) {
        self.rows.push(Row { id: self.next_id, name: name.to_string(), email: email.to_string(), age });
        self.next_id += 1;
    }

    fn select_all(&self) -> Vec<&Row> { self.rows.iter().collect() }

    fn select_where_age_gt(&self, threshold: i32) -> Vec<&Row> {
        self.rows.iter().filter(|r| r.age > threshold).collect()
    }

    fn select_by_name(&self, name: &str) -> Vec<&Row> {
        self.rows.iter().filter(|r| r.name == name).collect()
    }

    fn update_age(&mut self, name: &str, new_age: i32) -> usize {
        let mut count = 0;
        for row in self.rows.iter_mut() {
            if row.name == name { row.age = new_age; count += 1; }
        }
        count
    }

    fn delete_by_name(&mut self, name: &str) -> usize {
        let before = self.rows.len();
        self.rows.retain(|r| r.name != name);
        before - self.rows.len()
    }
}

fn main() {
    let mut db = Table::new();
    println!("=== Created users table ===");

    db.insert("Alice", "alice@example.com", 30);
    db.insert("Bob", "bob@example.com", 25);
    db.insert("Charlie", "charlie@example.com", 35);
    db.insert("Diana", "diana@example.com", 28);
    println!("Inserted 4 users");

    println!("\n=== All Users ===");
    for row in db.select_all() {
        println!("  id={} name={} email={} age={}", row.id, row.name, row.email, row.age);
    }

    println!("\n=== Users over 28 ===");
    for row in db.select_where_age_gt(28) {
        println!("  {} (age {})", row.name, row.age);
    }

    let changed = db.update_age("Alice", 31);
    println!("\n=== Updated {} row(s) ===", changed);
    let alice_rows = db.select_by_name("Alice");
    println!("  Alice is now age {}", alice_rows[0].age);

    let deleted = db.delete_by_name("Charlie");
    println!("\n=== Deleted {} row(s) ===", deleted);
    let names: Vec<&str> = db.select_all().iter().map(|r| r.name.as_str()).collect();
    println!("  Remaining users: {}", names.join(", "));

    let count = db.select_all().len();
    println!("  Total users: {}", count);

    println!("\nDatabase closed.");
}

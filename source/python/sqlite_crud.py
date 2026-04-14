import sqlite3

db = sqlite3.connect(":memory:")
db.row_factory = sqlite3.Row

db.execute("CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT, email TEXT, age INTEGER)")
print("=== Created users table ===")

db.execute("INSERT INTO users (name, email, age) VALUES (?, ?, ?)", ("Alice", "alice@example.com", 30))
db.execute("INSERT INTO users (name, email, age) VALUES (?, ?, ?)", ("Bob", "bob@example.com", 25))
db.execute("INSERT INTO users (name, email, age) VALUES (?, ?, ?)", ("Charlie", "charlie@example.com", 35))
db.execute("INSERT INTO users (name, email, age) VALUES (?, ?, ?)", ("Diana", "diana@example.com", 28))
db.commit()
print("Inserted 4 users")

print("\n=== All Users ===")
for row in db.execute("SELECT * FROM users"):
    print(f"  id={row['id']} name={row['name']} email={row['email']} age={row['age']}")

print("\n=== Users over 28 ===")
for row in db.execute("SELECT name, age FROM users WHERE age > ?", (28,)):
    print(f"  {row['name']} (age {row['age']})")

cursor = db.execute("UPDATE users SET age = 31 WHERE name = ?", ("Alice",))
db.commit()
changed = cursor.rowcount
print(f"\n=== Updated {changed} row(s) ===")
alice = db.execute("SELECT name, age FROM users WHERE name = ?", ("Alice",)).fetchone()
print(f"  Alice is now age {alice['age']}")

cursor = db.execute("DELETE FROM users WHERE name = ?", ("Charlie",))
db.commit()
deleted = cursor.rowcount
print(f"\n=== Deleted {deleted} row(s) ===")
remaining = db.execute("SELECT name FROM users").fetchall()
names = [r["name"] for r in remaining]
print(f"  Remaining users: {', '.join(names)}")

count_row = db.execute("SELECT COUNT(*) as cnt FROM users").fetchone()
print(f"  Total users: {count_row['cnt']}")

db.close()
print("\nDatabase closed.")

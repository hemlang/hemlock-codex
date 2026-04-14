package main

import (
	"database/sql"
	"fmt"
	"strings"

	_ "github.com/mattn/go-sqlite3"
)

func main() {
	db, err := sql.Open("sqlite3", ":memory:")
	if err != nil {
		fmt.Println("open error:", err)
		return
	}
	defer db.Close()

	_, err = db.Exec("CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT, email TEXT, age INTEGER)")
	if err != nil {
		fmt.Println("create error:", err)
		return
	}
	fmt.Println("=== Created users table ===")

	users := [][]interface{}{
		{"Alice", "alice@example.com", 30},
		{"Bob", "bob@example.com", 25},
		{"Charlie", "charlie@example.com", 35},
		{"Diana", "diana@example.com", 28},
	}
	for _, u := range users {
		db.Exec("INSERT INTO users (name, email, age) VALUES (?, ?, ?)", u[0], u[1], u[2])
	}
	fmt.Println("Inserted 4 users")

	fmt.Println("\n=== All Users ===")
	rows, _ := db.Query("SELECT * FROM users")
	defer rows.Close()
	for rows.Next() {
		var id, age int
		var name, email string
		rows.Scan(&id, &name, &email, &age)
		fmt.Printf("  id=%d name=%s email=%s age=%d\n", id, name, email, age)
	}

	fmt.Println("\n=== Users over 28 ===")
	rows2, _ := db.Query("SELECT name, age FROM users WHERE age > ?", 28)
	defer rows2.Close()
	for rows2.Next() {
		var name string
		var age int
		rows2.Scan(&name, &age)
		fmt.Printf("  %s (age %d)\n", name, age)
	}

	result, _ := db.Exec("UPDATE users SET age = 31 WHERE name = ?", "Alice")
	changed, _ := result.RowsAffected()
	fmt.Printf("\n=== Updated %d row(s) ===\n", changed)
	row := db.QueryRow("SELECT name, age FROM users WHERE name = ?", "Alice")
	var aliceName string
	var aliceAge int
	row.Scan(&aliceName, &aliceAge)
	fmt.Printf("  Alice is now age %d\n", aliceAge)

	result2, _ := db.Exec("DELETE FROM users WHERE name = ?", "Charlie")
	deleted, _ := result2.RowsAffected()
	fmt.Printf("\n=== Deleted %d row(s) ===\n", deleted)
	rows3, _ := db.Query("SELECT name FROM users")
	defer rows3.Close()
	var names []string
	for rows3.Next() {
		var name string
		rows3.Scan(&name)
		names = append(names, name)
	}
	fmt.Printf("  Remaining users: %s\n", strings.Join(names, ", "))

	var cnt int
	db.QueryRow("SELECT COUNT(*) as cnt FROM users").Scan(&cnt)
	fmt.Printf("  Total users: %d\n", cnt)

	fmt.Println("\nDatabase closed.")
}

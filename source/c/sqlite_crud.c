// gcc -o sqlite_crud sqlite_crud.c -lsqlite3
// Requires: libsqlite3-dev
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

sqlite3 *db;

void exec_sql(const char *sql) {
    char *err = NULL;
    sqlite3_exec(db, sql, NULL, NULL, &err);
    if (err) { fprintf(stderr, "SQL error: %s\n", err); sqlite3_free(err); }
}

int main(void) {
    sqlite3_open(":memory:", &db);

    exec_sql("CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT, email TEXT, age INTEGER)");
    printf("=== Created users table ===\n");

    sqlite3_stmt *stmt;
    const char *insert_sql = "INSERT INTO users (name, email, age) VALUES (?, ?, ?)";

    typedef struct { const char *name; const char *email; int age; } UserRow;
    UserRow inserts[] = {
        {"Alice", "alice@example.com", 30},
        {"Bob", "bob@example.com", 25},
        {"Charlie", "charlie@example.com", 35},
        {"Diana", "diana@example.com", 28}
    };
    for (int i = 0; i < 4; i++) {
        sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
        sqlite3_bind_text(stmt, 1, inserts[i].name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, inserts[i].email, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, inserts[i].age);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    printf("Inserted 4 users\n");

    printf("\n=== All Users ===\n");
    sqlite3_prepare_v2(db, "SELECT * FROM users", -1, &stmt, NULL);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("  id=%d name=%s email=%s age=%d\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2),
               sqlite3_column_int(stmt, 3));
    }
    sqlite3_finalize(stmt);

    printf("\n=== Users over 28 ===\n");
    sqlite3_prepare_v2(db, "SELECT name, age FROM users WHERE age > ?", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, 28);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("  %s (age %d)\n", sqlite3_column_text(stmt, 0), sqlite3_column_int(stmt, 1));
    }
    sqlite3_finalize(stmt);

    sqlite3_prepare_v2(db, "UPDATE users SET age = 31 WHERE name = ?", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, "Alice", -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    int changed = sqlite3_changes(db);
    printf("\n=== Updated %d row(s) ===\n", changed);

    sqlite3_prepare_v2(db, "SELECT name, age FROM users WHERE name = ?", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, "Alice", -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    printf("  Alice is now age %d\n", sqlite3_column_int(stmt, 1));
    sqlite3_finalize(stmt);

    sqlite3_prepare_v2(db, "DELETE FROM users WHERE name = ?", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, "Charlie", -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    int deleted = sqlite3_changes(db);
    printf("\n=== Deleted %d row(s) ===\n", deleted);

    sqlite3_prepare_v2(db, "SELECT name FROM users", -1, &stmt, NULL);
    int first = 1;
    printf("  Remaining users: ");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (!first) printf(", ");
        printf("%s", sqlite3_column_text(stmt, 0));
        first = 0;
    }
    printf("\n");
    sqlite3_finalize(stmt);

    sqlite3_prepare_v2(db, "SELECT COUNT(*) as cnt FROM users", -1, &stmt, NULL);
    sqlite3_step(stmt);
    printf("  Total users: %d\n", sqlite3_column_int(stmt, 0));
    sqlite3_finalize(stmt);

    sqlite3_close(db);
    printf("\nDatabase closed.\n");
    return 0;
}

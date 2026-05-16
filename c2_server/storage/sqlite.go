package main

import (
	"database/sql"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

var db *sql.DB

func InitDB() {
	var err error
	db, err = sql.Open("sqlite3", "./clients.db")
	if err != nil {
		log.Fatal(err)
	}
	db.Exec(`CREATE TABLE IF NOT EXISTS clients (
        id TEXT PRIMARY KEY,
        os TEXT,
        arch TEXT,
        av TEXT,
        is_admin INTEGER,
        last_seen INTEGER
    )`)
}

func SaveClient(c ClientInfo) {
	stmt, _ := db.Prepare(`INSERT OR REPLACE INTO clients (id, os, arch, av, is_admin, last_seen) VALUES (?,?,?,?,?,?)`)
	stmt.Exec(c.ID, c.OS, c.Arch, c.AV, c.IsAdmin, c.LastSeen)
}

func GetAllClients() []ClientInfo {
	rows, _ := db.Query("SELECT id, os, arch, av, is_admin, last_seen FROM clients")
	var clients []ClientInfo
	for rows.Next() {
		var c ClientInfo
		rows.Scan(&c.ID, &c.OS, &c.Arch, &c.AV, &c.IsAdmin, &c.LastSeen)
		clients = append(clients, c)
	}
	return clients
}

package main

import (
	"encoding/json"
	"net/http"
	"time"
)

type Client struct {
	ID       string `json:"id"`
	OS       string `json:"os"`
	Arch     string `json:"arch"`
	LastSeen int64  `json:"last_seen"`
}

var clients = map[string]Client{}

func registerHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
		return
	}
	var c Client
	json.NewDecoder(r.Body).Decode(&c)
	c.LastSeen = time.Now().Unix()
	clients[c.ID] = c
	w.WriteHeader(http.StatusOK)
	json.NewEncoder(w).Encode(map[string]string{"status": "ok"})
}

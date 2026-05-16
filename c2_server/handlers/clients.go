package main

import (
	"encoding/json"
	"net/http"
)

func clientsHandler(w http.ResponseWriter, r *http.Request) {
	clients := GetAllClients()
	json.NewEncoder(w).Encode(clients)
}

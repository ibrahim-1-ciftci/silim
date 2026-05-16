package main

import (
	"encoding/json"
	"net/http"
	"sync"
)

var cmdQueue = struct {
	sync.RWMutex
	m map[string][]string
}{m: make(map[string][]string)}

func pollHandler(w http.ResponseWriter, r *http.Request) {
	id := r.URL.Query().Get("id")
	cmdQueue.RLock()
	cmds := cmdQueue.m[id]
	delete(cmdQueue.m, id)
	cmdQueue.RUnlock()
	json.NewEncoder(w).Encode(cmds)
}

func sendCmdHandler(w http.ResponseWriter, r *http.Request) {
	var req struct {
		ClientID string `json:"client_id"`
		Command  string `json:"command"`
	}
	json.NewDecoder(r.Body).Decode(&req)
	cmdQueue.Lock()
	cmdQueue.m[req.ClientID] = append(cmdQueue.m[req.ClientID], req.Command)
	cmdQueue.Unlock()
	w.WriteHeader(http.StatusOK)
}

package main

import (
	"encoding/json"
	"io/ioutil"
	"net/http"
	"time"
)

func aiReportHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
		return
	}
	body, _ := ioutil.ReadAll(r.Body)
	var report map[string]interface{}
	json.Unmarshal(body, &report)
	report["received_at"] = time.Now().Unix()
	// Save to file or DB
	go func() {
		// Optionally broadcast to GUI via WebSocket
	}()
	w.WriteHeader(http.StatusOK)
}

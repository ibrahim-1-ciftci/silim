package main

import (
	"crypto/sha256"
	"encoding/hex"
	"time"
)

var dgaSeed = "SUPER_SECRET_SEED_2025"

func GenerateDomain() string {
	hour := time.Now().Unix() / 3600
	h := sha256.Sum256([]byte(dgaSeed + string(hour)))
	return hex.EncodeToString(h[:8]) + ".ddns.net"
}

from cryptography.fernet import Fernet
import json

key = Fernet.generate_key()
cipher = Fernet(key)
data = {"c2_url": "https://c2.example.com", "dga_seed": "SUPER_SECRET"}
enc = cipher.encrypt(json.dumps(data).encode())
with open("config.bin", "wb") as f:
    f.write(enc)
print(f"Key: {key.decode()}")
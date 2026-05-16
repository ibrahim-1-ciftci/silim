import hashlib, time

def dga(seed, interval=3600):
    t = int(time.time() / interval)
    h = hashlib.sha256(f"{seed}{t}".encode()).hexdigest()
    return f"{h[:12]}.ddns.net"

if __name__ == "__main__":
    print(dga("SUPER_SECRET"))
import platform, psutil, uuid, hashlib

def get_fingerprint():
    data = f"{platform.node()}{platform.processor()}{uuid.getnode()}{psutil.disk_usage('/').total}"
    return hashlib.sha256(data.encode()).hexdigest()
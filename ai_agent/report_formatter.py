import json, time

def format_report(client_id, threat_level, behaviors):
    return json.dumps({
        "client_id": client_id,
        "timestamp": time.time(),
        "threat_level": threat_level,
        "behaviors": behaviors
    })
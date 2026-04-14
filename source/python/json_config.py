import json

defaults = {
    "host": "localhost",
    "port": 8080,
    "debug": False,
    "log_level": "info",
    "max_connections": 100,
    "timeout": 30,
}

user_config_str = '{"port": 3000, "debug": true, "log_level": "debug"}'
user_config = json.loads(user_config_str)

def merge_config(base, overrides):
    result = dict(base)
    for key in overrides:
        if key in result:
            result[key] = overrides[key]
    return result

final_config = merge_config(defaults, user_config)

def pretty(obj):
    return json.dumps(obj, indent=2)

print("=== Default Config ===")
print(pretty(defaults))
print("=== User Overrides ===")
print(pretty(user_config))
print("=== Final Config ===")
print(pretty(final_config))

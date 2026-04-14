import json

json_str = '{"users": [{"name": "Alice", "age": 30, "active": true}, {"name": "Bob", "age": 25, "active": false}, {"name": "Charlie", "age": 35, "active": true}]}'

data = json.loads(json_str)
users = data["users"]

active = [u for u in users if u["active"]]
names = [u["name"] for u in active]

result = {"active_names": names, "count": len(names)}
print(json.dumps(result))

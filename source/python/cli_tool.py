tool_name = "hemlock-tool"
version = "1.0.0"

config = {
    "verbose": False,
    "output": "stdout",
    "format": "text",
    "count": 10,
}

def parse_option(key, value, cfg):
    if key in ("--verbose", "-v"):
        cfg["verbose"] = True
    elif key in ("--output", "-o"):
        cfg["output"] = value
    elif key in ("--format", "-f"):
        cfg["format"] = value
    elif key in ("--count", "-n"):
        cfg["count"] = int(value)
    return cfg

simulated_args = [
    ("--verbose", ""),
    ("--output", "result.txt"),
    ("--format", "json"),
    ("--count", "25"),
]

for key, val in simulated_args:
    config = parse_option(key, val, config)

print(f"{tool_name} v{version}")
print("Parsed configuration:")
print(f"  verbose: {str(config['verbose']).lower()}")
print(f"  output:  {config['output']}")
print(f"  format:  {config['format']}")
print(f"  count:   {config['count']}")
print("Ready to process.")

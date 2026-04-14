// JSON config loader with defaults and override
const defaults = {
    host: "localhost", port: 8080, debug: false,
    log_level: "info", max_connections: 100, timeout: 30
};

const userConfigStr = '{"port": 3000, "debug": true, "log_level": "debug"}';
const userConfig = JSON.parse(userConfigStr);

function mergeConfig(base, overrides) {
    const result = { ...base };
    for (const key of Object.keys(overrides)) {
        if (overrides[key] != null) result[key] = overrides[key];
    }
    return result;
}

const finalConfig = mergeConfig(defaults, userConfig);

function pretty(obj) {
    return JSON.stringify(obj, null, 2);
}

console.log("=== Default Config ===");
console.log(pretty(defaults));
console.log("=== User Overrides ===");
console.log(pretty(userConfig));
console.log("=== Final Config ===");
console.log(pretty(finalConfig));

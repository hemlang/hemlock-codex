// Object spread operator
const defaults = { host: "localhost", port: 8080, debug: false };
const userConfig = { port: 3000, debug: true };

const config = { ...defaults, ...userConfig, name: "myapp" };

console.log(`host: ${config.host}`);
console.log(`port: ${config.port}`);
console.log(`debug: ${config.debug}`);
console.log(`name: ${config.name}`);

const updated = { ...config, port: 9090 };
console.log(`updated port: ${updated.port}`);
console.log(`original port: ${config.port}`);

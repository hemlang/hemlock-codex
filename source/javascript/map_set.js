// Map and Set
const map = new Map();
map.set("name", "hemlock");
map.set("version", "2.0");
map.set("type", "language");

console.log(`has name: ${map.has("name")}`);
console.log(`name: ${map.get("name")}`);

map.delete("type");
console.log(`has type: ${map.has("type")}`);

const keys = [...map.keys()].sort();
console.log(`keys: ${keys.join(", ")}`);

const s = new Set();
s.add("apple");
s.add("banana");
s.add("apple"); // duplicate ignored

console.log(`set size: ${s.size}`);
console.log(`has apple: ${s.has("apple")}`);

const vals = [...s.values()].sort();
console.log(`values: ${vals.join(", ")}`);

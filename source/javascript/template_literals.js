// Template literals
const name = "World";
const a = 10, b = 20;

console.log(`Hello, ${name}!`);
console.log(`${a} + ${b} = ${a + b}`);
console.log(`Is ${a} > ${b}? ${a > b}`);

const items = ["apple", "banana", "cherry"];
console.log(`Items: ${items.join(", ")}`);
console.log(`Upper: ${"hemlock".toUpperCase()}`);

const user = { name: "Alice", age: 30 };
console.log(`User: ${user.name}, Age: ${user.age}`);

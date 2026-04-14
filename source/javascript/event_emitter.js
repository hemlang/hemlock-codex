// EventEmitter pattern using Node.js built-in events
const EventEmitter = require('events');

const emitter = new EventEmitter();

emitter.on('data', (msg) => console.log(`received: ${msg}`));

emitter.emit('data', 'hello');
emitter.emit('data', 'world');
emitter.emit('data', 'hemlock');
emitter.emit('done', null);

console.log("all events processed");

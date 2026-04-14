// Manual reference counting simulation
function rcNew(data) {
    const obj = { refcount: 1, data };
    console.log(`created obj(data=${data}, refcount=1)`);
    return obj;
}

function rcRetain(obj) {
    obj.refcount++;
    console.log(`retain obj(data=${obj.data}, refcount=${obj.refcount})`);
    return obj;
}

function rcRelease(obj) {
    obj.refcount--;
    if (obj.refcount === 0) {
        console.log(`release obj(data=${obj.data}, refcount=0) -> freed`);
        return null;
    }
    console.log(`release obj(data=${obj.data}, refcount=${obj.refcount})`);
    return obj;
}

console.log("--- create object ---");
let a = rcNew(42);
console.log("--- share with b ---");
let b = rcRetain(a);
console.log("--- share with c ---");
let c = rcRetain(a);
console.log(`data: ${a.data}, refcount: ${a.refcount}`);
console.log("--- release a ---");
a = rcRelease(a);
console.log("--- release b ---");
b = rcRelease(b);
console.log("--- release c (last ref, should free) ---");
c = rcRelease(c);

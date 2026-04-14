// SoA layout with Float64Arrays (parallel arrays for x, y, z coordinates)
const COUNT = 5;
const xs = new Float64Array(COUNT);
const ys = new Float64Array(COUNT);
const zs = new Float64Array(COUNT);

function setPoint(i, x, y, z) { xs[i] = x; ys[i] = y; zs[i] = z; }
function getX(i) { return xs[i]; }
function getY(i) { return ys[i]; }
function getZ(i) { return zs[i]; }
function distance(i) { return Math.sqrt(xs[i] ** 2 + ys[i] ** 2 + zs[i] ** 2); }

setPoint(0, 1.0, 0.0, 0.0);
setPoint(1, 0.0, 2.0, 0.0);
setPoint(2, 0.0, 0.0, 3.0);
setPoint(3, 1.0, 1.0, 1.0);
setPoint(4, 3.0, 4.0, 0.0);

for (let i = 0; i < COUNT; i++) {
    const x = getX(i), y = getY(i), z = getZ(i), d = distance(i);
    console.log(`point ${i}: (${x}, ${y}, ${z}) distance = ${d}`);
}
console.log("all arrays freed");

// Base64 encoder/decoder from scratch (no stdlib)
const chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

function b64Encode(input) {
    const bytes = Buffer.from(input, 'utf8');
    let result = "";
    let i = 0;
    while (i < bytes.length) {
        const b0 = bytes[i];
        const b1 = i + 1 < bytes.length ? bytes[i + 1] : 0;
        const b2 = i + 2 < bytes.length ? bytes[i + 2] : 0;
        const pad = i + 1 >= bytes.length ? 2 : i + 2 >= bytes.length ? 1 : 0;

        const idx0 = (b0 >> 2) & 63;
        const idx1 = ((b0 & 3) << 4) | ((b1 >> 4) & 15);
        const idx2 = ((b1 & 15) << 2) | ((b2 >> 6) & 3);
        const idx3 = b2 & 63;

        result += chars[idx0] + chars[idx1];
        if (pad === 2) result += "==";
        else if (pad === 1) result += chars[idx2] + "=";
        else result += chars[idx2] + chars[idx3];
        i += 3;
    }
    return result;
}

function b64CharIndex(c) { return chars.indexOf(c); }

function b64Decode(input) {
    const result = [];
    let i = 0;
    while (i < input.length) {
        const c0 = b64CharIndex(input[i]);
        const c1 = b64CharIndex(input[i + 1]);
        const c2 = input[i + 2] !== '=' ? b64CharIndex(input[i + 2]) : -1;
        const c3 = input[i + 3] !== '=' ? b64CharIndex(input[i + 3]) : -1;

        result.push(((c0 << 2) | ((c1 >> 4) & 3)) & 255);
        if (c2 >= 0) result.push((((c1 & 15) << 4) | ((c2 >> 2) & 15)) & 255);
        if (c3 >= 0) result.push((((c2 & 3) << 6) | c3) & 255);
        i += 4;
    }
    return Buffer.from(result).toString('utf8');
}

const original = "Hello, World!";
const encoded = b64Encode(original);
console.log(`original: ${original}`);
console.log(`encoded:  ${encoded}`);

const expected = "SGVsbG8sIFdvcmxkIQ==";
if (encoded === expected) console.log("encoding: correct");
else console.log(`encoding: mismatch (expected ${expected})`);

const decoded = b64Decode(encoded);
console.log(`decoded:  ${decoded}`);
if (decoded === original) console.log("round-trip: ok");
else console.log("round-trip: FAILED");

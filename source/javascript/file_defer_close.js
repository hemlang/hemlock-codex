// File defer close - write, read back, verify
const fs = require('fs');

function main() {
    const path = '/tmp/js_defer_test.txt';
    fs.writeFileSync(path, 'hello from defer');
    try {
        const fd = fs.openSync(path, 'r');
        try {
            const contents = fs.readFileSync(fd, 'utf8');
            if (contents === 'hello from defer') {
                console.log('wrote and read back successfully');
            }
        } finally {
            fs.closeSync(fd);
        }
    } finally {
        fs.unlinkSync(path);
    }
}

main();

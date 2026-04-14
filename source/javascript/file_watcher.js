// File watcher: write a file, check for changes, detect modification
const fs = require('fs');

const watchPath = '/tmp/js_watch_test.txt';

fs.writeFileSync(watchPath, 'initial content');
const t1 = Date.now();
console.log(`[watcher] monitoring: ${watchPath}`);
console.log(`[watcher] initial write at t=${t1}`);

const initial = fs.readFileSync(watchPath, 'utf8');
console.log(`[watcher] initial content: ${initial}`);

fs.writeFileSync(watchPath, 'modified content');
const t2 = Date.now();
console.log(`[watcher] file modified at t=${t2}`);

const content = fs.readFileSync(watchPath, 'utf8');
if (content === 'modified content') {
    console.log('[watcher] file change detected');
    console.log(`[watcher] new content: ${content}`);
} else {
    console.log('[watcher] no change detected');
}

if (t2 > t1) console.log('[watcher] modification time advanced');

fs.unlinkSync(watchPath);
console.log('[watcher] done');

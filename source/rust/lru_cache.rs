use std::collections::HashMap;

struct LRUCache {
    capacity: usize,
    map: HashMap<i32, i32>,
    order: Vec<i32>, // front = most recent
}

impl LRUCache {
    fn new(capacity: usize) -> Self {
        LRUCache { capacity, map: HashMap::new(), order: Vec::new() }
    }

    fn get(&mut self, key: i32) -> Option<i32> {
        if let Some(&val) = self.map.get(&key) {
            self.order.retain(|&k| k != key);
            self.order.insert(0, key);
            println!("get({}) -> {} (hit)", key, val);
            Some(val)
        } else {
            println!("get({}) -> miss", key);
            None
        }
    }

    fn put(&mut self, key: i32, val: i32) {
        if self.map.contains_key(&key) {
            self.map.insert(key, val);
            self.order.retain(|&k| k != key);
            self.order.insert(0, key);
            println!("put({}, {}) -> updated", key, val);
        } else {
            self.map.insert(key, val);
            self.order.insert(0, key);
            if self.order.len() > self.capacity {
                let evicted = self.order.pop().unwrap();
                self.map.remove(&evicted);
                println!("put({}, {}) -> added, evicted key {}", key, val, evicted);
            } else {
                println!("put({}, {}) -> added", key, val);
            }
        }
    }
}

fn main() {
    let mut cache = LRUCache::new(3);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.get(2);
    cache.put(4, 40);
    cache.get(1);
    cache.get(3);
    cache.get(4);
}

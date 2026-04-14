from collections import OrderedDict

class LRUCache:
    def __init__(self, capacity):
        self.capacity = capacity
        self.cache = OrderedDict()

    def get(self, key):
        skey = str(key)
        if skey in self.cache:
            self.cache.move_to_end(skey, last=False)
            val = self.cache[skey]
            print(f"get({key}) -> {val} (hit)")
            return val
        print(f"get({key}) -> miss")
        return None

    def put(self, key, val):
        skey = str(key)
        if skey in self.cache:
            self.cache[skey] = val
            self.cache.move_to_end(skey, last=False)
            print(f"put({key}, {val}) -> updated")
        else:
            self.cache[skey] = val
            self.cache.move_to_end(skey, last=False)
            if len(self.cache) > self.capacity:
                evict_key, _ = self.cache.popitem(last=True)
                print(f"put({key}, {val}) -> added, evicted key {evict_key}")
            else:
                print(f"put({key}, {val}) -> added")

cache = LRUCache(3)
cache.put(1, 10)
cache.put(2, 20)
cache.put(3, 30)
cache.get(2)
cache.put(4, 40)
cache.get(1)
cache.get(3)
cache.get(4)

// Hash Table Implementation

using namespace std;

// Each bucket is a list of key-value pairs
    struct KeyValue {
        K key;
        V value;
        KeyValue(const K& k, const V& v) : key(k), value(v) {}
    };

template<typename K, typename V>
class HashTable {
private:
    vector<list<KeyValue>> buckets;
    size_t bucket_count;
    size_t size_count;
    
    // Simple hash function
    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % bucket_count;
    }
    
    // Load factor threshold for resizing
    static constexpr double MAX_LOAD_FACTOR = 0.75;
    
    // Resize when load factor gets too high
    void resize() {
        if ((double)size_count / bucket_count < MAX_LOAD_FACTOR) {
            return;
        }
        
        vector<list<KeyValue>> old_buckets = std::move(buckets);
        bucket_count *= 2;
        buckets = vector<list<KeyValue>>(bucket_count);
        size_count = 0;
        
        // Rehash all elements
        for (auto& bucket : old_buckets) {
            for (auto& kv : bucket) {
                insert(kv.key, kv.value);
            }
        }
    }

public:
    // Constructor
    HashTable(size_t initial_size = 8) 
        : bucket_count(initial_size), size_count(0) {
        buckets.resize(bucket_count);
    }
    
    // Insert key-value pair
    void insert(const K& key, const V& value) {
        size_t index = hash(key);
        
        // Check if key already exists
        for (auto& kv : buckets[index]) {
            if (kv.key == key) {
                kv.value = value;  // Update existing
                return;
            }
        }
        
        // Add new key-value pair
        buckets[index].emplace_back(key, value);
        size_count++;
        
        // Resize if needed
        resize();
    }
    
    // Get value by key
    V* get(const K& key) {
        size_t index = hash(key);
        
        for (auto& kv : buckets[index]) {
            if (kv.key == key) {
                return &kv.value;
            }
        }
        return nullptr;  // Key not found
    }
    
    // Check if key exists
    bool contains(const K& key) const {
        size_t index = hash(key);
        
        for (const auto& kv : buckets[index]) {
            if (kv.key == key) {
                return true;
            }
        }
        return false;
    }
    
    // Remove key-value pair
    bool remove(const K& key) {
        size_t index = hash(key);
        
        auto& bucket = buckets[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                size_count--;
                return true;
            }
        }
        return false;  // Key not found
    }
    
    // Get current size
    size_t size() const {
        return size_count;
    }
    
    // Check if empty
    bool empty() const {
        return size_count == 0;
    }
    
    // Get load factor
    double load_factor() const {
        return (double)size_count / bucket_count;
    }
    
};
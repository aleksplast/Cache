#ifndef LFU_HPP
#define LFU_HPP

#include <iterator>
#include <unordered_map>
#include <list>
#include <iostream>

namespace lfu {

template <typename page_t, typename key_t>
class lfu_cache {
    struct lfu_elem;

public:
    using list_iter = typename std::list<lfu_elem>::iterator;
    using hash_iter = typename std::unordered_map<key_t, list_iter>::iterator;

private:

    size_t capacity;
    int64_t total_hits = 0;
    bool full = false;

    struct lfu_elem {
        page_t page;
        key_t key;
        size_t frequency;

        lfu_elem(key_t key) : key(key) {};
    };

    std::unordered_map<key_t, list_iter> hash;
    std::list<lfu_elem> cache;

public:
    lfu_cache(size_t capacity) : capacity(capacity) {};

    bool lookup_update(key_t key) {
        auto hit = hash.find(key);

        if (hit == hash.end()) {
            add_new_elem(key);
            return false;
        }
        else {
            handle_existing_elem(hit);
            return true;
        }
    }

private:
    void add_new_elem(key_t key) {
        if (full) {
            auto delete_elem = std::prev(cache.end());
            cache.erase(delete_elem);
            hash.erase(delete_elem->key);
        }

        cache.emplace_front(key);
        hash[key] = std::next(cache.end());

        if (!full && cache.size() == capacity)
            full = true;
    }

    void handle_existing_elem(hash_iter hit) {
        total_hits++;
        list_iter element = hit->second;
        element->frequency++;
        list_iter next_element = element;

        for (; next_element != cache.begin(); next_element++) {
            if (element->frequency < next_element->frequency) {
                break;
            }
        }

        if (element != next_element) {
            cache.insert(next_element, *element);
            cache.erase(element);
        }
    }

public:

    void get_hit_counts() const {
        std::cout << total_hits << '\n';
    }
};

}; // namespace lfu

#endif // LFU_HPP

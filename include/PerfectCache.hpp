#ifndef PERFECTCACHE_HPP
#define PERFECTCACHE_HPP

#include <iterator>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <iostream>
#include <deque>
#include <vector>

namespace perfect_cache {

template <typename page_t, typename key_t>
class perfect_cache {
    struct cache_elem;

public:
    using list_iter = typename std::list<cache_elem>::iterator;
    using hashmap_iter = typename std::unordered_map<key_t, list_iter>::iterator;
    using input_iter = typename std::vector<key_t>::iterator;

private:

    size_t capacity;
    size_t input_num;
    int64_t total_hits = 0;
    bool full = false;

    struct cache_elem {
        page_t page;
        key_t key;

        cache_elem(key_t key) : key(key) {};
    };

    std::unordered_map<key_t, std::deque<size_t>> hashmap;
    std::list<cache_elem> cache;
    std::vector<key_t> input;
    std::unordered_set<key_t> elem_set;

public:
    perfect_cache(size_t capacity, size_t input_num) : capacity(capacity), input_num(input_num) {};

    void run_cache() {
        fill_input();

        fill_hashmap();

        for (auto curr = input.begin(); curr != input.end(); curr++) {
            lookup_update(curr);
        }
    }

    size_t get_total_hits() {
        return total_hits;
    }

private:

    void lookup_update(input_iter key) {
        auto elem = elem_set.find(*key);

        if (elem == elem_set.end()) {
            add_new_elem(*key);
        } else {
            total_hits++;
        }

        hashmap[*key].pop_front();
        if (hashmap[*key].empty()) {
            hashmap.erase(*key);
        }
    }

    void add_new_elem(key_t key) {
        elem_set.insert(key);

        if (full) {
            auto furthest = get_furthest_elem();
            elem_set.erase(furthest->key);

            *furthest = {key};
        } else {
            cache.emplace_back(key);
        }

        if (!full && elem_set.size() == capacity) {
            full = true;
        }
    }

    list_iter get_furthest_elem() {
        list_iter furthest = cache.begin();
        size_t max_len = 0;

        for (auto curr = cache.begin(); curr != cache.end(); curr++) {
            auto found_elem = hashmap.find(curr->key);

            if (found_elem != hashmap.end()) {
                if (found_elem->second.front() > max_len) {
                    furthest = curr;
                    max_len = found_elem->second.front();
                }
            } else {
                furthest = curr;
                break;
            }
        }

        return furthest;
    }

    void fill_hashmap() {
        for (size_t i = 0; i < input_num; i++) {
            key_t key = input[i];
            hashmap[key].push_back(i);
        }
    }

    void fill_input() {
        for (int i = 0; i < input_num; i++) {
            key_t elem;
            std::cin >> elem;
            input.push_back(elem);
        }
    }
};

}; // namespace perfect_cache

#endif //PERFECTCACHE_HPP

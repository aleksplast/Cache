#include "../include/LFU.hpp"

#include <iostream>

int main() {
    size_t capacity;
    size_t num_elems;

    std::cin >> capacity >> num_elems;

    lfu::lfu_cache<int, int> cache(capacity);

    for (int i = 0; i < num_elems; i++) {
        int elem;
        std::cin >> elem;

        cache.lookup_update(elem);
    }

    cache.get_hit_counts();

    return 1;
}

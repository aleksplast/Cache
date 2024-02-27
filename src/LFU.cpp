#include "LFU.hpp"

#include <iostream>
#include <istream>

int main() {
    size_t capacity;
    size_t num_elems;

    std::cin >> capacity >> num_elems;

    lfu::lfu_cache<int, int> cache(capacity);

    for (int i = 0; i < num_elems; i++) {
        int elem;
        std::cin >> elem;

        if (!std::cin.good())
            throw std::runtime_error("Invalid input");

        cache.lookup_update(elem);
    }

    std::cout << cache.get_hit_counts() << '\n';

    return 0;
}

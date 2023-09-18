#include "../include/PerfectCache.hpp"

#include <iostream>

int main() {
    size_t capacity;
    size_t num_elems;

    std::cin >> capacity >> num_elems;

    perfect_cache::perfect_cache<int, int> cache(capacity, num_elems);
    cache.run_cache();

    std::cout << cache.get_total_hits() << '\n';

    return 1;
}

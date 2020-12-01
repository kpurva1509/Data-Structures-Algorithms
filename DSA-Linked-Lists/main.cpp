#include "headers.hpp"
#include "GenericLRUCache.hpp"

int main()
{
    GenericLRUCache<int, int> local_cache(5);
    local_cache.put(1,2);
    local_cache.put(2,4);
    local_cache.put(3,6);
    local_cache.get(1);
    local_cache.get(2);
    local_cache.put(5,7);
    local_cache.put(2,14);
    local_cache.get(3);
    local_cache.put(9,15);

    local_cache.print();

    return 0;
}
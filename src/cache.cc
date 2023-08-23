#include "cache.hpp"

#include <iostream>
//--------------------------------------------------------------------------
int main()
{
    size_t cache_size;
    int number_of_elementes;
    int hits = 0;
    
    std::cin >> cache_size >> number_of_elementes;

    Cache<int> lfu{cache_size}; 

    std::cout << "Now start entering the elements: ";

    for(int i = 0; i < number_of_elementes; i++)
    {
        int elem;
        std::cin >> elem;
        if(lfu.lookup_update(elem))
        {
            hits += 1;
        };
    }

    std::cout << "Number of hits: " << hits << "\n";
}
//--------------------------------------------------------------------------
#include "cache.hpp"

#include <iostream>
//--------------------------------------------------------------------------
int main()
{
    int cache_size;
    int number_of_elementes;
    int hits = 0;
    
    std::cin >> cache_size >> number_of_elementes;

    Cache lfu{cache_size}; 

    std::cout << "Now start entering the elements: ";
    
    for(int i = 0; i < number_of_elementes; i++)
    {
        int elem;
        std::cin >> elem;
        hits = lfu.lookup_update(elem);
    }

    std::cout << "Number of hits: " << hits << "\n"; // число попаданий
}
//--------------------------------------------------------------------------
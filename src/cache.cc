#include "cache.hpp"

#include <iostream>
//--------------------------------------------------------------------------
int main()
{
    size_t cache_size;
    int number_of_elementes;
    
    std::cin >> cache_size >> number_of_elementes;

    Cache<int> lfu{cache_size}; 

    for(int i = 0; i < number_of_elementes; i++)
    {
        
    }
}
//--------------------------------------------------------------------------
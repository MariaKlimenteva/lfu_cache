#include "cache.hpp"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//--------------------------------------------------------------------------
int main(int argc, char** argv) 
{
    size_t cache_size;
    int number_of_elements;
    int hits = 0;
    int perfect_hits = 0;
    //----------------------------------------------------------------------
    #ifdef TEST_PARAM
    std::ifstream tests;
    tests.open(argv[1]);

    int number_of_tests;
    tests >> number_of_tests;

    for(int i = 0; i < number_of_tests; i++)
    {
        tests >> cache_size >> number_of_elements;
        hits = 0;
        perfect_hits = 0;

        Cache<int> lfu{cache_size};
        Perfect_Cache<int> perfect{cache_size};
        
        for(int i = 0; i < number_of_elements; i++)
        {
            int elem;
            tests >> elem;

            if(lfu.lookup_update(elem))
            {
                hits += 1;
            }
            perfect.make_list(elem);
        }
                
        perfect.make_map();

        for(auto elem : perfect.all_elements)
        {
            
            if(perfect.perfect_hit_counter(elem))
            {
                perfect_hits += 1;
            }
            perfect.update_map(elem);
        }

        std::cout << hits << " ";
        std::cout << perfect_hits << "\n";
    }
    
    tests.close();

    #endif
    //----------------------------------------------------------------------
    #ifndef TEST_PARAM
    std::cin >> cache_size >> number_of_elements;
    
    Cache<int> lfu{cache_size};
    Perfect_Cache<int> perfect{cache_size};

    for(int i = 0; i < number_of_elements; i++)
    {
        int elem;
        std::cin >> elem;

        if(lfu.lookup_update(elem))
        {
            hits += 1;
        }

        perfect.make_list(elem);
    }
    perfect.make_map();
    // perfect.print_map();

    for(auto elem : perfect.all_elements)
    {
        if(perfect.perfect_hit_counter(elem))
        {
            perfect_hits += 1;
        }
        perfect.update_map(elem);
    }

    std::cout << hits << " ";
    std::cout << perfect_hits << "\n";

    #endif
    //----------------------------------------------------------------------
}
//--------------------------------------------------------------------------
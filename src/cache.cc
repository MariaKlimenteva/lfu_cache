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
    int hits;
    int perfect_hits;
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
            
            if(perfect.perfect_hit_counter(elem, number_of_elements))
            {
                perfect_hits += 1;
            }
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
    perfect.print_map();

    for(auto elem : perfect.all_elements)
    {
        if(perfect.perfect_hit_counter(elem, number_of_elements))
        {
            perfect_hits += 1;
        }

        auto current_iterator = std::find(perfect.all_elements.begin(), perfect.all_elements.end(), elem);
        int index = std::distance(perfect.all_elements.begin(), current_iterator);

        if(perfect.duplicate_elements.find(elem) != perfect.duplicate_elements.end())
        {
            if(perfect.duplicate_elements[elem].size() > 2)
            {
                perfect.duplicate_elements[elem].erase(std::next(perfect.duplicate_elements[elem].begin()));
            }
            else
            {
                perfect.duplicate_elements.erase(elem);
            }
        }
        

        // perfect.change_map_values(elem, current_iterator, index);
        // если этот итератор больше чем значение в векторе у данного elem - значение надо удалить из вектора
    }

    std::cout << hits << " ";
    std::cout << perfect_hits << "\n";

    #endif
    //----------------------------------------------------------------------
}
//--------------------------------------------------------------------------
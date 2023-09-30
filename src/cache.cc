#include "cache.hpp"

// #include <iostream>
#include <fstream>
#include <cstdio>
//--------------------------------------------------------------------------
int main(int argc, char** argv) 
{
    size_t cache_size = 0;
    int number_of_elements = 0;
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
        std::unique_ptr<Perfect_Cache<int>> perfect(new Perfect_Cache<int>(cache_size));
        
        for(int i = 0; i < number_of_elements; i++)
        {
            int elem;
            tests >> elem;

            if(lfu.lookup_update(elem, cache_size, number_of_elements))
            {
                hits += 1;
            }
            perfect->make_list(elem);
        }
                
        perfect->make_map();

        for(auto elem : *(perfect->all_elements))
        {
            
            if(perfect->perfect_hit_counter(elem))
            {
                perfect_hits += 1;
            }
            perfect->update_map(elem);
        }

        std::cout << hits << " ";
        std::cout << perfect_hits << "\n";
    }
    
    tests.close();

    #endif
    //----------------------------------------------------------------------
    #ifndef TEST_PARAM
    std::cin >> cache_size >> number_of_elements;
    
    std::unique_ptr<Cache<int>> lfu(new Cache<int>{cache_size});
    std::unique_ptr<Perfect_Cache<int>> perfect(new Perfect_Cache<int>(cache_size));
    
    // time_t start, end;
    // time(&start);

    int elem;
    for(int i = 0; i < number_of_elements; i++)
    {
        
        std::cin >> elem;

        if(lfu->lookup_update(elem, cache_size, number_of_elements))
        {
            hits += 1;
        }        
        perfect->make_list(elem);
    }
    
    
    perfect->make_map();     

    for(auto elem : *(perfect->all_elements))
    {
        if(perfect->perfect_hit_counter(elem))
        {
            perfect_hits += 1;
        }
        perfect->update_map(elem);
    }
    // time(&end);
    // double time_taken = double(end - start);
    // std::cout << "Time taken : " << time_taken << "\n";
    std::cout << hits << " ";
    std::cout << perfect_hits << "\n";


    #endif
    //----------------------------------------------------------------------
}
//--------------------------------------------------------------------------
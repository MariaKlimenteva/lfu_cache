#include "cache.hpp"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//--------------------------------------------------------------------------
// TEST(CheckValues, Subtest_1) 
// {
//     std::ifstream tests_file;
//     tests_file.open("tests.txt");

//     size_t cache_size;
//     int number_of_elementes;
//     int hits = 0;

//     Cache<int> lfu{cache_size};

//     tests_file >> cache_size >> number_of_elementes;

//     for(int i = 0; i < number_of_elementes; i++)
//     {
//         int elem;
//         tests_file >> elem;
//         if(lfu.lookup_update(elem))
//         {
//             hits += 1;
//         };
//     }

//     int answer;
//     tests_file >> answer;
//     EXPECT_EQ(hits, answer);
//     tests_file.close();
// }
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
        // std::cout << cache_size << number_of_elements;
        hits = 0;
        perfect_hits = 0;

        Cache<int> lfu{cache_size};
        Perfect_Cache<int> perfect{cache_size};
        
        for(int i = 0; i < number_of_elements; i++)
        {
            int elem;
            tests >> elem;
            // std::cout << elem;

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

    for(auto elem : perfect.all_elements)
    {
        if(perfect.perfect_hit_counter(elem, number_of_elements))
        {
            perfect_hits += 1;
        }
    }

    std::cout << hits << " ";
    std::cout << perfect_hits << "\n";

    #endif
    //----------------------------------------------------------------------
}
//--------------------------------------------------------------------------
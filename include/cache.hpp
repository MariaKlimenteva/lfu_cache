#pragma once
//--------------------------------------------------------------------------
#include <iterator>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <iostream>
//--------------------------------------------------------------------------
template<typename T, typename KeyT = int>
class Cache 
{
    public:
    Cache(size_t size): size_(size) {} 

    private:
    size_t size_; 
    std::list<T> cache_;
    std::unordered_map<T, KeyT> hash_;
    // std::unordered_map<T, std::pair<int, int>> perfect_hash;

    bool cache_is_full()
    {
        return cache_.size() == size_;
    }

    public:
    bool lookup_update(T element) 
    {
        int counter = 0;

        if(!cache_is_full())
        {
            cache_.emplace_back(element);
            hash_.emplace(element, counter);
            return false;
        }
        else
        {
            if(auto iter = hash_.find(element); iter != hash_.end())
            {
                hash_[element]++;
                return true;
            }
            else
            {
                std::pair<T, KeyT> min = *std::min_element(hash_.begin(), hash_.end(),
                [](const std::pair<const T, KeyT> &a, const std::pair<const T, KeyT> &b) 
                { return a.second < b.second; }); 

                cache_.remove(min.first);
                cache_.emplace_back(element);

                min.first = element;
                min.second = 0;
                
                return false;
            }
        }
    } 
};
//--------------------------------------------------------------------------
template<typename T, typename KeyT = int>
class Perfect_Cache
{
    private:
    size_t size_; 
    std::list<T> all_elements;
    std::list<T> perfect_cache;
    std::unordered_map<T, int> duplicate_elements;

    public:
    Perfect_Cache(size_t size): size_(size) {} 

    void make_list(T element, int number_of_elements)
    {
        for(int i = 0; i < number_of_elements; i++)
        {
            all_elements.emplace_back(element);
        }
    }

    void make_map(int number_of_elements)
    {
        all_elements.sort();
        std::cout << all_elements;
        auto it = unique(all_elements.begin(), all_elements.end(), [] (const int& a, const int& b) 
        {
            return a == b; 
        });

        all_elements.erase(it, all_elements.end());

        for(auto elem: all_elements)
        {
            // найти индекс где находились повторяющиеся элементы
            
            // duplicate_elements.insert({iterator, elem});
        }
    }
};
//--------------------------------------------------------------------------
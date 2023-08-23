#pragma once
//--------------------------------------------------------------------------
#include <iterator>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <iostream>
//--------------------------------------------------------------------------
// template<typename T, typename KeyT = int>
class Cache 
{
    public:
    Cache(int size): size_(size) {} 

    private:
    int size_; 
    std::list<int> cache_;
    std::unordered_map<int, int> hash_;

    bool cache_is_full()
    {
        return cache_.size() == size_;
    }

    public:
    bool lookup_update(int element) // карта = ключ + значение
    {
        int hits = 0;
        int counter = 1;

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
                hash_[element]++;   // увеличили счетчик
                return true;
            }
            else
            {
                std::pair<int, int> min = *std::min_element(hash_.begin(), hash_.end(),
                [](const std::pair<const int, int> &a, const std::pair<const int, int> &b) 
                { return a.second < b.second; }); //компаратор с лямбда выражением
                std::cout << "" << min.first;
                return false;
            }
        }
    }   
};
//--------------------------------------------------------------------------
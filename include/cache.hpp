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

    bool cache_is_full()
    {
        return cache_.size() == size_;
    }

    public:
    bool lookup_update(T element) 
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
                hash_[element]++;   
                return true;
            }
            else
            {
                std::pair<T, KeyT> min = *std::min_element(hash_.begin(), hash_.end(),
                [](const std::pair<const T, KeyT> &a, const std::pair<const T, KeyT> &b) 
                { return a.second < b.second; }); 
                // нашли элемент с минимальным счетчиком (если их несколько то берется рандомный) в unordered_map
                // заменяем значение элемента на новый элемент который кладем и делаем counter = 1
                min.first = element;
                min.second = 1;
                
                return false;
            }
        }
    }   
};
//--------------------------------------------------------------------------
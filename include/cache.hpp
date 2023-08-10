#pragma once
//--------------------------------------------------------------------------
#include <iterator>
#include <list>
#include <unordered_map>
#include <vector>
//--------------------------------------------------------------------------
template<typename T, typename KeyT = int>
class Cache 
{
    public:
    Cache(size_t size): size_(size) {} 

    private:
    size_t size_; 
    std::list<std::pair<KeyT, T>> cache_;

    using ListIt = typename std::list<std::pair<KeyT, T>>::iterator;
    std::unordered_map<KeyT, ListIt> hash_; // ListIt - итератор который будет пробегаться по элементам листа

    bool is_full()
    {
        return cache_.size() == size_;
    }

    
};



//--------------------------------------------------------------------------
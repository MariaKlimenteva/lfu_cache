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
    int lookup_update(int element) // карта = ключ + значение
    {
        int hits = 0;
        int counter = 1;

        if(!cache_is_full())
        {
            cache_.emplace_back(element);

            hash_.insert({element, counter});
        }
        else
        {
            if(auto iter = hash_.find(element); iter != hash_.end())
            {
                hash_[element]++;   // увеличили счетчик
                hits++; //увеличили число попаданий
            }
            else
            {
                std::pair<int, int> min = *std::min_element(hash_.begin(), hash_.end(),
                [](const std::pair<const int, int> &a, const std::pair<const int, int> &b) 
                { return a.second < b.second; });//компаратор с лямбда выражением
                std::cout << "" << min.first;
            }
        }

        return hits; //возвращает число попаданий
    }   
};

//--------------------------------------------------------------------------
// Алгоритм кэширования LFU
// 1. Мы получаем новый элемент (значение) -> пробегаемся по списку

// 2. Если есть этот элемент в списке -> увеличиваем ключ

// 3. Если нет -> пробегаемся по хэшу и находим самый маленький ключ
//             идем по итератору связанному с этим ключом в список и делаем замену

// попадания это ситуация пункт 2
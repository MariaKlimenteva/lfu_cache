#pragma once
//--------------------------------------------------------------------------
#include <iterator>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <iostream>
#include <cmath>
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
        int counter = 0;
        if(auto iter = hash_.find(element); iter != hash_.end())
        {
            hash_[element]++;
            return true;
        }
        else
        {
            if(!cache_is_full())
            {
                cache_.emplace_back(element);
                hash_.emplace(element, counter);
                return false;
            }
            else
            {
                std::pair<T, KeyT> min = *std::min_element(hash_.begin(), hash_.end(),
                [](const std::pair<const T, KeyT> &a, const std::pair<const T, KeyT> &b) 
                { return a.second < b.second; }); 

                cache_.remove(min.first);
                cache_.emplace_back(element);

                hash_.erase(min.first);
                hash_.emplace(element, counter);
                
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
    std::unordered_map<T, std::string> duplicate_elements;

    public:
    Perfect_Cache(size_t size): size_(size) {} 

    bool cache_is_full()
    {
        return perfect_cache.size() == size_;
    }

    void make_list(T element)
    {
        all_elements.emplace_back(element);
    }

    void make_map()
    {
        for(auto it = all_elements.begin(); it != all_elements.end(); ++it)
        {
            if (duplicate_elements.find(*it) != duplicate_elements.end()) //нашли элемент в map
            {
                auto index = std::distance(all_elements.begin(), it);
                duplicate_elements[*it] += index;
            }
            else
            {
                duplicate_elements.emplace(*it, std::to_string(0));
            }
        }
        for (auto it = duplicate_elements.begin(); it != duplicate_elements.end(); ) //удалить все элементы со значением 0 по ключу == не повторяющиеся
        {
            if (it->second == std::to_string(0)) 
            {
                it = duplicate_elements.erase(it);
            } 
            else 
            {
                ++it;
            }
        }
    }

    bool perfect_hit_counter(T element, int number_of_elements)
    {
        auto it = std::find(perfect_cache.begin(), perfect_cache.end(), element);

        if(it != perfect_cache.end()) //нашли в кэше этот элемент
        {
            return true;
        }
        else //не нашли
        {
            if(cache_is_full())
            {
                for(T elem : perfect_cache)
                {
                    int min = number_of_elements;

                    if(duplicate_elements.find(elem) == duplicate_elements.end()) // элемент не повторяющийся
                    {
                        std::replace(perfect_cache.begin(), perfect_cache.end(), elem, element);
                        return false;
                        break;
                    }
                    else // если все значения в perfect_cache повторятся в будущем
                    {
                        auto length = duplicate_elements[elem].length() - 1; //в длине строки посчитали первый 0, поэтому вычитаем 1
                        auto index = std::stoi(duplicate_elements[elem], nullptr, 10); // получили само число 

                        if(index/pow(10, length - 1) < min) // находим ближайшее по индексу
                        {
                            min = index/pow(10, length - 1);
                            duplicate_elements[elem] = index - pow(10, length - 1);
                            std::replace(perfect_cache.begin(), perfect_cache.end(), elem, element);
                            return false;
                            break;
                        }
                    }
                }
            }
            else
            {
                perfect_cache.emplace_back(element);
                return false;
            }
        }
        return false;
    }
};
//--------------------------------------------------------------------------
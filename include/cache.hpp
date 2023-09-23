#pragma once
//--------------------------------------------------------------------------
#include <iterator>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <iostream>
#include <cmath>
#include <vector>
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
template<typename T>
class Perfect_Cache
{
    private:
    size_t size_; 
    std::list<T> perfect_cache;
    std::unordered_map<T, std::vector<int>> duplicate_elements;

    public:
    std::list<T> all_elements;
    Perfect_Cache(size_t size): size_(size) {} 
    //--------------------------------------------------------------------------
    bool cache_is_full()
    {
        return perfect_cache.size() == size_;
    }
    //--------------------------------------------------------------------------
    void make_list(T element)
    {
        all_elements.emplace_back(element);
    }
    //--------------------------------------------------------------------------
    void print_map()
    {
        for (const auto& pair : duplicate_elements) 
        {
            std::cout << pair.first << ": ";
            for (const auto& element : pair.second) 
            {
                std::cout << element << " ";
                
            }
            std::cout << "size: "<< pair.second.size(); 
            std::cout << std::endl;
        }
    }
    //--------------------------------------------------------------------------
    void make_map()
    {
        for(auto it = all_elements.begin(); it != all_elements.end(); ++it)
        {
            if (duplicate_elements.find(*it) != duplicate_elements.end()) 
            {
                auto index = std::distance(all_elements.begin(), it);
                duplicate_elements[*it].emplace_back(index);
            }
            else
            {
                duplicate_elements[*it].emplace_back(0);
            }
        }

        for (auto it = duplicate_elements.begin(); it != duplicate_elements.end(); ) 
        {
            if (it->second == std::vector<int>{0}) 
            {
                it = duplicate_elements.erase(it);
            } 
            else 
            {
                ++it;
            }
        }
    }
    //--------------------------------------------------------------------------
    void swap(T element)
    {
        int max = 0;

        for(T elem : perfect_cache)
        {
            if(!find_element_in_map(element))
            {
                break;
            }
            if(!find_element_in_map(elem)) 
            {
                std::replace(perfect_cache.begin(), perfect_cache.end(), elem, element);
                break;
            }
            else 
            {
                if(duplicate_elements[elem].at(1) > max)
                {
                    max = duplicate_elements[elem].at(1);
                }
                else
                {
                    std::replace(perfect_cache.begin(), perfect_cache.end(), elem, element);
                    break;
                }
            }
        }
    }
    //--------------------------------------------------------------------------
    bool find_element_in_map (T element)
    {
        if(duplicate_elements.find(element) != duplicate_elements.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //--------------------------------------------------------------------------
    bool not_a_hit(T element)
    {
        if(cache_is_full())
        {
            swap(element);
        }
        else 
        {
            if(find_element_in_map(element))
            {
                perfect_cache.emplace_back(element);
            }
        }
        return false;
    }
    //--------------------------------------------------------------------------
    bool perfect_hit_counter(T element)
    {
        auto perfect_cache_it = std::find(perfect_cache.begin(), perfect_cache.end(), element);

        if(perfect_cache_it != perfect_cache.end()) 
        {            
            return true;
        } 
        else
        {
            return not_a_hit(element);
        }
    }
    //--------------------------------------------------------------------------
    void update_map(T elem)
    {
        if(duplicate_elements.find(elem) != duplicate_elements.end())
        {
            if(duplicate_elements[elem].size() > 2)
            {
                duplicate_elements[elem].erase(std::next(duplicate_elements[elem].begin()));
            }
            else
            {
                duplicate_elements.erase(elem);
            }
        }
    }
};
//--------------------------------------------------------------------------
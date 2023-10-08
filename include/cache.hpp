#pragma once
//--------------------------------------------------------------------------
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <memory>
//--------------------------------------------------------------------------
template<typename T, typename KeyT = int>
class Cache 
{
    private:
    size_t size_; 
    int min_element = 0;
    
    std::unique_ptr<std::unordered_map<T,T>> cache_;

    inline bool cache_is_full()
    {
        return cache_->size() == size_;
    }

    public:
    Cache(size_t size): size_(size),
    cache_(std::make_unique<std::unordered_map<T,T>>()){}

    inline bool find_elem_in_cache(T element)
    {
        if(auto iter = cache_->find(element); iter != cache_->end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    inline void is_a_hit(T element, int counter, int min)
    {
        (*cache_)[element]++;
        
        if(size_ > 100000)
        {
            if(cache_is_full()) // пересчет минимального
            {
                for(auto elem: (*cache_))  
                {
                    min = 3050000;
                    if((*cache_)[elem.first] < min)
                    {
                        min = (*cache_)[elem.first];
                        min_element = elem.first;
                    }
                }
            }
        }
    }

    inline void not_a_hit(T element, int counter, int min)
    {
        if(!cache_is_full())
        {
            cache_->emplace(element, counter);
            (*cache_)[element]++;

            if(size_ > 100000)
            {
                if(cache_->size() == size_ - 1) //перед заполнением кэша узнаем 1 раз min
                {
                    for(auto elem: (*cache_))
                    {
                        if((*cache_)[elem.first] < min)
                        {
                            min = (*cache_)[elem.first];
                            min_element = elem.first;
                        }
                    }
                }
                
            }
        }
        else 
        {          
            if(size_ < 100000)
            {
                for(auto elem: (*cache_))  // 0m0.050s для теста 11
                {
                    if((*cache_)[elem.first] < min)
                    {
                        min = (*cache_)[elem.first];
                        min_element = elem.first;
                    }
                } 
            }
            
            cache_->erase(min_element);
            cache_->emplace(element, counter);
            (*cache_)[element]++;
        }
    }

    inline bool lookup_update(T element, size_t cache_size, int number_of_elements)
    {
        int counter = 0;
        int min = number_of_elements;

        if(find_elem_in_cache(element))
        {
            is_a_hit(element, counter, min);
            return true;
        }
        else
        {
            not_a_hit(element, counter, min);
            return false;
        }
    } 
};
//--------------------------------------------------------------------------
template<typename T>
class Perfect_Cache
{
    private:
    size_t size_; 
    std::unique_ptr<std::unordered_set<T>> perfect_cache; 
    std::unique_ptr<std::unordered_map<T, std::vector<int>>> duplicate_elements;

    public:
    std::unique_ptr<std::vector<T>> all_elements;

    Perfect_Cache(size_t size): size_(size), 
    perfect_cache(std::make_unique<std::unordered_set<T>>()), 
    all_elements(std::make_unique<std::vector<T>>()), 
    duplicate_elements(std::make_unique<std::unordered_map<T, std::vector<int>>>()) {}
    //--------------------------------------------------------------------------
    bool cache_is_full()
    {
        return perfect_cache->size() == size_;
    }
    //--------------------------------------------------------------------------
    void make_list(T element)
    {
        all_elements->emplace_back(element);
    }
    //--------------------------------------------------------------------------
    void print_map()
    {
        for (const auto& pair : (*duplicate_elements)) 
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
    void print_perfect_cache()
    {
        for(T elem : (*perfect_cache))
        {
            std::cout << " " << elem << std::endl;;
        }
    }
    //--------------------------------------------------------------------------
    void make_map()
    {
        for(auto it = all_elements->begin(); it != all_elements->end(); ++it)
        {
            auto index = std::distance(all_elements->begin(), it);
            (*duplicate_elements)[*it].emplace_back(index);
        }

        for (auto it = duplicate_elements->begin(); it != duplicate_elements->end(); ) 
        {
            if(it->second.size() < 2)
            {
                it = duplicate_elements->erase(it);
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
        T max_elem = 0;
        
        for(T elem : (*perfect_cache))
        {
            if((*duplicate_elements)[elem].size() > 0)
            {
                if((*duplicate_elements)[elem].at(0) > max)
                {
                    max = (*duplicate_elements)[elem].at(0);
                    max_elem = elem;
                }
            }
            else
            {
                break;
            }
        }

        if((*duplicate_elements)[element].size() > 1)
        {
            if((*duplicate_elements)[element].at(1) < max)
            {
                perfect_cache->erase(max_elem);
                perfect_cache->emplace(element);
            }
        }
    }
    //--------------------------------------------------------------------------
    bool find_element_in_map(T element)
    {
        if(duplicate_elements->find(element) != duplicate_elements->end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //--------------------------------------------------------------------------
    void not_a_hit(T element)
    {
        if(cache_is_full())
        {
            swap(element);
        }
        else 
        {
            perfect_cache->emplace(element);
        }
    }
    //--------------------------------------------------------------------------
    bool perfect_hit_counter(T element)
    {
        auto perfect_cache_it = perfect_cache->find(element);

        if(perfect_cache_it != perfect_cache->end()) 
        {            
            return true;
        } 
        else
        {
            if(find_element_in_map(element))
            {
                not_a_hit(element);
            }
            return false; 
        }
    }
    //--------------------------------------------------------------------------
    void update_map(T elem)
    {
        if(duplicate_elements->find(elem) != duplicate_elements->end())
        {
            if((*duplicate_elements)[elem].size() > 1)
            {
                (*duplicate_elements)[elem].erase((*duplicate_elements)[elem].begin());
            }
            else
            {
                duplicate_elements->erase(elem);
            }
        }
    }
};
//--------------------------------------------------------------------------
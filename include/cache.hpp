#pragma once
//--------------------------------------------------------------------------
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>
// #include <execution>
// #include <tbb/parallel_for.h>
//--------------------------------------------------------------------------
template<typename T, typename KeyT = int>
class Cache 
{
    private:
    size_t size_; 
    std::unique_ptr<std::vector<T>> cache_;
    // std::unique_ptr<std::unordered_map<T,T>> cache_;
    std::unique_ptr<std::unordered_map<T, KeyT>> hash_;

    inline bool cache_is_full()
    {
        return cache_->size() == size_;
    }

    public:
    Cache(size_t size): size_(size),
    // cache_(std::make_unique<std::unordered_map<T,T>>()),
    cache_(std::make_unique<std::vector<T>>()),
    hash_(std::make_unique<std::unordered_map<T, KeyT>>()) {} 

    inline bool find_elem_in_cache(T element)
    {
        if(auto iter = std::find(cache_->begin(), cache_->end(), element); iter != cache_->end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    inline void is_a_hit(T element, int counter)
    {
        if(hash_->find(element) == hash_->end())
        {
            hash_->emplace(element, counter);
        }
        (*hash_)[element]++;
    }

    inline void not_a_hit(T element, int counter, int min)
    {
        if(!cache_is_full())
        {
            cache_->emplace_back(element);
            hash_->emplace(element, counter);
            (*hash_)[element]++;
        }
        else
        {
            int min_element = 0;
            
            for(auto elem: (*cache_))
            {
                if((*hash_)[elem] == 0)
                {
                    min = 0;
                    min_element = elem;
                    break;
                }
                else
                {
                    if((*hash_)[elem] < min)
                    {
                        min = (*hash_)[elem];
                        min_element = elem;
                    }
                }
            }
            
            if((*hash_)[element] < min)
            {
                min = (*hash_)[element];
                min_element = element;
            }
            
            if(min_element != element)
            {
                cache_->erase(std::find(cache_->begin(), cache_->end(), min_element));
                cache_->emplace_back(element);
                
                if(hash_->find(element) == hash_->end())
                {
                    hash_->emplace(element, counter);
                }
                (*hash_)[element]++;
            }
        }
    }

    inline bool lookup_update(T element, size_t cache_size, int number_of_elements)
    {
        int counter = 0;
        int min = number_of_elements;

        if(find_elem_in_cache(element)) // это становится долго после того как полностью заполнили кэш
        {
            is_a_hit(element, counter);
            return true;
        }
        else
        {
            // time_t start, end;
            // time(&start);
            
            not_a_hit(element, counter, min);

            // time(&end);
            // double time_taken = double(end - start);
            // std::cout << "Time taken by not_a_hit : " << time_taken << "\n";

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
    std::unique_ptr<std::vector<T>> perfect_cache; 
    std::unique_ptr<std::unordered_map<T, std::vector<int>>> duplicate_elements;

    public:
    std::unique_ptr<std::vector<T>> all_elements;

    Perfect_Cache(size_t size): size_(size), 
    perfect_cache(std::make_unique<std::vector<T>>()), 
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
        T max_elem;
        
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
                max_elem = elem;
                break;
            }
        }

        if((*duplicate_elements)[element].size() > 1)
        {
            if((*duplicate_elements)[element].at(1) < max)
            {
                std::replace(perfect_cache->begin(), perfect_cache->end(), max_elem, element);
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
            perfect_cache->emplace_back(element);
        }
    }
    //--------------------------------------------------------------------------
    bool perfect_hit_counter(T element)
    {
        auto perfect_cache_it = std::find(perfect_cache->begin(), perfect_cache->end(), element);

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
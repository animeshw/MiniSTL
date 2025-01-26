#ifndef _ALGORITHM_HPP
#define _ALGORITHM_HPP

#include "functional.hpp"

namespace ani{
    template <typename InputIt, typename T = typename InputIt::value_type>
    InputIt find(InputIt first, InputIt last, const T& val){
        for(; first != last; ++first){
            if(*first == val)
                return first;
        }
        return last;
    }

    template <typename RandomIt>
    void make_heap(RandomIt first, RandomIt last){
        make_heap(first, last, ani::less<typename RandomIt::value_type>());
    }
    
    template <typename RandomIt, typename Comapre>
    void make_heap(RandomIt first, RandomIt last, Comapre comp){
        typename RandomIt::difference_type len = last - first;
        typename RandomIt::difference_type hole = len >> 1;
        while(hole > 0){
            --hole;
            typename RandomIt::value_type val = std::move(*(first + hole));
            _pop_heap_by_index(first, hole, len, std::move(val), comp);
        }
    }

    template <typename RandomIt, typename T, typename Compare>
    void _push_heap_by_index(RandomIt first, typename RandomIt::difference_type hole, typename RandomIt::difference_type top,
                    T&& val, Compare comp){
        typename RandomIt::difference_type i = (hole - 1) >> 1;
        for(; hole > top && comp(*(first + i), val); i = (hole - 1) >> 1){
            *(first + hole) = std::move(*(first + i));
            hole = i;
        }

        *(first + hole) = std::move(val);
    }

    template <typename RandomIt>
    void push_heap(RandomIt first, RandomIt last){
        push_heap(first, last, ani::less<typename RandomIt::value_type>());
    }

    template <typename RandomIt, typename Compare>
    void push_heap(RandomIt first, RandomIt last, Compare comp){
        typename RandomIt::difference_type len = last - first;
        if(len > 1){
            typename RandomIt::value_type val = std::move(*--last);
            _push_heap_by_index(first, --len, 0, std::move(val), comp);
        }
    }

    template <typename RandomIt, typename T, typename Compare>
    void _pop_heap_by_index(RandomIt first, typename RandomIt::difference_type hole, typename RandomIt::difference_type bottom,
                    T&& val, Compare comp){
        typename RandomIt::difference_type i = hole;
        typename RandomIt::difference_type top = hole;
        typename RandomIt::difference_type max_leaf_index = (bottom - 1) >> 1;

        while(i < max_leaf_index){
            i = 2 * i + 2;
            if(comp(*(first + i), *(first + (i - 1))))
                --i;
            *(first + hole) = std::move(*(first + i));
            hole = i;
        }

        if(i == max_leaf_index && bottom % 2 == 0){
            *(first + hole) = std::move(*(first +(bottom - 1)));
            hole = bottom - 1;
        }

        _push_heap_by_index(first, hole, top, std::move(val), comp);
    }

    template <typename RandomIt>
    void pop_heap(RandomIt first, RandomIt last){
        pop_heap(first, last, ani::less<typename RandomIt::value_type>());
    }

    template <typename RandomIt, typename Compare>
    void pop_heap(RandomIt first, RandomIt last, Compare comp){
        typename RandomIt::difference_type len = last - first;
        if(len > 1){
            typename RandomIt::value_type val = std::move(*--last);
            *last = std::move(*first);
            _pop_heap_by_index(first, 0, len - 1, std::move(val), comp);
        }
    }
    
    template <typename InputIt, typename UnaryOps>
    UnaryOps for_each(InputIt first, InputIt last, UnaryOps ops){
        for(; first != last; ++first)
            ops(*first);
        return ops;
    }
}

#endif // _ALGORITHM_HPP
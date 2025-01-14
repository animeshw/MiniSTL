#ifndef _UNORDERED_MULTISET_HPP
#define _UNORDERED_MULTISET_HPP

#include "hash_table.hpp"

namespace ani{
    template <typename T,typename Hash, typename KeyEqual>
    class _unordered_multiset_traits{
        public:
            using value_type = T;
            using key_type = T;
            using size_type = size_t;
            using difference_type = ptrdiff_t;
            using pointer = T*;
            using const_pointer = const T*;
            using reference = value_type&;
            using const_reference = const value_type&;
            using hasher = Hash;
            using key_eq = KeyEqual;
            constexpr static bool Multi = true;
    };

    template <typename T, typename Hash = std::hash<T>, typename KeyEqual = ani::equal_to<T>>
    class unordered_multiset : public _hash_table<_unordered_multiset_traits<T, Hash, KeyEqual>>{
        public:
            using MyBase = _hash_table<_unordered_multiset_traits<T, Hash, KeyEqual>>;
            using iterator = typename MyBase::iterator;
            using const_iterator = typename MyBase::const_iterator;

            using value_type = typename MyBase::value_type;
            
            static constexpr size_t DEFAULT_BUCKET_COUNT = 8;
        
        public:
            unordered_multiset() : unordered_multiset(DEFAULT_BUCKET_COUNT) { }

            unordered_multiset(size_t n, const Hash& hf = Hash(), const KeyEqual& eql = KeyEqual()) : MyBase(n, hf, eql) { }

            template <typename InputIt>
            unordered_multiset(InputIt first, InputIt last, size_t n = DEFAULT_BUCKET_COUNT, const Hash& hf = Hash(), 
                            const KeyEqual& eql = KeyEqual()) : unordered_multiset(n, hf, eql) {
                insert(first, last);
            }

            unordered_multiset(const unordered_multiset& other) : MyBase(other) { }

            unordered_multiset(unordered_multiset&& other) : MyBase(std::move(other)) { }

            unordered_multiset(std::initializer_list<value_type> init_list) : unordered_multiset(init_list.begin(), init_list.end()) { }

            unordered_multiset& operator=(const unordered_multiset& other){
                MyBase::operator=(other);
                return *this;
            }

            unordered_multiset& operator=(unordered_multiset&& other){
                MyBase::operator=(std::move(other));
                return *this;
            }

            unordered_multiset& operator=(std::initializer_list<value_type> init_list){
                clear();
                insert(init_list);
                return *this;
            }
    };
}

#endif // _UNORDERED_MULTISET_HPP
#ifndef _UNORDERED_SET_HPP
#define _UNORDERED_SET_HPP

#include "hash_table.hpp"

namespace ani{
    template <typename T, typename Hash, typename KeyEqual>
    class _unordered_set_traits{
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
            constexpr static bool Multi = false;
    };

    template <typename T, typename Hash = std::hash<T>, typename KeyEqual = ani::equal_to<T>>
    class unordered_set : public _hash_table<_unordered_set_traits<T, Hash, KeyEqual>>{
        public:
            using MyBase = _hash_table<_unordered_set_traits<T, Hash, KeyEqual>>;
            using iterator = typename MyBase::iterator;
            using const_iterator = typename MyBase::const_iterator;

            using value_type = typename MyBase::value_type;

            static constexpr size_t DEFAULT_BUCKET_COUNT = 8;

        public:
            unordered_set() : unordered_set(DEFAULT_BUCKET_COUNT) { }

            unordered_set(size_t n, const Hash& hf = Hash(), const KeyEqual& eql = KeyEqual()) : MyBase(n, hf, eql) { }

            template <typename InputIt>
            unordered_set(InputIt first, InputIt last, size_t n = DEFAULT_BUCKET_COUNT, const Hash& hf = Hash(), 
                            const KeyEqual& eql = KeyEqual()) : unordered_set(n, hf, eql) {
                insert(first, last);
            }

            unordered_set(const unordered_set& other) : MyBase(other) { }

            unordered_set(unordered_set&& other) : MyBase(std::move(other)) { }

            unordered_set(std::initializer_list<value_type> init_list) : unordered_set(init_list.begin(), init_list.end()) { }

            unordered_set& operator=(const unordered_set& other){
                MyBase::operator=(other);
                return *this;
            }

            unordered_set& operator=(unordered_set&& other){
                MyBase::operator=(std::move(other));
                return *this;
            }

            unordered_set& operator=(std::initializer_list<value_type> init_list){
                clear();
                insert(init_list);
                return *this;
            }
    };
}

#endif // _UNORDERED_SET_HPP
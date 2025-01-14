#ifndef _UNORDERED_MULTIMAP_HPP
#define _UNORDERED_MULTIMAP_HPP

#include "hash_table.hpp"

namespace ani{
    template <typename Hash>
    class MyHash{
        private:
            Hash hash;

        public:
            MyHash(Hash& hf = Hash()) : hash(hf) { }

            template <typename T>
            size_t operator()(const T& val) const{
                return hash(val);
            }

            template <typename Key, typename T>
            size_t operator()(const ani::pair<const Key, T>& val) const{
                return hash(val.first);
            }
    };

    template <typename KeyEqual>
    class MyKeyEqual{
        private:
            KeyEqual key_eq;

        public:
            MyKeyEqual(KeyEqual& _key_eq = KeyEqual()) : key_eq(_key_eq) { }

            template <typename T>
            bool operator()(const T& lhs, const T& rhs) const{
                return key_eq(lhs.first, rhs.first);
            }

            template <typename Key, typename T>
            bool operator()(const Key& lhs, const ani::pair<const Key, T>& rhs) const{
                return key_eq(lhs, rhs.first);
            }

            template <typename Key, typename T>
            bool operator()(const ani::pair<const Key, T>& lhs, const Key& rhs) const{
                return key_eq(lhs.first, rhs);
            }
    };

    template <typename Key, typename T, typename Hash, typename KeyEqual>
    class _unordered_multimap_traits{
        public:
            using value_type = ani::pair<const Key, T>;
            using key_type = Key;
            using size_type = size_t;
            using difference_type = ptrdiff_t;
            using pointer = value_type*;
            using const_pointer = const value_type *;
            using hasher = MyHash<Hash>;
            using key_eq = MyKeyEqual<KeyEqual>;
            constexpr static bool Multi = true;
    };

    template <typename Key, typename T, typename Hash = std::hash<Key>, typename KeyEqual = ani::equal_to<Key>>
    class unordered_multimap : public _hash_table<_unordered_multimap_traits<Key, T, Hash, KeyEqual>>{
        public:
            using MyBase = _hash_table<_unordered_multimap_traits<Key, T, Hash, KeyEqual>>;
            using iterator = typename MyBase::iterator;
            using const_iterator = typename MyBase::const_iterator;
            using value_type = typename MyBase::value_type;

            using hasher = typename MyBase::hasher;
            using key_equal = typename MyBase::key_equal;

            static constexpr size_t DEFAULT_BUCKET_COUNT = 8;

        public:
            unordered_multimap() : unordered_multimap(DEFAULT_BUCKET_COUNT) { }

            unordered_multimap(size_t n, const hasher& hf = hasher(), const key_equal& eql = key_equal()) : MyBase(n, hf, eql) { }

            template <typename InputIt>
            unordered_multimap(InputIt first, InputIt last, size_t n = DEFAULT_BUCKET_COUNT, const hasher& hf = hasher(), 
                            const key_equal& eql = key_equal()) : unordered_multimap(n, hf, eql) {
                insert(first, last);
            }

            unordered_multimap(const unordered_multimap& other) : MyBase(other) { }

            unordered_multimap(unordered_multimap&& other) : MyBase(std::move(other)) { }

            unordered_multimap(std::initializer_list<value_type> init_list) : unordered_multimap(init_list.begin(), init_list.end()) { }

            unordered_multimap& operator=(const unordered_multimap& other){
                MyBase::operator=(other);
                return *this;
            }

            unordered_multimap& operator=(unordered_multimap&& other){
                MyBase::operator=(std::move(other));
                return *this;
            }

            unordered_multimap& operator=(std::initializer_list<value_type> init_list){
                clear();
                insert(init_list);
                return *this;
            }
    };
}

#endif // _UNORDERED_MULTIMAP_HPP
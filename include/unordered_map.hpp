#ifndef _UNORDERED_MAP_HPP
#define _UNORDERED_MAP_HPP

#include "hash_table.hpp"
#include "exception\unordered_map_exception.hpp"

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
    class _unordered_map_traits{
        public:
            using value_type = ani::pair<const Key, T>;
            using key_type = Key;
            using size_type = size_t;
            using difference_type = ptrdiff_t;
            using pointer = value_type*;
            using const_pointer = const value_type *;
            using hasher = MyHash<Hash>;
            using key_eq = MyKeyEqual<KeyEqual>;
            constexpr static bool Multi = false;
    };

    template <typename Key, typename T, typename Hash = std::hash<Key>, typename KeyEqual = ani::equal_to<Key>>
    class unordered_map : public _hash_table<_unordered_map_traits<Key, T, Hash, KeyEqual>>{
        public:
            using MyBase = _hash_table<_unordered_map_traits<Key, T, Hash, KeyEqual>>;
            using iterator = typename MyBase::iterator;
            using const_iterator = typename MyBase::const_iterator;
            using value_type = typename MyBase::value_type;

            using hasher = typename MyBase::hasher;
            using key_equal = typename MyBase::key_equal;

            static constexpr size_t DEFAULT_BUCKET_COUNT = 8;

        public:
            unordered_map() : unordered_map(DEFAULT_BUCKET_COUNT) { }

            unordered_map(size_t n, const hasher& hf = hasher(), const key_equal& eql = key_equal()) : MyBase(n, hf, eql) { }

            template <typename InputIt>
            unordered_map(InputIt first, InputIt last, size_t n = DEFAULT_BUCKET_COUNT, const hasher& hf = hasher(), 
                            const key_equal& eql = key_equal()) : unordered_map(n, hf, eql) {
                insert(first, last);
            }

            unordered_map(const unordered_map& other) : MyBase(other) { }

            unordered_map(unordered_map&& other) : MyBase(std::move(other)) { }

            unordered_map(std::initializer_list<value_type> init_list) : unordered_map(init_list.begin(), init_list.end()) { }

            unordered_map& operator=(const unordered_map& other){
                MyBase::operator=(other);
                return *this;
            }

            unordered_map& operator=(unordered_map&& other){
                MyBase::operator=(std::move(other));
                return *this;
            }

            unordered_map& operator=(std::initializer_list<value_type> init_list){
                clear();
                insert(init_list);
                return *this;
            }

            T& operator[](const Key& key){
                iterator iter = find(key);
                if(iter == end())
                    return insert(pair<const Key, T>(key, T())).first->second;
                return iter->second;
            }

            T& operator[](Key&& key){
                iterator iter = find(key);
                if(iter == end())
                    return insert(pair<const Key, T>(std::move(key), T())).first->second;
                return iter->second;
            }

            T& at(const Key& key){
                iterator iter = find(key);
                if(iter == end())
                    throw unordered_map_out_of_range();
                return iter->second;
            }

            const T& at(const Key& key) const{
                const_iterator citer = find(key);
                if(citer == end())
                    throw unordered_map_out_of_range();
                return citer->second;
            }
    };
}

#endif // _UNORDERED_MAP_HPP
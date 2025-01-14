#ifndef _MAP_HPP
#define _MAP_HPP

#include "exception\map_exception.hpp"
#include "utility.hpp"
#include "functional.hpp"
#include "rb_tree.hpp"

namespace ani{
    template <typename Compare>
    class _map_val_comp{
        private:
            Compare comp;

        public:
            _map_val_comp(Compare& _comp = Compare()) : comp(_comp) { }

            template <typename T>
            bool operator()(const T& lhs, const T& rhs) const{
                return comp(lhs.first, rhs.first);
            }

            template <typename Key, typename T>
            bool operator()(const Key& lhs, const ani::pair<const Key, T>& rhs) const{
                return comp(lhs, rhs.first);
            }

            template <typename Key, typename T>
            bool operator()(const ani::pair<const Key, T>& lhs, const Key& rhs) const{
                return comp(lhs.first, rhs);
            }
    };

    template <typename Key, typename T, typename Compare>
    class _map_traits{
        public:
            using value_type = ani::pair<const Key, T>;
            using key_type = Key;
            using mapped_type = T;
            using size_type = size_t;
            using difference_type = ptrdiff_t;
            using pointer = value_type*;
            using const_pointer = const value_type*;
            using reference = value_type&;
            using const_reference = const value_type&;
            
            using value_compare = _map_val_comp<Compare>;
            using key_compare = _map_val_comp<ani::equal_to<Key>>;
            constexpr static bool Multi = false;
    };

    template <typename Key, typename T, typename Comp = ani::less<Key>>
    class map : public _rb_tree<_map_traits<Key, T, Comp>>{
        public:
            using MyBase = _rb_tree<_map_traits<Key, T, Comp>>;
            using iterator = typename MyBase::iterator;
            using const_iterator = typename MyBase::const_iterator;
            using reverse_iterator = typename MyBase::reverse_iterator;
            using const_reverse_iterator = typename MyBase::const_reverse_iterator;

            using Compare = typename _map_traits<Key, T, Comp>::value_compare;
            using value_compare = typename _map_traits<Key, T, Comp>::value_compare;
            using key_compare = typename _map_traits<Key, T, Comp>::key_compare;

            using value_type = typename _map_traits<Key, T, Comp>::value_type;

        public:
            map() : MyBase() { }

            map(const Compare& _comp) : MyBase(_comp) { }

            template <typename InputIt>
            map(InputIt first, InputIt last, const Compare& _comp = Compare()) : map(_comp) { insert(first, last); }

            map(const map& other) : map(other.cbegin(), other.cend(), other.comp) { }

            map(map&& other) : MyBase(std::move(other)) { }

            map(std::initializer_list<value_type> init_list, const Compare& _comp = Compare()) : map(init_list.begin(), init_list.end(), _comp) { }

            map& operator=(const map& other){
                MyBase::operator=(other);
                return *this;
            }

            map& operator=(map&& other){
                MyBase::operator=(std::move(other));
                return *this;
            }

            map& operator=(std::initializer_list<value_type> init_list){
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
                    throw map_out_of_range();
                return iter->second;
            }

            const T& at(const Key& key) const{
                const_iterator citer = find(key);
                if(citer == end())
                    throw map_out_of_range();
                return citer->second;
            }
    };
}

#endif // _MAP_HPP
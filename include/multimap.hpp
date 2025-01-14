#ifndef _MULTIMAP_HPP
#define _MULTIMAP_HPP

#include "utility.hpp"
#include "functional.hpp"
#include "rb_tree.hpp"

namespace ani{
    template <typename Compare>
    class _multimap_val_comp{
        private:
            Compare comp;

        public:
            _multimap_val_comp(Compare& _comp = Compare()) : comp(_comp) { }

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
    class _multimap_traits{
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
            
            using value_compare = _multimap_val_comp<Compare>;
            using key_compare = _multimap_val_comp<ani::equal_to<Key>>;
            constexpr static bool Multi = true;
    };

    template <typename Key, typename T, typename Comp = ani::less<Key>>
    class multimap : public _rb_tree<_multimap_traits<Key, T, Comp>>{
        public:
            using MyBase = _rb_tree<_multimap_traits<Key, T, Comp>>;
            using iterator = typename MyBase::iterator;
            using const_iterator = typename MyBase::const_iterator;
            using reverse_iterator = typename MyBase::reverse_iterator;
            using const_reverse_iterator = typename MyBase::const_reverse_iterator;

            using Compare = typename _multimap_traits<Key, T, Comp>::value_compare;
            using value_compare = typename _multimap_traits<Key, T, Comp>::value_compare;
            using key_compare = typename _multimap_traits<Key, T, Comp>::key_compare;

            using value_type = typename _multimap_traits<Key, T, Comp>::value_type;

        public:
            multimap() : MyBase() { }

            multimap(const Compare& _comp) : MyBase(_comp) { }

            template <typename InputIt>
            multimap(InputIt first, InputIt last, const Compare& _comp = Compare()) : multimap(_comp) { insert(first, last); }

            multimap(const multimap& other) : multimap(other.cbegin(), other.cend(), other.comp) { }

            multimap(multimap&& other) : MyBase(std::move(other)) { }

            multimap(std::initializer_list<value_type> init_list, const Compare& _comp = Compare()) : multimap(init_list.begin(), init_list.end(), _comp) { }

            multimap& operator=(const multimap& other){
                MyBase::operator=(other);
                return *this;
            }

            multimap& operator=(multimap&& other){
                MyBase::operator=(std::move(other));
                return *this;
            }

            multimap& operator=(std::initializer_list<value_type> init_list){
                clear();
                insert(init_list);
                return *this;
            }
    };
}

#endif // _MULTIMAP_HPP
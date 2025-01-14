#ifndef _MULTISET_HPP
#define _MULTISET_HPP

#include "functional.hpp"
#include "rb_tree.hpp"

namespace ani{
    template <typename T, typename Compare>
    class _multiset_traits{
        public:
            using value_type = T;
            using key_type = T;
            using size_type = size_t;
            using difference_type = ptrdiff_t;
            using pointer = T*;
            using const_pointer = const T*;
            using reference = value_type&;
            using const_reference = const value_type&;
            using value_compare = Compare;
            using key_compare = ani::equal_to<T>;
            constexpr static bool Multi = true;
    };

    template <typename T, typename Compare = ani::less<T>>
    class multiset : public _rb_tree<_multiset_traits<T, Compare>>{
        public:
            using MyBase = _rb_tree<_multiset_traits<T, Compare>>;
            using iterator = typename MyBase::iterator;
            using const_iterator = typename MyBase::const_iterator;
            using reverse_iterator = typename MyBase::reverse_iterator;
            using const_reverse_iterator = typename MyBase::const_reverse_iterator;

        public:
            multiset() : multiset(Compare()) { }

            multiset(const Compare& _comp) : MyBase(_comp) { }

            template <typename InputIt>
            multiset(InputIt first, InputIt last, const Compare& _comp = Compare()) : multiset(_comp) { insert(first, last); }

            multiset(const multiset& other) : multiset(other.cbegin(), other.cend(), other.comp) { }

            multiset(multiset&& other) : MyBase(std::move(other)) { }

            multiset(std::initializer_list<T> init_list, const Compare& _comp = Compare()) : multiset(init_list.begin(), init_list.end(), _comp) { }

            multiset& operator=(const multiset& other){
                MyBase::operator=(other);
                return *this;
            }

            multiset& operator=(multiset&& other){
                MyBase::operator=(std::move(other));
                return *this;
            }

            multiset& operator=(std::initializer_list<T> init_list){
                clear();
                insert(init_list);
                return *this;
            }
    };
}

#endif // _MULTISET_HPP
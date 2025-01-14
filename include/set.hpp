#ifndef _SET_HPP
#define _SET_HPP

#include "functional.hpp"
#include "rb_tree.hpp"

namespace ani{
    template <typename T, typename Compare>
    class _set_traits{
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
            constexpr static bool Multi = false;
    };

    template <typename T, typename Compare = ani::less<T>>
    class set : public _rb_tree<_set_traits<T, Compare>>{
        public:
            using MyBase = _rb_tree<_set_traits<T, Compare>>;
            using iterator = typename MyBase::iterator;
            using const_iterator = typename MyBase::const_iterator;
            using reverse_iterator = typename MyBase::reverse_iterator;
            using const_reverse_iterator = typename MyBase::const_reverse_iterator;

        public:
            set() : set(Compare()) { }

            set(const Compare& _comp) : MyBase(_comp) { }

            template <typename InputIt>
            set(InputIt first, InputIt last, const Compare& _comp = Compare()) : set(_comp) { insert(first, last); }

            set(const set& other) : set(other.cbegin(), other.cend(), other.comp) { }

            set(set&& other) : MyBase(std::move(other)) { }

            set(std::initializer_list<T> init_list, const Compare& _comp = Compare()) : set(init_list.begin(), init_list.end(), _comp) { }

            set& operator=(const set& other){
                MyBase::operator=(other);
                return *this;
            }

            set& operator=(set&& other){
                MyBase::operator=(std::move(other));
                return *this;
            }

            set& operator=(std::initializer_list<T> init_list){
                clear();
                insert(init_list);
                return *this;
            }
    };
}

#endif // _SET_HPP
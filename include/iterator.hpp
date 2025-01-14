#ifndef _ITERATOR_HPP
#define _ITERATOR_HPP

namespace ani{
    class input_iterator_tag { };

    class output_iterator_tag { };

    class forward_iterator_tag : public input_iterator_tag { };

    class bidirectional_iterator_tag : public forward_iterator_tag { };

    class random_access_iterator_tag : public bidirectional_iterator_tag { };

    template <typename T>
    class simple_type{
        public:
            using value_type = T;
            using size_type = size_t;
            using difference_type = ptrdiff_t;
            using pointer = value_type*;
            using const_pointer = const value_type*;
    };

    template <typename BiDirIt>
    class reverse_iterator{
        public:
            using iterator_category = typename BiDirIt::iterator_category;
            using value_type = typename BiDirIt::value_type;
            using difference_type = typename BiDirIt::difference_type;
            using pointer = typename BiDirIt::pointer;
            using reference = typename BiDirIt::reference;

        protected:
            BiDirIt curr;

        public:
            reverse_iterator() : curr() { }

            reverse_iterator(BiDirIt _curr) : curr(_curr) { }

            reverse_iterator& operator+=(const difference_type _off){
                curr -= _off;
                return *this;
            }

            reverse_iterator operator+(const difference_type _off){
                return reverse_iterator(curr - _off);
            }

            reverse_iterator& operator-=(const difference_type _off){
                curr += _off;
                return *this;
            }

            reverse_iterator operator-(const difference_type _off){
                return reverse_iterator(curr + _off);
            }

            reference operator[](const difference_type _off) const{
                return curr[-_off - 1];
            }

            reverse_iterator& operator++(){
                --curr;
                return *this;
            }

            reverse_iterator operator++(int){
                reverse_iterator tmp = *this;
                --curr;
                return tmp;
            }

            reverse_iterator& operator--(){
                ++curr;
                return *this;
            }

            reverse_iterator operator--(int){
                reverse_iterator tmp = *this;
                ++curr;
                return tmp;
            }

            pointer operator->() const{
                BiDirIt tmp = curr;
                --tmp;
                return tmp.operator->(); 
            }

            reference operator*() const{
                BiDirIt tmp = curr;
                return *--tmp;
            }

            BiDirIt base() const { return curr; }
    };

    template <typename BiDirIt>    
    bool operator==(const reverse_iterator<BiDirIt>& left, const reverse_iterator<BiDirIt>& right) {
        return (left.base() == right.base()); 
    }

    template <typename BiDirIt>    
    bool operator!=(const reverse_iterator<BiDirIt>& left, const reverse_iterator<BiDirIt>& right) {
        return (left.base() != right.base()); 
    }

    template <typename BiDirIt>    
    bool operator<(const reverse_iterator<BiDirIt>& left, const reverse_iterator<BiDirIt>& right) {
        return (left.base() < right.base()); 
    }

    template <typename BiDirIt>    
    bool operator>(const reverse_iterator<BiDirIt>& left, const reverse_iterator<BiDirIt>& right) {
        return (left.base() > right.base()); 
    }

    template <typename BiDirIt>    
    bool operator<=(const reverse_iterator<BiDirIt>& left, const reverse_iterator<BiDirIt>& right) {
        return (left.base() <= right.base()); 
    }

    template <typename BiDirIt>    
    bool operator>=(const reverse_iterator<BiDirIt>& left, const reverse_iterator<BiDirIt>& right) {
        return (left.base() >= right.base()); 
    }

    template <typename BiDirIt>    
    typename BiDirIt::difference_type operator-(const reverse_iterator<BiDirIt>& left, const reverse_iterator<BiDirIt>& right) {
        return (right.base() - left.base());
    }

    template <typename InputIt>
    void _advance(InputIt& it, typename InputIt::difference_type n, input_iterator_tag){
        while(n > 0){
            --n;
            ++it;
        }
    }

    template <typename BiDirIt>
    void _advance(BiDirIt& it, typename BiDirIt::difference_type n, bidirectional_iterator_tag){
        while(n > 0){
            --n;
            ++it;
        }

        while(n < 0){
            ++n;
            --it;
        }
    }

    template <typename RandomIt>
    void _advance(RandomIt& it, typename RandomIt::difference_type n, random_access_iterator_tag){
        it += n;
    }

    template <typename InputIt, typename Distance>
    void advance(InputIt& it, Distance n){
        _advance(it, n, typename InputIt::iterator_category());
    }

    template <typename InputIt>
    typename InputIt::difference_type _distance(InputIt first, InputIt last, input_iterator_tag){
        typename InputIt::difference_type n = 0;
        while(first != last){
            ++n;
            ++first;
        }
        return n;
    }

    template <typename RandomIt>
    typename RandomIt::difference_type _distance(RandomIt first, RandomIt last, random_access_iterator_tag){
        return last - first;
    }

    template <typename InputIt>
    typename InputIt::difference_type distance(InputIt first, InputIt last){
        return _distance(first, last, typename InputIt::iterator_category());
    }

    template <typename InputIt>
    InputIt next(InputIt it, typename InputIt::difference_type n = 1){
        advance(it, n);
        return it;
    }

    template <typename BidirIt>
    BidirIt prev(BidirIt it, typename BidirIt::difference_type n = 1){
        advance(it, -n);
        return it;
    }
}

#endif // _ITERATOR_HPP
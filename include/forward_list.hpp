#ifndef _FORWARD_LIST_HPP
#define _FORWARD_LIST_HPP

#include "exception\forward_list_exception.hpp"
#include "iterator.hpp"
#include "functional.hpp"

namespace ani{
    template <typename MyForwardList>
    class _forward_list_const_iterator;

    template <typename MyForwardList>
    class _forward_list_iterator;

    template <typename T>
    class forward_list;

    template <typename MyForwardList>
    class forward_list_node{
        using value_type = typename MyForwardList::value_type;

        friend class _forward_list_const_iterator<MyForwardList>;
        friend class _forward_list_iterator<MyForwardList>;
        friend class forward_list<value_type>;

        private:
            value_type data;
            forward_list_node<MyForwardList>* next;

            forward_list_node(const value_type& _data = value_type()) : data(_data), next(nullptr) { }
    };

    template <typename MyForwardList>
    class _forward_list_const_iterator{
        public:
            using iterator_category = ani::forward_iterator_tag;
            using value_type = typename MyForwardList::value_type;
            using difference_type = typename MyForwardList::difference_type;
            using pointer = typename MyForwardList::const_pointer;
            using reference = const value_type&;
            using T_ptr = forward_list_node<MyForwardList>*;

        protected:
            T_ptr ptr;

        public:
            _forward_list_const_iterator(T_ptr _ptr = nullptr) : ptr(_ptr) { }

            _forward_list_const_iterator& operator++(){
                ptr = ptr->next;
                return *this;
            }

            _forward_list_const_iterator operator++(int){
                _forward_list_const_iterator tmp(ptr);
                ptr = ptr->next;
                return tmp;
            }

            pointer operator->() const { return &(ptr->data); }
            
            reference operator*() const { return ptr->data; }

            bool operator==(const _forward_list_const_iterator& other) const { return ptr == other.ptr; }

            bool operator!=(const _forward_list_const_iterator& other) const { return ptr != other.ptr; }

            const T_ptr _unwrapped() const { return ptr; }
    };

    template <typename MyForwardList>
    class _forward_list_iterator : public _forward_list_const_iterator<MyForwardList>{
        public:
            using iterator_category = ani::forward_iterator_tag;
            using value_type = typename MyForwardList::value_type;
            using difference_type = typename MyForwardList::difference_type;
            using pointer = typename MyForwardList::pointer;
            using reference = value_type&;

        public:
            _forward_list_iterator(forward_list_node<MyForwardList>* _ptr = nullptr) : _forward_list_const_iterator<MyForwardList>(_ptr) { }

            _forward_list_iterator& operator++(){
                _forward_list_const_iterator::operator++();
                return *this;
            }

            _forward_list_iterator operator++(int){
                _forward_list_iterator tmp(ptr);
                _forward_list_const_iterator::operator++();
                return tmp;
            }

            pointer operator->() const { return &(ptr->data); }
            
            reference operator*() const { return ptr->data; }

            forward_list_node<MyForwardList>* _unwrapped() const { return ptr; }
    };

    template <typename T>
    class forward_list{
        public:
            using value_type = T;
            using size_typt = size_t;
            using difference_type = ptrdiff_t;
            using pointer = T*;
            using const_pointer = const T*;
            using reference = T&;
            using const_reference = const T&;

            using simple_val = simple_type<T>;
            using iterator = _forward_list_iterator<simple_val>;
            using const_iterator = _forward_list_const_iterator<simple_val>;

        private:
            forward_list_node<simple_val>* head;

        public:
            class iterator;
            class const_iterator;

        public:
            forward_list() : head(new forward_list_node<simple_val>()) { }

            forward_list(size_t count, const T& val = T()) : forward_list() { insert_after(cbefore_begin(), count, val); }

            template <typename InputIt, std::enable_if_t<!std::is_integral_v<InputIt>, int> = 0>
            forward_list(InputIt first, InputIt last) : forward_list() { insert_after(cbefore_begin(), first, last); }

            forward_list(const forward_list& other) : forward_list(other.begin(), other.end()) { }

            forward_list(forward_list&& other){
                head = other.head;
                other.head = new forward_list_node<simple_val>();
                other.head->next = nullptr;
            }

            forward_list(std::initializer_list<T> init_list) : forward_list(init_list.begin(), init_list.end()) { }

            ~forward_list(){
                clear();
                delete head;
                head = nullptr;
            }

            forward_list& operator=(const forward_list& other){
                if(&other == this)
                    return *this;
                clear();
                insert_after(cbefore_begin(), other.begin(), other.end());
                return *this;
            }

            forward_list& operator=(forward_list&& other){
                if(&other == this)
                    return *this;
                clear();

                head->next = other.head->next;
                other.head->next = nullptr;
                return *this;
            }

            forward_list& operator=(std::initializer_list<T> init_list){
                clear();
                insert_after(cbefore_begin(), init_list.begin(), init_list.end());
                return *this;
            }

            void assign(size_t count, const T& val){
                clear();
                insert_after(cbefore_begin(), count, val);
            }

            template <typename InputIt, std::enable_if_t<!std::is_integral_v<InputIt>, int> = 0>
            void assign(InputIt first, InputIt last){
                clear();
                insert_after(cbefore_begin(), first, last);
            }

            void assign(std::initializer_list<T> init_list){
                clear();
                insert_after(cbefore_begin(), init_list.begin(), init_list.end());
            }

            T& front(){
                if(empty())
                    throw fl_empty();
                return head->next->data;
            }

            const T& front() const{
                if(empty())
                    throw fl_empty();
                return head->next->data;
            }

            bool empty() const { return head->next == nullptr; }
            
            void clear() { erase_after(cbefore_begin(), cend()); }

            iterator insert_after(const_iterator pos, const T& val){
                if(pos._unwrapped() == nullptr)
                    throw fl_invalid_iterator();
                _push(pos._unwrapped(), new forward_list_node<simple_val>(val), pos._unwrapped()->next);
                return iterator(pos._unwrapped()->next);
            }

            iterator insert_after(const_iterator pos, T&& val){
                if(pos._unwrapped() == nullptr)
                    throw fl_invalid_iterator();
                _push(pos._unwrapped(), new forward_list_node<simple_val>(std::move(val)), pos._unwrapped()->next);
                return iterator(pos._unwrapped()->next);
            }

            iterator insert_after(const_iterator pos, size_t count, const T& val){
                if(count == 0)
                    return iterator(pos._unwrapped());

                if(pos._unwrapped() == nullptr)
                    throw fl_invalid_iterator();
                forward_list_node<simple_val>* ret_node = pos._unwrapped();
                while(count--){
                    insert_after(pos, val);
                    ++pos;
                }
                return iterator(ret_node->next);
            }

            template <typename InputIt, std::enable_if_t<!std::is_integral_v<InputIt>, int> = 0>
            iterator insert_after(const_iterator pos, InputIt first, InputIt last){
                if(pos._unwrapped() == nullptr)
                    throw fl_invalid_iterator();

                if(first == last)
                    return iterator(pos._unwrapped());
                forward_list_node<simple_val>* ret_node = pos._unwrapped();
                for(InputIt iter = first; iter != last; ++iter){
                    insert_after(pos, *iter);
                    ++pos;
                }
                return iterator(ret_node->next);
            }

            iterator insert_after(const_iterator pos, std::initializer_list<T> init_list){
                return insert_after(pos, init_list.begin(), init_list.end());
            }

            iterator erase_after(const_iterator pos){
                if(pos == cend() || pos._unwrapped()->next == nullptr)
                    return end();

                _pop(pos._unwrapped(), pos._unwrapped()->next);
                return iterator(pos._unwrapped()->next);
            }

            iterator erase_after(const_iterator first, const_iterator last){
                if(first == last)
                    return iterator(last._unwrapped());
                    
                while(first._unwrapped()->next != last._unwrapped()){
                    _pop(first._unwrapped(), first._unwrapped()->next);
                }
                
                return iterator(last._unwrapped());
            }

            void push_front(const T& val) { _push(head, new forward_list_node<simple_val>(val), head->next); }

            void push_front(T&& val) { _push(head, new forward_list_node<simple_val>(std::move(val)), head->next); }

            void pop_front(){
                if(empty())
                    throw fl_empty();
                _pop(head, head->next);
            }

            void resize(size_t count){ resize(count, T()); }

            void resize(size_t count, const T& val){
                size_t nr_elements = 0;

                const_iterator bfr_iter = cbefore_begin();
                const_iterator iter = cbegin();
                for(; iter != cend(); ++iter){
                    ++nr_elements;
                    if(nr_elements > count){
                        erase_after(bfr_iter, cend());
                        return;
                    }
                    ++bfr_iter;
                }
                
                if(count == nr_elements)
                    return;
                else
                    insert_after(bfr_iter, count - nr_elements, val);
            }

            void swap(forward_list& other){
                forward_list_node<simple_val>* temp_head = other.head;
                other.head = head;
                head = temp_head;
            }

            void merge(forward_list& other) { merge(other, ani::less<T>()); }

            void merge(forward_list&& other) { merge(other, ani::less<T>()); }

            template <typename Compare>
            void merge(forward_list& other, Compare comp){
                if(other.empty() || &other == this)
                    return;
                
                forward_list_node<simple_val>* run_1 = head->next;
                forward_list_node<simple_val>* run_2 = other.head->next;
                forward_list_node<simple_val>* prev_run_1 = head;
                forward_list_node<simple_val>* next_run_2;

                while(run_1 != nullptr && run_2 != nullptr){
                    if(comp(run_1->data, run_2->data)){
                        prev_run_1 = run_1;
                        run_1 = run_1->next;
                    }
                    else{
                        next_run_2 = run_2->next;
                        _push(prev_run_1, run_2, run_1);
                        prev_run_1 = run_2;
                        run_2 = next_run_2;
                    }
                }

                if(run_1 == nullptr && run_2 != nullptr)
                    prev_run_1->next = run_2;

                other.head->next = nullptr;
            }

            template <typename Compare>
            void merge(forward_list&& other, Compare comp) { merge(other, comp); }

            size_t remove(const T& val){
                size_t count = 0;
                iterator ret_iter;
                const_iterator bfr_iter = cbefore_begin();
                for(const_iterator iter = cbegin(); iter != cend(); ){
                    if(*iter == val){
                        ret_iter = erase_after(bfr_iter);
                        ++count;
                        iter = const_iterator(ret_iter._unwrapped());
                    }
                    else{
                        ++iter;
                        ++bfr_iter;
                    }
                }
                return count;
            }

            void reverse(){
                forward_list_node<simple_val>* curr = head->next;
                forward_list_node<simple_val>* next_curr = nullptr;
                forward_list_node<simple_val>* run = nullptr;

                while(curr != nullptr){
                    next_curr = curr->next;
                    curr->next = run;
                    run = curr;
                    curr = next_curr;
                }
                head->next = run;
            }

            template <typename Compare>
            void sort(Compare comp){
                if(empty() || head->next->next == nullptr)
                    return;

                forward_list_node<simple_val>* run = head->next;
                size_t len = 0;
                while(run != nullptr){
                    ++len;
                    run = run->next;
                }

                forward_list_node<simple_val>* left = nullptr;
                forward_list_node<simple_val>* right = nullptr;
                forward_list_node<simple_val>* tail = head->next;

                for(size_t step = 1; step < len; step <<= 1){
                    forward_list_node<simple_val>* curr = head->next;
                    tail = head;
                    while(curr != nullptr){
                        left = curr;
                        right = _partition(left, step);
                        curr = _partition(right, step);
                        tail = _merge(left, right, tail, comp);
                    }
                }
            }

            void sort() { sort(ani::less<T>()); }

        private:
            template <typename Compare>
            static forward_list_node<simple_val>* _merge(forward_list_node<simple_val>* left, forward_list_node<simple_val>* right, forward_list_node<simple_val>* tail, Compare cmp){
                forward_list_node<simple_val>* cur = tail;
                
                while(left != nullptr && right != nullptr){
                    if(cmp(left->data, right->data)){
                        cur->next = left;
                        cur = left;
                        left = left->next;
                    }
                    else{
                        cur->next = right;
                        cur = right;
                        right = right->next;
                    }
                }
                if(left != nullptr)
                    cur->next = left;
                else
                    cur->next = right;
                
                while(cur->next != nullptr)
                    cur = cur->next;
                return cur;
            }

            static forward_list_node<simple_val>* _partition(forward_list_node<simple_val>* curr, size_t n){
                for(size_t i = 1; curr != nullptr && i < n; ++i)
                    curr = curr->next;
                
                if(curr == nullptr)
                    return nullptr;
                
                forward_list_node<simple_val>* new_right = curr->next;
                curr->next = nullptr;
                
                return new_right;
            }

            static void _push(forward_list_node<simple_val>* beg, forward_list_node<simple_val>* mid, forward_list_node<simple_val>* end){
                mid->next = end;
                beg->next = mid;
            }

            static void _pop(forward_list_node<simple_val>* before, forward_list_node<simple_val>* del){
                before->next = del->next;
                delete del;
            }

        public:
            iterator begin() { return iterator(head->next); }

            iterator end() { return iterator(nullptr); }

            const_iterator begin() const { return const_iterator(head->next); }

            const_iterator end() const { return const_iterator(nullptr); }

            const_iterator cbegin() const { return begin(); }

            const_iterator cend() const { return end(); }

            iterator before_begin() { return iterator(head); }

            const_iterator before_begin() const { return const_iterator(head); }

            const_iterator cbefore_begin() const { return before_begin(); }
    };

    template <typename T>
    bool operator==(const forward_list<T>& lhs, const forward_list<T>& rhs){
        typename forward_list<T>::const_iterator l_iter = lhs.cbegin();
        typename forward_list<T>::const_iterator r_iter = rhs.cbegin();
        for(; l_iter != lhs.cend() && r_iter != rhs.cend(); ++l_iter, ++r_iter){
            if(*l_iter != *r_iter)
                return false;
        }
        return l_iter == lhs.cend() && r_iter == rhs.cend();
    }

    template <typename T>
    bool operator!=(const forward_list<T>& lhs, const forward_list<T>& rhs) { return !(lhs == rhs); }

    template <typename T>
    bool operator<(const forward_list<T>& lhs, const forward_list<T>& rhs){
        typename forward_list<T>::const_iterator l_iter = lhs.cbegin();
        typename forward_list<T>::const_iterator r_iter = rhs.cbegin();
        for(; l_iter != lhs.cend() && r_iter != rhs.cend(); ++l_iter, ++r_iter){
            if(*l_iter < *r_iter)
                return true;
            if(*r_iter < *l_iter)
                return false;
        }
        return l_iter == lhs.cend() && r_iter != rhs.cend();
    }

    template <typename T>
    bool operator>(const forward_list<T>& lhs, const forward_list<T>& rhs) { return rhs < lhs; }

    template <typename T>
    bool operator<=(const forward_list<T>& lhs, const forward_list<T>& rhs) { return !(rhs < lhs); }

    template <typename T>
    bool operator>=(const forward_list<T>& lhs, const forward_list<T>& rhs) { return !(lhs < rhs); }

    template <typename T>
    void swap(forward_list<T>& lhs, forward_list<T>& rhs) { lhs.swap(rhs); }
}

#endif // _LIST_HPP
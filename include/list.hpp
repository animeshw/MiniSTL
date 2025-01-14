#ifndef _LIST_HPP
#define _LIST_HPP

#include "exception\list_exception.hpp"
#include "iterator.hpp"
#include "functional.hpp"

namespace ani{
    template <typename MyList>
    class _list_const_iterator;

    template <typename MyList>
    class _list_iterator;

    template <typename T>
    class list;

    template <typename MyList>
    class list_node{
        using value_type = typename MyList::value_type;
        
        friend class _list_const_iterator<MyList>;
        friend class _list_iterator<MyList>;
        friend class list<value_type>;

        private:
            value_type data;
            list_node<MyList>* prev;
            list_node<MyList>* next;
            
            list_node(const value_type& _data = value_type()) : data(_data), prev(nullptr), next(nullptr) { }
    };

    template <typename MyList>
    class _list_const_iterator{
        public:
            using iterator_category = ani::bidirectional_iterator_tag;
            using value_type = typename MyList::value_type;
            using difference_type = typename MyList::difference_type;
            using pointer = typename MyList::const_pointer;
            using reference = const value_type&;
            using T_ptr = list_node<MyList>*;

        protected:
            T_ptr ptr;

        public:
            _list_const_iterator(T_ptr _ptr = nullptr) : ptr(_ptr) { }

            _list_const_iterator& operator++(){
                ptr = ptr->next;
                return *this;
            }

            _list_const_iterator operator++(int){
                _list_const_iterator tmp(ptr);
                ptr = ptr->next;
                return tmp;
            }

            _list_const_iterator& operator--(){
                ptr = ptr->prev;
                return *this;
            }

            _list_const_iterator operator--(int){
                _list_const_iterator tmp(ptr);
                ptr = ptr->prev;
                return tmp;
            }

            pointer operator->() const { return &(ptr->data); }
            
            reference operator*() const { return ptr->data; }

            bool operator==(const _list_const_iterator& other) const { return ptr == other.ptr; }

            bool operator!=(const _list_const_iterator& other) const { return ptr != other.ptr; }

            const T_ptr _unwrapped() const { return ptr; }
    };

    template <typename MyList>
    class _list_iterator : public _list_const_iterator<MyList>{
        public:
            using iterator_category = ani::bidirectional_iterator_tag;
            using value_type = typename MyList::value_type;
            using difference_type = typename MyList::difference_type;
            using pointer = typename MyList::pointer;
            using reference = value_type&;

        public:
            _list_iterator(list_node<MyList>* _ptr = nullptr) : _list_const_iterator<MyList>(_ptr) { }

            _list_iterator& operator++(){
                _list_const_iterator::operator++();
                return *this;
            }

            _list_iterator operator++(int){
                _list_iterator tmp(ptr);
                _list_const_iterator::operator++();
                return tmp;
            }

            _list_iterator& operator--(){
                _list_const_iterator::operator--();
                return *this;
            }

            _list_iterator operator--(int){
                _list_iterator tmp(ptr);
                _list_const_iterator::operator--();
                return tmp;
            }

            pointer operator->() const { return &(ptr->data); }
            
            reference operator*() const { return ptr->data; }

            list_node<MyList>* _unwrapped() const { return ptr; }
    };

    template <typename T>
    class list{
        public:
            using value_type = T;
            using size_typt = size_t;
            using difference_type = ptrdiff_t;
            using pointer = T*;
            using const_pointer = const T*;
            using reference = T&;
            using const_reference = const T&;

            using simple_val = simple_type<T>;
            using iterator = _list_iterator<simple_val>;
            using const_iterator = _list_const_iterator<simple_val>;
            using reverse_iterator = ani::reverse_iterator<iterator>;
            using const_reverse_iterator = ani::reverse_iterator<const_iterator>;

        private:
            list_node<simple_val>* head;
            size_t nr_elements;

        public:
            list() : head(new list_node<simple_val>()), nr_elements(0){
                head->prev = head;
                head->next = head;
            }

            list(size_t count, const T& val = T()) : list() { insert(cbegin(), count, val); }

            template <typename InputIt, std::enable_if_t<!std::is_integral_v<InputIt>, int> = 0>
            list(InputIt first, InputIt last) : list() { insert(cbegin(), first, last); }

            list(const list& other) : list(other.begin(), other.end()) { }

            list(list&& other) {
                head = other.head;
                nr_elements = other.nr_elements;

                other.head = new list_node<simple_val>();
                other.head->next = other.head;
                other.head->prev = other.head;
                other.nr_elements = 0;
            }

            list(std::initializer_list<T> init_list) : list(init_list.begin(), init_list.end()) { }

            ~list(){
                clear();
                delete head;
                head = nullptr;
            }

            list& operator=(const list& other){
                if(&other == this)
                    return *this;
                clear();
                insert(cbegin(), other.begin(), other.end());
                return *this;
            }

            list& operator=(list&& other){
                if(&other == this)
                    return *this;
                clear();

                head->next = other.head->next;
                other.head->next->prev = head;
                head->prev = other.head->prev;
                other.head->prev->next = head;
                nr_elements = other.nr_elements;

                other.head->next = other.head;
                other.head->prev = other.head;
                other.nr_elements = 0;

                return *this;
            }

            list& operator=(std::initializer_list<T> init_list){
                clear();
                insert(cbegin(), init_list.begin(), init_list.end());
                return *this;
            }

            void assign(size_t count, const T& val){
                clear();
                insert(cbegin(), count, val);
            }

            template <typename InputIt, std::enable_if_t<!std::is_integral_v<InputIt>, int> = 0>
            void assign(InputIt first, InputIt last){
                clear();
                insert(cbegin(), first, last);
            }

            void assign(std::initializer_list<T> init_list){
                clear();
                insert(cbegin(), init_list.begin(), init_list.end());
            }

            T& front(){
                if(empty())
                    throw list_empty();
                return head->next->data;
            }

            const T& front() const{
                if(empty())
                    throw list_empty();
                return head->next->data;
            }

            T& back(){
                if(empty())
                    throw list_empty();
                return head->prev->data;
            }

            const T& back() const{
                if(empty())
                    throw list_empty();
                return head->prev->data;
            }

            bool empty() const { return head->next == head && head->prev == head; }

            size_t size() const { return nr_elements; }

            void clear() { erase(cbegin(), cend()); }

            iterator insert(const_iterator pos, const T& val){
                list_node<simple_val>* new_node = new list_node<simple_val>(val);
                _push(pos._unwrapped()->prev, new_node, pos._unwrapped());
                ++nr_elements;
                return iterator(new_node);
            }

            iterator insert(const_iterator pos, T&& val){
                list_node<simple_val>* new_node = new list_node<simple_val>(std::move(val));
                _push(pos._unwrapped()->prev, new_node, pos._unwrapped());
                ++nr_elements;
                return iterator(new_node);
            }

            iterator insert(const_iterator pos, size_t count, const T& val){
                if(count == 0)
                    return iterator(pos._unwrapped());
                
                list_node<simple_val>* ret_node = pos._unwrapped()->prev;
                while(count--){
                    list_node<simple_val>* new_node = new list_node<simple_val>(val);
                    _push(pos._unwrapped()->prev, new_node, pos._unwrapped());
                    ++nr_elements;
                }
                return iterator(ret_node->next);
            }

            template <typename InputIt, std::enable_if_t<!std::is_integral_v<InputIt>, int> = 0>
            iterator insert(const_iterator pos, InputIt first, InputIt last){
                if(first == last)
                    return iterator(pos._unwrapped());
                
                list_node<simple_val>* ret_node = pos._unwrapped()->prev;
                for(InputIt iter = first; iter != last; ++iter){
                    list_node<simple_val>* new_node = new list_node<simple_val>(*iter);
                    _push(pos._unwrapped()->prev, new_node, pos._unwrapped());
                    ++nr_elements;
                }
                return iterator(ret_node->next);
            }

            iterator insert(const_iterator pos, std::initializer_list<T> init_list){
                return insert(pos, init_list.begin(), init_list.end());
            }

            iterator erase(const_iterator pos){
                if(pos == cend())
                    return end();
                
                list_node<simple_val>* del_node = pos._unwrapped();
                iterator ret_iter(del_node->next);
                
                _pop(del_node);
                --nr_elements;
                return ret_iter;
            }

            iterator erase(const_iterator first, const_iterator last){
                if(first == last)
                    return iterator(last._unwrapped());

                iterator ret_iter = (last == cend()) ? end() : iterator(last._unwrapped());
            
                for(const_iterator iter = first; iter != last; )
                    iter = erase(iter);
                
                return ret_iter;
            }

            void push_front(const T& val){
                _push(head, new list_node<simple_val>(val), head->next);
                ++nr_elements;
            }

            void push_front(T&& val){
                _push(head, new list_node<simple_val>(std::move(val)), head->next);
                ++nr_elements;
            }

            void push_back(const T& val){
                _push(head->prev, new list_node<simple_val>(val), head);
                ++nr_elements;
            }

            void push_back(T&& val){
                _push(head->prev, new list_node<simple_val>(std::move(val)), head);
                ++nr_elements;
            }

            void pop_front(){
                if(empty())
                    throw list_empty();
                _pop(head->next);
                --nr_elements;
            }

            void pop_back(){
                if(empty())
                    throw list_empty();
                _pop(head->prev);
                --nr_elements;
            }

            void resize(size_t count){ resize(count, T()); }

            void resize(size_t count, const T& val){
                if(nr_elements == count)
                    return;
                
                if(count > nr_elements){
                    while(count != nr_elements)
                        push_back(val);
                }
                else{
                    while(count != nr_elements)
                        pop_back();
                }
            }

            void swap(list& other){
                list_node<simple_val>* temp_head = other.head;
                other.head = head;
                head = temp_head;

                size_t temp_size = other.nr_elements;
                other.nr_elements = nr_elements;
                nr_elements = temp_size;
            }

            void merge(list& other) { merge(other, ani::less<T>()); }

            void merge(list&& other) { merge(other, ani::less<T>()); }

            template <typename Compare>
            void merge(list& other, Compare comp){
                if(other.empty() || &other == this)
                    return;
                
                list_node<simple_val>* run_1 = head->next;
                list_node<simple_val>* run_2 = other.head->next;
                list_node<simple_val>* next_run_2;

                while(run_1 != head && run_2 != other.head){
                    if(comp(run_1->data, run_2->data))
                        run_1 = run_1->next;
                    else{
                        next_run_2 = run_2->next;
                        _push(run_1->prev, run_2, run_1);
                        run_2 = next_run_2;
                    }
                }

                if(run_1 == head){
                    while(run_2 != other.head){
                        next_run_2 = run_2->next;
                        _push(run_1->prev, run_2, run_1);
                        run_2 = next_run_2;
                    }
                }
                nr_elements += other.nr_elements;

                other.nr_elements = 0;
                other.head->next = other.head;
                other.head->prev = other.head;
            }

            template <typename Compare>
            void merge(list&& other, Compare comp) { merge(other, comp); }

            size_t remove(const T& val){
                size_t count = 0;
                iterator ret_iter;
                for(const_iterator iter = cbegin(); iter != cend(); ){
                    if(*iter != val){
                        ++iter;
                        continue;
                    }
                    ret_iter = erase(iter);
                    ++count;
                    iter = const_iterator(ret_iter._unwrapped());
                }
                return count;
            }

            void reverse(){
                list_node<simple_val>* curr = nullptr;
                list_node<simple_val>* prev_curr = nullptr;

                curr = head->prev;
                while(curr != head){
                    prev_curr = curr->prev;
                    curr->prev = curr->next;
                    curr->next = prev_curr;
                    curr = prev_curr;
                }
                prev_curr = curr->prev;
                curr->prev = curr->next;
                curr->next = prev_curr;
            }

            template <typename Compare>
            void sort(Compare comp){
                if(empty() || size() == 1)
                    return;

                list_node<simple_val>* left = nullptr;
                list_node<simple_val>* right = nullptr;
                list_node<simple_val>* tail = head->next;

                for(size_t step = 1; step < size(); step <<= 1){
                    list_node<simple_val>* curr = head->next;
                    tail = head;
                    while(curr != head){
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
            list_node<simple_val>* _merge(list_node<simple_val>* left, list_node<simple_val>* right, list_node<simple_val>* tail, Compare comp){
                list_node<simple_val>* curr = tail;

                while(left != head && right != head){
                    if(comp(left->data, right->data)){
                        curr->next = left;
                        left->prev = curr;
                        curr = left;
                        left = left->next;
                    }
                    else{
                        curr->next = right;
                        right->prev = curr;
                        curr = right;
                        right = right->next;
                    }
                }

                if(left != head){
                    curr->next = left;
                    left->prev = curr;
                }
                else{
                    curr->next = right;
                    right->prev = curr;
                }

                while(curr->next != head)
                    curr = curr->next;
                
                head->prev = curr;
                return curr;
            }

            list_node<simple_val>* _partition(list_node<simple_val>* curr, size_t n){
                for(size_t i = 1; curr != head && i < n; ++i)
                    curr = curr->next;
                
                if(curr == head)
                    return head;
                
                list_node<simple_val>* new_right = curr->next;
                curr->next = head;

                return new_right;
            }

            static void _push(list_node<simple_val>* beg, list_node<simple_val>* mid, list_node<simple_val>* end){
                mid->next = end;
                mid->prev = beg;
                beg->next = mid;
                end->prev = mid;
            }

            static void _pop(list_node<simple_val>* del){
                del->prev->next = del->next;
                del->next->prev = del->prev;
                delete del;
            }

        public:
            iterator begin() { return iterator(head->next); }

            iterator end() { return iterator(head); }

            const_iterator begin() const { return const_iterator(head->next); }

            const_iterator end() const { return const_iterator(head); }

            const_iterator cbegin() const { return begin(); }

            const_iterator cend() const { return end(); }
            
            reverse_iterator rbegin() { return reverse_iterator(end()); }

            reverse_iterator rend() { return reverse_iterator(begin()); }

            const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

            const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

            const_reverse_iterator crbegin() const { return rbegin(); }
            
            const_reverse_iterator crend() const { return rend(); }
    };

    template <typename T>
    bool operator==(const list<T>& lhs, const list<T>& rhs){
        if(lhs.size() != rhs.size())
            return false;
        typename list<T>::const_iterator l_iter = lhs.cbegin();
        typename list<T>::const_iterator r_iter = rhs.cbegin();
        for(; l_iter != lhs.cend() && r_iter != rhs.cend(); ++l_iter, ++r_iter){
            if(*l_iter != *r_iter)
                return false;
        }
        return true;
    }

    template <typename T>
    bool operator!=(const list<T>& lhs, const list<T>& rhs) { return !(lhs == rhs); }

    template <typename T>
    bool operator<(const list<T>& lhs, const list<T>& rhs){
        typename list<T>::const_iterator l_iter = lhs.cbegin();
        typename list<T>::const_iterator r_iter = rhs.cbegin();
        for(; l_iter != lhs.cend() && r_iter != rhs.cend(); ++l_iter, ++r_iter){
            if(*l_iter < *r_iter)
                return true;
            if(*r_iter < *l_iter)
                return false;
        }
        return lhs.size() < rhs.size();
    }

    template <typename T>
    bool operator>(const list<T>& lhs, const list<T>& rhs) { return rhs < lhs; }

    template <typename T>
    bool operator<=(const list<T>& lhs, const list<T>& rhs) { return !(rhs < lhs); }

    template <typename T>
    bool operator>=(const list<T>& lhs, const list<T>& rhs) { return !(lhs < rhs); }

    template <typename T>
    void swap(list<T>& lhs, list<T>& rhs) { lhs.swap(rhs); }
}

#endif // _LIST_HPP
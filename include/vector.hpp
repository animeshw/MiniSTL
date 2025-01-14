#ifndef _VECTOR_HPP
#define _VECTOR_HPP

#include "exception\vector_exception.hpp"
#include "iterator.hpp"

namespace ani{
    template <typename MyVec>
    class _vector_const_iterator{
        public:
            using iterator_category = ani::random_access_iterator_tag;
            using value_type = typename MyVec::value_type;
            using difference_type = typename MyVec::difference_type;
            using pointer = typename MyVec::const_pointer;
            using reference = const value_type&;

        protected:
            value_type* ptr;
        
        public:
            _vector_const_iterator(value_type* _ptr = nullptr) : ptr(_ptr) { }

            _vector_const_iterator& operator+=(const difference_type _off){
                ptr += _off;
                return *this;
            }

            _vector_const_iterator operator+(const difference_type _off) const{
                _vector_const_iterator tmp(ptr);
                tmp += _off;
                return tmp;
            }

            _vector_const_iterator& operator-=(const difference_type _off){
                ptr -= _off;
                return *this;
            }

            _vector_const_iterator operator-(const difference_type _off) const{
                _vector_const_iterator tmp(ptr);
                tmp -= _off;
                return tmp;
            }

            difference_type operator-(const _vector_const_iterator& right) const{
                return ptr - right.ptr;
            }

            reference operator[](const difference_type _off) const{
                return *(ptr + _off);
            }

            _vector_const_iterator& operator++(){
                ++ptr;
                return *this;
            }

            _vector_const_iterator operator++(int){
                _vector_const_iterator tmp(ptr);
                ++ptr;
                return tmp;
            }

            _vector_const_iterator& operator--(){
                --ptr;
                return *this;
            }

            _vector_const_iterator operator--(int){
                _vector_const_iterator tmp(ptr);
                --ptr;
                return tmp;
            }

            pointer operator->() const{ return ptr; }

            reference operator*() const{ return *ptr; }

            bool operator==(const _vector_const_iterator& other) const{ return ptr == other.ptr; }

            bool operator!=(const _vector_const_iterator& other) const{ return !(ptr == other.ptr); }

            bool operator<(const _vector_const_iterator& other) const{ return ptr < other.ptr; }

            bool operator>(const _vector_const_iterator& other) const{ return other.ptr < ptr; }

            bool operator<=(const _vector_const_iterator& other) const{ return !(other.ptr < ptr); }

            bool operator>=(const _vector_const_iterator& other) const{ return !(ptr < other.ptr); }

            value_type* _unwrapped() const { return ptr; }
    };

    template <typename MyVec>
    class _vector_iterator : public _vector_const_iterator<MyVec>{
        public:
            using iterator_category = ani::random_access_iterator_tag;
            using value_type = typename MyVec::value_type;
            using difference_type = typename MyVec::difference_type;
            using pointer = typename MyVec::pointer;
            using reference = value_type&;

        public:
            _vector_iterator(pointer _ptr = nullptr) : _vector_const_iterator<MyVec>(_ptr) { }

            _vector_iterator& operator+=(const difference_type _off){
                _vector_const_iterator<MyVec>::operator+=(_off);
                return *this;
            }

            _vector_iterator operator+(const difference_type _off) const{
                _vector_iterator tmp(ptr);
                tmp += _off;
                return tmp;
            }

            _vector_iterator& operator-=(const difference_type _off){
                _vector_const_iterator<MyVec>::operator-=(_off);
                return *this;
            }

            _vector_iterator operator-(const difference_type _off) const{
                _vector_iterator tmp(ptr);
                tmp -= _off;
                return tmp;
            }

            difference_type operator-(const _vector_iterator& right) const{
                return _vector_const_iterator<MyVec>::operator-(right);
            }

            reference operator[](const difference_type _off) const{
                return const_cast<reference>(_vector_const_iterator<MyVec>::operator[](_off));
            }

            _vector_iterator& operator++(){
                _vector_const_iterator<MyVec>::operator++();
                return *this;
            }

            _vector_iterator operator++(int){
                _vector_iterator tmp(ptr);
                _vector_const_iterator<MyVec>::operator++();
                return tmp;
            }

            _vector_iterator& operator--(){
                _vector_const_iterator<MyVec>::operator--();
                return *this;
            }

            _vector_iterator operator--(int){
                _vector_iterator tmp(ptr);
                _vector_const_iterator<MyVec>::operator--();
                return tmp;
            }

            pointer operator->() { return ptr; }
            
            reference operator*() { return *ptr; }

            pointer _unwrapped() { return ptr; }
    };

    template <typename T>
    class vector{
        private:
            T* elements;
            size_t nr_elements;
            size_t cap;

            static const int DEFAULT_CAPACITY = 8;

        public:
            using value_type = T;
            using size_typt = size_t;
            using difference_type = ptrdiff_t;
            using pointer = T*;
            using const_pointer = const T*;
            using reference = T&;
            using const_reference = const T&;

            using simple_val = simple_type<T>;
            using iterator = _vector_iterator<simple_val>;
            using const_iterator = _vector_const_iterator<simple_val>;
            using reverse_iterator = ani::reverse_iterator<iterator>;
            using const_reverse_iterator = ani::reverse_iterator<const_iterator>;

        public:
            vector() : vector(DEFAULT_CAPACITY) { }

            vector(size_t new_cap) : elements(new T[new_cap]), nr_elements(0), cap(new_cap) { }

            vector(size_t new_cap, const T& val) : elements(new T[new_cap]), nr_elements(new_cap), cap(new_cap){
                for(size_t i = 0; i < nr_elements; ++i)
                    elements[i] = val;
            }

            template <typename InputIt, std::enable_if_t<!std::is_integral_v<InputIt>, int> = 0>
            vector(InputIt first, InputIt last) : vector() { insert(cbegin(), first, last); }

            vector(const vector& other) : vector(other.cap) { insert(cbegin(), other.cbegin(), other.cend()); }

            vector(vector&& other){
                elements = other.elements;
                other.elements = new T[other.cap];

                nr_elements = other.nr_elements;
                other.nr_elements = 0;

                cap = other.cap;
            }
            
            vector(std::initializer_list<T> init_list) : vector(init_list.begin(), init_list.end()) { }

            ~vector() { delete[] elements; }

            vector& operator=(const vector& other){
                if(&other == this)
                    return *this;
                delete[] elements;
                nr_elements = 0;
                elements = new T[other.cap]();
                insert(cbegin(), other.cbegin(), other.cend());
                return *this;
            }

            vector& operator=(vector&& other){
                if(&other == this)
                    return *this;
                
                delete[] elements;
                elements = other.elements;
                other.elements = new T[other.cap];

                nr_elements = other.nr_elements;
                other.nr_elements = 0;

                cap = other.cap;

                return *this;
            }

            vector& operator=(std::initializer_list<T> init_list){
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

            T& at(size_t pos){
                if(empty())
                    throw vector_empty();
                if(pos < 0 || pos >= nr_elements)
                    throw vector_out_of_range();
                return elements[pos];
            }

            const T& at(size_t pos) const{
                if(empty())
                    throw vector_empty();
                if(pos < 0 || pos >= nr_elements)
                    throw vector_out_of_range();
                return elements[pos];
            }

            T& operator[](size_t pos){
                if(empty())
                    throw vector_empty();
                if(pos < 0 || pos >= nr_elements)
                    throw vector_out_of_range();
                return elements[pos];
            }

            const T& operator[](size_t pos) const{
                if(empty())
                    throw vector_empty();
                if(pos < 0 || pos >= nr_elements)
                    throw vector_out_of_range();
                return elements[pos];
            }

            T& front() { return at(0); }

            const T& front() const { return at(0); }

            T& back() { return at(nr_elements - 1); }

            const T& back() const { return at(nr_elements - 1); }

            T* data() { return elements; }

            const T* data() const { return elements; }

            bool empty() const { return nr_elements == 0; }

            size_t size() const { return nr_elements; }

            void reserve(size_t new_cap){
                if(cap < new_cap){
                    cap = new_cap;
                    T* new_elements = new T[cap];
                    for(size_t i = 0; i < nr_elements; ++i)
                        new_elements[i] = elements[i];
                    delete[] elements;
                    elements = new_elements;
                }
            }

            size_t capacity() const { return cap; }

            void clear(){ 
                delete[] elements;
                elements = new T[cap];
                nr_elements = 0;
            }

            iterator insert(const_iterator pos, const T& val){
                if(nr_elements == cap){
                    cap *= 2;
                    T* new_elements = new T[cap];
                    
                    size_t i = 0;
                    const_iterator iter;
                    for(iter = cbegin() ; iter != pos; ++iter)
                        new_elements[i++] = *iter;
                    
                    iterator ret_iter(new_elements + i);
                    new_elements[i++] = val;

                    for(iter = pos; iter != cend(); ++iter)
                        new_elements[i++] = *iter;

                    delete[] elements;
                    elements = new_elements;

                    ++nr_elements;
                    return ret_iter;
                }
                else if(pos == cend()){
                    elements[nr_elements++] = val;
                    return iterator(elements + nr_elements - 1);
                }
                else{
                    T temp1 = *pos;
                    T temp2 = *pos;
                    iterator ret_iter(pos._unwrapped());

                    while(++pos != cend()){
                        temp1 = *pos;
                        const_cast<T&>(*pos) = temp2;
                        temp2 = temp1;
                    }

                    elements[nr_elements++] = temp1;
                    *ret_iter = val;

                    return ret_iter;
                }
            }

            iterator insert(const_iterator pos, T&& val){
                if(nr_elements == cap){
                    cap *= 2;
                    T* new_elements = new T[cap];
                    
                    size_t i = 0;
                    const_iterator iter;
                    for(iter = cbegin() ; iter != pos; ++iter)
                        new_elements[i++] = *iter;
                    
                    iterator ret_iter(new_elements + i);
                    new_elements[i++] = std::move(val);

                    for(iter = pos; iter != cend(); ++iter)
                        new_elements[i++] = *iter;

                    delete[] elements;
                    elements = new_elements;

                    ++nr_elements;
                    return ret_iter;
                }
                else if(pos == cend()){
                    elements[nr_elements++] = std::move(val);
                    return iterator(elements + nr_elements - 1);
                }
                else{
                    T temp1 = *pos;
                    T temp2 = *pos;
                    iterator ret_iter(pos._unwrapped());

                    while(++pos != cend()){
                        temp1 = *pos;
                        const_cast<T&>(*pos) = temp2;
                        temp2 = temp1;
                    }

                    elements[nr_elements++] = temp1;
                    *ret_iter = std::move(val);

                    return ret_iter;
                }
            }

            iterator insert(const_iterator pos, size_t count, const T& val){
                if(nr_elements + count > cap){
                    while(nr_elements + count > cap)
                        cap *= 2;
                    T* new_elements = new T[cap];

                    size_t cnt = count;
                    size_t i = 0;
                    const_iterator iter;
                    for(iter = cbegin(); iter != pos; ++iter)
                        new_elements[i++] = *iter;
                    
                    iterator ret_iter(new_elements + i);
                    while(cnt--)
                        new_elements[i++] = val;

                    for(iter = pos; iter != cend(); ++iter)
                        new_elements[i++] = *iter;

                    delete[] elements;
                    elements = new_elements;

                    nr_elements += count;
                    return ret_iter;
                }
                else if(pos == cend()){
                    size_t cnt = count;
                    while(cnt--)
                        elements[nr_elements++] = val;
                    return iterator(elements + nr_elements - count);
                }
                else{
                    size_t i;
                    for(i = nr_elements - 1; (elements + i) != pos._unwrapped(); --i)
                        elements[i + count] = elements[i];
                    elements[i + count] = elements[i];

                    iterator ret_iter(pos._unwrapped());
                    size_t cnt = count;

                    while(cnt--){
                        const_cast<T&>(*pos) = val;
                        ++pos;
                    }
                    nr_elements += count;
                    return ret_iter;
                }
            }

            template <typename InputIt, std::enable_if_t<!std::is_integral_v<InputIt>, int> = 0>
            iterator insert(const_iterator pos, InputIt first, InputIt last){
                if(first == last)
                    return iterator(pos._unwrapped());
                
                size_t count = 0;
                InputIt iter = first;
                while(iter != last){
                    ++count;
                    ++iter;
                }
                
                if(nr_elements + count > cap){
                    while(nr_elements + count > cap)
                        cap *= 2;
                    T* new_elements = new T[cap];

                    size_t i = 0;
                    const_iterator iter;
                    for(iter = cbegin() ; iter != pos; ++iter)
                        new_elements[i++] = *iter;
                    
                    iterator ret_iter(new_elements + i);
                    for(InputIt it = first; it != last; ++it)
                        new_elements[i++] = *it;

                    for(iter = pos; iter != cend(); ++iter)
                        new_elements[i++] = *iter;

                    delete[] elements;
                    elements = new_elements;

                    nr_elements += count;
                    return ret_iter;
                }
                else if(pos == cend()){
                    for(InputIt it = first; it != last; ++it)
                        elements[nr_elements++] = *it;
                    return iterator(elements);
                }
                else{
                    size_t i;
                    for(i = nr_elements - 1; (elements + i) != pos._unwrapped(); --i)
                        elements[i + count] = elements[i];
                    elements[i + count] = elements[i];

                    iterator ret_iter(pos._unwrapped());
                    
                    for(InputIt it = first; it != last; ++it){
                        const_cast<T&>(*pos) = *it;
                        ++pos;
                    }
                    nr_elements += count;
                    return ret_iter;
                }
            }

            iterator insert(std::initializer_list<T> init_list) { return insert(init_list.begin(), init_list.end()); }

            iterator erase(const_iterator pos){
                if(pos == cend())
                    return end();
                
                const_iterator tmp = pos;
                iterator ret_iter(pos._unwrapped());

                while(++pos != cend()){
                    const_cast<T&>(*tmp) = *pos;
                    ++tmp;
                }
                --nr_elements;
                return ret_iter;
            }

            iterator erase(const_iterator first, const_iterator last){
                if(first == last)
                    return iterator(last._unwrapped());

                size_t count = 0;
                const_iterator iter = first;
                while(iter != last){
                    ++count;
                    ++iter;
                }
                
                if(last == cend()){
                    nr_elements -= count;
                    return end();
                }
                else{
                    for(const_iterator it = last; it != cend(); ++it)
                        *(it._unwrapped() - count) = *it;
                    nr_elements -= count;
                    return iterator(last._unwrapped() - count);
                }
            }

            void push_back(const T& val){
                if(nr_elements == cap)
                    reserve(nr_elements * 2);
                elements[nr_elements++] = val;
            }

            void push_back(T&& val){
                if(nr_elements == cap)
                    reserve(nr_elements * 2);
                elements[nr_elements++] = std::move(val);
            }

            void pop_back(){
                if(empty())
                    throw vector_empty();
                --nr_elements;
            }

            void resize(size_t count) { resize(count, T()); }

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

            void swap(vector& other){
                if(this == &other)
                    return;
                
                T* tmp_elements = other.elements;
                other.elements = elements;
                elements = tmp_elements;

                size_t temp = other.nr_elements;
                other.nr_elements = nr_elements;
                nr_elements = temp;

                temp = other.cap;
                other.cap = cap;
                cap = temp;
            }
    
            iterator begin() { return iterator(elements); }

            iterator end() { return iterator(elements + nr_elements); }

            const_iterator begin() const { return const_iterator(elements); }

            const_iterator end() const { return const_iterator(elements + nr_elements); }

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
    bool operator==(const vector<T>& lhs, const vector<T>& rhs){
        if(lhs.size() != rhs.size())
            return false;
        typename vector<T>::const_iterator l_iter = lhs.cbegin();
        typename vector<T>::const_iterator r_iter = rhs.cbegin();
        for(; l_iter != lhs.cend() && r_iter != rhs.cend(); ++l_iter, ++r_iter){
            if(*l_iter != *r_iter)
                return false;
        }
        return true;
    }

    template <typename T>
    bool operator!=(const vector<T>& lhs, const vector<T>& rhs) { return !(lhs == rhs); }

    template <typename T>
    bool operator<(const vector<T>& lhs, const vector<T>& rhs){
        typename vector<T>::const_iterator l_iter = lhs.cbegin();
        typename vector<T>::const_iterator r_iter = rhs.cbegin();
        for(; l_iter != lhs.cend() && r_iter != rhs.cend(); ++l_iter, ++r_iter){
            if(*l_iter < *r_iter)
                return true;
            if(*r_iter < *l_iter)
                return false;
        }
        return lhs.size() < rhs.size();
    }

    template <typename T>
    bool operator>(const vector<T>& lhs, const vector<T>& rhs) { return rhs < lhs; }

    template <typename T>
    bool operator<=(const vector<T>& lhs, const vector<T>& rhs) { return !(rhs < lhs); }

    template <typename T>
    bool operator>=(const vector<T>& lhs, const vector<T>& rhs) { return !(lhs < rhs); }

    template <typename T>
    void swap(vector<T>& lhs, vector<T>& rhs) { lhs.swap(rhs); }
};

#endif // _VECTOR_HPP
#ifndef _STRING_HPP
#define _STRING_HPP

#include "iterator.hpp"
#include "utility.hpp"
#include "exception\string_exception.hpp"

namespace ani{
    class _string_const_iterator{
        public:
            using iterator_category = ani::random_access_iterator_tag;
            using value_type = char;
            using difference_type = ptrdiff_t;
            using pointer = const char*;
            using reference = const char&;
        
        protected:
            char* ptr;

        public:
            _string_const_iterator(char* _ptr = nullptr) : ptr(_ptr) { }

            _string_const_iterator& operator+=(const difference_type _off){
                ptr += _off;
                return *this;
            }

            _string_const_iterator operator+(const difference_type _off) const{
                _string_const_iterator tmp(ptr);
                tmp += _off;
                return tmp;
            }

            _string_const_iterator& operator-=(const difference_type _off){
                ptr -= _off;
                return *this;
            }

            _string_const_iterator operator-(const difference_type _off) const{
                _string_const_iterator tmp(ptr);
                tmp -= _off;
                return tmp;
            }

            difference_type operator-(const _string_const_iterator& right) const{
                return ptr - right.ptr;
            }

            reference operator[](const difference_type _off) const{
                return *(ptr + _off);
            }

            _string_const_iterator& operator++(){
                ++ptr;
                return *this;
            }

            _string_const_iterator operator++(int){
                _string_const_iterator tmp(ptr);
                ++ptr;
                return tmp;
            }

            _string_const_iterator& operator--(){
                --ptr;
                return *this;
            }

            _string_const_iterator operator--(int){
                _string_const_iterator tmp(ptr);
                --ptr;
                return tmp;
            }

            pointer operator->() const{ return ptr; }

            reference operator*() const{ return *ptr; }

            bool operator==(const _string_const_iterator& other) const{ return ptr == other.ptr; }

            bool operator!=(const _string_const_iterator& other) const{ return !(ptr == other.ptr); }

            bool operator<(const _string_const_iterator& other) const{ return ptr < other.ptr; }

            bool operator>(const _string_const_iterator& other) const{ return other.ptr < ptr; }

            bool operator<=(const _string_const_iterator& other) const{ return !(other.ptr < ptr); }

            bool operator>=(const _string_const_iterator& other) const{ return !(ptr < other.ptr); }
    };

    class _string_iterator : public _string_const_iterator{
        public:
            using iterator_category = ani::random_access_iterator_tag;
            using value_type = char;
            using difference_type = ptrdiff_t;
            using pointer = char*;
            using reference = char&;

        public:
            _string_iterator(char* _ptr = nullptr) : _string_const_iterator(_ptr) { }

            _string_iterator& operator+=(const difference_type _off){
                _string_const_iterator::operator+=(_off);
                return *this;
            }

            _string_iterator operator+(const difference_type _off) const{
                _string_iterator tmp(ptr);
                tmp += _off;
                return tmp;
            }

            _string_iterator& operator-=(const difference_type _off){
                _string_const_iterator::operator-=(_off);
                return *this;
            }

            _string_iterator operator-(const difference_type _off) const{
                _string_iterator tmp(ptr);
                tmp -= _off;
                return tmp;
            }

            difference_type operator-(const _string_iterator& right) const{
                return _string_const_iterator::operator-(right);
            }

            reference operator[](const difference_type _off) const{
                return const_cast<reference>(_string_const_iterator::operator[](_off));
            }

            _string_iterator& operator++(){
                _string_const_iterator::operator++();
                return *this;
            }

            _string_iterator operator++(int){
                _string_iterator tmp(ptr);
                _string_const_iterator::operator++();
                return tmp;
            }

            _string_iterator& operator--(){
                _string_const_iterator::operator--();
                return *this;
            }

            _string_iterator operator--(int){
                _string_iterator tmp(ptr);
                _string_const_iterator::operator--();
                return tmp;
            }

            pointer operator->() { return ptr; }
            
            reference operator*() { return const_cast<reference>(_string_const_iterator::operator*()); }
    };

    class string{
        private:
            char* str;
            size_t n;
            size_t cap;

            static const size_t DEFAULT_CAPACITY = 8;

        public:
            static const size_t npos = -1;

        public:
            using value_type = char;
            using size_typt = size_t;
            using difference_type = ptrdiff_t;
            using pointer = char*;
            using const_pointer = const char*;
            using reference = char&;
            using const_reference = const char&;

            using iterator = _string_iterator;
            using const_iterator = _string_const_iterator;
            using reverse_iterator = ani::reverse_iterator<iterator>;
            using const_reverse_iterator = ani::reverse_iterator<const_iterator>;

        public:
            string() : n(0), cap(DEFAULT_CAPACITY){
                str = new char[DEFAULT_CAPACITY + 1];
                str[0] = '\0';
            }

            string(size_t count, char ch) : n(count), cap(n){
                str = new char[cap + 1];
                for(size_t i = 0; i < n; ++i)
                    str[i] = ch;
                str[n] = '\0';
            }

            string(const string& other, size_t pos) : string(other.substr(pos)) { }

            string(string&& other, size_t pos) : string(std::move(other.substr(pos))) { }

            string(const string& other, size_t pos, size_t count) : string(other.substr(pos, count)) { }

            string(string&& other, size_t pos, size_t count) : string(std::move(other.substr(pos, count))) { }

            string(const char* c_s, size_t count) : string(string(c_s).substr(0, count)) { }

            string(const char* c_s) : n(strlen(c_s)), cap(n){
                str = new char[cap + 1];
                for(size_t i = 0; i < n; ++i)
                    str[i] = c_s[i];
                str[n] = '\0';
            }

            template <typename InputIt, std::enable_if_t<!std::is_integral_v<InputIt>, int> = 0>
            string(InputIt first, InputIt last) : string(){
                for(InputIt iter = first; iter != last; ++iter)
                    push_back(*iter);
            }

            string(const string& other) : string(other.c_str()) { }

            string(string&& other){
                str = other.str;
                n = other.n;
                cap = other.cap;
                
                other.str = new char[cap + 1];
                other.n = 0;
                other.str[0] = '\0';
            }

            string(std::initializer_list<char> init_list) : string(init_list.begin(), init_list.end()) { }
            
            ~string() { delete[] str; }

            string& operator=(const string& other){
                if(&other == this)
                    return *this;
                
                delete[] str;
                cap = other.cap;
                n = other.n;
                str = new char[cap + 1];
                for(size_t i = 0; i < n; ++i)
                    str[i] = other.str[i];
                str[n] = '\0';
                return *this;
            }

            string& operator=(string&& other){
                if(&other == this)
                    return *this;
                
                delete[] str;
                cap = other.cap;
                n = other.n;
                str = other.str;
                
                other.str = new char[other.cap + 1];
                other.n = 0;
                other.str[0] = '\0';

                return *this;
            }

            string& operator=(const char* c_s){
                delete[] str;
                cap = strlen(c_s);
                n = cap;
                str = new char[cap + 1];
                for(size_t i = 0; i < n; ++i)
                    str[i] = c_s[i];
                str[n] = '\0';
                return *this;
            }

            string& operator=(const char ch){
                delete[] str;
                cap = 1;
                n = 1;
                str = new char[cap + 1];
                str[0] = ch;
                str[1] = '\0';
                return *this;
            }

            string& assign(size_t count, char ch){
                delete[] str;
                cap = count;
                n = cap;
                str = new char[cap + 1];
                for(size_t i = 0; i < n; ++i)
                    str[i] = ch;
                str[n] = '\0';
                return *this;
            }

            string& assign(const string& other){
                *this = other;
                return *this;
            }

            string& assign(const string& other, size_t pos, size_t count = npos){
                *this = other.substr(pos, count);
                return *this;
            }

            string& assign(string&& other){
                *this = std::move(other);
                return *this;
            }

            string& assign(const char* c_s, size_t count){
                *this = string(c_s).substr(0, count);
                return *this;
            }

            string& assign(const char* c_s){
                *this = c_s;
                return *this;
            }

            template <typename InputIt, std::enable_if_t<!std::is_integral_v<InputIt>, int> = 0>
            string& assign(InputIt first, InputIt last){
                *this = string(first, last);
                return *this;
            }

            string& assign(std::initializer_list<char> init_list){
                *this = string(init_list.begin(), init_list.end());
                return *this;
            }

            char& at(size_t pos){
                if(empty())
                    throw string_empty();
                if(pos < 0 || pos >= n)
                    throw string_out_of_range();
                return str[pos];
            }

            const char& at(size_t pos) const{
                if(empty())
                    throw string_empty();
                if(pos < 0 || pos >= n)
                    throw string_out_of_range();
                return str[pos];
            }

            char& operator[](size_t pos){
                if(empty())
                    throw string_empty();
                if(pos < 0 || pos >= n)
                    throw string_out_of_range();
                return str[pos];
            }

            const char& operator[](size_t pos) const{
                if(empty())
                    throw string_empty();
                if(pos < 0 || pos >= n)
                    throw string_out_of_range();
                return str[pos];
            }

            char& front(){ return at(0); }

            const char& front() const{ return at(0); }

            char& back(){ return at(n - 1); }

            const char& back() const{ return at(n - 1); }

            char* data() { return str; }

            const char* data() const { return str; }

            const char* c_str() const { return str; }

            bool empty() const{ return (n == 0 && str[0] == '\0'); }

            size_t size() const { return n; }

            size_t length() const { return n; }

            void reserve(size_t new_cap){
                if(cap < new_cap){
                    string tmp(*this);
                    cap = new_cap;
                    delete[] str;
                    str = new char[cap + 1];
                    for(size_t i = 0; i < n; ++i)  
                        str[i] = tmp[i];
                    str[n] = '\0';
                }
            }

            size_t capacity() const { return cap; }

            void clear(){
                delete[] str;
                str = new char[cap + 1];
                n = 0;
                str[n] = '\0';
            }

            string& insert(size_t index, size_t count, char ch){
                if(index > n)
                    return *this;
                if(cap < (n + count)){
                    size_t new_cap = cap;
                    while(new_cap < (n + count))
                        new_cap *= 2;
                    reserve(new_cap);
                }
                
                size_t i;
                for(i = n; i > index; --i)
                    str[i + count - 1] = str[i - 1];
                for(i = index; i < index + count; ++i)
                    str[i] = ch;
                n += count;
                str[n] = '\0';
                return *this;
            }

            string& insert(size_t index, const char* c_s) { return insert(index, string(c_s)); }

            string& insert(size_t index, const char* c_s, size_t count){ return insert(index, string(c_s).substr(0, count)) ;}

            string& insert(size_t index, const string& s){
                if(index > n)
                    return *this;
                if(cap < (n + s.size())){
                    size_t new_cap = cap;
                    while(new_cap < (n + s.size()))
                        new_cap *= 2;
                    reserve(new_cap);
                }
                
                size_t i;
                for(i = n; i > index; --i)
                    str[i + s.size() - 1] = str[i - 1];
                for(i = index; i < index + s.size(); ++i)
                    str[i] = s.str[i - index];
                n += s.size();
                str[n] = '\0';
                return *this;
            }
    
            string& insert(size_t index, const string& s, size_t s_index, size_t count = npos){ return insert(index, s.substr(s_index, count)); }

            iterator insert(const_iterator pos, char ch){ return insert(pos, 1, ch); }

            iterator insert(const_iterator pos, size_t count, char ch){
                size_t index = pos - begin();
                insert(index, count, ch);
                return iterator(str + index);
            }

            template <typename InputIt, std::enable_if_t<!std::is_integral_v<InputIt>, int> = 0>
            iterator insert(const_iterator pos, InputIt first, InputIt last){
                size_t index = pos - begin();
                insert(index, string(first, last));
                return iterator(str + index);
            }

            iterator insert(const_iterator pos, std::initializer_list<char> init_list) { return insert(pos, init_list.begin(), init_list.end()); }

            string& erase(size_t index = 0, size_t count = npos){
                if(count > n - index)
                    count = n - index;
                for(size_t i = index; i < n - count; ++i)
                    str[i] = str[i + count];
                n -= count;
                str[n] = '\0';
                return *this;
            }

            iterator erase(const_iterator pos){
                size_t index = pos - begin();
                erase(index, 1);
                return iterator(str + index);
            }

            iterator erase(const_iterator first, const_iterator last){
                size_t index = first - begin();
                erase(index, last - first);
                return iterator(str + index);
            }

            void push_back(char ch) { insert(end(), ch);  }

            void pop_back(){
                if(!empty())
                    erase(end() - 1);
            }

            string& append(size_t count, char ch) { return append(string(count, ch)); }

            string& append(const string& other){
                if(cap < (n + other.n)){
                    size_t new_cap = cap;
                    while(new_cap < (n + other.n))
                        new_cap *= 2;
                    reserve(new_cap);
                }
                for(size_t i = n; i < n + other.n; ++i)
                    str[i] = other.str[i - n];
                n += other.n;
                str[n] = '\0';
                return *this;
            }

            string& append(const string& other, size_t pos, size_t count = npos) { return append(other.substr(pos, npos)); }

            string& append(const char* c_s, size_t count) { return append(string(c_s).substr(0, count)); }

            string& append(const char* c_s) { return append(string(c_s)); }

            template <typename InputIt, std::enable_if_t<!std::is_integral_v<InputIt>, int> = 0>
            string& append(InputIt first, InputIt last) { return append(string(first, last)); }

            string& append(std::initializer_list<char> init_list) { return append(string(init_list.begin(), init_list.end())); }

            string& operator+=(const string& other) { return append(other); }

            string& operator+=(char ch) { return append(1, ch); }

            string& operator+=(const char* c_s) { return append(string(c_s)); }

            string& operator+=(std::initializer_list<char> init_list) { return append(init_list); }

            void swap(string& other){
                if(&other == this)
                    return;
                ani::swap(str, other.str);
                ani::swap(n, other.n);
                ani::swap(cap, other.cap);
            }

            size_t find(const string& other, size_t pos = 0) const{
                size_t len1 = size();
                size_t len2 = other.size();

                if(empty())
                    throw string_empty();

                if(other.empty()){
                    if(pos < n)
                        return pos;
                    else
                        return n;
                }

                if(len2 > len1)
                    return npos;

                bool is_found = false;
                for(size_t i = pos; i < len1 - len2 + 1; ++i){
                    if(str[i] == other.str[0]){
                        is_found = true;
                        for(size_t j = 1; j < len2; ++j){
                            if(str[i+j] != other.str[j]){
                                is_found = false;
                                break;
                            }
                        }
                        if(is_found)
                            return i;
                    }
                }
                return npos;
            }

            size_t find(const char* c_s, size_t pos, size_t count) const { return find(string(c_s).substr(0, count), pos); }

            size_t find(const char* c_s, size_t pos = 0) const { return find(string(c_s), pos); }

            size_t find(char ch, size_t pos = 0) const { return find(string(1, ch), pos); }

            size_t rfind(const string& other, size_t pos = 0) const{
                size_t len1 = size();
                size_t len2 = other.size();

                if(empty())
                    throw string_empty();

                if(other.empty()){
                    if(pos < n)
                        return pos;
                    else
                        return n;
                }

                if(len2 > len1)
                    return npos;

                bool is_found = false;
                for(size_t i = len1 - len2; i != npos; --i){
                    if(str[i] == other.str[0]){
                        is_found = true;
                        for(size_t j = 1; j < len2; ++j){
                            if(str[i+j] != other.str[j]){
                                is_found = false;
                                break;
                            }
                        }
                        if(is_found)
                            return i;
                    }
                }
                return npos;
            }

            size_t rfind(const char* c_s, size_t pos, size_t count) const { return rfind(string(c_s).substr(0, count), pos); }

            size_t rfind(const char* c_s, size_t pos = 0) const { return rfind(string(c_s), pos); }

            size_t rfind(char ch, size_t pos = 0) const { return rfind(string(1, ch), pos); }

            int compare(const string& other) const{
                size_t len1 = size();
                size_t len2 = other.size();
                size_t i = 0;

                while(true){
                    if(i == len1 || i == len2){
                        if(len1 == len2)
                            return 0;
                        else if(len1 > len2)
                            return 1;
                        else
                            return -1;
                    }

                    if(str[i] < other.str[i]){
                        return str[i] - other.str[i];
                    }
                    else if(str[i] > other.str[i]){
                        return str[i] - other.str[i];
                    }
                    ++i;
                }
            }

            int compare(size_t pos1, size_t count1, const string& other) const { substr(pos1, count1).compare(other); }

            int compare(size_t pos1, size_t count1, const string& other, size_t pos2, size_t count2 = npos) const { substr(pos1, count1).compare(other.substr(pos2, count2)); }

            int compare(const char* c_s) const { return compare(string(c_s)); }

            int compare(size_t pos1, size_t count1, const char* c_s) const { return substr(pos1, count1).compare(string(c_s)); }

            int compare(size_t pos1, size_t count1, const char* c_s, size_t pos2, size_t count2) const { return substr(pos1, count1).compare(string(c_s).substr(pos2, count2)); }

            string substr(size_t pos = 0, size_t count = npos) const{
                string s;
                if(count == npos || count > size() - pos)
                    count = size();
                for(size_t i = 0; i < count; ++i)
                    s.push_back(str[pos + i]);
                return s;
            }
    
            iterator begin() { return iterator(str); }

            iterator end() { return iterator(str + n); }

            const_iterator begin() const { return const_iterator(str); }
            
            const_iterator end() const { return const_iterator(str + n); }

            const_iterator cbegin() const { return begin(); }

            const_iterator cend() const { return end(); }

            reverse_iterator rbegin() { return reverse_iterator(end()); }

            reverse_iterator rend() { return reverse_iterator(begin()); }

            const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

            const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

            const_reverse_iterator crbegin() const { return rbegin(); }

            const_reverse_iterator crend() const { return rend(); }
    };

    string operator+(const string& lhs, const string rhs){
        string str(lhs);
        str.append(rhs);
        return str;
    }

    string operator+(const string& lhs, const char* rhs){
        string str(lhs);
        str.append(rhs);
        return str;
    }

    string operator+(const string& lhs, char rhs){
        string str(lhs);
        str.push_back(rhs);
        return str;
    }

    string operator+(const char* lhs, const string& rhs){
        string str(lhs);
        str.append(rhs);
        return str;
    }

    string operator+(char lhs, const string& rhs){
        string str(1, lhs);
        str.append(rhs);
        return str;
    }

    string operator+(string&& lhs, string&& rhs){
        lhs.append(rhs);
        return std::move(lhs);
    }

    string operator+(string&& lhs, const string& rhs){
        lhs.append(rhs);
        return std::move(lhs);
    }

    string operator+(string&& lhs, const char* rhs){
        lhs.append(rhs); 
        return std::move(lhs);
    }

    string operator+(string&& lhs, char rhs){
        lhs.push_back(rhs); 
        return std::move(lhs);
    }

    string operator+(const string& lhs, string&& rhs){
        rhs.insert(0, lhs);
        return std::move(rhs);
    }

    string operator+(const char* lhs, string&& rhs){
        rhs.insert(0, lhs);
        return std::move(rhs);
    }

    string operator+(char lhs, string&& rhs){
        rhs.insert(rhs.begin(), lhs);
        return std::move(rhs);
    }

    bool operator<(const string& lhs, const string& rhs) { return (lhs.compare(rhs) < 0); }

    bool operator>(const string& lhs, const string& rhs) { return (lhs.compare(rhs) > 0); }

    bool operator<=(const string& lhs, const string& rhs) { return (lhs.compare(rhs) <= 0); }

    bool operator>=(const string& lhs, const string& rhs) { return (lhs.compare(rhs) >= 0); }

    bool operator==(const string& lhs, const string& rhs) { return (lhs.compare(rhs) == 0); }

    bool operator!=(const string& lhs, const string& rhs) { return (lhs.compare(rhs) != 0); }

    bool operator<(const string& lhs, const char* rhs) { return (lhs.compare(rhs) < 0); }

    bool operator>(const string& lhs, const char* rhs) { return (lhs.compare(rhs) > 0); }

    bool operator<=(const string& lhs, const char* rhs) { return (lhs.compare(rhs) <= 0); }

    bool operator>=(const string& lhs, const char* rhs) { return (lhs.compare(rhs) >= 0); }

    bool operator==(const string& lhs, const char* rhs) { return (lhs.compare(rhs) == 0); }

    bool operator!=(const string& lhs, const char* rhs) { return (lhs.compare(rhs) != 0); }

    bool operator<(const char* lhs, const string& rhs) { return (string(lhs).compare(rhs) < 0); }

    bool operator>(const char* lhs, const string& rhs) { return (string(lhs).compare(rhs) > 0); }

    bool operator<=(const char* lhs, const string& rhs) { return (string(lhs).compare(rhs) <= 0); }

    bool operator>=(const char* lhs, const string& rhs) { return (string(lhs).compare(rhs) >= 0); }

    bool operator==(const char* lhs, const string& rhs) { return (string(lhs).compare(rhs) == 0); }

    bool operator!=(const char* lhs, const string& rhs) { return (string(lhs).compare(rhs) != 0); }
    
    void swap(string& lhs, string& rhs) { lhs.swap(rhs); }

    std::ostream& operator<<(std::ostream& os, const ani::string& s){
        os << s.c_str();
        return os;
    }

    int stoi(const string& s, int base = 10){
        int val = 0;
        int tmp;
        const char* str = s.c_str();

        for(size_t i = 0; i < s.size(); ++i){
            tmp = str[i] - 48;
            val = val * base + tmp;
        }
        return val;
    }

    string to_string(int val){
        string s;
        char ch;
        while(val != 0){
            ch = (val % 10) + 48;
            s.insert(0, 1, ch);
            val = val / 10;
        }
        return s;
    }
}

#endif // _STRING_HPP
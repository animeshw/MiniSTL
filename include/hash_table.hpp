#ifndef _HASH_TABLE_HPP
#define _HASH_TABLE_HPP

#include "list.hpp"
#include "vector.hpp"
#include "utility.hpp"

namespace ani{
    template <typename MyHashTable>
    class _hash_table;

    template <typename MyHashTable>
    class _hash_table_const_iterator{
        friend class _hash_table<MyHashTable>;
        public:
            using iterator_category = ani::bidirectional_iterator_tag;
            using value_type = typename MyHashTable::value_type;
            using difference_type = typename MyHashTable::difference_type;
            using pointer = typename MyHashTable::const_pointer;
            using const_pointer = typename MyHashTable::const_pointer;
            using reference = const value_type&;

            using value_type = typename MyHashTable::value_type;
            using key_type = typename MyHashTable::key_type;
            using size_type = typename MyHashTable::size_type;

        protected:
            using list_iterator = typename list<list<value_type>>::const_iterator;
            using local_iterator = typename list<value_type>::const_iterator;
            list_iterator list_iter;
            local_iterator lcl_iter;

        public:
            _hash_table_const_iterator() : list_iter(), lcl_iter() { }

            _hash_table_const_iterator(const list_iterator& d_it, const local_iterator& l_it) : list_iter(d_it), lcl_iter(l_it) { }

            _hash_table_const_iterator& operator++(){
                if(++lcl_iter == list_iter->cend()){
                    ++list_iter;
                    lcl_iter = list_iter->cbegin();
                }
                return *this;
            }

            _hash_table_const_iterator operator++(int){
                _hash_table_const_iterator tmp(list_iter, lcl_iter);
                this->operator++();
                return tmp;
            }

            _hash_table_const_iterator& operator--(){
                if(--lcl_iter == list_iter->cend()){
                    --list_iter;
                    lcl_iter = --list_iter->cend();
                }
                return *this;
            }

            _hash_table_const_iterator operator--(int){
                _hash_table_const_iterator tmp(list_iter, lcl_iter);
                this->operator--();
                return tmp;
            }

            pointer operator->() const { return &(*lcl_iter); }
            
            reference operator*() const { return *lcl_iter; }

            bool operator==(const _hash_table_const_iterator& other) const { return (list_iter == other.list_iter) && (lcl_iter == other.lcl_iter); }

            bool operator!=(const _hash_table_const_iterator& other) const { return (list_iter != other.list_iter) || (lcl_iter != other.lcl_iter); }
    };

    template <typename MyHashTable>
    class _hash_table_iterator : public _hash_table_const_iterator<MyHashTable>{
        public:
            using iterator_category = ani::bidirectional_iterator_tag;
            using value_type = typename MyHashTable::value_type;
            using difference_type = typename MyHashTable::difference_type;
            using pointer = typename MyHashTable::pointer;
            using const_pointer = typename MyHashTable::const_pointer;
            using reference = value_type&;

        public:
            _hash_table_iterator() : _hash_table_const_iterator<MyHashTable>(){ }

            _hash_table_iterator(const list_iterator& d_it, const local_iterator& l_it) : _hash_table_const_iterator<MyHashTable>(d_it, l_it) { }

            _hash_table_iterator& operator++(){
                _hash_table_const_iterator::operator++();
                return *this;
            }

            _hash_table_iterator operator++(int){
                _hash_table_iterator tmp(list_iter, lcl_iter);
                _hash_table_const_iterator::operator++();
                return tmp;
            }

            _hash_table_iterator& operator--(){
                _hash_table_const_iterator::operator--();
                return *this;
            }

            _hash_table_iterator operator--(int){
                _hash_table_iterator tmp(list_iter, lcl_iter);
                _hash_table_const_iterator::operator--();
                return tmp;
            }

            pointer operator->() const { return const_cast<pointer>(&(*lcl_iter)); }
            
            reference operator*() const { return const_cast<reference>(*lcl_iter); }
    };

    template <typename MyHashTable>
    class _hash_table{
        protected:
            using MyList = ani::list<typename MyHashTable::value_type>;

        public:
            using value_type = typename MyHashTable::value_type;
            using key_type = typename MyHashTable::key_type;
            using size_type = typename MyHashTable::size_type;
            using difference_type = typename MyHashTable::difference_type;
            using pointer = typename MyHashTable::pointer;
            using const_pointer = typename MyHashTable::const_pointer;
            using reference = value_type&;
            using const_reference = const value_type&;

            using iterator = std::conditional_t<std::is_same_v<key_type, value_type>, _hash_table_const_iterator<MyHashTable>, _hash_table_iterator<MyHashTable>>;
            using const_iterator = _hash_table_const_iterator<MyHashTable>;
            using local_iterator = std::conditional_t<std::is_same_v<key_type, value_type>, typename MyList::const_iterator, typename MyList::iterator>;
            using const_local_iterator = typename MyList::const_iterator;

            using hasher = typename MyHashTable::hasher;
            using key_equal = typename MyHashTable::key_eq;

        protected:
            list<list<value_type>> elements;
            vector<typename list<list<value_type>>::const_iterator> buckets;
            hasher hash;
            key_equal keq;
            size_t nr_buckets;
            size_t nr_elements;
            size_t mask;
            float ld_factor;

            static constexpr bool Multi = typename MyHashTable::Multi;

        public:
            _hash_table(size_t _n, const hasher& _hf, const key_equal& _eql, const float& _ldf = 1.0f) : elements(), hash(_hf), keq(_eql), nr_elements(0), ld_factor(_ldf){
                nr_buckets = 8;
                while(_n > nr_buckets)
                    nr_buckets *= 2;
                buckets.assign(nr_buckets, elements.cend());
                mask = nr_buckets - 1;
            }
            
            _hash_table(const _hash_table& other) : _hash_table(other.nr_buckets, other.hash, other.keq, other.ld_factor){ insert(other.begin(), other.end()); }

            _hash_table(_hash_table&& other) : elements(std::move(other.elements)), buckets(std::move(other.buckets)), hash(other.hash),
                        keq(other.keq), nr_buckets(other.nr_buckets), nr_elements(other.nr_elements), mask(nr_buckets - 1), ld_factor(other.ld_factor){
                other.nr_elements = 0;
            }

            _hash_table& operator=(const _hash_table& other){
                if(&other == this)
                    return *this;

                clear();
                
                hash = other.hash;
                keq = other.keq;
                ld_factor = other.ld_factor;
                rehash(other.nr_buckets);
                insert(other.begin(), other.end());
                return *this;
            }

            _hash_table& operator=(_hash_table&& other){
                if(&other == this)
                    return *this;

                elements = std::move(other.elements);
                buckets = std::move(other.buckets);
                hash = other.hash;
                keq = other.keq;
                ld_factor = other.ld_factor;
                nr_elements = other.nr_elements;
                nr_buckets = other.nr_buckets;
                mask = other.mask;

                other.nr_elements = 0;

                return *this;
            }

            _hash_table& operator=(std::initializer_list<value_type> init_list){
                clear();
                insert(init_list);
                return *this;
            }

            bool empty() const { return nr_elements == 0; }

            size_t size() const { return nr_elements; }

            void clear(){
                elements.clear();
                buckets.assign(nr_buckets, elements.cend());
                nr_elements = 0;
            }

            template <bool IsMulti = Multi, std::enable_if_t<!IsMulti, int> = 0>
            pair<iterator, bool> insert(const value_type& val){
                size_t id = hash(val) & mask;
                if(buckets.at(id) != elements.cend()){
                    MyList::const_iterator iter = buckets.at(id)->cbegin();
                    while(iter != buckets.at(id)->cend()){
                        if(keq(*iter, val))
                            break;
                        ++iter;
                    }
                    if(iter != buckets.at(id)->cend())
                        return ani::make_pair(iterator(buckets.at(id), iter), false);
                }
                
                if(load_factor() == max_load_factor()){
                    rehash(nr_buckets * 2);
                    id = hash(val) & mask;
                }

                if(buckets.at(id) != elements.cend())
                    const_cast<list<value_type>&>(*buckets.at(id)).push_front(val);
                else{
                    elements.push_back(list<value_type>());
                    elements.back().push_front(val);
                    buckets.at(id) = --(elements.cend());
                }
                
                ++nr_elements;
                return ani::make_pair(iterator(buckets.at(id), buckets.at(id)->cbegin()), true);
            }

            template <bool IsMulti = Multi, std::enable_if_t<IsMulti, int> = 0>
            iterator insert(const value_type& val){
                if(load_factor() == max_load_factor())
                    rehash(nr_buckets * 2);
                
                size_t id = hash(val) & mask;
                if(buckets.at(id) != elements.cend()){
                    MyList::const_iterator iter;
                    for(iter = buckets.at(id)->cbegin(); iter != buckets.at(id)->cend(); ++iter){
                        if(keq(*iter, val))
                            break;
                    }
                    if(iter != buckets.at(id)->cend()){
                        while(++iter != buckets.at(id)->cend() && *iter == val){
                        }
                        const_cast<list<value_type>&>(*buckets.at(id)).insert(iter, val);
                        ++nr_elements;
                        return iterator(buckets.at(id), --iter);
                    }
                    const_cast<list<value_type>&>(*buckets.at(id)).push_front(val);
                }
                else{
                    elements.push_back(list<value_type>());
                    elements.back().push_front(val);
                    buckets.at(id) = --(elements.cend());
                }
                ++nr_elements;
                return iterator(buckets.at(id), buckets.at(id)->cbegin());
            }

            template <bool IsMulti = Multi, std::enable_if_t<!IsMulti, int> = 0>
            pair<iterator, bool> insert(value_type&& val){
                size_t id = hash(val) & mask;
                if(buckets.at(id) != elements.cend()){
                    MyList::const_iterator iter = buckets.at(id)->cbegin();
                    while(iter != buckets.at(id)->cend()){
                        if(keq(*iter, val))
                            break;
                        ++iter;
                    }
                    if(iter != buckets.at(id)->cend())
                        return ani::make_pair(iterator(buckets.at(id), iter), false);
                }
                
                if(load_factor() == max_load_factor()){
                    rehash(nr_buckets * 2);
                    id = hash(val) & mask;
                }

                if(buckets.at(id) != elements.cend())
                    const_cast<list<value_type>&>(*buckets.at(id)).push_front(std::move(val));
                else{
                    elements.push_back(list<value_type>());
                    elements.back().push_front(std::move(val));
                    buckets.at(id) = --(elements.cend());
                }
                
                ++nr_elements;
                return ani::make_pair(iterator(buckets.at(id), buckets.at(id)->cbegin()), true);
            }

            template <bool IsMulti = Multi, std::enable_if_t<IsMulti, int> = 0>
            iterator insert(value_type&& val){
                if(load_factor() == max_load_factor())
                    rehash(nr_buckets * 2);
                
                size_t id = hash(val) & mask;
                if(buckets.at(id) != elements.cend()){
                    MyList::const_iterator iter;
                    for(iter = buckets.at(id)->cbegin(); iter != buckets.at(id)->cend(); ++iter){
                        if(keq(*iter, val))
                            break;
                    }
                    if(iter != buckets.at(id)->cend()){
                        while(++iter != buckets.at(id)->cend() && *iter == val){
                        }
                        const_cast<list<value_type>&>(*buckets.at(id)).insert(iter, std::move(val));
                        ++nr_elements;
                        return iterator(buckets.at(id), --iter);
                    }
                    const_cast<list<value_type>&>(*buckets.at(id)).push_front(std::move(val));
                }
                else{
                    elements.push_back(list<value_type>());
                    elements.back().push_front(std::move(val));
                    buckets.at(id) = --(elements.cend());
                }
                ++nr_elements;
                return iterator(buckets.at(id), buckets.at(id)->cbegin());
            }

            template <typename InputIt>
            void insert(InputIt first, InputIt last){
                for(InputIt it = first; it != last; ++it)
                    insert(*it);
            }

            void insert(std::initializer_list<value_type> init_list){
                insert(init_list.begin(), init_list.end());
            }
    
            template <typename InputIt = iterator, std::enable_if_t<!std::is_same_v<InputIt, const_iterator>, int> = 0>
            iterator erase(iterator pos){
                if(pos == end())
                    return end();
                
                size_t id = hash(*pos) & mask;
                iterator iter(pos);
                ++iter;

                const_cast<list<value_type>&>(*pos.list_iter).erase(pos.lcl_iter);
                if(pos.list_iter->empty()){
                    buckets.at(id) = elements.cend();
                    elements.erase(pos.list_iter);
                }
                --nr_elements;
                return iter;
            }

            iterator erase(const_iterator pos){
                if(pos == cend())
                    return end();
                
                size_t id = hash(*pos) & mask;
                iterator iter(pos.list_iter, pos.lcl_iter);
                ++iter;

                const_cast<list<value_type>&>(*pos.list_iter).erase(pos.lcl_iter);
                if(pos.list_iter->empty()){
                    buckets.at(id) = elements.cend();
                    elements.erase(pos.list_iter);
                }
                --nr_elements;
                return iter;
            }

            iterator erase(const_iterator first, const_iterator last){
                const_iterator next;
                for(const_iterator iter = first; iter != last; iter = next){
                    next = iter;
                    ++next;
                    erase(iter);
                }
                return iterator(last.list_iter, last.lcl_iter);
            }

            size_t erase(const key_type& val){
                size_t count = 0;
                const_iterator iter = find(val);
                const_iterator last_iter;
                while(iter != cend() && keq(*iter, val)){
                    last_iter = iter++;
                    erase(last_iter);
                    ++count;
                }
                return count;
            }
    
            void swap(_hash_table& other){
                elements.swap(other.elements);
                buckets.swap(other.buckets);
                ani::swap(hash, other.hash);
                ani::swap(keq, other.keq);
                ani::swap(nr_elements, other.nr_elements);
                ani::swap(nr_buckets, other.nr_buckets);
                ani::swap(mask, other.mask);
                ani::swap(ld_factor, other.ld_factor);
            }

            size_t count(const key_type& val) const{ 
                size_t count = 0;
                const_iterator iter = find(val);
                while(iter != cend() && keq(*iter, val)){
                    ++iter;
                    ++count;
                }
                return count;
            }

            iterator find(const key_type& val){
                size_t id = hash(val) & mask;
                if(buckets.at(id) == elements.cend())
                    return end();
                
                list<value_type>::const_iterator iter;
                for(iter = buckets.at(id)->begin(); iter != buckets.at(id)->end(); ++iter){
                    if(keq(*iter, val))
                        return iterator(buckets.at(id), iter);
                }
                return end();
            }

            const_iterator find(const key_type& val) const{
                size_t id = hash(val) & mask;
                if(buckets.at(id) == elements.cend())
                    return cend();
                
                list<value_type>::const_iterator iter;
                for(iter = buckets.at(id)->cbegin(); iter != buckets.at(id)->cend(); ++iter){
                    if(keq(*iter, val))
                        return const_iterator(buckets.at(id), iter);
                }
                return cend();
            }

            bool contains(const key_type& val) const{ return find(val) != cend(); }

            local_iterator begin(size_t n) { return const_cast<list<value_type>&>(*buckets.at(n)).begin(); }

            local_iterator end(size_t n) { return const_cast<list<value_type>&>(*buckets.at(n)).end(); }

            const_local_iterator begin(size_t n) const { return buckets.at(n)->cbegin(); }

            const_local_iterator end(size_t n) const { return buckets.at(n)->cend(); }

            const_local_iterator cbegin(size_t n) const { return buckets.at(n)->cbegin(); }

            const_local_iterator cend(size_t n) const { return buckets.at(n)->cend(); }

            size_t bucket_count() const { return nr_buckets; }

            size_t bucket_size(size_t n) const { return buckets.at(n)->size(); }

            size_t bucket(const key_type& val) const { return hash(val) & mask; }

            float load_factor() const { return static_cast<float>(size()) / static_cast<float>(bucket_count()); }

            float max_load_factor() const { return ld_factor; }

            void max_load_factor(float lf) { ld_factor = (lf > 0) ? lf : ld_factor; }

            void rehash(size_t new_bucket_count){
                if(new_bucket_count > nr_buckets){
                    while(new_bucket_count > nr_buckets){
                        if(nr_buckets < 512)
                            nr_buckets *= 8;
                        else
                            nr_buckets *= 2;
                    }
                    mask = nr_buckets - 1;
                    
                    list<list<value_type>> new_elements;
                    buckets.assign(nr_buckets, new_elements.cend());

                    for(iterator iter = begin(); iter != end(); ++iter){
                        size_t id = hash(*iter) & mask;
                        if(buckets.at(id) != new_elements.cend())
                            const_cast<list<value_type>&>(*buckets.at(id)).push_front(*iter);
                        else{
                            new_elements.push_back(list<value_type>());
                            new_elements.back().push_front(*iter);
                            buckets.at(id) = --(new_elements.cend());
                        }
                    }
                    elements.swap(new_elements);
                }
            }

            void reserve(size_t count) { rehash(std::ceil(count / max_load_factor())); }

            hasher hash_function() const { return hash; }

            key_equal key_eq() const { return keq; }

            iterator begin() { return iterator(elements.cbegin(), elements.cbegin()->cbegin()); }

            iterator end() { return iterator(elements.cend(), elements.cend()->cend()); }

            const_iterator begin() const { return const_iterator(elements.cbegin(), elements.cbegin()->cbegin()); }

            const_iterator end() const { return const_iterator(elements.cend(), elements.cend()->cend()); }

            const_iterator cbegin() const { return const_iterator(elements.cbegin(), elements.cbegin()->cbegin()); }

            const_iterator cend() const { return const_iterator(elements.cend(), elements.cend()->cend()); }
    };
}

#endif // _HASH_TABLE_HPP
#ifndef _RB_TREE_HPP
#define _RB_TREE_HPP

#include "iterator.hpp"
#include "utility.hpp"

namespace ani{
    template <typename MyRBTree>
    class _rb_tree_const_iterator;

    template <typename MyRBTree>
    class _rb_tree_iterator;

    template <typename T>
    class _rb_tree;

    enum _rb_tree_color { RED, BLACK };

    template <typename MyRBTree>
    class _rb_tree_node{
        using value_type = typename MyRBTree::value_type;

        friend class _rb_tree_const_iterator<MyRBTree>;
        friend class _rb_tree_iterator<MyRBTree>;
        friend class _rb_tree<MyRBTree>;

        private:
            value_type data;
            _rb_tree_color color;
            _rb_tree_node* left;
            _rb_tree_node* right;
            _rb_tree_node* parent;

            _rb_tree_node(const value_type& _data, _rb_tree_color _col, _rb_tree_node* _l = nullptr, _rb_tree_node* _r = nullptr,
                    _rb_tree_node* _p = nullptr) : data(_data), color(_col), left(_l), right(_r), parent(_p) { }
    };

    template <typename MyRBTree>
    class _rb_tree_const_iterator{
        friend class _rb_tree<MyRBTree>;
        public:
            using iterator_category = ani::bidirectional_iterator_tag;
            using value_type = typename MyRBTree::value_type;
            using difference_type = typename MyRBTree::difference_type;
            using pointer = typename MyRBTree::const_pointer;
            using reference = const value_type&;
            using T_ptr = _rb_tree_node<MyRBTree>*;

        protected:
            T_ptr ptr;
            T_ptr root;
            T_ptr nil;

        public:
            _rb_tree_const_iterator(T_ptr _ptr = nullptr, T_ptr _root = nullptr, T_ptr _nil = nullptr) : ptr(_ptr), root(_root), nil(_nil) { }

            _rb_tree_const_iterator& operator++(){
                _increment();
                return *this;
            }

            _rb_tree_const_iterator operator++(int){
                _rb_tree_const_iterator tmp(ptr, root, nil);
                _increment();
                return tmp;
            }

            _rb_tree_const_iterator& operator--(){
                _decrement();
                return *this;
            }

            _rb_tree_const_iterator operator--(int){
                _rb_tree_const_iterator tmp(ptr, root, nil);
                _decrement();
                return tmp;
            }

            pointer operator->() const { return &(ptr->data); }

            reference operator*() const { return ptr->data; }

            bool operator==(const _rb_tree_const_iterator& other) const { return ptr == other.ptr; }

            bool operator!=(const _rb_tree_const_iterator& other) const { return ptr != other.ptr; }
        
        protected:
            void _increment(){
                if(ptr == nil){
                    ptr = root;
                    while(ptr != nil && ptr->left != nil)
                        ptr = ptr->left;
                }
                else if(ptr->right != nil){
                    ptr = ptr->right;
                    while(ptr->left != nil)
                        ptr = ptr->left;
                }
                else{
                    T_ptr parent = ptr->parent;
                    while(parent != nil && ptr == parent->right) {
                        ptr = parent;
                        parent = parent->parent;
                    }
                    ptr = parent;
                }
            }

            void _decrement(){                
                if(ptr == nil){
                    ptr = root;
                    while(ptr != nil && ptr->right != nil)
                        ptr = ptr->right;
                }
                else if(ptr->left != nil){
                    ptr = ptr->left;
                    while(ptr->right != nil)
                        ptr = ptr->right;
                }
                else{
                    T_ptr parent = ptr->parent;
                    while(parent != nil && ptr == parent->left) {
                        ptr = parent;
                        parent = parent->parent;
                    }
                    ptr = parent;
                }
            }
    };

    template <typename MyRBTree>
    class _rb_tree_iterator : public _rb_tree_const_iterator<MyRBTree>{
        friend class _rb_tree<MyRBTree>;
        public:
            using iterator_category = ani::bidirectional_iterator_tag;
            using value_type = typename MyRBTree::value_type;
            using difference_type = typename MyRBTree::difference_type;
            using pointer = typename MyRBTree::pointer;
            using reference = value_type&;
        
        public:
            _rb_tree_iterator(_rb_tree_node<MyRBTree>* _ptr = nullptr, _rb_tree_node<MyRBTree>* _root = nullptr, 
                    _rb_tree_node<MyRBTree>* _nil = nullptr) : _rb_tree_const_iterator<MyRBTree>(_ptr, _root, _nil) { }

            _rb_tree_iterator& operator++(){
                _rb_tree_const_iterator::operator++();
                return *this;
            }

            _rb_tree_iterator operator++(int){
                _rb_tree_iterator tmp(ptr, root, nil);
                _rb_tree_const_iterator::operator++();
                return tmp;
            }

            _rb_tree_iterator& operator--(){
                _rb_tree_const_iterator::operator--();
                return *this;
            }

            _rb_tree_iterator operator--(int){
                _rb_tree_iterator tmp(ptr, root, nil);
                _rb_tree_const_iterator::operator--();
                return tmp;
            }

            pointer operator->() const { return &(ptr->data); }

            reference operator*() const { return ptr->data; }
    };

    template <typename MyRBTree>
    class _rb_tree{
        public:
            using value_type = typename MyRBTree::value_type;
            using key_type = typename MyRBTree::key_type;
            using size_type = typename MyRBTree::size_type;
            using difference_type = typename MyRBTree::difference_type;
            using pointer = typename MyRBTree::pointer;
            using const_pointer = typename MyRBTree::const_pointer;
            using reference = value_type&;
            using const_reference = const value_type&;

            using Compare = typename MyRBTree::value_compare;
            using value_compare = typename MyRBTree::value_compare;
            using key_compare = typename MyRBTree::key_compare;
            static constexpr bool Multi = typename MyRBTree::Multi;

            using iterator = std::conditional_t<std::is_same_v<key_type, value_type>, _rb_tree_const_iterator<MyRBTree>, _rb_tree_iterator<MyRBTree>>;
            using const_iterator = _rb_tree_const_iterator<MyRBTree>;
            using reverse_iterator = ani::reverse_iterator<iterator>;
            using const_reverse_iterator = ani::reverse_iterator<const_iterator>;

        protected:
            _rb_tree_node<MyRBTree>* nil;
            _rb_tree_node<MyRBTree>* root;
            size_t nr_nodes;
            Compare comp;
            key_compare key_comp;
            value_compare val_comp;

        public:
            _rb_tree() : _rb_tree(Compare()) { }

            _rb_tree(const Compare& _comp) : nil(new _rb_tree_node<MyRBTree>(value_type(), _rb_tree_color::BLACK)), root(nil), nr_nodes(0), comp(_comp) { }

            _rb_tree(const _rb_tree& other) : _rb_tree(other.comp) { insert(other.cbegin(), other.cend()); }

            _rb_tree(_rb_tree&& other){
                nil = other.nil;
                root = other.root;
                nr_nodes = other.nr_nodes;
                comp = other.comp;

                other.nil = new _rb_tree_node<MyRBTree>(value_type(), _rb_tree_color::BLACK);
                other.root = other.nil;
                other.nr_nodes = 0;
            }

            ~_rb_tree(){
                clear();
                delete nil;
            }

            _rb_tree& operator=(const _rb_tree& other){
                if(this == &other)
                    return *this;
                
                clear();
                comp = other.comp;
                insert(other.cbegin(), other.cend());

                return *this;
            }

            _rb_tree& operator=(_rb_tree&& other){
                if(this == &other)
                    return *this;
                
                clear();
                delete nil;

                nil = other.nil;
                root = other.root;
                nr_nodes = other.nr_nodes;
                comp = other.comp;

                other.nil = new _rb_tree_node<MyRBTree>(value_type(), _rb_tree_color::BLACK);
                other.root = other.nil;
                other.nr_nodes = 0;

                return *this;
            }
            
            bool empty() const { return nr_nodes == 0; }

            size_t size() const { return nr_nodes; }

            void clear(){
                _destroy(root);
                root = nil;
                nr_nodes = 0;
            }

            template <bool IsMulti = Multi, std::enable_if_t<!IsMulti, int> = 0>
            pair<iterator, bool> insert(const value_type& val){
                _rb_tree_node<MyRBTree>* x = root;
                _rb_tree_node<MyRBTree>* y = root;

                while(x != nil){
                    y = x;
                    if(key_comp(val, x->data))
                        return ani::make_pair(iterator(x, nil), false);
                    else if(comp(val, x->data))
                        x = x->left;
                    else
                        x = x->right;
                }
                _rb_tree_node<MyRBTree>* z = new _rb_tree_node<MyRBTree>(val, _rb_tree_color::RED, nil, nil, nil);
                z->parent = y;

                if(y == nil)
                    root = z;
                else if(comp(z->data, y->data))
                    y->left = z;
                else
                    y->right = z;
                
                ++nr_nodes;
                _insert_fixup(z);
                return ani::make_pair(iterator(z, root, nil), true);
            }

            template <bool IsMulti = Multi, std::enable_if_t<IsMulti, int> = 0>
            iterator insert(const value_type& val){
                _rb_tree_node<MyRBTree>* x = root;
                _rb_tree_node<MyRBTree>* y = root;

                while(x != nil){
                    y = x;
                    if(comp(val, x->data))
                        x = x->left;
                    else
                        x = x->right;
                }
                _rb_tree_node<MyRBTree>* z = new _rb_tree_node<MyRBTree>(val, _rb_tree_color::RED, nil, nil, nil);
                z->parent = y;

                if(y == nil)
                    root = z;
                else if(comp(z->data, y->data))
                    y->left = z;
                else
                    y->right = z;
                
                ++nr_nodes;
                _insert_fixup(z);
                return iterator(z, root, nil);
            }

            template <bool IsMulti = Multi, std::enable_if_t<!IsMulti, int> = 0>
            pair<iterator, bool> insert(value_type&& val){
                _rb_tree_node<MyRBTree>* x = root;
                _rb_tree_node<MyRBTree>* y = root;

                while(x != nil){
                    y = x;
                    if(key_comp(val, x->data))
                        return ani::make_pair(iterator(x, root, nil), false);
                    else if(comp(val, x->data))
                        x = x->left;
                    else
                        x = x->right;
                }
                _rb_tree_node<MyRBTree>* z = new _rb_tree_node<MyRBTree>(std::move(val), _rb_tree_color::RED, nil, nil, nil);
                z->parent = y;

                if(y == nil)
                    root = z;
                else if(comp(z->data, y->data))
                    y->left = z;
                else
                    y->right = z;
                
                ++nr_nodes;
                _insert_fixup(z);
                return ani::make_pair(iterator(z, root, nil), true);
            }

            template <bool IsMulti = Multi, std::enable_if_t<IsMulti, int> = 0>
            iterator insert(value_type&& val){
                _rb_tree_node<MyRBTree>* x = root;
                _rb_tree_node<MyRBTree>* y = root;

                while(x != nil){
                    y = x;
                    if(comp(val, x->data))
                        x = x->left;
                    else
                        x = x->right;
                }
                _rb_tree_node<MyRBTree>* z = new _rb_tree_node<MyRBTree>(std::move(val), _rb_tree_color::RED, nil, nil, nil);
                z->parent = y;

                if(y == nil)
                    root = z;
                else if(comp(z->data, y->data))
                    y->left = z;
                else
                    y->right = z;
                
                ++nr_nodes;
                _insert_fixup(z);
                return iterator(z, root, nil);
            }

            /*
            iterator insert(const_iterator pos, const value_type& val){

            }

            iterator insert(const_iterator pos, value_type&& val){

            }
            */

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
                _rb_tree_node<MyRBTree>* x = nullptr;
                _rb_tree_node<MyRBTree>* y = nullptr;
                _rb_tree_node<MyRBTree>* z = nullptr;
                _rb_tree_color y_original_color;

                if(pos == end() || pos.nil != nil)
                    return iterator(pos.ptr, pos.root, pos.nil);
                
                z = pos.ptr;
                ++pos;

                y = z;
                y_original_color = y->color;

                if(z->left == nil){
                    x = z->right;
                    _transplant(z, z->right);
                }
                else if(z->right == nil){
                    x = z->left;
                    _transplant(z, z->left);
                }
                else{
                    y = _min(z->right);
                    y_original_color = y->color;
                    x = y->right;
                    if(y->parent == z)
                        x->parent = y; 
                    else{
                        _transplant(y, y->right);
                        y->right = z->right;
                        y->right->parent = y;
                    }
                    _transplant(z, y);
                    y->left = z->left;
                    y->left->parent = y;
                    y->color = z->color;
                }

                if(y_original_color == _rb_tree_color::BLACK && x != nil)
                    _erase_fixup(x);

                --nr_nodes;
                delete(z);
                z = nullptr;
                return iterator(pos.ptr, pos.root, pos.nil);
            }

            iterator erase(const_iterator pos){
                _rb_tree_node<MyRBTree>* x = nullptr;
                _rb_tree_node<MyRBTree>* y = nullptr;
                _rb_tree_node<MyRBTree>* z = nullptr;
                _rb_tree_color y_original_color;

                if(pos == end() || pos.nil != nil)
                    return iterator(pos.ptr, pos.root, pos.nil);
                
                z = pos.ptr;
                ++pos;

                y = z;
                y_original_color = y->color;

                if(z->left == nil){
                    x = z->right;
                    _transplant(z, z->right);
                }
                else if(z->right == nil){
                    x = z->left;
                    _transplant(z, z->left);
                }
                else{
                    y = _min(z->right);
                    y_original_color = y->color;
                    x = y->right;
                    if(y->parent == z)
                        x->parent = y; 
                    else{
                        _transplant(y, y->right);
                        y->right = z->right;
                        y->right->parent = y;
                    }
                    _transplant(z, y);
                    y->left = z->left;
                    y->left->parent = y;
                    y->color = z->color;
                }

                if(y_original_color == _rb_tree_color::BLACK && x != nil)
                    _erase_fixup(x);

                --nr_nodes;
                delete(z);
                z = nullptr;
                return iterator(pos.ptr, pos.root, pos.nil);
            }

            iterator erase(const_iterator first, const_iterator last){
                for(const_iterator it = first; it != last; )
                    it = erase(it);
                return iterator(last.ptr, last.root, last.nil);
            }

            size_t erase(const key_type& key){
                size_t count = 0;
                iterator iter;
                while((iter = find(key)) != end()){
                    erase(iter);
                    ++count;
                }
                return count;
            }

            void swap(_rb_tree& other){
                ani::swap(nil, other.nil);
                ani::swap(root, other.root);
                ani::swap(nr_nodes, other.nr_nodes);
                ani::swap(comp, other.comp);
            }

            size_t count(const key_type& key) const{
                const_iterator citer = find(key);
                size_t cnt = 0;
                
                if(citer == cend())
                    return cnt;
                
                ++cnt;
                const_iterator l_citer = citer;
                const_iterator r_citer = citer;

                while(--l_citer != cend() && key_comp(*l_citer, key))
                    ++cnt;

                while(++r_citer != cend() && key_comp(*r_citer, key))
                    ++cnt;
                
                return cnt;
            }
            
            iterator find(const key_type& key){
                _rb_tree_node<MyRBTree>* x = root;

                while(x != nil){
                    if(key_comp(key, x->data))
                        return iterator(x, root, nil);
                    else if(val_comp(key, x->data))
                        x = x->left;
                    else
                        x = x->right;
                }
                return end();
            }

            const_iterator find(const key_type& key) const{
                _rb_tree_node<MyRBTree>* x = root;

                while(x != nil){
                    if(key_comp(key, x->data))
                        return const_iterator(x, root, nil);
                    else if(val_comp(key, x->data))
                        x = x->left;
                    else
                        x = x->right;
                }
                return cend();
            }

            bool contains(const key_type& key) const { return find(key) != cend(); }

            iterator lower_bound(const key_type& key){
                iterator iter = begin();
                while(iter != end()){
                    if(!val_comp(*iter, key))
                        break;
                    ++iter;
                }
                return iter;
            }

            const_iterator lower_bound(const key_type& key) const{
                const_iterator citer = begin();
                while(citer != end()){
                    if(!val_comp(*citer, key))
                        break;
                    ++citer;
                }
                return citer;
            }

            iterator upper_bound(const key_type& key){
                iterator iter = begin();
                while(iter != end()){
                    if(val_comp(key, *iter))
                        break;
                    ++iter;
                }
                return iter;
            }

            const_iterator upper_bound(const key_type& key) const{
                const_iterator citer = begin();
                while(citer != end()){
                    if(val_comp(key, *citer))
                        break;
                    ++citer;
                }
                return citer;
            }

        private:
            private:
            void _left_rotate(_rb_tree_node<MyRBTree>* x){
                _rb_tree_node<MyRBTree>* y = nullptr;

                y = x->right;
                x->right = y->left;
                if(y->left != nil)
                    y->left->parent = x;

                y->parent = x->parent;
                if(x->parent == nil)
                    root = y;
                else if(x == x->parent->left)
                    x->parent->left = y;
                else if(x == x->parent->right)
                    x->parent->right = y;

                y->left = x;
                x->parent = y;
            }

            void _right_rotate(_rb_tree_node<MyRBTree>* x){
                _rb_tree_node<MyRBTree>* y = nullptr;

                y = x->left;
                x->left = y->right;
                if(y->right != nil)
                    y->right->parent = x;
                
                y->parent = x->parent;
                if(x->parent == nil)
                    root = y;
                else if(x == x->parent->left)
                    x->parent->left = y;
                else if(x == x->parent->right)
                    x->parent->right = y;

                y->right = x;
                x->parent = y;
            }

            void _insert_fixup(_rb_tree_node<MyRBTree>* z){
                _rb_tree_node<MyRBTree>* y = nullptr;
                
                while(z->parent->color == _rb_tree_color::RED){
                    if(z->parent == z->parent->parent->left){
                        y = z->parent->parent->right;
                        
                        if(y->color == _rb_tree_color::RED){
                            z->parent->color = _rb_tree_color::BLACK;
                            y->color = _rb_tree_color::BLACK;
                            z->parent->parent->color = _rb_tree_color::RED;
                            z = z->parent->parent;
                        }
                        else{
                            if(z == z->parent->right){
                                z = z->parent;
                                _left_rotate(z);
                            }
                            z->parent->color = _rb_tree_color::BLACK;
                            z->parent->parent->color = _rb_tree_color::RED;
                            _right_rotate(z->parent->parent);
                        }
                    }
                    else{
                        y = z->parent->parent->left;
                        if(y->color == _rb_tree_color::RED){
                            z->parent->color = _rb_tree_color::BLACK;
                            y->color = _rb_tree_color::BLACK;
                            z->parent->parent->color = _rb_tree_color::RED;
                            z = z->parent->parent;
                        }
                        else{
                            if(z == z->parent->left){
                                z = z->parent;
                                _right_rotate(z);
                            }
                            z->parent->color = _rb_tree_color::BLACK;
                            z->parent->parent->color = _rb_tree_color::RED;
                            _left_rotate(z->parent->parent);
                        }
                    }
                }
                root->color = _rb_tree_color::BLACK;
            }

            _rb_tree_node<MyRBTree>* _min(_rb_tree_node<MyRBTree>* x) const{
                _rb_tree_node<MyRBTree>* run = x;
                while(run != nil && run->left != nil)
                    run = run->left;
                return run;
            }

            _rb_tree_node<MyRBTree>* _max(_rb_tree_node<MyRBTree>* x) const{
                _rb_tree_node<MyRBTree>* run = x;
                while(run != nil && run->right != nil)
                    run = run->right;
                return run;
            }

            void _transplant(_rb_tree_node<MyRBTree>* u, _rb_tree_node<MyRBTree>* v){
                if(u->parent == nil)
                    root = v;
                else if(u == u->parent->left)
                    u->parent->left = v;
                else
                    u->parent->right = v;

                if(v != nil)
                    v->parent = u->parent;
            }

            void _erase_fixup(_rb_tree_node<MyRBTree>* x){
                _rb_tree_node<MyRBTree>* w = nil;
                while(x != root && x->color == _rb_tree_color::BLACK){
                    if(x == x->parent->left){

                        w = x->parent->right;
                        if(w->color == _rb_tree_color::RED){
                            w->color = _rb_tree_color::BLACK;
                            x->parent->color = _rb_tree_color::RED;
                            _left_rotate(x->parent);
                            w = x->parent->right;
                        }

                        if(w == nil){
                            x = x->parent;
                            continue;
                        }

                        if(w->left->color == _rb_tree_color::BLACK && w->right->color == _rb_tree_color::BLACK){
                            w->color = _rb_tree_color::RED;
                            x = x->parent;
                        }
                        else{
                            if(w->right->color == _rb_tree_color::BLACK){
                                w->left->color = _rb_tree_color::BLACK;
                                w->color = _rb_tree_color::RED;
                                _right_rotate(w);
                                w = x->parent->right;
                            }
                            w->color = x->parent->color;
                            x->parent->color = _rb_tree_color::BLACK;
                            w->right->color = _rb_tree_color::BLACK;
                            _left_rotate(x->parent);
                            x = root;
                        }

                    }
                    else{
                        w = x->parent->left;

                        if(w->color == _rb_tree_color::RED){
                            w->color = _rb_tree_color::BLACK;
                            x->parent->color = _rb_tree_color::RED;
                            _right_rotate(x->parent);
                            w = x->parent->left;
                        }

                        if(w == nil){
                            x = x->parent;
                            continue;
                        }

                        if(w->left->color == _rb_tree_color::BLACK && w->right->color == _rb_tree_color::BLACK){
                            w->color = _rb_tree_color::RED;
                            x = x->parent;
                        }
                        else{
                            if(w->left->color == _rb_tree_color::BLACK){
                                w->right->color = _rb_tree_color::BLACK;
                                w->color = _rb_tree_color::RED;
                                _left_rotate(w);
                                w = x->parent->left;
                            }
                            w->color = x->parent->color;
                            x->parent->color = _rb_tree_color::BLACK;
                            w->left->color = _rb_tree_color::BLACK;
                            _right_rotate(x->parent);
                            x = root;
                        }
                    }
                }
                x->color = _rb_tree_color::BLACK;
            }

            void _destroy(_rb_tree_node<MyRBTree>* _ptr){
                if(_ptr != nil){
                    _destroy(_ptr->left);
                    _destroy(_ptr->right);
                    delete _ptr;
                    _ptr = nullptr;
                }
            }
    
        public:
            iterator begin() { return iterator(_min(root), root, nil); }

            iterator end() { return iterator(nil, root, nil); }

            const_iterator begin() const { return const_iterator(_min(root), root, nil); }

            const_iterator end() const { return const_iterator(nil, root, nil); }

            const_iterator cbegin() const { return begin(); }

            const_iterator cend() const { return end(); }
            
            reverse_iterator rbegin() { return reverse_iterator(end()); }

            reverse_iterator rend() { return reverse_iterator(begin()); }

            const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
            
            const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

            const_reverse_iterator crbegin() const { return rbegin(); }
            
            const_reverse_iterator crend() const { return begin(); }
    };

    template <typename MyRBTree>
    bool operator==(const _rb_tree<MyRBTree>& lhs, const _rb_tree<MyRBTree>& rhs){
        typename _rb_tree<MyRBTree>::const_iterator l_iter = lhs.cbegin();
        typename _rb_tree<MyRBTree>::const_iterator r_iter = rhs.cbegin();
        for(; l_iter != lhs.cend() && r_iter != rhs.cend(); ++l_iter, ++r_iter){
            if(*l_iter != *r_iter)
                return false;
        }
        return l_iter == lhs.cend() && r_iter == rhs.cend();
    }

    template <typename MyRBTree>
    bool operator!=(const _rb_tree<MyRBTree>& lhs, const _rb_tree<MyRBTree>& rhs) { return !(lhs == rhs); }

    template <typename MyRBTree>
    bool operator<(const _rb_tree<MyRBTree>& lhs, const _rb_tree<MyRBTree>& rhs){
        typename _rb_tree<MyRBTree>::const_iterator l_iter = lhs.cbegin();
        typename _rb_tree<MyRBTree>::const_iterator r_iter = rhs.cbegin();
        for(; l_iter != lhs.cend() && r_iter != rhs.cend(); ++l_iter, ++r_iter){
            if(*l_iter < *r_iter)
                return true;
            if(*r_iter < *l_iter)
                return false;
        }
        return l_iter == lhs.cend() && r_iter != rhs.cend();
    }

    template <typename MyRBTree>
    bool operator>(const _rb_tree<MyRBTree>& lhs, const _rb_tree<MyRBTree>& rhs) { return rhs < lhs; }

    template <typename MyRBTree>
    bool operator<=(const _rb_tree<MyRBTree>& lhs, const _rb_tree<MyRBTree>& rhs) { return !(rhs < lhs); }

    template <typename MyRBTree>
    bool operator>=(const _rb_tree<MyRBTree>& lhs, const _rb_tree<MyRBTree>& rhs) { return !(lhs < rhs); }

    template <typename MyRBTree>
    void swap(_rb_tree<MyRBTree>& lhs, _rb_tree<MyRBTree>& rhs) { lhs.swap(rhs); }

}

#endif // _RB_TREE_HPP
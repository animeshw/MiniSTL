#ifndef _STACK_HPP
#define _STACK_HPP

#include "list.hpp"

namespace ani{
    template <typename T, typename Container = ani::list<T>>
    class stack{
        private:
            Container cntr;

        public:
            stack() : stack(Container()) { }

            stack(const Container& _cntr) : cntr(_cntr) { }

            stack(Container&& _cntr) : cntr(std::move(_cntr)) { }

            stack(const stack& other) : cntr(other.cntr) { }

            stack(stack&& other) : cntr(std::move(other.cntr)) { }

            template <typename InputIt>
            stack(InputIt first, InputIt last) : cntr(first, last) { }

            stack& operator=(const stack& other){
                if(&other == *this)
                    return *this;
                
                cntr = other.cntr;
                return *this;
            }

            stack& operator=(stack&& other){
                if(&other == *this)
                    return *this;
                
                cntr = std::move(other.cntr);
                return *this;
            }

            T& top() { return cntr.back(); }

            const T& top() const { return cntr.back(); }

            bool empty() const { return cntr.empty(); }

            size_t size() const { return cntr.size(); }

            void push(const T& val) { cntr.push_back(val); }

            void push(T&& val) { cntr.push_back(std::move(val)); }

            void pop() { cntr.pop_back(); }

            void swap(stack& other) { swap(cntr, other.cntr); }

            const Container& _get_container() const { return cntr; }
    };

    template <typename T, typename Container>
    bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs._get_container() == rhs._get_container(); }

    template <typename T, typename Container>
    bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(lhs == rhs); }

    template <typename T, typename Container>
    bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs._get_container() < rhs._get_container(); }

    template <typename T, typename Container>
    bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return rhs < lhs; }

    template <typename T, typename Container>
    bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(rhs < lhs); }

    template <typename T, typename Container>
    bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(lhs < rhs); }

    template <typename T, typename Container>
    void swap(stack<T, Container>& lhs, stack<T, Container>& rhs) { lhs.swap(rhs); }
};

#endif // _STACK_HPP
#ifndef _QUEUE_HPP
#define _QUEUE_HPP

#include "list.hpp"

namespace ani{
    template <typename T, typename Container = ani::list<T>>
    class queue{
        private:
            Container cntr;

        public:
            queue() : queue(Container()) { }

            queue(const Container& _cntr) : cntr(_cntr) { }

            queue(Container&& _cntr) : cntr(std::move(_cntr)) { }

            queue(const queue& other) : cntr(other.cntr) { }

            queue(queue&& other) : cntr(std::move(other.cntr)) { }

            template <typename InputIt>
            queue(InputIt first, InputIt last) : cntr(first, last) { }

            queue& operator=(const queue& other){
                if(&other == *this)
                    return *this;
                
                cntr = other.cntr;
                return *this;
            }

            queue& operator=(queue&& other){
                if(&other == *this)
                    return *this;
                
                cntr = std::move(other.cntr);
                return *this;
            }

            T& front() { return cntr.front(); }

            const T& front() const { return cntr.front(); }

            T& back() { return cntr.back(); }

            const T& back() const { return cntr.back(); }

            bool empty() const { return cntr.empty(); }

            size_t size() const { return cntr.size(); }

            void push(const T& val) { cntr.push_back(val); }

            void push(T&& val) { cntr.push_back(std::move(val)); }

            void pop() { cntr.pop_front(); }

            void swap(queue& other) { swap(cntr, other.cntr); }

            const Container& _get_container() const { return cntr; }
    };

    template <typename T, typename Container>
    bool operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs) { return lhs._get_container() == rhs._get_container(); }

    template <typename T, typename Container>
    bool operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) { return !(lhs == rhs); }

    template <typename T, typename Container>
    bool operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs) { return lhs._get_container() < rhs._get_container(); }

    template <typename T, typename Container>
    bool operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs) { return rhs < lhs; }

    template <typename T, typename Container>
    bool operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) { return !(rhs < lhs); }

    template <typename T, typename Container>
    bool operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) { return !(lhs < rhs); }

    template <typename T, typename Container>
    void swap(queue<T, Container>& lhs, queue<T, Container>& rhs) { lhs.swap(rhs); }
}

#endif // _QUEUE_HPP
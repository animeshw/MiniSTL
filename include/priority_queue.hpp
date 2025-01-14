#ifndef _PRIORITY_QUEUE_HPP
#define _PRIORITY_QUEUE_HPP

#include "vector.hpp"
#include "algorithm.hpp"
#include "functional.hpp"
#include "utility.hpp"

namespace ani{
    template <typename T, typename Container = ani::vector<T>, typename Compare = ani::less<T>>
    class priority_queue{
        private:
            Container cntr;
            Compare comp;

        public:
            priority_queue() : priority_queue(Compare(), Container()) { }

            priority_queue(const Compare& _comp, const Container& _cntr) : cntr(_cntr), comp(_comp){
                ani::make_heap(cntr.begin(), cntr.end(), comp);
            }

            priority_queue(const Compare& _comp) : priority_queue(_comp, Container()) { }

            priority_queue(const Compare& _comp, Container&& _cntr) : cntr(std::move(_cntr)), comp(_comp){
                ani::make_heap(cntr.begin(), cntr.end(), comp);
            }

            priority_queue(const priority_queue& other) : cntr(other.cntr), comp(other.comp) { }

            priority_queue(priority_queue&& other) : cntr(std::move(other.cntr)), comp(std::move(other.comp)) { }

            template <typename InputIt>
            priority_queue(InputIt first, InputIt last, const Compare& _comp = Compare()) : cntr(first, last), comp(_comp){
                ani::make_heap(cntr.begin(), cntr.end(), comp);
            }

            template <typename InputIt>
            priority_queue(InputIt first, InputIt last, const Compare& _comp, const Container& _cntr) : cntr(_cntr), comp(_comp){ 
                cntr.insert(c.end(), first, last);
                ani::make_heap(cntr.begin(), cntr.end(), comp);
            }

            template <typename InputIt>
            priority_queue(InputIt first, InputIt last, const Compare& _comp, Container&& _cntr) : cntr(std::move(_cntr)), comp(_comp){
                cntr.insert(c.end(), first, last);
                ani::make_heap(cntr.begin(), cntr.end(), comp);
            }

            priority_queue& operator=(const priority_queue& other){
                cntr = other.cntr;
                comp = other.comp;
            }

            priority_queue& operator=(priority_queue&& other){
                cntr = std::move(other.cntr);
                comp = std::move(other.comp);
            }

            const T& top() const { return cntr.front(); }

            bool empty() const { return cntr.empty(); }

            size_t size() const { return cntr.size(); }

            void push(const T& val){
                cntr.push_back(val);
                ani::push_heap(cntr.begin(), cntr.end(), comp);
            }

            void push(T&& val){
                cntr.push_back(std::move(val));
                ani::push_heap(cntr.begin(), cntr.end(), comp);
            }

            void pop(){
                ani::pop_heap(cntr.begin(), cntr.end(), comp);
                cntr.pop_back();
            }

            void swap(){
                ani::swap(cntr, other.cntr);
                ani::swap(comp, other.comp);
            }
    };
}

#endif // _PRIORITY_QUEUE_HPP
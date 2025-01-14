#include <iostream>
#include "..\include\priority_queue.hpp"
#include <queue>

void test(){
    std::priority_queue<int> pq;
    pq.push(1);
    pq.push(4);
    pq.push(7);
    pq.push(2);
    pq.push(3);
    pq.push(9);
    pq.push(6);
    // std::cout << pq.top() << " ";
    while(!pq.empty()){
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << std::endl;
}

void test2(){
    ani::priority_queue<int> pq;
    pq.push(1);
    pq.push(4);
    pq.push(7);
    pq.push(2);
    pq.push(3);
    pq.push(9);
    pq.push(6);
    // std::cout << pq.top() << " ";
    while(!pq.empty()){
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << std::endl;
}

int main(){
    test();
    test2();
    return 0;
}

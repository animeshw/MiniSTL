#include <iostream>
#include <cassert>
#include "..\include\unordered_set.hpp"

template <typename T>
void print(const char* msg, const ani::unordered_set<T>& ust){
    std::cout << msg << " : ";
    std::cout << "[";
    for(const T& elem : ust)
        std::cout << elem << " ";
    std::cout << "] [size : " << ust.size() << ", bucket count : " << ust.bucket_count() << "]" << std::endl;
}

void test_construct(){
    puts("#--------------------------------------------------------#");
    puts("Default construct");
    ani::unordered_set<int> ust_default;
    assert(ust_default.empty());
    print("ust_default", ust_default);

    puts("#--------------------------------------------------------#");
    puts("Construct using size");
    ani::unordered_set<int> ust_size(10);
    assert(ust_size.empty());
    print("ust_size", ust_size);

    puts("#--------------------------------------------------------#");
    puts("Constructed using initialzier list");
    ani::unordered_set<int> ust_init_list {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    print("ust_init_list", ust_init_list);

    puts("#--------------------------------------------------------#");
    puts("Constructed using iterator range");
    ani::unordered_set<int> ust_iter_range(++ust_init_list.begin(), --ust_init_list.end());
    print("ust_iter_range", ust_iter_range);

    puts("#--------------------------------------------------------#");
    puts("Copy Constructed");
    ani::unordered_set<int> ust_copy(ust_init_list);
    print("ust_copy", ust_copy);

    puts("#--------------------------------------------------------#");
    puts("Copy Assigned");
    ani::unordered_set<int> ust_copy_assign = ust_copy;
    assert(!ust_copy.empty());
    print("ust_copy_assign", ust_copy_assign);

    ust_copy_assign = ust_init_list;
    assert(!ust_init_list.empty());
    print("ust_copy_assign", ust_copy_assign);
    
    puts("#--------------------------------------------------------#");
    puts("Move Constructed");
    ani::unordered_set<int> ust_move(std::move(ust_init_list));
    assert(ust_init_list.empty());
    print("ust_move", ust_move);
    print("ust_init_list", ust_init_list);

    puts("#--------------------------------------------------------#");
    puts("Move Assigned");
    ani::unordered_set<int> ust_move_assign = std::move(ust_copy);
    assert(ust_copy.empty());
    print("ust_move_assign", ust_move_assign);
    print("ust_copy", ust_copy);

    ust_move_assign = std::move(ust_iter_range);
    print("ust_move_assign", ust_move_assign);
    print("ust_iter_range", ust_iter_range);
    
    puts("#--------------------------------------------------------#");
    puts("Initializer list assigned");
    ani::unordered_set<int> ust_init_list_assign = {2, 4, 7, 1, 4, 5, 7, 3, 6};
    print("ust_init_list_assign", ust_init_list_assign);
    ust_init_list_assign = {66, 42, 124, 22, 12, 74, 23, 40};
    print("ust_init_list_assign", ust_init_list_assign);
    
    puts("#--------------------------------------------------------#\n");
}

void test_traverse(){
    ani::unordered_set<int> ust{4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    
    puts("#--------------------------------------------------------#");
    puts("Traverse using iterator");
    for(ani::unordered_set<int>::iterator it = ust.begin(); it != ust.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using const_iterator");
    for(ani::unordered_set<int>::const_iterator it = ust.cbegin(); it != ust.cend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_modifiers(){
    puts("#--------------------------------------------------------#");
    ani::unordered_set<int> ust_1 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("ust_1", ust_1);
    ust_1.insert(-10);
    ust_1.insert(75);
    print("ust_1", ust_1);

    puts("#--------------------------------------------------------#");
    ani::unordered_set<int> ust_2;
    ust_2.insert(ust_1.begin(), ust_1.end());
    print("ust_2", ust_2);

    puts("#--------------------------------------------------------#");
    ani::unordered_set<int> ust_3;
    ust_3.insert({5, 32, -23, 34, 72, 12, 37});
    print("ust_3", ust_3);

    puts("#--------------------------------------------------------#");
    ani::unordered_set<int> ust_4 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("ust_4", ust_4);
    ust_4.erase(ust_4.begin());
    print("ust_4", ust_4);
    ust_4.erase(--ust_4.end());
    print("ust_4", ust_4);

    ust_4.erase(53);
    print("ust_4", ust_4);

    ust_4.clear();
    print("ust_4", ust_4);

    puts("#--------------------------------------------------------#");
    ani::unordered_set<int> ust_5 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("ust_5", ust_5);
    ust_5.erase(++ust_5.begin(), --ust_5.end());
    print("ust_5", ust_5);

    puts("#--------------------------------------------------------#");
    ani::unordered_set<int> ust_6 {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    print("ust_5", ust_5);
    print("ust_6", ust_6);
    ust_6.swap(ust_5);
    print("ust_5", ust_5);
    print("ust_6", ust_6);

    puts("#--------------------------------------------------------#\n");
}

void test_lookup(){
    puts("#--------------------------------------------------------#");
    ani::unordered_set<int> ust_1 {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    std::cout << "count(4) : " << ust_1.count(4) << std::endl;
    std::cout << "count(-7) : " << ust_1.count(-7) << std::endl;
    
    auto it = ust_1.find(9);
    if(it != ust_1.end())
        std::cout << "find(9) != end() : " << (it != ust_1.end()) << ", val : " << *it << std::endl;

    it = ust_1.find(12);
    if(it == ust_1.end())
        std::cout << "find(12) == end() : " << (it == ust_1.end()) << std::endl;

    std::cout << "contains(3) : " << ust_1.contains(3) << std::endl;
    std::cout << "contains(0) : " << ust_1.contains(0) << std::endl;
    puts("#--------------------------------------------------------#\n");
}

void test_bucket_interface(){
    ani::unordered_set<int> ust;
    for(int i = 0; i < 48; ++i)
        ust.insert(i);

    puts("#--------------------------------------------------------#");
    for(ani::unordered_set<int>::iterator iter = ust.begin(); iter != ust.end(); ++iter)
        std::cout << *iter << " ";
    std::cout << std::endl;

    for(int i = 0; i < ust.bucket_count(); ++i){
        std::cout << "bucket_size(" << i << ") : " << ust.bucket_size(i) << " : ";
        for(ani::unordered_set<int>::local_iterator l_it = ust.begin(i); l_it != ust.end(i); ++l_it)
            std::cout << *l_it << " ";
        std::cout << std::endl;
    }

    puts("#--------------------------------------------------------#\n");
}

void test_hash_policy(){
    ani::unordered_set<int> ust;
    for(int i = 0; i < 48; ++i)
        ust.insert(i);

    puts("#--------------------------------------------------------#");
    std::cout << "load factor : " << ust.load_factor() << std::endl;
    std::cout << "max_load_factor : " << ust.max_load_factor() << std::endl;
    std::cout << "bucket count : " << ust.bucket_count() << std::endl;

    ust.clear();
    ust.max_load_factor(0.5);

    for(int i = 0; i < 48; ++i)
        ust.insert(i);

    std::cout << "load factor : " << ust.load_factor() << std::endl;
    std::cout << "max_load_factor : " << ust.max_load_factor() << std::endl;
    std::cout << "bucket count : " << ust.bucket_count() << std::endl;

    puts("#--------------------------------------------------------#\n");
}

int main(){
    test_construct();
    test_traverse();
    test_modifiers();
    test_lookup();
    test_bucket_interface();
    test_hash_policy();
    puts("All tests passed!");
    return 0;
}
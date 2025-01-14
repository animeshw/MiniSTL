#include <iostream>
#include <cassert>
#include "..\include\unordered_multiset.hpp"

template <typename T>
void print(const char* msg, const ani::unordered_multiset<T>& umst){
    std::cout << msg << " : ";
    std::cout << "[";
    for(const T& elem : umst)
        std::cout << elem << " ";
    std::cout << "] [size : " << umst.size() << ", bucket count : " << umst.bucket_count() << "]" << std::endl;
}

void test_construct(){
    puts("#--------------------------------------------------------#");
    puts("Default construct");
    ani::unordered_multiset<int> umst_default;
    assert(umst_default.empty());
    print("umst_default", umst_default);

    puts("#--------------------------------------------------------#");
    puts("Construct using size");
    ani::unordered_multiset<int> umst_size(24);
    assert(umst_size.empty());
    print("umst_size", umst_size);

    puts("#--------------------------------------------------------#");
    puts("Constructed using initialzier list");
    ani::unordered_multiset<int> umst_init_list {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    print("umst_init_list", umst_init_list);

    puts("#--------------------------------------------------------#");
    puts("Constructed using iterator range");
    ani::unordered_multiset<int> umst_iter_range(++umst_init_list.begin(), --umst_init_list.end());
    print("umst_iter_range", umst_iter_range);

    puts("#--------------------------------------------------------#");
    puts("Copy Constructed");
    ani::unordered_multiset<int> umst_copy(umst_init_list);
    print("umst_copy", umst_copy);

    puts("#--------------------------------------------------------#");
    puts("Copy Assigned");
    ani::unordered_multiset<int> umst_copy_assign = umst_copy;
    assert(!umst_copy.empty());
    print("umst_copy_assign", umst_copy_assign);

    umst_copy_assign = umst_init_list;
    assert(!umst_init_list.empty());
    print("umst_copy_assign", umst_copy_assign);
    
    puts("#--------------------------------------------------------#");
    puts("Move Constructed");
    ani::unordered_multiset<int> umst_move(std::move(umst_init_list));
    assert(umst_init_list.empty());
    print("umst_move", umst_move);
    print("umst_init_list", umst_init_list);

    puts("#--------------------------------------------------------#");
    puts("Move Assigned");
    ani::unordered_multiset<int> umst_move_assign = std::move(umst_copy);
    assert(umst_copy.empty());
    print("umst_move_assign", umst_move_assign);
    print("umst_copy", umst_copy);

    umst_move_assign = std::move(umst_iter_range);
    print("umst_move_assign", umst_move_assign);
    print("umst_iter_range", umst_iter_range);
    
    puts("#--------------------------------------------------------#");
    puts("Initializer list assigned");
    ani::unordered_multiset<int> umst_init_list_assign = {2, 4, 7, 1, 4, 5, 7, 3, 6};
    print("umst_init_list_assign", umst_init_list_assign);
    umst_init_list_assign = {66, 42, 124, 22, 12, 74, 23, 40};
    print("umst_init_list_assign", umst_init_list_assign);
    
    puts("#--------------------------------------------------------#\n");
}

void test_traverse(){
    ani::unordered_multiset<int> umst{4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    
    puts("#--------------------------------------------------------#");
    puts("Traverse using iterator");
    for(ani::unordered_multiset<int>::iterator it = umst.begin(); it != umst.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using const_iterator");
    for(ani::unordered_multiset<int>::const_iterator it = umst.cbegin(); it != umst.cend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_modifiers(){
    puts("#--------------------------------------------------------#");
    ani::unordered_multiset<int> umst_1 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("umst_1", umst_1);
    umst_1.insert(-10);
    umst_1.insert(75);
    print("umst_1", umst_1);

    puts("#--------------------------------------------------------#");
    ani::unordered_multiset<int> umst_2;
    umst_2.insert(umst_1.begin(), umst_1.end());
    print("umst_2", umst_2);

    puts("#--------------------------------------------------------#");
    ani::unordered_multiset<int> umst_3;
    umst_3.insert({5, 32, -23, 34, 72, 12, 37});
    print("umst_3", umst_3);

    puts("#--------------------------------------------------------#");
    ani::unordered_multiset<int> umst_4 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("umst_4", umst_4);
    umst_4.erase(umst_4.begin());
    print("umst_4", umst_4);
    umst_4.erase(--umst_4.end());
    print("umst_4", umst_4);

    umst_4.erase(53);
    print("umst_4", umst_4);

    umst_4.clear();
    print("umst_4", umst_4);

    puts("#--------------------------------------------------------#");
    ani::unordered_multiset<int> umst_5 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("umst_5", umst_5);
    umst_5.erase(++umst_5.begin(), --umst_5.end());
    print("umst_5", umst_5);

    puts("#--------------------------------------------------------#");
    ani::unordered_multiset<int> umst_6 {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    print("umst_5", umst_5);
    print("umst_6", umst_6);
    umst_6.swap(umst_5);
    print("umst_5", umst_5);
    print("umst_6", umst_6);

    puts("#--------------------------------------------------------#\n");
}

void test_lookup(){
    puts("#--------------------------------------------------------#");
    ani::unordered_multiset<int> umst_1 {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    std::cout << "count(4) : " << umst_1.count(4) << std::endl;
    std::cout << "count(-7) : " << umst_1.count(-7) << std::endl;
    
    auto it = umst_1.find(9);
    if(it != umst_1.end())
        std::cout << "find(9) != end() : " << (it != umst_1.end()) << ", val : " << *it << std::endl;

    it = umst_1.find(12);
    if(it == umst_1.end())
        std::cout << "find(12) == end() : " << (it == umst_1.end()) << std::endl;

    std::cout << "contains(3) : " << umst_1.contains(3) << std::endl;
    std::cout << "contains(0) : " << umst_1.contains(0) << std::endl;
    puts("#--------------------------------------------------------#\n");
}

void test_bucket_interface(){
    ani::unordered_multiset<int> umst;
    for(int i = 0; i < 48; ++i)
        umst.insert(i);

    puts("#--------------------------------------------------------#");
    for(ani::unordered_multiset<int>::iterator iter = umst.begin(); iter != umst.end(); ++iter)
        std::cout << *iter << " ";
    std::cout << std::endl;

    for(int i = 0; i < umst.bucket_count(); ++i){
        std::cout << "bucket_size(" << i << ") : " << umst.bucket_size(i) << " : ";
        for(ani::unordered_multiset<int>::local_iterator l_it = umst.begin(i); l_it != umst.end(i); ++l_it)
            std::cout << *l_it << " ";
        std::cout << std::endl;
    }

    puts("#--------------------------------------------------------#\n");
}

void test_hash_policy(){
    ani::unordered_multiset<int> umst;
    for(int i = 0; i < 48; ++i)
        umst.insert(i);

    puts("#--------------------------------------------------------#");
    std::cout << "load factor : " << umst.load_factor() << std::endl;
    std::cout << "max_load_factor : " << umst.max_load_factor() << std::endl;
    std::cout << "bucket count : " << umst.bucket_count() << std::endl;

    umst.clear();
    umst.max_load_factor(0.5);

    for(int i = 0; i < 48; ++i)
        umst.insert(i);

    std::cout << "load factor : " << umst.load_factor() << std::endl;
    std::cout << "max_load_factor : " << umst.max_load_factor() << std::endl;
    std::cout << "bucket count : " << umst.bucket_count() << std::endl;

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
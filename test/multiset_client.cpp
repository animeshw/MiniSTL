#include <iostream>
#include <cassert>
#include "..\include\multiset.hpp"

template <typename T, typename Compare>
void print(const char* msg, const ani::multiset<T, Compare>& mst){
    std::cout << msg << " : ";
    std::cout << "[";
    for(const T& elem : mst)
        std::cout << elem << " ";
    std::cout << "] [size : " << mst.size() << "]" << std::endl;
}

void test_construct(){
    puts("#--------------------------------------------------------#");
    puts("Default construct");
    ani::multiset<int> mst_default;
    assert(mst_default.empty());
    print("mst_default", mst_default);

    puts("#--------------------------------------------------------#");
    puts("Constructed using initializer list and default Compare");
    ani::multiset<int> mst_init_list {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    print("mst_init_list", mst_init_list);

    puts("#--------------------------------------------------------#");
    puts("Constructed using initializer list and custom Compare");
    ani::multiset<int, ani::greater<int>> mst_grtr_init_list {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    print("mst_grtr_init_list", mst_grtr_init_list);
    
    puts("#--------------------------------------------------------#");
    puts("Constructed using iterator range");
    ani::multiset<int> mst_iter_range(++mst_init_list.begin(), --mst_init_list.end());
    print("mst_iter_range", mst_iter_range);

    puts("#--------------------------------------------------------#");
    puts("Copy Constructed");
    ani::multiset<int> mst_copy(mst_init_list);
    print("mst_copy", mst_copy);

    puts("#--------------------------------------------------------#");
    puts("Copy Assigned");
    ani::multiset<int> mst_copy_assign = mst_copy;
    print("mst_copy_assign", mst_copy_assign);

    mst_copy_assign = mst_init_list;
    print("mst_copy_assign", mst_copy_assign);
    
    puts("#--------------------------------------------------------#");
    puts("Move Constructed");
    ani::multiset<int> mst_move(std::move(mst_init_list));
    assert(mst_init_list.empty());
    print("mst_move", mst_move);
    print("mst_init_list", mst_init_list);

    puts("#--------------------------------------------------------#");
    puts("Move Assigned");
    ani::multiset<int> mst_move_assign = std::move(mst_copy);
    assert(mst_copy.empty());
    print("mst_move_assign", mst_move_assign);
    print("mst_copy", mst_copy);

    mst_move_assign = std::move(mst_iter_range);
    print("mst_move_assign", mst_move_assign);
    print("mst_iter_range", mst_iter_range);
    
    puts("#--------------------------------------------------------#");
    puts("Initializer list assigned");
    ani::multiset<int> mst_init_list_assign = {2, 4, 7, 1, 4, 5, 7, 3, 6};
    print("mst_init_list_assign", mst_init_list_assign);
    mst_init_list_assign = {66, 42, 124, 22, 12, 74, 23};
    print("mst_init_list_assign", mst_init_list_assign);
    
    puts("#--------------------------------------------------------#\n");
}

void test_traverse(){
    ani::multiset<int> mst{4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    
    puts("#--------------------------------------------------------#");
    puts("Traverse using iterator");
    for(ani::multiset<int>::iterator it = mst.begin(); it != mst.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using const_iterator");
    for(ani::multiset<int>::const_iterator it = mst.cbegin(); it != mst.cend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using reverse_iterator");
    for(ani::multiset<int>::reverse_iterator it = mst.rbegin(); it != mst.rend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using const_reverse_iterator");
    for(ani::multiset<int>::const_reverse_iterator it = mst.crbegin(); it != mst.crend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_modifiers(){
    puts("#--------------------------------------------------------#");
    ani::multiset<int> i_mst_1 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("i_mst_1", i_mst_1);
    i_mst_1.insert(-10);
    i_mst_1.insert(75);
    print("i_mst_1", i_mst_1);

    puts("#--------------------------------------------------------#");
    ani::multiset<int, ani::greater<int>> i_mst_2 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("i_mst_2", i_mst_2);
    i_mst_2.insert(-10);
    i_mst_2.insert(75);
    print("i_mst_2", i_mst_2);
    
    puts("#--------------------------------------------------------#");
    ani::multiset<int> i_mst_3;
    i_mst_3.insert(i_mst_2.begin(), i_mst_2.end());
    print("i_mst_3", i_mst_3);

    puts("#--------------------------------------------------------#");
    ani::multiset<int> i_mst_4;
    i_mst_4.insert({5, 32, -23, 34, 72, 12, 37});
    print("i_mst_4", i_mst_4);

    puts("#--------------------------------------------------------#");
    ani::multiset<int> i_mst_5 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("i_mst_5", i_mst_5);
    i_mst_5.erase(i_mst_5.begin());
    print("i_mst_5", i_mst_5);
    i_mst_5.erase(--i_mst_5.end());
    print("i_mst_5", i_mst_5);

    i_mst_5.erase(53);
    print("i_mst_5", i_mst_5);

    i_mst_5.clear();
    print("i_mst_5", i_mst_5);

    puts("#--------------------------------------------------------#");
    ani::multiset<int> i_mst_6 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("i_mst_6", i_mst_6);
    i_mst_6.erase(++i_mst_6.begin(), --i_mst_6.end());
    print("i_mst_6", i_mst_6);

    puts("#--------------------------------------------------------#");
    ani::multiset<int> i_mst_7 {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    print("i_mst_6", i_mst_6);
    print("i_mst_7", i_mst_7);
    i_mst_7.swap(i_mst_6);
    print("i_mst_6", i_mst_6);
    print("i_mst_7", i_mst_7);

    puts("#--------------------------------------------------------#\n");
}

void test_lookup(){
    puts("#--------------------------------------------------------#");
    ani::multiset<int> i_mst {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    std::cout << "count(4) : " << i_mst.count(4) << std::endl;
    std::cout << "count(-7) : " << i_mst.count(-7) << std::endl;
    
    auto it = i_mst.find(9);
    if(it != i_mst.end())
        std::cout << "find(9) != end() : " << (it != i_mst.end()) << ", val : " << *it << std::endl;

    it = i_mst.find(12);
    if(it == i_mst.end())
        std::cout << "find(12) == end() : " << (it == i_mst.end()) << std::endl;

    std::cout << "contains(3) : " << i_mst.contains(3) << std::endl;
    std::cout << "contains(0) : " << i_mst.contains(0) << std::endl;

    it = i_mst.lower_bound(3);
    std::cout << "lower_bound(3) : " << *it << std::endl;
    it = i_mst.upper_bound(8);
    std::cout << "upper_bound(8) : " << *it << std::endl;
    puts("#--------------------------------------------------------#\n");
}

void test_compare(){
    puts("#--------------------------------------------------------#");
    ani::multiset<int> i_mst_1 {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    ani::multiset<int> i_mst_2 {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    ani::multiset<int> i_mst_3 {4, 9, 1, 3, 2, 7, 5, 8, 1, 4};
    ani::multiset<int> i_mst_4 {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4, 10};

    std::cout << std::boolalpha;
    std::cout << "i_mst_1 == i_mst_2 : " << (i_mst_1 == i_mst_2) << std::endl;
    std::cout << "i_mst_1 == i_mst_3 : " << (i_mst_1 == i_mst_3) << std::endl;
    std::cout << "i_mst_1 != i_mst_3 : " << (i_mst_1 != i_mst_3) << std::endl;

    std::cout << "i_mst_1 < i_mst_2 : " << (i_mst_1 < i_mst_2) << std::endl;
    std::cout << "i_mst_1 < i_mst_4 : " << (i_mst_1 < i_mst_4) << std::endl;
    std::cout << "i_mst_1 > i_mst_3 : " << (i_mst_1 > i_mst_3) << std::endl;
    std::cout << "i_mst_1 >= i_mst_2 : " << (i_mst_1 >= i_mst_2) << std::endl;
    std::cout << "i_mst_1 <= i_mst_4 : " << (i_mst_1 <= i_mst_4) << std::endl;

    puts("#--------------------------------------------------------#\n");
}

int main(){
    test_construct();
    test_traverse();
    test_modifiers();
    test_lookup();
    test_compare();
    puts("All tests passed!");
    return 0;
}
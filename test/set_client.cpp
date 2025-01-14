#include <iostream>
#include "..\include\set.hpp"
#include <cassert>

template <typename T, typename Compare>
void print(const char* msg, const ani::set<T, Compare>& st){
    std::cout << msg << " : ";
    std::cout << "[";
    for(const T& elem : st)
        std::cout << elem << " ";
    std::cout << "] [size : " << st.size() << "]" << std::endl;
}

void test_construct(){
    puts("#--------------------------------------------------------#");
    puts("Default construct");
    ani::set<int> st_default;
    assert(st_default.empty());
    print("st_default", st_default);

    puts("#--------------------------------------------------------#");
    puts("Constructed using initializer list and default Compare");
    ani::set<int> st_init_list {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    print("st_init_list", st_init_list);

    puts("#--------------------------------------------------------#");
    puts("Constructed using initializer list and custom Compare");
    ani::set<int, ani::greater<int>> st_grtr_init_list {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    print("st_grtr_init_list", st_grtr_init_list);
    
    puts("#--------------------------------------------------------#");
    puts("Constructed using iterator range");
    ani::set<int> st_iter_range(++st_init_list.begin(), --st_init_list.end());
    print("st_iter_range", st_iter_range);

    puts("#--------------------------------------------------------#");
    puts("Copy Constructed");
    ani::set<int> st_copy(st_init_list);
    print("st_copy", st_copy);

    puts("#--------------------------------------------------------#");
    puts("Copy Assigned");
    ani::set<int> st_copy_assign = st_copy;
    print("st_copy_assign", st_copy_assign);

    st_copy_assign = st_init_list;
    print("st_copy_assign", st_copy_assign);
    
    puts("#--------------------------------------------------------#");
    puts("Move Constructed");
    ani::set<int> st_move(std::move(st_init_list));
    assert(st_init_list.empty());
    print("st_move", st_move);
    print("st_init_list", st_init_list);

    puts("#--------------------------------------------------------#");
    puts("Move Assigned");
    ani::set<int> st_move_assign = std::move(st_copy);
    assert(st_copy.empty());
    print("st_move_assign", st_move_assign);
    print("st_copy", st_copy);

    st_move_assign = std::move(st_iter_range);
    print("st_move_assign", st_move_assign);
    print("st_iter_range", st_iter_range);
    
    puts("#--------------------------------------------------------#");
    puts("Initializer list assigned");
    ani::set<int> st_init_list_assign = {2, 4, 7, 1, 4, 5, 7, 3, 6};
    print("st_init_list_assign", st_init_list_assign);
    st_init_list_assign = {66, 42, 124, 22, 12, 74, 23};
    print("st_init_list_assign", st_init_list_assign);
    
    puts("#--------------------------------------------------------#\n");
}

void test_traverse(){
    ani::set<int> st{4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    
    puts("#--------------------------------------------------------#");
    puts("Traverse using iterator");
    for(ani::set<int>::iterator it = st.begin(); it != st.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using const_iterator");
    for(ani::set<int>::const_iterator it = st.cbegin(); it != st.cend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using reverse_iterator");
    for(ani::set<int>::reverse_iterator it = st.rbegin(); it != st.rend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using const_reverse_iterator");
    for(ani::set<int>::const_reverse_iterator it = st.crbegin(); it != st.crend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_modifiers(){
    puts("#--------------------------------------------------------#");
    ani::set<int> i_set_1 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("i_set_1", i_set_1);
    i_set_1.insert(-10);
    i_set_1.insert(75);
    print("i_set_1", i_set_1);

    puts("#--------------------------------------------------------#");
    ani::set<int, ani::greater<int>> i_set_2 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("i_set_2", i_set_2);
    i_set_2.insert(-10);
    i_set_2.insert(75);
    print("i_set_2", i_set_2);
    
    puts("#--------------------------------------------------------#");
    ani::set<int> i_set_3;
    i_set_3.insert(i_set_2.begin(), i_set_2.end());
    print("i_set_3", i_set_3);

    puts("#--------------------------------------------------------#");
    ani::set<int> i_set_4;
    i_set_4.insert({5, 32, -23, 34, 72, 12, 37});
    print("i_set_4", i_set_4);

    puts("#--------------------------------------------------------#");
    ani::set<int> i_set_5 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("i_set_5", i_set_5);
    i_set_5.erase(i_set_5.begin());
    print("i_set_5", i_set_5);
    i_set_5.erase(--i_set_5.end());
    print("i_set_5", i_set_5);

    i_set_5.erase(53);
    print("i_set_5", i_set_5);

    i_set_5.clear();
    print("i_set_5", i_set_5);

    puts("#--------------------------------------------------------#");
    ani::set<int> i_set_6 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("i_set_6", i_set_6);
    i_set_6.erase(++i_set_6.begin(), --i_set_6.end());
    print("i_set_6", i_set_6);

    puts("#--------------------------------------------------------#");
    ani::set<int> i_set_7 {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    print("i_set_6", i_set_6);
    print("i_set_7", i_set_7);
    i_set_7.swap(i_set_6);
    print("i_set_6", i_set_6);
    print("i_set_7", i_set_7);

    puts("#--------------------------------------------------------#\n");
}

void test_lookup(){
    puts("#--------------------------------------------------------#");
    ani::set<int> i_set_1 {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    std::cout << "count(4) : " << i_set_1.count(4) << std::endl;
    std::cout << "count(-7) : " << i_set_1.count(-7) << std::endl;
    
    auto it = i_set_1.find(9);
    if(it != i_set_1.end())
        std::cout << "find(9) != end() : " << (it != i_set_1.end()) << ", val : " << *it << std::endl;

    it = i_set_1.find(12);
    if(it == i_set_1.end())
        std::cout << "find(12) == end() : " << (it == i_set_1.end()) << std::endl;

    std::cout << "contains(3) : " << i_set_1.contains(3) << std::endl;
    std::cout << "contains(0) : " << i_set_1.contains(0) << std::endl;

    it = i_set_1.lower_bound(3);
    std::cout << "lower_bound(3) : " << *it << std::endl;
    it = i_set_1.upper_bound(8);
    std::cout << "upper_bound(8) : " << *it << std::endl;
    puts("#--------------------------------------------------------#\n");
}

void test_compare(){
    puts("#--------------------------------------------------------#");
    ani::set<int> i_set_1 {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    ani::set<int> i_set_2 {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4};
    ani::set<int> i_set_3 {4, 9, 1, 3, 2, 7, 5, 8, 1, 4};
    ani::set<int> i_set_4 {4, 9, 1, 3, 2, 6, 7, 5, 8, 1, 4, 10};

    std::cout << std::boolalpha;
    std::cout << "i_set_1 == i_set_2 : " << (i_set_1 == i_set_2) << std::endl;
    std::cout << "i_set_1 == i_set_3 : " << (i_set_1 == i_set_3) << std::endl;
    std::cout << "i_set_1 != i_set_3 : " << (i_set_1 != i_set_3) << std::endl;

    std::cout << "i_set_1 < i_set_2 : " << (i_set_1 < i_set_2) << std::endl;
    std::cout << "i_set_1 < i_set_4 : " << (i_set_1 < i_set_4) << std::endl;
    std::cout << "i_set_1 > i_set_3 : " << (i_set_1 > i_set_3) << std::endl;
    std::cout << "i_set_1 >= i_set_2 : " << (i_set_1 >= i_set_2) << std::endl;
    std::cout << "i_set_1 <= i_set_4 : " << (i_set_1 <= i_set_4) << std::endl;

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
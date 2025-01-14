#include <iostream>
#include <cassert>
#include "..\include\list.hpp"

template <typename T>
void print(const char* msg, const ani::list<T>& lst){
    if(msg)
        std::cout << msg << " : ";
    std::cout << "[";
    for(const T& elem : lst)
        std::cout << elem << " ";
    std::cout << "] [size : " << lst.size() << "]" << std::endl;
}

void test_contruct(){
    puts("#--------------------------------------------------------#");
    puts("Default construct");
    ani::list<int> lst_default;
    assert(lst_default.empty());
    print("lst_default", lst_default);

    puts("#--------------------------------------------------------#");
    puts("Constructed using count");
    ani::list<int> lst_count(10);
    assert(!lst_count.empty());
    print("lst_count", lst_count);

    puts("#--------------------------------------------------------#");
    puts("Constructed using count and value");
    ani::list<int> lst_count_and_value(8, 99);
    assert(!lst_count_and_value.empty());
    print("lst_count_and_value", lst_count_and_value);

    puts("#--------------------------------------------------------#");
    puts("Constructed using initializer list");
    ani::list<int> lst_init_list {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    assert(!lst_init_list.empty());
    print("lst_init_list", lst_init_list);

    puts("#--------------------------------------------------------#");
    puts("Constructed using iterator range");
    ani::list<int> lst_iter_range(++lst_init_list.begin(), --lst_init_list.end());
    assert(!lst_iter_range.empty());
    print("lst_iter_range", lst_iter_range);

    puts("#--------------------------------------------------------#");
    puts("Copy Constructed");
    ani::list<int> lst_copy(lst_init_list);
    assert(!lst_copy.empty());
    print("lst_copy", lst_copy);

    puts("#--------------------------------------------------------#");
    puts("Copy Assigned");
    ani::list<int> lst_copy_assign = lst_copy;
    assert(!lst_copy_assign.empty());
    print("lst_copy_assign", lst_copy_assign);

    lst_copy_assign = lst_count_and_value;
    print("lst_copy_assign", lst_copy_assign);
    
    puts("#--------------------------------------------------------#");
    puts("Move Constructed");
    ani::list<int> lst_move(std::move(lst_init_list));
    assert(!lst_move.empty());
    print("lst_move", lst_move);
    assert(lst_init_list.empty());
    print("lst_init_list", lst_init_list);

    puts("#--------------------------------------------------------#");
    puts("Move Assigned");
    ani::list<int> lst_move_assign = std::move(lst_iter_range);
    print("lst_move_assign", lst_move_assign);
    assert(lst_iter_range.empty());
    print("lst_iter_range", lst_iter_range);

    lst_move_assign = std::move(lst_count_and_value);
    print("lst_move_assign", lst_move_assign);
    assert(lst_count_and_value.empty());
    print("lst_count_and_value", lst_count_and_value);

    puts("#--------------------------------------------------------#");
    puts("Initializer list assigned");
    ani::list<int> lst_init_list_assign = {10, 20, 30, 40, 50};
    print("lst_init_list_assign", lst_init_list_assign);
    lst_init_list_assign = {66, 42, 124, 22, 12, 74, 23};
    print("lst_init_list_assign", lst_init_list_assign);
    puts("#--------------------------------------------------------#\n");
}

void test_element_access(){
    ani::list<int> lst_of_ints {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    puts("#--------------------------------------------------------#");
    puts("Read");
    std::cout << "front() : " << lst_of_ints.front() << std::endl;
    std::cout << "back() : " << lst_of_ints.back() << std::endl;
    puts("#--------------------------------------------------------#");
    puts("Write");
    std::cout << "front() = 19 : " << (lst_of_ints.front() = 19) << std::endl;
    std::cout << "back() = -66 : " << (lst_of_ints.back() = -66) << std::endl;
    print("lst_of_ints", lst_of_ints);

    puts("#--------------------------------------------------------#");
    puts("Access on empty list");
    ani::list<int> lst_empty;
    try{
        // lst_empty.front();
        // lst_empty.back();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    puts("#--------------------------------------------------------#\n");
}

void test_modifiers(){
    puts("#--------------------------------------------------------#");
    ani::list<int> i_lst1{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_lst1", i_lst1);
    i_lst1.insert(i_lst1.begin(), -10);
    print("i_lst1", i_lst1);
    i_lst1.insert(i_lst1.end(), -20);
    print("i_lst1", i_lst1);
    auto it = i_lst1.begin();
    ++it; ++it; ++it;               // replace by ani::advance()
    i_lst1.insert(it, -20);
    print("i_lst1", i_lst1);
    puts("#--------------------------------------------------------#");
    ani::list<int> i_lst2{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_lst2", i_lst2);
    i_lst2.insert(i_lst2.begin(), 4, 999);
    print("i_lst2", i_lst2);
    i_lst2.insert(i_lst2.end(), 2, -10);
    print("i_lst2", i_lst2);
    it = i_lst2.begin();
    ++it; ++it; ++it;
    i_lst2.insert(it, 4, -30);
    print("i_lst2", i_lst2);

    puts("#--------------------------------------------------------#");
    ani::list<int> i_lst3{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_lst3", i_lst3);
    i_lst3.insert(i_lst3.begin(), ++i_lst2.begin(), --i_lst2.end());
    print("i_lst3", i_lst3);

    puts("#--------------------------------------------------------#");
    ani::list<int> i_lst4{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_lst4", i_lst4);
    i_lst4.erase(++i_lst4.begin());
    print("i_lst4", i_lst4);
    i_lst4.erase(i_lst4.end());
    print("i_lst4", i_lst4);

    i_lst4.erase(++i_lst4.begin(), i_lst4.end());
    print("i_lst4", i_lst4);

    puts("#--------------------------------------------------------#");
    ani::list<int> i_lst5{1, 2, 3, 4, 5, 6, 7, 8};
    i_lst5.push_back(10);
    i_lst5.push_front(-20);
    print("i_lst5", i_lst5);

    i_lst5.pop_back();
    i_lst5.pop_front();
    print("i_lst5", i_lst5);

    i_lst5.clear();
    puts("Pop on empty list");
    try{
        // i_lst5.pop_front();
        // i_lst5.pop_back();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    puts("#--------------------------------------------------------#");

    ani::list<int> i_lst6{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_lst6", i_lst6);
    i_lst6.resize(8);
    print("i_lst6", i_lst6);
    i_lst6.resize(4);
    print("i_lst6", i_lst6);
    i_lst6.resize(10);
    print("i_lst6", i_lst6);

    i_lst6.clear();
    print("i_lst6", i_lst6);
    puts("#--------------------------------------------------------#");

    ani::list<int> i_lst7{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_lst7", i_lst7);
    i_lst7.assign(10, 100);
    print("i_lst7", i_lst7);
    i_lst7.assign(i_lst4.begin(), i_lst4.end());
    print("i_lst7", i_lst7);
    i_lst7.assign({90, 80, 70, 60, 50, 40});
    print("i_lst7", i_lst7);

    puts("#--------------------------------------------------------#");
    print("i_lst2", i_lst2);
    print("i_lst7", i_lst7);
    i_lst2.swap(i_lst7);
    print("i_lst2", i_lst2);
    print("i_lst7", i_lst7);

    puts("#--------------------------------------------------------#\n");
}

void test_traverse(){
    ani::list<int> lst{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    puts("#--------------------------------------------------------#");
    puts("Traverse using iterator");
    for(ani::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using const_iterator");
    for(ani::list<int>::const_iterator it = lst.cbegin(); it != lst.cend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using reverse_iterator");
    for(ani::list<int>::reverse_iterator it = lst.rbegin(); it != lst.rend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using const_reverse_iterator");
    for(ani::list<int>::const_reverse_iterator it = lst.crbegin(); it != lst.crend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_compare(){
    puts("#--------------------------------------------------------#");
    ani::list<int> i_lst_1 {10, 20, 30, 40, 50, 60, 70};
    ani::list<int> i_lst_2 {10, 20, 30, 40, 50, 60, 70};
    ani::list<int> i_lst_3 {10, 20, 30, 40, 50, 60};
    ani::list<int> i_lst_4 {10, 20, 30, 40, 50, 60, 70, 80};

    std::cout << std::boolalpha;
    std::cout << "i_lst_1 == i_lst_2 : " << (i_lst_1 == i_lst_2) << std::endl;
    std::cout << "i_lst_1 == i_lst_3 : " << (i_lst_1 == i_lst_3) << std::endl;
    std::cout << "i_lst_1 != i_lst_3 : " << (i_lst_1 != i_lst_3) << std::endl;

    std::cout << "i_lst_1 < i_lst_2 : " << (i_lst_1 < i_lst_2) << std::endl;
    std::cout << "i_lst_1 < i_lst_4 : " << (i_lst_1 < i_lst_4) << std::endl;
    std::cout << "i_lst_1 > i_lst_3 : " << (i_lst_1 > i_lst_3) << std::endl;
    std::cout << "i_lst_1 >= i_lst_2 : " << (i_lst_1 >= i_lst_2) << std::endl;
    std::cout << "i_lst_1 <= i_lst_4 : " << (i_lst_1 <= i_lst_4) << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_operations(){
    puts("#--------------------------------------------------------#");
    puts("Sort");
    ani::list<int> i_lst_1 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("i_lst_1", i_lst_1);
    i_lst_1.sort(ani::greater<int>());
    print("i_lst_1", i_lst_1);

    ani::list<int> i_lst_2 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("i_lst_2", i_lst_2);
    i_lst_2.sort();
    print("i_lst_2", i_lst_2);

    puts("#--------------------------------------------------------#");
    puts("Merge");
    ani::list<int> i_lst_3 {65, 35, 53, 99, 12, 44, 27, -14, 53};
    ani::list<int> i_lst_4 {5, 32, -23, 34, 72, 12, 37};
    
    i_lst_3.sort();
    i_lst_4.sort();
    print("i_lst_3", i_lst_3);
    print("i_lst_4", i_lst_4);
    i_lst_3.merge(i_lst_4);
    print("i_lst_3", i_lst_3);
    print("i_lst_4", i_lst_4);

    puts("#--------------------------------------------------------#");
    puts("Remove");
    print("i_lst_3", i_lst_3);
    std::cout << "remove(12) : " << i_lst_3.remove(12) << std::endl;
    std::cout << "remove(53) : " << i_lst_3.remove(53) << std::endl;
    std::cout << "remove(37) : " << i_lst_3.remove(37) << std::endl;
    print("i_lst_3", i_lst_3);

    puts("#--------------------------------------------------------#");
    puts("Reverse");
    ani::list<int> i_lst_5 {30, 27, 26, 76, 72, 45, 99, 1, 34, 19};
    print("i_lst_5", i_lst_5);
    i_lst_5.reverse();
    print("i_lst_5", i_lst_5);

    puts("#--------------------------------------------------------#\n");
}

int main(){
    test_contruct();
    test_element_access();
    test_modifiers();
    test_traverse();
    test_compare();
    test_operations();
    puts("All tests passed!");
    return 0;
}
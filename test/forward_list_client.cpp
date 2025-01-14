#include <iostream>
#include <cassert>
#include "..\include\forward_list.hpp"

template <typename T>
void print(const char* msg, const ani::forward_list<T>& lst){
    if(msg)
        std::cout << msg << " : ";
    std::cout << "[";
    size_t n = 0;
    for(const T& elem : lst){
        std::cout << elem << " ";
        ++n;
    }
    std::cout << "] [size : " << n << "]" << std::endl;
}

void test_contruct(){
    puts("#--------------------------------------------------------#");
    puts("Default construct");
    ani::forward_list<int> flst_default;
    assert(flst_default.empty());
    print("flst_default", flst_default);

    puts("#--------------------------------------------------------#");
    puts("Constructed using count");
    ani::forward_list<int> flst_count(10);
    assert(!flst_count.empty());
    print("flst_count", flst_count);

    puts("#--------------------------------------------------------#");
    puts("Constructed using count and value");
    ani::forward_list<int> flst_count_and_value(8, 99);
    assert(!flst_count_and_value.empty());
    print("flst_count_and_value", flst_count_and_value);

    puts("#--------------------------------------------------------#");
    puts("Constructed using initializer list");
    ani::forward_list<int> flst_init_list {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    assert(!flst_init_list.empty());
    print("flst_init_list", flst_init_list);

    puts("#--------------------------------------------------------#");
    puts("Constructed using iterator range");
    ani::forward_list<int> flst_iter_range(++flst_init_list.begin(), flst_init_list.end());
    assert(!flst_iter_range.empty());
    print("flst_iter_range", flst_iter_range);

    puts("#--------------------------------------------------------#");
    puts("Copy Constructed");
    ani::forward_list<int> flst_copy(flst_init_list);
    assert(!flst_copy.empty());
    print("flst_copy", flst_copy);

    puts("#--------------------------------------------------------#");
    puts("Copy Assigned");
    ani::forward_list<int> flst_copy_assign = flst_copy;
    assert(!flst_copy_assign.empty());
    print("flst_copy_assign", flst_copy_assign);

    flst_copy_assign = flst_count_and_value;
    print("flst_copy_assign", flst_copy_assign);
    
    puts("#--------------------------------------------------------#");
    puts("Move Constructed");
    ani::forward_list<int> flst_move(std::move(flst_init_list));
    assert(!flst_move.empty());
    print("flst_move", flst_move);
    assert(flst_init_list.empty());
    print("flst_init_list", flst_init_list);

    puts("#--------------------------------------------------------#");
    puts("Move Assigned");
    ani::forward_list<int> flst_move_assign = std::move(flst_iter_range);
    print("flst_move_assign", flst_move_assign);
    assert(flst_iter_range.empty());
    print("flst_iter_range", flst_iter_range);

    flst_move_assign = std::move(flst_count_and_value);
    print("flst_move_assign", flst_move_assign);
    assert(flst_count_and_value.empty());
    print("flst_count_and_value", flst_count_and_value);

    puts("#--------------------------------------------------------#");
    puts("Initializer list assigned");
    ani::forward_list<int> flst_init_list_assign = {10, 20, 30, 40, 50};
    print("flst_init_list_assign", flst_init_list_assign);
    flst_init_list_assign = {66, 42, 124, 22, 12, 74, 23};
    print("flst_init_list_assign", flst_init_list_assign);
    puts("#--------------------------------------------------------#\n");
}

void test_element_access(){
    ani::forward_list<int> flst_of_ints {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    puts("#--------------------------------------------------------#");
    puts("Read");
    std::cout << "front() : " << flst_of_ints.front() << std::endl;
    puts("#--------------------------------------------------------#");
    puts("Write");
    std::cout << "front() = 19 : " << (flst_of_ints.front() = 19) << std::endl;
    print("flst_of_ints", flst_of_ints);

    puts("#--------------------------------------------------------#");
    puts("Access on empty list");
    ani::forward_list<int> flst_empty;
    try{
        flst_empty.front();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    puts("#--------------------------------------------------------#\n");
}

void test_modifiers(){
    puts("#--------------------------------------------------------#");
    ani::forward_list<int> i_flst1{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_flst1", i_flst1);
    i_flst1.insert_after(i_flst1.before_begin(), -10);
    print("i_flst1", i_flst1);
    try{
        i_flst1.insert_after(i_flst1.end(), -20);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    auto it = i_flst1.begin();
    ++it; ++it; ++it;               // replace by ani::advance()
    i_flst1.insert_after(it, -20);
    print("i_flst1", i_flst1);
    
    puts("#--------------------------------------------------------#");
    ani::forward_list<int> i_flst2{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_flst2", i_flst2);
    i_flst2.insert_after(i_flst2.begin(), 4, 999);
    print("i_flst2", i_flst2);
    it = i_flst2.begin();
    ++it; ++it; ++it;
    i_flst2.insert_after(it, 4, -30);
    print("i_flst2", i_flst2);

    puts("#--------------------------------------------------------#");
    ani::forward_list<int> i_flst3{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_flst3", i_flst3);
    i_flst3.insert_after(i_flst3.begin(), ++i_flst2.begin(), i_flst2.end());
    print("i_flst3", i_flst3);

    puts("#--------------------------------------------------------#");
    ani::forward_list<int> i_flst4{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_flst4", i_flst4);
    i_flst4.erase_after(i_flst4.before_begin());
    print("i_flst4", i_flst4);
    i_flst4.erase_after(i_flst4.begin());
    print("i_flst4", i_flst4);

    i_flst4.erase_after(++i_flst4.begin(), i_flst4.end());
    print("i_flst4", i_flst4);

    puts("#--------------------------------------------------------#");
    ani::forward_list<int> i_flst5{1, 2, 3, 4, 5, 6, 7, 8};
    i_flst5.push_front(-20);
    print("i_flst5", i_flst5);

    i_flst5.pop_front();
    print("i_flst5", i_flst5);

    i_flst5.clear();
    puts("Pop on empty list");
    try{
        i_flst5.pop_front();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    puts("#--------------------------------------------------------#");

    ani::forward_list<int> i_flst6{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_flst6", i_flst6);
    i_flst6.resize(8);
    print("i_flst6", i_flst6);
    i_flst6.resize(4);
    print("i_flst6", i_flst6);
    i_flst6.resize(10);
    print("i_flst6", i_flst6);

    i_flst6.clear();
    print("i_flst6", i_flst6);
    puts("#--------------------------------------------------------#");

    ani::forward_list<int> i_flst7{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_flst7", i_flst7);
    i_flst7.assign(10, 100);
    print("i_flst7", i_flst7);
    i_flst7.assign(i_flst4.begin(), i_flst4.end());
    print("i_flst7", i_flst7);
    i_flst7.assign({90, 80, 70, 60, 50, 40});
    print("i_flst7", i_flst7);

    puts("#--------------------------------------------------------#");
    print("i_flst2", i_flst2);
    print("i_flst7", i_flst7);
    i_flst2.swap(i_flst7);
    print("i_flst2", i_flst2);
    print("i_flst7", i_flst7);

    puts("#--------------------------------------------------------#\n");
}

void test_traverse(){
    ani::forward_list<int> flst{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    puts("#--------------------------------------------------------#");
    puts("Traverse using iterator");
    for(ani::forward_list<int>::iterator it = flst.begin(); it != flst.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using const_iterator");
    for(ani::forward_list<int>::const_iterator it = flst.cbegin(); it != flst.cend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_compare(){
    puts("#--------------------------------------------------------#");
    ani::forward_list<int> i_flst_1 {10, 20, 30, 40, 50, 60, 70};
    ani::forward_list<int> i_flst_2 {10, 20, 30, 40, 50, 60, 70};
    ani::forward_list<int> i_flst_3 {10, 20, 30, 40, 50, 60};
    ani::forward_list<int> i_flst_4 {10, 20, 30, 40, 50, 60, 70, 80};

    std::cout << std::boolalpha;
    std::cout << "i_flst_1 == i_flst_2 : " << (i_flst_1 == i_flst_2) << std::endl;
    std::cout << "i_flst_1 == i_flst_3 : " << (i_flst_1 == i_flst_3) << std::endl;
    std::cout << "i_flst_1 != i_flst_3 : " << (i_flst_1 != i_flst_3) << std::endl;

    std::cout << "i_flst_1 < i_flst_2 : " << (i_flst_1 < i_flst_2) << std::endl;
    std::cout << "i_flst_1 < i_flst_4 : " << (i_flst_1 < i_flst_4) << std::endl;
    std::cout << "i_flst_1 > i_flst_3 : " << (i_flst_1 > i_flst_3) << std::endl;
    std::cout << "i_flst_1 >= i_flst_2 : " << (i_flst_1 >= i_flst_2) << std::endl;
    std::cout << "i_flst_1 <= i_flst_4 : " << (i_flst_1 <= i_flst_4) << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_operations(){
    puts("#--------------------------------------------------------#");
    puts("Sort");
    ani::forward_list<int> i_flst_1 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("i_flst_1", i_flst_1);
    i_flst_1.sort(ani::greater<int>());
    print("i_flst_1", i_flst_1);

    ani::forward_list<int> i_flst_2 {65, 35, 53, 99, 12, 44, 27, -23, 53};
    print("i_flst_2", i_flst_2);
    i_flst_2.sort();
    print("i_flst_2", i_flst_2);

    puts("#--------------------------------------------------------#");
    puts("Merge");
    ani::forward_list<int> i_flst_3 {65, 35, 53, 99, 12, 44, 27, -14, 53};
    ani::forward_list<int> i_flst_4 {5, 32, -23, 34, 72, 12, 37};
    
    i_flst_3.sort();
    i_flst_4.sort();
    print("i_flst_3", i_flst_3);
    print("i_flst_4", i_flst_4);
    i_flst_3.merge(i_flst_4);
    print("i_flst_3", i_flst_3);
    print("i_flst_4", i_flst_4);

    puts("#--------------------------------------------------------#");
    puts("Remove");
    print("i_flst_3", i_flst_3);
    std::cout << "remove(12) : " << i_flst_3.remove(12) << std::endl;
    std::cout << "remove(53) : " << i_flst_3.remove(53) << std::endl;
    std::cout << "remove(37) : " << i_flst_3.remove(37) << std::endl;
    print("i_flst_3", i_flst_3);

    puts("#--------------------------------------------------------#");
    puts("Reverse");
    ani::forward_list<int> i_flst_5 {30, 27, 26, 76, 72, 45, 99, 1, 34, 19};
    print("i_flst_5", i_flst_5);
    i_flst_5.reverse();
    print("i_flst_5", i_flst_5);

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
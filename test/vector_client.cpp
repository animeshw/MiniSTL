#include <iostream>
#include <cassert>
#include "..\include\vector.hpp"

template <typename T>
void print(const char* msg, const ani::vector<T>& vec){
    if(msg)
        std::cout << msg << " : ";
    std::cout << "[";
    for(const T& elem : vec)
        std::cout << elem << " ";
    std::cout << "] [size : " << vec.size() << ", capacity : " << vec.capacity() << "]" << std::endl;
}

void test_contruct(){
    puts("#--------------------------------------------------------#");
    puts("Default construct");
    ani::vector<int> vec_default;
    assert(vec_default.empty());
    assert(vec_default.size() == 0);
    std::cout << "default capacity : " << vec_default.capacity() << std::endl;
    
    puts("#--------------------------------------------------------#");
    puts("Constructed using capacity");
    ani::vector<int> vec_cap(20);
    assert(vec_cap.empty());
    assert(vec_cap.size() == 0);
    std::cout << "capacity : " << vec_cap.capacity() << std::endl;
    
    puts("#--------------------------------------------------------#");
    puts("Constructed using capacity and value");
    ani::vector<int> vec_cap_and_val(12, 99);
    assert(!vec_cap_and_val.empty());
    std::cout << "vec_cap_and_val : ";
    for(const auto& elem : vec_cap_and_val)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << "capacity : " << vec_cap_and_val.capacity() << std::endl;
    std::cout << "size : " << vec_cap_and_val.size() << std::endl;
    
    puts("#--------------------------------------------------------#");
    puts("Constructed using initializer list");
    ani::vector<int> vec_init_list {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    assert(!vec_init_list.empty());
    std::cout << "vec_init_list : ";
    for(const auto& elem : vec_init_list)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << "capacity : " << vec_init_list.capacity() << std::endl;
    std::cout << "size : " << vec_init_list.size() << std::endl;
    
    puts("#--------------------------------------------------------#");
    puts("Constructed using iterator range");
    ani::vector<int> vec_iter_range(vec_init_list.begin() + 2, vec_init_list.begin() + 8);
    assert(!vec_iter_range.empty());
    std::cout << "vec_iter_range : ";
    for(const auto& elem : vec_iter_range)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << "capacity : " << vec_iter_range.capacity() << std::endl;
    std::cout << "size : " << vec_iter_range.size() << std::endl;
    
    puts("#--------------------------------------------------------#");
    puts("Copy Constructed");
    std::cout << "vec_copy : ";
    ani::vector<int> vec_copy(vec_init_list);
    for(const auto& elem : vec_init_list)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << "capacity : " << vec_init_list.capacity() << std::endl;
    std::cout << "size : " << vec_init_list.size() << std::endl;

    puts("#--------------------------------------------------------#");
    puts("Copy Assigned");
    ani::vector<int> vec_copy_assign = vec_copy;
    std::cout << "vec_copy_assign : ";
    for(const auto& elem : vec_copy_assign)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << "capacity : " << vec_copy_assign.capacity() << std::endl;
    std::cout << "size : " << vec_copy_assign.size() << std::endl;
    
    vec_copy_assign = vec_cap_and_val;
    std::cout << "vec_cap_and_val : ";
    for(const auto& elem : vec_cap_and_val)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << "capacity : " << vec_cap_and_val.capacity() << std::endl;
    std::cout << "size : " << vec_cap_and_val.size() << std::endl;

    puts("#--------------------------------------------------------#");
    puts("Move Constructed");
    ani::vector<int> vec_move(std::move(vec_init_list));
    std::cout << "vec_move : ";
    for(const auto& elem : vec_move)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << "capacity : " << vec_move.capacity() << std::endl;
    std::cout << "size : " << vec_move.size() << std::endl;

    std::cout << "vec_init_list : ";
    for(const auto& elem : vec_init_list)
        std::cout << elem << " ";
    std::cout << std::endl;
    assert(vec_init_list.empty());
    std::cout << "capacity : " << vec_init_list.capacity() << std::endl;
    std::cout << "size : " << vec_init_list.size() << std::endl;


    puts("#--------------------------------------------------------#");
    puts("Move Assigned");
    ani::vector<int> vec_move_assign = std::move(vec_iter_range);
    std::cout << "vec_move_assign : ";
    for(const auto& elem : vec_move_assign)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << "capacity : " << vec_move_assign.capacity() << std::endl;
    std::cout << "size : " << vec_move_assign.size() << std::endl;

    std::cout << "vec_iter_range : ";
    for(const auto& elem : vec_iter_range)
        std::cout << elem << " ";
    std::cout << std::endl;
    assert(vec_iter_range.empty());
    std::cout << "capacity : " << vec_iter_range.capacity() << std::endl;
    std::cout << "size : " << vec_iter_range.size() << std::endl;

    vec_move_assign = std::move(vec_cap_and_val);
    std::cout << "vec_move_assign : ";
    for(const auto& elem : vec_move_assign)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << "capacity : " << vec_move_assign.capacity() << std::endl;
    std::cout << "size : " << vec_move_assign.size() << std::endl;

    std::cout << "vec_cap_and_val : ";
    for(const auto& elem : vec_cap_and_val)
        std::cout << elem << " ";
    std::cout << std::endl;
    assert(vec_cap_and_val.empty());
    std::cout << "capacity : " << vec_cap_and_val.capacity() << std::endl;
    std::cout << "size : " << vec_cap_and_val.size() << std::endl;
    puts("#--------------------------------------------------------#");

    puts("Initializer list Assigned");
    ani::vector<int> vec_init_list_assign = {10, 20, 30, 40, 50};
    std::cout << "vec_init_list_assign : ";
    for(const auto& elem : vec_init_list_assign)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << "capacity : " << vec_init_list_assign.capacity() << std::endl;
    std::cout << "size : " << vec_init_list_assign.size() << std::endl;

    vec_init_list_assign = {66, 42, 124, 22};
    std::cout << "vec_init_list_assign : ";
    for(const auto& elem : vec_init_list_assign)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << "capacity : " << vec_init_list_assign.capacity() << std::endl;
    std::cout << "size : " << vec_init_list_assign.size() << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_element_access(){
    ani::vector<int> vec_of_ints {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    puts("#--------------------------------------------------------#");
    puts("Read");
    std::cout << "front() : " << vec_of_ints.front() << std::endl;
    std::cout << "back() : " << vec_of_ints.back() << std::endl;
    std::cout << "at(4) : " << vec_of_ints.at(4) << std::endl;
    std::cout << "operator[](6) : " << vec_of_ints[6] << std::endl;
    
    puts("#--------------------------------------------------------#");
    puts("Write");
    std::cout << "front() = 7 : " << (vec_of_ints.front() = 7) << std::endl;
    std::cout << "back() = 15 : " << (vec_of_ints.back() = 15) << std::endl;
    std::cout << "at(4) = 45 : " << (vec_of_ints.at(4) = 45) << std::endl;
    std::cout << "operator[](6) = 18 : " << (vec_of_ints[6] = 18) << std::endl;
    
    puts("#--------------------------------------------------------#");
    puts("Access on empty vector");
    ani::vector<int> vec_empty;
    try{
        // vec_empty.front();
        // vec_empty.back();
        // vec_empty.at(7);
        // vec_empty[4];
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    
    puts("#--------------------------------------------------------#");
    puts("Access on out of range element");

    try{
        // vec_of_ints.at(-4);
        // vec_of_ints.at(11);
        // vec_of_ints[-1];
        // vec_of_ints[15];
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    puts("#--------------------------------------------------------#");
    puts("Internal data");
    int* values = vec_of_ints.data();
    for(size_t i = 0; i < vec_of_ints.size(); ++i)
        std::cout << values[i] << " ";
    std::cout << std::endl;

    std::cout << "vec_of_ints before writting : ";
    for(const auto& elem : vec_of_ints)
        std::cout << elem << " ";
    std::cout << std::endl;

    values[2] = 990;

    std::cout << "vec_of_ints after writting : ";
    for(const auto& elem : vec_of_ints)
        std::cout << elem << " ";
    std::cout << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_reserve_and_capacity(){
    puts("#--------------------------------------------------------#");
    puts("Default capacity");
    ani::vector<int> vec_empty;
    std::cout << vec_empty.capacity() << std::endl;
    
    vec_empty.reserve(15);
    puts("Capacity after reserve(15)");
    std::cout << vec_empty.capacity() << std::endl; 
    
    puts("#--------------------------------------------------------#\n");
    ani::vector<int> vec_init_list {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    for(const auto& elem : vec_init_list)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << vec_init_list.capacity() << std::endl;
    
    vec_init_list.reserve(10);
    for(const auto& elem : vec_init_list)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << vec_init_list.capacity() << std::endl;
    
    puts("Capacity after reserve(10)");
    std::cout << vec_init_list.capacity() << std::endl; 

    vec_init_list.reserve(30);
    for(const auto& elem : vec_init_list)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << vec_init_list.capacity() << std::endl;
    
    puts("Capacity after reserve(30)");
    std::cout << vec_init_list.capacity() << std::endl; 

    puts("#--------------------------------------------------------#\n");
}

void test_modifiers(){
    puts("#--------------------------------------------------------#");
    ani::vector<int> i_vec1{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_vec1", i_vec1);
    i_vec1.insert(i_vec1.begin(), -10);             // insert case 1
    print("i_vec1", i_vec1);
    i_vec1.insert(i_vec1.end(), -20);               // insert case 2
    print("i_vec1", i_vec1);
    i_vec1.insert(i_vec1.begin() + 3, -30);         // insert case 3
    print("i_vec1", i_vec1);

    puts("#--------------------------------------------------------#");
    ani::vector<int> i_vec2{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_vec2", i_vec2);
    i_vec2.insert(i_vec2.begin(), 4, 999);          // insert case 1
    print("i_vec2", i_vec2);
    i_vec2.insert(i_vec2.end(), 2, -10);            // insert case 2
    print("i_vec2", i_vec2);
    i_vec2.insert(i_vec2.begin() + 6, 4, -30);      // insert case 3
    print("i_vec2", i_vec2);
    
    puts("#--------------------------------------------------------#");
    ani::vector<int> i_vec3{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_vec3", i_vec3);
    i_vec3.insert(i_vec3.cbegin(), i_vec2.begin() + 10, i_vec2.end() - 5);      // insert case 1
    print("i_vec3", i_vec3);
    i_vec3.insert(i_vec3.cend(), i_vec2.begin() + 2, i_vec2.end() - 14);        // insert case 2
    print("i_vec3", i_vec3);
    i_vec3.insert(i_vec3.begin() + 6, i_vec2.cbegin() + 16, i_vec2.cend());      // insert case 3
    print("i_vec3", i_vec3);

    puts("#--------------------------------------------------------#");
    ani::vector<int> i_vec4{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_vec4", i_vec4);
    i_vec4.erase(i_vec4.cend() - 1);
    print("i_vec4", i_vec4);
    i_vec4.erase(i_vec4.begin() + 2);
    print("i_vec4", i_vec4);

    puts("#--------------------------------------------------------#");
    ani::vector<int> i_vec5{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_vec5", i_vec5);
    i_vec5.erase(i_vec5.begin(), i_vec5.begin() + 3);
    print("i_vec5", i_vec5);
    i_vec5.erase(i_vec5.begin() + 2, i_vec5.end());
    print("i_vec5", i_vec5);
    i_vec5.erase(i_vec5.begin(), i_vec5.end());
    print("i_vec5", i_vec5);

    puts("#--------------------------------------------------------#");
    i_vec5.push_back(10);
    i_vec5.push_back(20);
    i_vec5.push_back(30);
    print("i_vec5", i_vec5);

    i_vec5.pop_back();
    print("i_vec5", i_vec5);
    i_vec5.pop_back();
    i_vec5.pop_back();
    print("i_vec5", i_vec5);
    
    try{
        i_vec5.pop_back();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    puts("#--------------------------------------------------------#");
    ani::vector<int> i_vec6{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_vec6", i_vec6);
    i_vec6.resize(8);
    print("i_vec6", i_vec6);
    i_vec6.resize(4);
    print("i_vec6", i_vec6);
    i_vec6.resize(10);
    print("i_vec6", i_vec6);

    i_vec6.clear();
    print("i_vec6", i_vec6);

    puts("#--------------------------------------------------------#");
    ani::vector<int> i_vec7{1, 2, 3, 4, 5, 6, 7, 8};
    print("i_vec7", i_vec7);
    i_vec7.assign(10, 100);
    print("i_vec7", i_vec7);
    i_vec7.assign(i_vec4.begin(), i_vec4.end());
    print("i_vec7", i_vec7);
    i_vec7.assign({90, 80, 70, 60, 50, 40});
    print("i_vec7", i_vec7);

    puts("#--------------------------------------------------------#");
    print("i_vec2", i_vec2);
    print("i_vec7", i_vec7);
    i_vec2.swap(i_vec7);
    print("i_vec2", i_vec2);
    print("i_vec7", i_vec7);

    puts("#--------------------------------------------------------#\n");
}

void test_traverse(){
    ani::vector<int> vec {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    puts("#--------------------------------------------------------#");
    puts("Traverse using iterator");
    for(ani::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using const_iterator");
    for(ani::vector<int>::const_iterator it = vec.cbegin(); it != vec.cend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using reverse_iterator");
    for(ani::vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("Traverse using const_reverse_iterator");
    for(ani::vector<int>::const_reverse_iterator it = vec.crbegin(); it != vec.crend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_compare(){
    puts("#--------------------------------------------------------#");
    ani::vector<int> vec_1 {10, 20, 30, 40, 50, 60, 70};
    ani::vector<int> vec_2 {10, 20, 30, 40, 50, 60, 70};
    ani::vector<int> vec_3 {10, 20, 30, 40, 50, 60};
    ani::vector<int> vec_4 {10, 20, 30, 40, 50, 60, 70, 80};

    std::cout << std::boolalpha;
    std::cout << "vec_1 == vec_2 : " << (vec_1 == vec_2) << std::endl;
    std::cout << "vec_1 == vec_3 : " << (vec_1 == vec_3) << std::endl;
    std::cout << "vec_1 != vec_3 : " << (vec_1 != vec_3) << std::endl;

    std::cout << "vec_1 < vec_2 : " << (vec_1 < vec_2) << std::endl;
    std::cout << "vec_1 < vec_4 : " << (vec_1 < vec_4) << std::endl;
    std::cout << "vec_1 > vec_3 : " << (vec_1 > vec_3) << std::endl;
    std::cout << "vec_1 >= vec_2 : " << (vec_1 >= vec_2) << std::endl;
    std::cout << "vec_1 <= vec_4 : " << (vec_1 <= vec_4) << std::endl;

    puts("#--------------------------------------------------------#\n");
}

int main(){
    test_contruct();
    test_element_access();
    test_reserve_and_capacity();
    test_modifiers();
    test_traverse();
    test_compare();
    puts("All tests passed!");
    return 0;
}
#include <iostream>
#include <cassert>
#include "..\include\unordered_map.hpp"

template <typename Key, typename T>
void print(const char* msg, const ani::unordered_map<Key, T>& ump){
    std::cout << msg << " : ";
    std::cout << "[";
    for(const ani::pair<const Key, T>& elem : ump)
        std::cout << "{" << elem.first << "-" << elem.second << "} ";
    std::cout << "] [size : " << ump.size() << ", bucket count : " << ump.bucket_count() << "]" << std::endl;
}

void test_construct(){
    puts("#--------------------------------------------------------#");
    puts("Default construct");
    ani::unordered_map<char, int> ump_default;
    assert(ump_default.empty());
    print("ump_default", ump_default);

    puts("#--------------------------------------------------------#");
    puts("Construct using size");
    ani::unordered_map<char, int> ump_size(24);
    assert(ump_size.empty());
    print("ump_size", ump_size);
    
    puts("#--------------------------------------------------------#");
    puts("Constructed using initializer list and default Compare");
    ani::unordered_map<char, int> ump_init_list {{'g', 43}, {'e', 52}, {'k', 32}, {'a', 52}, {'p', 91}, {'k', 47}, {'l', 54}, {'b', 66}, {'a', 52}};
    print("ump_init_list", ump_init_list);

    puts("#--------------------------------------------------------#");
    puts("Constructed using iterator range");
    ani::unordered_map<char, int> ump_iter_range(++ump_init_list.begin(), --ump_init_list.end());
    print("ump_iter_range", ump_iter_range);

    puts("#--------------------------------------------------------#");
    puts("Copy Constructed");
    ani::unordered_map<char, int> ump_copy(ump_init_list);
    print("ump_copy", ump_copy);
    
    puts("#--------------------------------------------------------#");
    puts("Copy Assigned");
    ani::unordered_map<char, int> ump_copy_assign = ump_copy;
    print("ump_copy_assign", ump_copy_assign);

    ump_copy_assign = ump_init_list;
    print("ump_copy_assign", ump_copy_assign);
    
    puts("#--------------------------------------------------------#");
    puts("Move Constructed");
    ani::unordered_map<char, int> ump_move(std::move(ump_init_list));
    assert(ump_init_list.empty());
    print("ump_move", ump_move);
    print("ump_init_list", ump_init_list);

    puts("#--------------------------------------------------------#");
    puts("Move Assigned");
    ani::unordered_map<char, int> ump_move_assign = std::move(ump_copy);
    assert(ump_copy.empty());
    print("ump_move_assign", ump_move_assign);
    print("ump_copy", ump_copy);

    ump_move_assign = std::move(ump_iter_range);
    print("ump_move_assign", ump_move_assign);
    print("ump_iter_range", ump_iter_range);
    
    puts("#--------------------------------------------------------#");
    puts("Initializer list assigned");
    ani::unordered_map<char, int> ump_init_list_assign = {{'g', 43}, {'e', 52}, {'k', 32}, {'a', 52}, {'p', 91}, {'k', 47}, {'l', 54}, {'b', 66}, {'a', 52}};
    print("ump_init_list_assign", ump_init_list_assign);
    ump_init_list_assign = {{'t', 54}, {'t', 87}, {'m', 35}, {'h', 45}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("ump_init_list_assign", ump_init_list_assign);
    
    puts("#--------------------------------------------------------#\n");
}

void test_traverse(){
    ani::unordered_map<char, int> ump {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    puts("#--------------------------------------------------------#");
    puts("Traverse using iterator");
    for(ani::unordered_map<char, int>::iterator it = ump.begin(); it != ump.end(); ++it)
        std::cout << "{" << it->first << "-" << it->second << "} ";
    std::cout << std::endl;

    puts("Traverse using const_iterator");
    for(ani::unordered_map<char, int>::const_iterator it = ump.cbegin(); it != ump.cend(); ++it)
        std::cout << "{" << it->first << "-" << it->second << "} ";
    std::cout << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_element_access(){
    ani::unordered_map<char, int> ump {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};

    puts("#--------------------------------------------------------#");
    puts("Read");
    std::cout << "at('t') : " << ump.at('t') << std::endl;
    std::cout << "operator[]('a') : " << ump['a'] << std::endl;
    
    puts("#--------------------------------------------------------#");
    puts("Write");
    std::cout << "at('t') = 86 : " << (ump.at('t') = 86) << std::endl;
    std::cout << "operator[]('a') = -29 : " << (ump['a'] = -29) << std::endl;
    
    puts("#--------------------------------------------------------#");
    puts("Access on empty map");
    ani::unordered_map<char, int> ump_empty;
    try{
        ump_empty.at('v');
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    try{
        ump_empty['w']; // works
        print("ump_empty", ump_empty);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    puts("#--------------------------------------------------------#");
    puts("Access on out of range element");

    try{
        ump.at('v');
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    try{
        ump['w']; // works
        print("ump", ump);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    puts("#--------------------------------------------------------#\n");
}

void test_modifiers(){
    puts("#--------------------------------------------------------#");
    ani::unordered_map<char, int> ump_1 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("ump_1", ump_1);
    ump_1.insert({'j', 47});
    print("ump_1", ump_1);

    puts("#--------------------------------------------------------#");
    ani::unordered_map<char, int> ump_3;
    ump_3.insert(++ump_1.begin(), --ump_1.end());
    print("ump_3", ump_3);
    
    puts("#--------------------------------------------------------#");
    ani::unordered_map<char, int> ump_4;
    ump_4.insert({{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}});
    print("ump_4", ump_4);
    
    puts("#--------------------------------------------------------#");
    ani::unordered_map<char, int> ump_5 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("ump_5", ump_5);
    ump_5.erase(ump_5.begin());
    print("ump_5", ump_5);
    ump_5.erase(--ump_5.end());
    print("ump_5", ump_5);

    ump_5.erase('z');
    print("ump_5", ump_5);
    
    puts("#--------------------------------------------------------#");
    ani::unordered_map<char, int> ump_6 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("ump_6", ump_6);
    ump_6.erase(++ump_6.begin(), --ump_6.end());
    print("ump_6", ump_6);
    
    puts("#--------------------------------------------------------#");
    ani::unordered_map<char, int> ump_7 {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};
    print("ump_6", ump_6);
    print("ump_7", ump_7);
    ump_7.swap(ump_6);
    print("ump_6", ump_6);
    print("ump_7", ump_7);

    puts("#--------------------------------------------------------#\n");
}

void test_lookup(){
    puts("#--------------------------------------------------------#");
    ani::unordered_map<char, int> ump {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};
    std::cout << "count('s') : " << ump.count('s') << std::endl;
    std::cout << "count('z') : " << ump.count('z') << std::endl;
    
    auto it = ump.find('k');
    if(it != ump.end())
        std::cout << "find('k') != end() : " << (it != ump.end()) << " : {" << it->first << "-" << it->second << "}" << std::endl;

    it = ump.find('x');
    if(it == ump.end())
        std::cout << "find('x') == end() : " << (it == ump.end()) << std::endl;

    std::cout << "contains('u') : " << ump.contains('u') << std::endl;
    std::cout << "contains('d') : " << ump.contains('d') << std::endl;
    puts("#--------------------------------------------------------#\n");
}

void test_bucket_interface(){
    ani::unordered_map<char, int> ump {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};

    puts("#--------------------------------------------------------#");
    for(ani::unordered_map<char, int>::iterator iter = ump.begin(); iter != ump.end(); ++iter)
        std::cout << "(" << iter->first << ", " << iter->second << ") ";
    std::cout << std::endl;

    for(int i = 0; i < ump.bucket_count(); ++i){
        std::cout << "bucket_size(" << i << ") : " << ump.bucket_size(i) << " : ";
        for(ani::unordered_map<char, int>::local_iterator l_it = ump.begin(i); l_it != ump.end(i); ++l_it)
            std::cout << "(" << l_it->first << ", " << l_it->second << ") ";;
        std::cout << std::endl;
    }

    puts("#--------------------------------------------------------#\n");
}

void test_hash_policy(){
    ani::unordered_map<char, int> ump {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};

    puts("#--------------------------------------------------------#");
    std::cout << "load factor : " << ump.load_factor() << std::endl;
    std::cout << "max_load_factor : " << ump.max_load_factor() << std::endl;
    std::cout << "bucket count : " << ump.bucket_count() << std::endl;

    ump.clear();
    ump.max_load_factor(0.5);

    ump = {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};

    std::cout << "load factor : " << ump.load_factor() << std::endl;
    std::cout << "max_load_factor : " << ump.max_load_factor() << std::endl;
    std::cout << "bucket count : " << ump.bucket_count() << std::endl;

    puts("#--------------------------------------------------------#\n");
}

int main(){
    test_construct();
    test_traverse();
    test_element_access();
    test_modifiers();
    test_lookup();
    test_bucket_interface();
    test_hash_policy();
    puts("All tests passed!");
    return 0;
}
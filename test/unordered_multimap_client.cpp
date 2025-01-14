#include <iostream>
#include <cassert>
#include "..\include\unordered_multimap.hpp"

template <typename Key, typename T>
void print(const char* msg, const ani::unordered_multimap<Key, T>& ummp){
    std::cout << msg << " : ";
    std::cout << "[";
    for(const ani::pair<const Key, T>& elem : ummp)
        std::cout << "{" << elem.first << "-" << elem.second << "} ";
    std::cout << "] [size : " << ummp.size() << ", bucket count : " << ummp.bucket_count() << "]" << std::endl;
}

void test_construct(){
    puts("#--------------------------------------------------------#");
    puts("Default construct");
    ani::unordered_multimap<char, int> ummp_default;
    assert(ummp_default.empty());
    print("ummp_default", ummp_default);

    puts("#--------------------------------------------------------#");
    puts("Construct using size");
    ani::unordered_multimap<char, int> ummp_size(24);
    assert(ummp_size.empty());
    print("ummp_size", ummp_size);
    
    puts("#--------------------------------------------------------#");
    puts("Constructed using initializer list and default Compare");
    ani::unordered_multimap<char, int> ummp_init_list {{'g', 43}, {'e', 52}, {'k', 32}, {'a', 52}, {'p', 91}, {'k', 47}, {'l', 54}, {'b', 66}, {'a', 52}};
    print("ummp_init_list", ummp_init_list);

    puts("#--------------------------------------------------------#");
    puts("Constructed using iterator range");
    ani::unordered_multimap<char, int> ummp_iter_range(++ummp_init_list.begin(), --ummp_init_list.end());
    print("ummp_iter_range", ummp_iter_range);

    puts("#--------------------------------------------------------#");
    puts("Copy Constructed");
    ani::unordered_multimap<char, int> ummp_copy(ummp_init_list);
    print("ummp_copy", ummp_copy);
    
    puts("#--------------------------------------------------------#");
    puts("Copy Assigned");
    ani::unordered_multimap<char, int> ummp_copy_assign = ummp_copy;
    print("ummp_copy_assign", ummp_copy_assign);

    ummp_copy_assign = ummp_init_list;
    print("ummp_copy_assign", ummp_copy_assign);
    
    puts("#--------------------------------------------------------#");
    puts("Move Constructed");
    ani::unordered_multimap<char, int> ummp_move(std::move(ummp_init_list));
    assert(ummp_init_list.empty());
    print("ummp_move", ummp_move);
    print("ummp_init_list", ummp_init_list);

    puts("#--------------------------------------------------------#");
    puts("Move Assigned");
    ani::unordered_multimap<char, int> ummp_move_assign = std::move(ummp_copy);
    assert(ummp_copy.empty());
    print("ummp_move_assign", ummp_move_assign);
    print("ummp_copy", ummp_copy);

    ummp_move_assign = std::move(ummp_iter_range);
    print("ummp_move_assign", ummp_move_assign);
    print("ummp_iter_range", ummp_iter_range);
    
    puts("#--------------------------------------------------------#");
    puts("Initializer list assigned");
    ani::unordered_multimap<char, int> ummp_init_list_assign = {{'g', 43}, {'e', 52}, {'k', 32}, {'a', 52}, {'p', 91}, {'k', 47}, {'l', 54}, {'b', 66}, {'a', 52}};
    print("ummp_init_list_assign", ummp_init_list_assign);
    ummp_init_list_assign = {{'t', 54}, {'t', 87}, {'m', 35}, {'h', 45}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("ummp_init_list_assign", ummp_init_list_assign);
    
    puts("#--------------------------------------------------------#\n");
}

void test_traverse(){
    ani::unordered_multimap<char, int> ummp {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    puts("#--------------------------------------------------------#");
    puts("Traverse using iterator");
    for(ani::unordered_multimap<char, int>::iterator it = ummp.begin(); it != ummp.end(); ++it)
        std::cout << "{" << it->first << "-" << it->second << "} ";
    std::cout << std::endl;

    puts("Traverse using const_iterator");
    for(ani::unordered_multimap<char, int>::const_iterator it = ummp.cbegin(); it != ummp.cend(); ++it)
        std::cout << "{" << it->first << "-" << it->second << "} ";
    std::cout << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_modifiers(){
    puts("#--------------------------------------------------------#");
    ani::unordered_multimap<char, int> ummp_1 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("ummp_1", ummp_1);
    ummp_1.insert({'j', 47});
    print("ummp_1", ummp_1);

    puts("#--------------------------------------------------------#");
    ani::unordered_multimap<char, int> ummp_3;
    ummp_3.insert(++ummp_1.begin(), --ummp_1.end());
    print("ummp_3", ummp_3);
    
    puts("#--------------------------------------------------------#");
    ani::unordered_multimap<char, int> ummp_4;
    ummp_4.insert({{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}});
    print("ummp_4", ummp_4);
    
    puts("#--------------------------------------------------------#");
    ani::unordered_multimap<char, int> ummp_5 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("ummp_5", ummp_5);
    ummp_5.erase(ummp_5.begin());
    print("ummp_5", ummp_5);
    ummp_5.erase(--ummp_5.end());
    print("ummp_5", ummp_5);

    ummp_5.erase('z');
    print("ummp_5", ummp_5);
    
    puts("#--------------------------------------------------------#");
    ani::unordered_multimap<char, int> ummp_6 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("ummp_6", ummp_6);
    ummp_6.erase(++ummp_6.begin(), --ummp_6.end());
    print("ummp_6", ummp_6);
    
    puts("#--------------------------------------------------------#");
    ani::unordered_multimap<char, int> ummp_7 {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};
    print("ummp_6", ummp_6);
    print("ummp_7", ummp_7);
    ummp_7.swap(ummp_6);
    print("ummp_6", ummp_6);
    print("ummp_7", ummp_7);

    puts("#--------------------------------------------------------#\n");
}

void test_lookup(){
    puts("#--------------------------------------------------------#");
    ani::unordered_multimap<char, int> ummp {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};
    std::cout << "count('s') : " << ummp.count('s') << std::endl;
    std::cout << "count('z') : " << ummp.count('z') << std::endl;
    
    auto it = ummp.find('k');
    if(it != ummp.end())
        std::cout << "find('k') != end() : " << (it != ummp.end()) << " : {" << it->first << "-" << it->second << "}" << std::endl;

    it = ummp.find('x');
    if(it == ummp.end())
        std::cout << "find('x') == end() : " << (it == ummp.end()) << std::endl;

    std::cout << "contains('u') : " << ummp.contains('u') << std::endl;
    std::cout << "contains('d') : " << ummp.contains('d') << std::endl;
    puts("#--------------------------------------------------------#\n");
}

void test_bucket_interface(){
    ani::unordered_multimap<char, int> ummp {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};

    puts("#--------------------------------------------------------#");
    for(ani::unordered_multimap<char, int>::iterator iter = ummp.begin(); iter != ummp.end(); ++iter)
        std::cout << "(" << iter->first << ", " << iter->second << ") ";
    std::cout << std::endl;

    for(int i = 0; i < ummp.bucket_count(); ++i){
        std::cout << "bucket_size(" << i << ") : " << ummp.bucket_size(i) << " : ";
        for(ani::unordered_multimap<char, int>::local_iterator l_it = ummp.begin(i); l_it != ummp.end(i); ++l_it)
            std::cout << "(" << l_it->first << ", " << l_it->second << ") ";;
        std::cout << std::endl;
    }

    puts("#--------------------------------------------------------#\n");
}

void test_hash_policy(){
    ani::unordered_multimap<char, int> ummp {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};

    puts("#--------------------------------------------------------#");
    std::cout << "load factor : " << ummp.load_factor() << std::endl;
    std::cout << "max_load_factor : " << ummp.max_load_factor() << std::endl;
    std::cout << "bucket count : " << ummp.bucket_count() << std::endl;

    ummp.clear();
    ummp.max_load_factor(0.5);

    ummp = {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};

    std::cout << "load factor : " << ummp.load_factor() << std::endl;
    std::cout << "max_load_factor : " << ummp.max_load_factor() << std::endl;
    std::cout << "bucket count : " << ummp.bucket_count() << std::endl;

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
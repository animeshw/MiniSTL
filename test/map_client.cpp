#include <iostream>
#include <cassert>
#include "..\include\map.hpp"

template <typename Key, typename T, typename Compare>
void print(const char* msg, const ani::map<Key, T, Compare>& mp){
    std::cout << msg << " : ";
    std::cout << "[";
    for(const ani::pair<const Key, T>& elem : mp)
        std::cout << "{" << elem.first << "-" << elem.second << "} ";
    std::cout << "] [size : " << mp.size() << "]" << std::endl;
}

void test_construct(){
    puts("#--------------------------------------------------------#");
    puts("Default construct");
    ani::map<char, int> mp_default;
    assert(mp_default.empty());
    print("mp_default", mp_default);
    
    puts("#--------------------------------------------------------#");
    puts("Constructed using initializer list and default Compare");
    ani::map<char, int> mp_init_list {{'g', 43}, {'e', 52}, {'k', 32}, {'a', 52}, {'p', 91}, {'k', 47}, {'l', 54}, {'b', 66}, {'a', 52}};
    print("mp_init_list", mp_init_list);
    
    puts("#--------------------------------------------------------#");
    puts("Constructed using initializer list and custom Compare");
    ani::map<char, int, ani::greater<char>> mp_grtr_init_list {{'g', 43}, {'e', 52}, {'k', 32}, {'a', 52}, {'p', 91}, {'k', 47}, {'l', 54}, {'b', 66}, {'a', 52}};
    print("mp_grtr_init_list", mp_grtr_init_list);

    puts("#--------------------------------------------------------#");
    puts("Constructed using iterator range");
    ani::map<char, int> mp_iter_range(++mp_init_list.begin(), --mp_init_list.end());
    print("mp_iter_range", mp_iter_range);

    puts("#--------------------------------------------------------#");
    puts("Copy Constructed");
    ani::map<char, int> mp_copy(mp_init_list);
    print("mp_copy", mp_copy);
    
    puts("#--------------------------------------------------------#");
    puts("Copy Assigned");
    ani::map<char, int> mp_copy_assign = mp_copy;
    print("mp_copy_assign", mp_copy_assign);

    mp_copy_assign = mp_init_list;
    print("mp_copy_assign", mp_copy_assign);
    
    puts("#--------------------------------------------------------#");
    puts("Move Constructed");
    ani::map<char, int> mp_move(std::move(mp_init_list));
    assert(mp_init_list.empty());
    print("mp_move", mp_move);
    print("mp_init_list", mp_init_list);

    puts("#--------------------------------------------------------#");
    puts("Move Assigned");
    ani::map<char, int> mp_move_assign = std::move(mp_copy);
    assert(mp_copy.empty());
    print("mp_move_assign", mp_move_assign);
    print("mp_copy", mp_copy);

    mp_move_assign = std::move(mp_iter_range);
    print("mp_move_assign", mp_move_assign);
    print("mp_iter_range", mp_iter_range);
    
    puts("#--------------------------------------------------------#");
    puts("Initializer list assigned");
    ani::map<char, int> mp_init_list_assign = {{'g', 43}, {'e', 52}, {'k', 32}, {'a', 52}, {'p', 91}, {'k', 47}, {'l', 54}, {'b', 66}, {'a', 52}};
    print("mp_init_list_assign", mp_init_list_assign);
    mp_init_list_assign = {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("mp_init_list_assign", mp_init_list_assign);
    
    puts("#--------------------------------------------------------#\n");
}

void test_traverse(){
    ani::map<char, int> mp {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    puts("#--------------------------------------------------------#");
    puts("Traverse using iterator");
    for(ani::map<char, int>::iterator it = mp.begin(); it != mp.end(); ++it)
        std::cout << "{" << it->first << "-" << it->second << "} ";
    std::cout << std::endl;

    puts("Traverse using const_iterator");
    for(ani::map<char, int>::const_iterator it = mp.cbegin(); it != mp.cend(); ++it)
        std::cout << "{" << it->first << "-" << it->second << "} ";
    std::cout << std::endl;

    puts("Traverse using reverse_iterator");
    for(ani::map<char, int>::reverse_iterator it = mp.rbegin(); it != mp.rend(); ++it)
        std::cout << "{" << it->first << "-" << it->second << "} ";
    std::cout << std::endl;

    puts("Traverse using const_reverse_iterator");
    for(ani::map<char, int>::const_reverse_iterator it = mp.crbegin(); it != mp.crend(); ++it)
        std::cout << "{" << it->first << "-" << it->second << "} ";
    std::cout << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_element_access(){
    ani::map<char, int> mp {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};

    puts("#--------------------------------------------------------#");
    puts("Read");
    std::cout << "at('t') : " << mp.at('t') << std::endl;
    std::cout << "operator[]('a') : " << mp['a'] << std::endl;
    
    puts("#--------------------------------------------------------#");
    puts("Write");
    std::cout << "at('t') = 86 : " << (mp.at('t') = 86) << std::endl;
    std::cout << "operator[]('a') = -29 : " << (mp['a'] = -29) << std::endl;
    
    puts("#--------------------------------------------------------#");
    puts("Access on empty map");
    ani::map<char, int> mp_empty;
    try{
        // mp_empty.at('v');
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    try{
        mp_empty['w']; // works
        print("mp_empty", mp_empty);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    puts("#--------------------------------------------------------#");
    puts("Access on out of range element");

    try{
        // mp.at('v');
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    try{
        mp['w']; // works
        print("mp", mp);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    puts("#--------------------------------------------------------#\n");
}

void test_modifiers(){
    puts("#--------------------------------------------------------#");
    ani::map<char, int> mp_1 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("mp_1", mp_1);
    mp_1.insert({'j', 47});
    print("mp_1", mp_1);

    puts("#--------------------------------------------------------#");
    ani::map<char, int, ani::greater<char>> mp_2 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("mp_2", mp_2);
    mp_2.insert({'j', 47});
    print("mp_2", mp_2);

    puts("#--------------------------------------------------------#");
    ani::map<char, int> mp_3;
    mp_3.insert(mp_2.begin(), mp_2.end());
    print("mp_3", mp_3);
    
    puts("#--------------------------------------------------------#");
    ani::map<char, int> mp_4;
    mp_4.insert({{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}});
    print("mp_4", mp_4);
    
    puts("#--------------------------------------------------------#");
    ani::map<char, int> mp_5 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("mp_5", mp_5);
    mp_5.erase(mp_5.begin());
    print("mp_5", mp_5);
    mp_5.erase(--mp_5.end());
    print("mp_5", mp_5);

    mp_5.erase('t');
    print("mp_5", mp_5);
    
    puts("#--------------------------------------------------------#");
    ani::map<char, int> mp_6 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("mp_6", mp_6);
    mp_6.erase(++mp_6.begin(), --mp_6.end());
    print("mp_6", mp_6);
    
    puts("#--------------------------------------------------------#");
    ani::map<char, int> mp_7 {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};
    print("mp_6", mp_6);
    print("mp_7", mp_7);
    mp_7.swap(mp_6);
    print("mp_6", mp_6);
    print("mp_7", mp_7);

    puts("#--------------------------------------------------------#\n");
}

void test_lookup(){
    puts("#--------------------------------------------------------#");
    ani::map<char, int> mp {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};
    std::cout << "count('s') : " << mp.count('s') << std::endl;
    std::cout << "count('z') : " << mp.count('z') << std::endl;
    
    auto it = mp.find('k');
    if(it != mp.end())
        std::cout << "find('k') != end() : " << (it != mp.end()) << " : {" << it->first << "-" << it->second << "}" << std::endl;

    it = mp.find('x');
    if(it == mp.end())
        std::cout << "find('x') == end() : " << (it == mp.end()) << std::endl;

    std::cout << "contains('u') : " << mp.contains('u') << std::endl;
    std::cout << "contains('d') : " << mp.contains('d') << std::endl;

    it = mp.lower_bound('k');
    std::cout << "lower_bound('k') : {" << it->first << "-" << it->second << "}" << std::endl;
    it = mp.upper_bound('t');
    std::cout << "upper_bound('t') : {" << it->first << "-" << it->second << "}" << std::endl;
    puts("#--------------------------------------------------------#\n");
}

void test_compare(){
    puts("#--------------------------------------------------------#");
    ani::map<char, int> mp1 {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};
    ani::map<char, int> mp2 {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};
    ani::map<char, int> mp3 {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'h', 99}};
    ani::map<char, int> mp4 {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}, {'z', 77}};

    std::cout << std::boolalpha;
    std::cout << "mp1 == mp2 : " << (mp1 == mp2) << std::endl;
    std::cout << "mp1 == mp3 : " << (mp1 == mp3) << std::endl;
    std::cout << "mp1 != mp3 : " << (mp1 != mp3) << std::endl;

    std::cout << "mp1 < mp2 : " << (mp1 < mp2) << std::endl;
    std::cout << "mp1 < mp4 : " << (mp1 < mp4) << std::endl;
    std::cout << "mp1 > mp3 : " << (mp1 > mp3) << std::endl;
    std::cout << "mp1 >= mp2 : " << (mp1 >= mp2) << std::endl;
    std::cout << "mp1 <= mp4 : " << (mp1 <= mp4) << std::endl;
    puts("#--------------------------------------------------------#\n");
}

int main(){
    test_construct();
    test_traverse();
    test_element_access();
    test_modifiers();
    test_lookup();
    test_compare();
    puts("All tests passed!");
    return 0;
}
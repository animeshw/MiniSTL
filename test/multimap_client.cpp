#include <iostream>
#include <cassert>
#include "..\include\multimap.hpp"

template <typename Key, typename T, typename Compare>
void print(const char* msg, const ani::multimap<Key, T, Compare>& mmp){
    std::cout << msg << " : ";
    std::cout << "[";
    for(const ani::pair<const Key, T>& elem : mmp)
        std::cout << "{" << elem.first << "-" << elem.second << "} ";
    std::cout << "] [size : " << mmp.size() << "]" << std::endl;
}

void test_construct(){
    puts("#--------------------------------------------------------#");
    puts("Default construct");
    ani::multimap<char, int> mmp_default;
    assert(mmp_default.empty());
    print("mmp_default", mmp_default);
    
    puts("#--------------------------------------------------------#");
    puts("Constructed using initializer list and default Compare");
    ani::multimap<char, int> mmp_init_list {{'g', 43}, {'e', 52}, {'k', 32}, {'a', 52}, {'p', 91}, {'k', 47}, {'l', 54}, {'b', 66}, {'a', 52}};
    print("mmp_init_list", mmp_init_list);
    
    puts("#--------------------------------------------------------#");
    puts("Constructed using initializer list and custom Compare");
    ani::multimap<char, int, ani::greater<char>> mmp_grtr_init_list {{'g', 43}, {'e', 52}, {'k', 32}, {'a', 52}, {'p', 91}, {'k', 47}, {'l', 54}, {'b', 66}, {'a', 52}};
    print("mmp_grtr_init_list", mmp_grtr_init_list);

    puts("#--------------------------------------------------------#");
    puts("Constructed using iterator range");
    ani::multimap<char, int> mmp_iter_range(++mmp_init_list.begin(), --mmp_init_list.end());
    print("mmp_iter_range", mmp_iter_range);

    puts("#--------------------------------------------------------#");
    puts("Copy Constructed");
    ani::multimap<char, int> mmp_copy(mmp_init_list);
    print("mmp_copy", mmp_copy);
    
    puts("#--------------------------------------------------------#");
    puts("Copy Assigned");
    ani::multimap<char, int> mmp_copy_assign = mmp_copy;
    print("mmp_copy_assign", mmp_copy_assign);

    mmp_copy_assign = mmp_init_list;
    print("mmp_copy_assign", mmp_copy_assign);
    
    puts("#--------------------------------------------------------#");
    puts("Move Constructed");
    ani::multimap<char, int> mmp_move(std::move(mmp_init_list));
    assert(mmp_init_list.empty());
    print("mmp_move", mmp_move);
    print("mmp_init_list", mmp_init_list);

    puts("#--------------------------------------------------------#");
    puts("Move Assigned");
    ani::multimap<char, int> mmp_move_assign = std::move(mmp_copy);
    assert(mmp_copy.empty());
    print("mmp_move_assign", mmp_move_assign);
    print("mmp_copy", mmp_copy);

    mmp_move_assign = std::move(mmp_iter_range);
    print("mmp_move_assign", mmp_move_assign);
    print("mmp_iter_range", mmp_iter_range);
    
    puts("#--------------------------------------------------------#");
    puts("Initializer list assigned");
    ani::multimap<char, int> mmp_init_list_assign = {{'g', 43}, {'e', 52}, {'k', 32}, {'a', 52}, {'p', 91}, {'k', 47}, {'l', 54}, {'b', 66}, {'a', 52}};
    print("mmp_init_list_assign", mmp_init_list_assign);
    mmp_init_list_assign = {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("mmp_init_list_assign", mmp_init_list_assign);
    
    puts("#--------------------------------------------------------#\n");
}

void test_traverse(){
    ani::multimap<char, int> mp {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    puts("#--------------------------------------------------------#");
    puts("Traverse using iterator");
    for(ani::multimap<char, int>::iterator it = mp.begin(); it != mp.end(); ++it)
        std::cout << "{" << it->first << "-" << it->second << "} ";
    std::cout << std::endl;

    puts("Traverse using const_iterator");
    for(ani::multimap<char, int>::const_iterator it = mp.cbegin(); it != mp.cend(); ++it)
        std::cout << "{" << it->first << "-" << it->second << "} ";
    std::cout << std::endl;

    puts("Traverse using reverse_iterator");
    for(ani::multimap<char, int>::reverse_iterator it = mp.rbegin(); it != mp.rend(); ++it)
        std::cout << "{" << it->first << "-" << it->second << "} ";
    std::cout << std::endl;

    puts("Traverse using const_reverse_iterator");
    for(ani::multimap<char, int>::const_reverse_iterator it = mp.crbegin(); it != mp.crend(); ++it)
        std::cout << "{" << it->first << "-" << it->second << "} ";
    std::cout << std::endl;

    puts("#--------------------------------------------------------#\n");
}

void test_modifiers(){
    puts("#--------------------------------------------------------#");
    ani::multimap<char, int> mmp_1 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("mmp_1", mmp_1);
    mmp_1.insert({'j', 47});
    print("mmp_1", mmp_1);

    puts("#--------------------------------------------------------#");
    ani::multimap<char, int, ani::greater<char>> mmp_2 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("mmp_2", mmp_2);
    mmp_2.insert({'j', 47});
    print("mmp_2", mmp_2);

    puts("#--------------------------------------------------------#");
    ani::multimap<char, int> mmp_3;
    mmp_3.insert(mmp_2.begin(), mmp_2.end());
    print("mmp_3", mmp_3);
    
    puts("#--------------------------------------------------------#");
    ani::multimap<char, int> mmp_4;
    mmp_4.insert({{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}});
    print("mmp_4", mmp_4);
    
    puts("#--------------------------------------------------------#");
    ani::multimap<char, int> mmp_5 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("mmp_5", mmp_5);
    mmp_5.erase(mmp_5.begin());
    print("mmp_5", mmp_5);
    mmp_5.erase(--mmp_5.end());
    print("mmp_5", mmp_5);

    mmp_5.erase('t');
    print("mmp_5", mmp_5);
    
    puts("#--------------------------------------------------------#");
    ani::multimap<char, int> mmp_6 {{'t', 54}, {'t', 87}, {'m', 35}, {'q', 90}, {'z', 0}, {'a', 97}, {'k', 22}, {'o', 43}, {'z', 10}, {'r', 32}};
    print("mmp_6", mmp_6);
    mmp_6.erase(++mmp_6.begin(), --mmp_6.end());
    print("mmp_6", mmp_6);
    
    puts("#--------------------------------------------------------#");
    ani::multimap<char, int> mmp_7 {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};
    print("mmp_6", mmp_6);
    print("mmp_7", mmp_7);
    mmp_7.swap(mmp_6);
    print("mmp_6", mmp_6);
    print("mmp_7", mmp_7);

    puts("#--------------------------------------------------------#\n");
}

void test_lookup(){
    puts("#--------------------------------------------------------#");
    ani::multimap<char, int> mp {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};
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
    ani::multimap<char, int> mp1 {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};
    ani::multimap<char, int> mp2 {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}};
    ani::multimap<char, int> mp3 {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'h', 99}};
    ani::multimap<char, int> mp4 {{'F', 58}, {'k', 15}, {'s', 40}, {'K', 31}, {'F', 42}, {'u', 78}, {'i', 84}, {'s', 65}, {'l', 45}, {'h', 99}, {'z', 77}};

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
    test_modifiers();
    test_lookup();
    test_compare();
    puts("All tests passed!");
    return 0;
}
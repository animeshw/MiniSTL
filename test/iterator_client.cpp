#include <iostream>
#include "..\include\vector.hpp"
#include "..\include\list.hpp"
#include "..\include\forward_list.hpp"

void test_advance(){
    puts("Test : advance with positive count");
    puts("#------------------------------------#");
    ani::vector<int> i_vec {1, 2, 3, 4, 5, 6, 7, 8};
    ani::list<int> i_list {1, 2, 3, 4, 5, 6, 7, 8};
    ani::forward_list<int> i_frwd_list {1, 2, 3, 4, 5, 6, 7, 8};
    
    puts("Vector Iterator");
    ani::vector<int>::iterator v_it = i_vec.begin();
    std::cout << "*v_it : " << *v_it << std::endl;
    ani::advance(v_it, 4);
    std::cout << "*v_it : " << *v_it << std::endl;

    puts("Vector Reverse Iterator");
    ani::vector<int>::reverse_iterator v_r_it = i_vec.rbegin();
    std::cout << "*v_r_it : " << *v_r_it << std::endl;
    ani::advance(v_r_it, 4);
    std::cout << "*v_r_it : " << *v_r_it << std::endl;
    
    puts("#------------------------------------#");
    puts("List Iterator");
    ani::list<int>::iterator l_it = i_list.begin();
    std::cout << "*l_it : " << *l_it << std::endl;
    ani::advance(l_it, 4);
    std::cout << "*l_it : " << *l_it << std::endl;

    puts("List Reverse Iterator");
    ani::list<int>::reverse_iterator l_r_it = i_list.rbegin();
    std::cout << "*l_r_it : " << *l_r_it << std::endl;
    ani::advance(l_r_it, 4);
    std::cout << "*l_r_it : " << *l_r_it << std::endl;

    puts("#------------------------------------#");
    puts("Forward List");
    ani::forward_list<int>::iterator fl_it = i_frwd_list.begin();
    std::cout << "*fl_it : " << *fl_it << std::endl;
    ani::advance(fl_it, 4);
    std::cout << "*fl_it : " << *fl_it << std::endl;
    puts("#------------------------------------#\n");


    puts("Test : advance with negative count");
    puts("#------------------------------------#");
    puts("Vector Iterator");
    v_it = --i_vec.end();
    std::cout << "*v_it : " << *v_it << std::endl;
    ani::advance(v_it, -3);
    std::cout << "*v_it : " << *v_it << std::endl;

    puts("Vector Reverse Iterator");
    v_r_it = --i_vec.rend();
    std::cout << "*v_r_it : " << *v_r_it << std::endl;
    ani::advance(v_r_it, -5);
    std::cout << "*v_r_it : " << *v_r_it << std::endl;

    puts("#------------------------------------#");
    puts("List Iterator");
    l_it = --i_list.end();
    std::cout << "*l_it : " << *l_it << std::endl;
    ani::advance(l_it, -3);
    std::cout << "*l_it : " << *l_it << std::endl;

    puts("List Reverse Iterator");
    l_r_it = --i_list.rend();
    std::cout << "*l_r_it : " << *l_r_it << std::endl;
    ani::advance(l_r_it, -5);
    std::cout << "*l_r_it : " << *l_r_it << std::endl;
    puts("#------------------------------------#\n");
}

void test_distance(){
    puts("Test : distance");
    puts("#------------------------------------#");
    ani::vector<int> i_vec {1, 2, 3, 4, 5, 6, 7, 8};
    ani::list<int> i_list {1, 2, 3, 4, 5, 6, 7, 8};
    ani::forward_list<int> i_frwd_list {1, 2, 3, 4, 5, 6, 7, 8};

    puts("Vector");
    std::cout << "distance(i_vec.begin(), i_vec.end()) : " << ani::distance(i_vec.begin(), i_vec.end()) << std::endl;
    std::cout << "distance(i_vec.rbegin(), i_vec.rend()) : " << ani::distance(i_vec.rbegin(), i_vec.rend()) << std::endl;
    
    puts("#------------------------------------#");
    puts("List");
    std::cout << "distance(i_list.begin(), i_list.end()) : " << ani::distance(i_list.begin(), i_list.end()) << std::endl;
    std::cout << "distance(i_list.rbegin(), i_list.rend()) : " << ani::distance(i_list.rbegin(), i_list.rend()) << std::endl;

    puts("#------------------------------------#");
    puts("Forward List");
    std::cout << "distance(i_frwd_list.begin(), i_frwd_list.end()) : " << ani::distance(i_frwd_list.begin(), i_frwd_list.end()) << std::endl;
    puts("#------------------------------------#\n");
}

void test_next_and_prev(){
    puts("Test : Next and Prev");
    puts("#------------------------------------#");
    ani::vector<int> i_vec {1, 2, 3, 4, 5, 6, 7, 8};
    ani::list<int> i_list {1, 2, 3, 4, 5, 6, 7, 8};
    ani::forward_list<int> i_frwd_list {1, 2, 3, 4, 5, 6, 7, 8};

    puts("Vector");
    std::cout << "*(ani::next(i_vec.begin())) : " << *(ani::next(i_vec.begin())) << std::endl;
    std::cout << "*(ani::prev(i_vec.end())) : " << *(ani::prev(i_vec.end())) << std::endl;

    std::cout << "*(ani::next(i_vec.rbegin())) : " << *(ani::next(i_vec.rbegin())) << std::endl;
    std::cout << "*(ani::prev(i_vec.rend())) : " << *(ani::prev(i_vec.rend())) << std::endl;
    
    puts("#------------------------------------#");
    puts("List");
    std::cout << "*(ani::next(i_list.begin())) : " << *(ani::next(i_list.begin())) << std::endl;
    std::cout << "*(ani::prev(i_list.end())) : " << *(ani::prev(i_list.end())) << std::endl;

    std::cout << "*(ani::next(i_list.rbegin())) : " << *(ani::next(i_list.rbegin())) << std::endl;
    std::cout << "*(ani::prev(i_list.rend())) : " << *(ani::prev(i_list.rend())) << std::endl;

    puts("#------------------------------------#");
    puts("Forward List");
    std::cout << "*(ani::next(i_frwd_list.begin())) : " << *(ani::next(i_frwd_list.begin())) << std::endl;
    puts("#------------------------------------#\n");
}

int main(){
    test_advance();
    test_distance();
    test_next_and_prev();
    puts("All tests passed!");
    return 0;
}

#ifndef _DCDS_HPP
#define _DCDS_HPP

#include <iostream>
#include "..\include\vector.hpp"
#include "dcds_exceptions.hpp"

namespace ani{
    class disjoint_set{
        private:
            friend class dcds;
        private:
            vector<int> set;
            int representative_element;

        public:
            disjoint_set(int r_element = 0) : representative_element(r_element){
                set.push_back(r_element);
            }

            void push_back(int data) { set.push_back(data); }

            size_t size() const { return set.size(); }

            bool find(int data) const{
                for(vector<int>::const_iterator citer = set.begin(); citer != set.end(); ++citer){
                    if(*citer == data)
                        return true;
                }
                return false;
            }

            int get_representative_element() const { return representative_element; }

            bool operator==(const disjoint_set& other){ return representative_element == other.representative_element; }
            
            bool operator!=(const disjoint_set& other){ return representative_element != other.representative_element; }
    };

    class dcds{
        private:
            vector<disjoint_set> vec_sets;

        public:
            void push_back(const disjoint_set& set){
                for(vector<disjoint_set>::iterator iter = vec_sets.begin(); iter != vec_sets.end(); ++iter){
                    if(iter->find(set.get_representative_element()))
                        throw dcds_representative_exists();
                }
                vec_sets.push_back(set);
            }

            void union_set(int r_data_1, int r_data_2){
                vector<disjoint_set>::iterator set1_iter;
                vector<disjoint_set>::iterator set2_iter;
                
                for(vector<disjoint_set>::iterator iter = vec_sets.begin(); iter != vec_sets.end(); ++iter){
                    if(iter->get_representative_element() == r_data_1)
                        set1_iter = iter;
                    if(iter->get_representative_element() == r_data_2)
                        set2_iter = iter;
                }

                if(set1_iter == vec_sets.end() || set2_iter == vec_sets.end())
                    throw dcds_representative_not_found();
                
                for(vector<int>::iterator set_iter = set2_iter->set.begin(); set_iter != set2_iter->set.end(); ++set_iter)
                    set1_iter->push_back(*set_iter);
                
                vec_sets.erase(set2_iter);
            }

            const disjoint_set& find_set(int data) const{
                vector<disjoint_set>::const_iterator iter;
                for(iter = vec_sets.begin(); iter != vec_sets.end(); ++iter){
                    if(iter->find(data))
                        break;
                }
                if(iter == vec_sets.end())
                    throw dcds_representative_not_found();
                return *iter;
            }

            void show() const{
                for(vector<disjoint_set>::const_iterator iter = vec_sets.begin(); iter != vec_sets.end(); ++iter){
                    std::cout << "[SET]\t->\t[" << iter->get_representative_element() << "]\t";
                    for(vector<int>::const_iterator set_iter = iter->set.begin(); set_iter != iter->set.end(); ++set_iter)
                        std::cout << "[" << *set_iter << "]";
                    std::cout << std::endl;
                }
            }
    };
};

#endif // _DCDS_HPP
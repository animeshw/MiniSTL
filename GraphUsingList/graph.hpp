#ifndef _GRAPH_HPP
#define _GRAPH_HPP

// Connected Undirected Positive Weighted Graph

#include <iostream>
#include <cmath>
#include "..\include\list.hpp"
#include "..\include\stack.hpp"
#include "..\include\queue.hpp"
#include "..\include\priority_queue.hpp"
#include "dcds.hpp"
#include "graph_exceptions.hpp"

namespace ani{
    enum color{ WHITE, GRAY };

    class edge{
        private:
            int start_id;
            int end_id;
            double weight;
        
        public:
            edge(int s_id = -1, int e_id = -1, double _w = INFINITY) : start_id(s_id), end_id(e_id), weight(_w){ }

            int get_start_id() const { return start_id; }

            int get_end_id() const { return end_id; }

            double get_weight() const { return weight; }

            bool operator>(const edge& right) const{ return get_weight() > right.get_weight(); }
    };

    class neighbor{
        private:
            friend class graph;
        private:
            int id;
            double weight;
            mutable color col;

        public:
            neighbor(int _d = -1, double _w = 0.0, color _c = WHITE) : id(_d), weight(_w), col(_c){ }

            const int get_id() const{ return id; }

            const double get_weight() const{ return weight; }

            const color get_color() const{ return col; }
    };

    bool operator==(const neighbor& left, const neighbor& right){ return left.get_id() == right.get_id(); }
    bool operator!=(const neighbor& left, const neighbor& right){ return left.get_id() != right.get_id(); }

    class vertex{
        private:
            friend class graph;
        private:
            int id;
            list<neighbor> neighbors;
            mutable color col;
            mutable double priority_field;
            mutable int pred_id;

        public:
            vertex(int _id = -1, color _col = WHITE, double _p = INFINITY, int _pred = -1) : id(_id), col(_col), priority_field(_p), pred_id(_pred){ }

            const int& get_id() const{ return id; }

            const color& get_color() const{ return col; }

            const double& get_priority_field() const{ return priority_field; }

            const list<neighbor>& get_neighbors() const{ return neighbors; }

            bool operator==(const vertex& right) const{ return get_id() == right.get_id(); }

            bool operator>(const vertex& right) const{ return get_priority_field() > right.get_priority_field(); }
    };

    class vertex_comparator{
        public:
            bool operator()(const vertex* v1, const vertex* v2) const { return v1->get_priority_field() < v2->get_priority_field(); }
    };

    class graph{
        private:
            size_t nr_vertices;
            size_t nr_edges;
            list<vertex> vertices;

        public:
            graph() : nr_vertices(0), nr_edges(0){ }

            void add_vertex(int vertex){
                if(find(vertices.begin(), vertices.end(), vertex) != vertices.end())
                    throw graph_vertex_exists();
                vertices.push_back(vertex);
                ++nr_vertices;
            }

            void add_edge(int start_vertex, int end_vertex, double weight = INFINITY){
                list<vertex>::iterator start_iter;
                list<vertex>::iterator end_iter;

                for(start_iter = vertices.begin(); start_iter != vertices.end(); ++start_iter){
                    if(*start_iter == start_vertex)
                        break;                        
                }
                if(start_iter == vertices.end())
                    throw graph_vertex_invalid();

                for(end_iter = vertices.begin(); end_iter != vertices.end(); ++end_iter){
                    if(*end_iter == end_vertex)
                        break;                        
                }
                if(end_iter == vertices.end())
                    throw graph_vertex_invalid();

                if(find((*start_iter).get_neighbors().begin(), (*start_iter).get_neighbors().end(), end_vertex) != (*start_iter).get_neighbors().end() && 
                    find((*end_iter).get_neighbors().begin(), (*end_iter).get_neighbors().end(), start_vertex) != (*end_iter).get_neighbors().end())
                    throw graph_edge_exists();

                if(find((*start_iter).get_neighbors().begin(), (*start_iter).get_neighbors().end(), end_vertex) != (*start_iter).get_neighbors().end() ^ 
                    find((*end_iter).get_neighbors().begin(), (*end_iter).get_neighbors().end(), start_vertex) != (*end_iter).get_neighbors().end())
                    throw graph_corrupted();

                (*start_iter).neighbors.push_back(neighbor(end_vertex, weight));
                (*end_iter).neighbors.push_back(neighbor(start_vertex, weight));

                ++nr_edges;
            }

            void remove_vertex(int del_vertex){
                list<vertex>::const_iterator del_iter;
                list<vertex>::iterator complimentry_vert_iter;
                list<neighbor>::const_iterator nbr_iter;

                for(del_iter = vertices.cbegin(); del_iter != vertices.cend(); ++del_iter){
                    if((*del_iter).get_id() == del_vertex)
                        break;                        
                }
                if(del_iter == vertices.cend())
                    throw graph_vertex_invalid();

                for(nbr_iter = (*del_iter).get_neighbors().begin(); nbr_iter != (*del_iter).get_neighbors().end(); ++nbr_iter){
                    for(complimentry_vert_iter = vertices.begin(); complimentry_vert_iter != vertices.end(); ++complimentry_vert_iter){
                        if((*complimentry_vert_iter).get_id() == (*nbr_iter).get_id())
                            break;                        
                    }
                    if(complimentry_vert_iter == vertices.end())
                        throw graph_corrupted();

                    (*complimentry_vert_iter).neighbors.remove(del_vertex);
                    --nr_edges;
                }
                vertices.erase(del_iter);
                --nr_vertices;
            }

            void remove_edge(int start_vertex, int end_vertex){
                list<vertex>::iterator start_iter;
                list<vertex>::iterator end_iter;

                for(start_iter = vertices.begin(); start_iter != vertices.end(); ++start_iter){
                    if((*start_iter).get_id() == start_vertex)
                        break;                        
                }
                if(start_iter == vertices.end())
                    throw graph_vertex_invalid();

                for(end_iter = vertices.begin(); end_iter != vertices.end(); ++end_iter){
                    if((*end_iter).get_id() == end_vertex)
                        break;                        
                }
                if(end_iter == vertices.end())
                    throw graph_vertex_invalid();

                (*start_iter).neighbors.remove(end_vertex);
                (*end_iter).neighbors.remove(start_vertex);
                --nr_edges;
            }
    
            void print(const char* msg) const{
                if(msg)
                    std::cout << msg << std::endl;
                
                std::cout << "|V| : " << nr_vertices << ", |E| : " << nr_edges << std::endl;
                
                for(list<vertex>::const_iterator vert_iter = vertices.begin(); vert_iter != vertices.end(); ++vert_iter){
                    std::cout << "[" << (*vert_iter).get_id() << "]\t->\t";
                    for(list<neighbor>::const_iterator nbr_iter = (*vert_iter).get_neighbors().begin(); nbr_iter != (*vert_iter).get_neighbors().end(); ++nbr_iter)
                        std::cout << "[" << (*nbr_iter).get_id() << "]<->";
                    std::cout << "[END]" << std::endl;
                }
            }

            void dfs(int start_vertex) const{
                _reset();
                std::cout << "DFS Traversal from vertex : " << start_vertex << std::endl;

                std::cout << "[START]<->";
                for(list<vertex>::const_iterator citer = vertices.begin(); citer != vertices.end(); ++citer){
                    if((*citer).get_id() == start_vertex){
                        _dfs(*citer);
                        break;
                    }
                }
                std::cout << "[END]" << std::endl;
            }

            void bfs(int start_vertex) const{
                _reset();

                std::cout << "BFS Traversal from vertex : " << start_vertex << std::endl;

                std::cout << "[START]<->";
                for(list<vertex>::const_iterator citer = vertices.begin(); citer != vertices.end(); ++citer){
                    if((*citer).get_id() == start_vertex){
                        _bfs(*citer);
                        break;
                    }
                }
                std::cout << "[END]" << std::endl;
            }

            void dijkstra(int start_vertex) const {
                list<vertex>::const_iterator start_citer;
                priority_queue<vertex, vector<vertex>, greater<vertex>> pq_vertices;
                double weight;

                for(list<vertex>::const_iterator vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                    if((*vert_citer).get_id() == start_vertex){
                        start_citer = vert_citer;
                        (*vert_citer).priority_field = 0.0;
                    }
                    else
                        (*vert_citer).priority_field = INFINITY;
                    (*vert_citer).pred_id = -1;
                }

                pq_vertices.push(*start_citer);

                while(!pq_vertices.empty()){
                    vertex min_vert = pq_vertices.top();
                    pq_vertices.pop();
                    for(list<neighbor>::const_iterator nbr_citer = min_vert.get_neighbors().begin(); nbr_citer != min_vert.get_neighbors().end(); ++nbr_citer){
                        list<vertex>::const_iterator vert_citer;
                        for(vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                            if((*vert_citer).get_id() == (*nbr_citer).get_id())
                                break;
                        }
                        if(vert_citer == vertices.end())
                            throw graph_corrupted();
                        weight = (*nbr_citer).get_weight();
                        
                        if((*vert_citer).get_priority_field() > min_vert.get_priority_field() + weight){                          
                            (*vert_citer).priority_field = min_vert.get_priority_field() + weight;
                            (*vert_citer).pred_id = min_vert.get_id();
                            pq_vertices.push(*vert_citer);
                        }
                    }
                }

                std::cout << "Dijkstra : Shortest Path : Source Vertex : " << start_vertex << std::endl;
                for(list<vertex>::const_iterator vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer)
                    print_shortest_path(*vert_citer);
            }

            void bellman_ford(int start_vertex) const{
                for(list<vertex>::const_iterator vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                    if((*vert_citer).get_id() == start_vertex)
                        (*vert_citer).priority_field = 0.0;
                    else
                        (*vert_citer).priority_field = INFINITY;
                    (*vert_citer).pred_id = -1;
                }

                for(size_t i = 1; i < nr_vertices; ++i){
                    for(list<vertex>::const_iterator vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                        for(list<neighbor>::const_iterator nbr_citer = (*vert_citer).get_neighbors().begin(); nbr_citer != (*vert_citer).get_neighbors().end(); ++nbr_citer){
                            for(list<vertex>::const_iterator vert_citer_1 = vertices.begin(); vert_citer_1 != vertices.end(); ++vert_citer_1){
                                if((*vert_citer_1).get_id() == (*nbr_citer).get_id()){
                                    if((*vert_citer_1).get_priority_field() > (*vert_citer).get_priority_field() + (*nbr_citer).get_weight()){
                                        (*vert_citer_1).priority_field = (*vert_citer).get_priority_field() + (*nbr_citer).get_weight();
                                        (*vert_citer_1).pred_id = (*vert_citer).get_id();
                                    }
                                }
                            }
                        }
                    }
                }

                for(list<vertex>::const_iterator vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                    for(list<neighbor>::const_iterator nbr_citer = (*vert_citer).get_neighbors().begin(); nbr_citer != (*vert_citer).get_neighbors().end(); ++nbr_citer){
                        for(list<vertex>::const_iterator vert_citer_1 = vertices.begin(); vert_citer_1 != vertices.end(); ++vert_citer_1){
                            if((*vert_citer_1).get_id() == (*nbr_citer).get_id()){
                                if((*vert_citer_1).get_priority_field() > (*vert_citer).get_priority_field() + (*nbr_citer).get_weight()){
                                    throw graph_negative_cycle();
                                }
                            }
                        }
                    }
                }

                std::cout << "Bellman-Ford : Shortest Path : Source Vertex : " << start_vertex << std::endl;
                for(list<vertex>::const_iterator vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer)
                    print_shortest_path(*vert_citer);
            }

            void prim(int start_vertex) const{
                list<vertex>::const_iterator start_citer;
                list<vertex>::const_iterator min_vert_citer;
                priority_queue<vertex, vector<vertex>, greater<vertex>> pq_vertices;
                double weight;

                for(list<vertex>::const_iterator vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                    if((*vert_citer).get_id() == start_vertex){
                        start_citer = vert_citer;
                        (*vert_citer).priority_field = 0.0;
                    }
                    else
                        (*vert_citer).priority_field = INFINITY;
                    (*vert_citer).pred_id = -1;
                    (*vert_citer).col = WHITE;
                }

                pq_vertices.push(*start_citer);

                while(!pq_vertices.empty()){
                    list<vertex>::const_iterator vert_citer;
                    for(vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                        if((*vert_citer).get_id() == pq_vertices.top().get_id())
                            break;
                    }
                    min_vert_citer = vert_citer;
                    pq_vertices.pop();

                    if((*min_vert_citer).col != WHITE)
                        continue;
                    (*min_vert_citer).col = GRAY;
                    
                    for(list<neighbor>::const_iterator nbr_citer = (*min_vert_citer).get_neighbors().begin(); nbr_citer != (*min_vert_citer).get_neighbors().end(); ++nbr_citer){
                        for(vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                            if((*vert_citer).get_id() == (*nbr_citer).get_id())
                                break;
                        }
                        if(vert_citer == vertices.end())
                            throw graph_corrupted();
                        weight = (*nbr_citer).get_weight();
                        
                        if((*vert_citer).col == WHITE && weight < (*vert_citer).get_priority_field()){
                            (*vert_citer).priority_field = weight;
                            (*vert_citer).pred_id = (*min_vert_citer).get_id();
                            pq_vertices.push(*vert_citer);
                        }
                    }
                }

                weight = 0.0;
                std::cout << "Prim : Minimum spanning tree : Source Vertex : " << start_vertex << std::endl;
                std::cout << "[START]<->";
                for(list<vertex>::const_iterator citer = vertices.begin(); citer != vertices.end(); ++citer) {
                    if((*citer).pred_id != -1){
                        std::cout << "[" << (*citer).pred_id << "-" << (*citer).get_id() << "]<->";
                        weight += (*citer).get_priority_field();
                    }
                }
                std::cout << "[END] : weight : " << weight << std::endl;
            }

            void krushkal() const{
                priority_queue<edge, vector<edge>, greater<edge>> edges;
                vector<edge> edges_A;
                dcds d;
                disjoint_set u_set;
                disjoint_set v_set;
                double weight;

                for(list<vertex>::const_iterator vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                    for(list<neighbor>::const_iterator nbr_citer = (*vert_citer).get_neighbors().begin(); nbr_citer != (*vert_citer).get_neighbors().end(); ++nbr_citer){
                        (*nbr_citer).col = WHITE;
                    }
                }

                for(list<vertex>::const_iterator vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                    for(list<neighbor>::const_iterator nbr_citer = (*vert_citer).get_neighbors().begin(); nbr_citer != (*vert_citer).get_neighbors().end(); ++nbr_citer){
                        if((*nbr_citer).get_color() != GRAY){
                            (*nbr_citer).col = GRAY;
                            for(list<vertex>::const_iterator vert_citer_1 = vertices.begin(); vert_citer_1 != vertices.end(); ++vert_citer_1){
                                if((*vert_citer_1).get_id() == (*nbr_citer).get_id()){
                                    for(list<neighbor>::const_iterator nbr_citer_1 = (*vert_citer_1).get_neighbors().begin(); nbr_citer_1 != (*vert_citer_1).get_neighbors().end(); ++nbr_citer_1){
                                        if((*nbr_citer_1).get_id() == (*vert_citer).get_id())
                                            (*nbr_citer_1).col = GRAY;
                                    }
                                }
                            }
                            edges.push(edge((*vert_citer).get_id(), (*nbr_citer).get_id(), (*nbr_citer).get_weight()));
                        }
                    }
                    d.push_back((*vert_citer).get_id());
                }

                while(!edges.empty()){
                    u_set = d.find_set(edges.top().get_start_id());
                    v_set = d.find_set(edges.top().get_end_id());
                    if(u_set != v_set){
                        d.union_set(u_set.get_representative_element(), v_set.get_representative_element());
                        edges_A.push_back(edges.top());
                    }
                    edges.pop();
                }

                weight = 0.0;
                std::cout << "Krushkal : Minimum spanning tree : " << std::endl;
                std::cout << "[START]<->";
                for(vector<edge>::iterator iter = edges_A.begin(); iter != edges_A.end(); ++iter){                    
                    std::cout << "[" << (*iter).get_start_id() << "-" << (*iter).get_end_id() << "]<->";
                    weight += (*iter).get_weight();
                }
                std::cout << "[END] : weight : " << weight << std::endl;
            }

        private:
            void print_shortest_path(const vertex& vert) const{                
                list<vertex>::const_iterator citer;
                stack<vertex> st_vertices;
                int pred_id;

                std::cout << "Shortest path to " << vert.get_id() << ", [COST : " << vert.get_priority_field() << "] : ";

                pred_id = vert.pred_id;
                st_vertices.push(vert);

                while(pred_id != -1){
                    for(citer = vertices.begin(); citer != vertices.end(); ++citer){
                        if((*citer).get_id() == pred_id)
                            break;
                    }
                    if(citer == vertices.end())
                        throw graph_vertex_invalid();
                    st_vertices.push(*citer);
                    pred_id = (*citer).pred_id;
                }

                std::cout << "[START]<->";
                while(!st_vertices.empty()){
                    std::cout << "[" << st_vertices.top().get_id() << "]<->";
                    st_vertices.pop();
                }
                std::cout << "[END]" << std::endl;
            }

            void _dfs(const vertex& vert) const{
                std::cout << "[" << vert.get_id() << "]<->";
                vert.col = GRAY;
                
                for(list<neighbor>::const_iterator nbr_citer = vert.get_neighbors().begin(); nbr_citer != vert.get_neighbors().end(); ++nbr_citer){
                    for(list<vertex>::const_iterator vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                        if((*vert_citer).get_id() == (*nbr_citer).get_id() && (*vert_citer).get_color() == WHITE){
                            _dfs(*vert_citer);
                            break;
                        }
                    }
                }
            }

            void _bfs(const vertex& vert)const{
                queue<vertex> queue;

                vert.col = GRAY;
                queue.push(vert);

                while(!queue.empty()){
                    std::cout << "[" << queue.front().get_id() << "]<->";
                    for(list<neighbor>::const_iterator nbr_citer = queue.front().get_neighbors().begin(); nbr_citer != queue.front().get_neighbors().end(); ++nbr_citer){
                        for(list<vertex>::const_iterator vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                            if((*vert_citer).get_id() == (*nbr_citer).get_id() && (*vert_citer).get_color() == WHITE){
                                (*vert_citer).col = GRAY;
                                queue.push(*vert_citer);
                                break;
                            }
                        }
                    }
                    queue.pop();
                }
            }

            void _reset() const{
                for(list<vertex>::const_iterator citer = vertices.begin(); citer != vertices.end(); ++citer)
                    (*citer).col = WHITE;
            }
    };
}

#endif // _GRAPH_HPP
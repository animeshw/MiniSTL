#ifndef _GRAPH_HPP
#define _GRAPH_HPP

#include <iostream>
#include <cmath>
#include "..\include\stack.hpp"
#include "..\include\queue.hpp"
#include "..\include\priority_queue.hpp"
#include "..\include\unordered_set.hpp"

#include "dcds.hpp"
#include "graph_exceptions.hpp"

namespace ani{
    enum color_t { WHITE, GRAY };

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
            mutable color_t col;

        public:
            neighbor(int _d = -1, double _w = 0.0, color_t _c = WHITE) : id(_d), weight(_w), col(_c){ }

            const int get_id() const{ return id; }

            const double get_weight() const{ return weight; }

            const color_t get_color() const{ return col; }

            bool operator==(const neighbor& right) const{ return get_id() == right.get_id(); }
    };

    template <typename T>
    class hasher{
        public:
            std::size_t operator()(const T& obj) const{
                return hasher(obj.get_id());
            }

        private:
            std::hash<int> hasher;
    };

    class vertex{
        private:
            friend class graph;
        private:
            int id;
            unordered_set<neighbor, hasher<neighbor>> neighbors;
            mutable color_t col;
            mutable double priority_field;
            mutable int pred_id;

        public:
            vertex(int _id = -1, color_t _col = WHITE, double _p = INFINITY, int _pred = -1) : id(_id), col(_col), priority_field(_p), pred_id(_pred){ }

            const int& get_id() const{ return id; }

            const color_t& get_color() const{ return col; }

            const double& get_priority_field() const{ return priority_field; }

            const unordered_set<neighbor, hasher<neighbor>>& get_neighbors() const{ return neighbors; }

            bool operator==(const vertex& right) const{ return get_id() == right.get_id(); }
    };

    class vertex_comparator{
        public:
            bool operator()(const vertex v1, const vertex v2) const { return v1.get_priority_field() > v2.get_priority_field(); }
    };

    class graph{
        private:
            size_t nr_vertices;
            size_t nr_edges;
            unordered_set<vertex, hasher<vertex>> vertices;

        public:
            graph() : nr_vertices(0), nr_edges(0){ }

            void add_vertex(int vertex){
                if(vertices.contains(vertex))
                    throw graph_vertex_exists();
                vertices.insert(vertex);
                ++nr_vertices;
            }

            void add_edge(int start_vertex, int end_vertex, double weight = INFINITY){
                unordered_set<vertex, hasher<vertex>>::const_iterator start_iter;
                unordered_set<vertex, hasher<vertex>>::const_iterator end_iter;

                start_iter = vertices.find(start_vertex);
                if(start_iter == vertices.cend())
                    throw graph_vertex_invalid();
                
                end_iter = vertices.find(end_vertex);
                if(end_iter == vertices.cend())
                    throw graph_vertex_invalid();

                if(start_iter->get_neighbors().contains(end_vertex) && end_iter->get_neighbors().contains(start_vertex))
                    throw graph_edge_exists();
                if(start_iter->get_neighbors().contains(end_vertex) ^ end_iter->get_neighbors().contains(start_vertex))
                    throw graph_corrupted();

                const_cast<vertex&>(*start_iter).neighbors.insert(neighbor(end_vertex, weight));
                const_cast<vertex&>(*end_iter).neighbors.insert(neighbor(start_vertex, weight));
                ++nr_edges;
            }

            void remove_vertex(int del_vertex){
                unordered_set<vertex, hasher<vertex>>::const_iterator del_iter;
                unordered_set<vertex, hasher<vertex>>::const_iterator complimentry_vert_iter;
                unordered_set<neighbor, hasher<neighbor>>::const_iterator nbr_iter;

                del_iter = vertices.find(del_vertex);
                if(del_iter == vertices.cend())
                    throw graph_vertex_invalid();

                for(nbr_iter = del_iter->get_neighbors().begin(); nbr_iter != del_iter->get_neighbors().end(); ++nbr_iter){
                    complimentry_vert_iter = vertices.find(nbr_iter->get_id());
                    if(complimentry_vert_iter == vertices.cend())
                        throw graph_corrupted();
                    
                    const_cast<vertex&>(*complimentry_vert_iter).neighbors.erase(neighbor(del_vertex));
                    --nr_edges;
                }
                vertices.erase(del_iter);
                --nr_vertices;
            }

            void remove_edge(int start_vertex, int end_vertex){
                unordered_set<vertex, hasher<vertex>>::const_iterator start_iter;
                unordered_set<vertex, hasher<vertex>>::const_iterator end_iter;

                start_iter = vertices.find(start_vertex);
                if(start_iter == vertices.cend())
                    throw graph_vertex_invalid();
                
                end_iter = vertices.find(end_vertex);
                if(end_iter == vertices.cend())
                    throw graph_vertex_invalid();
                
                const_cast<vertex&>(*start_iter).neighbors.erase(end_vertex);
                const_cast<vertex&>(*end_iter).neighbors.erase(start_vertex);
                --nr_edges;
            }

            void print(const char* msg) const{
                if(msg)
                    std::cout << msg << std::endl;
                
                std::cout << "|V| : " << nr_vertices << ", |E| : " << nr_edges << std::endl;
                
                unordered_set<vertex, hasher<vertex>>::const_iterator vert_iter;
                unordered_set<neighbor, hasher<neighbor>>::const_iterator nbr_iter;
                for(vert_iter = vertices.begin(); vert_iter != vertices.end(); ++vert_iter){
                    std::cout << "[" << vert_iter->get_id() << "]\t->\t";
                    for(nbr_iter = vert_iter->get_neighbors().begin(); nbr_iter != vert_iter->get_neighbors().end(); ++nbr_iter)
                        std::cout << "[" << nbr_iter->get_id() << "]<->";
                    std::cout << "[END]" << std::endl;
                }
            }

            void dfs(int start_vertex) const{
                _reset();
                std::cout << "DFS Traversal from vertex : " << start_vertex << std::endl;

                std::cout << "[START]<->";
                unordered_set<vertex, hasher<vertex>>::const_iterator citer = vertices.find(start_vertex);
                if(citer != vertices.end())
                    _dfs(*citer);
                std::cout << "[END]" << std::endl;
            }
            
            void bfs(int start_vertex) const{
                _reset();
                std::cout << "BFS Traversal from vertex : " << start_vertex << std::endl;

                std::cout << "[START]<->";
                unordered_set<vertex, hasher<vertex>>::const_iterator citer = vertices.find(start_vertex);
                if(citer != vertices.end())
                    _bfs(*citer);
                std::cout << "[END]" << std::endl;
            }

            void dijkstra(int start_vertex) const {
                unordered_set<vertex, hasher<vertex>>::const_iterator start_citer;
                priority_queue<vertex, vector<vertex>, vertex_comparator> pq_vertices;
                double weight;

                unordered_set<vertex, hasher<vertex>>::const_iterator vert_citer;
                for(vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                    if(vert_citer->get_id() == start_vertex){
                        start_citer = vert_citer;
                        vert_citer->priority_field = 0.0;
                    }
                    else
                        vert_citer->priority_field = INFINITY;
                    vert_citer->pred_id = -1;
                }

                pq_vertices.push(*start_citer);

                while(!pq_vertices.empty()){
                    vertex min_vert = pq_vertices.top();
                    pq_vertices.pop();
                    unordered_set<neighbor, hasher<neighbor>>::const_iterator nbr_citer;
                    for(nbr_citer = min_vert.get_neighbors().begin(); nbr_citer != min_vert.get_neighbors().end(); ++nbr_citer){
                        vert_citer = vertices.find(nbr_citer->get_id());
                        if(vert_citer == vertices.end())
                            throw graph_corrupted();
                        weight = nbr_citer->get_weight();
                        
                        if(vert_citer->get_priority_field() > min_vert.get_priority_field() + weight){                          
                            vert_citer->priority_field = min_vert.get_priority_field() + weight;
                            vert_citer->pred_id = min_vert.get_id();
                            pq_vertices.push(*vert_citer);
                        }
                    }
                }

                std::cout << "Dijkstra : Shortest Path : Source Vertex : " << start_vertex << std::endl;
                for(vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer)
                    print_shortest_path(*vert_citer);
            }

            void bellman_ford(int start_vertex) const{
                unordered_set<vertex, hasher<vertex>>::const_iterator vert_citer;
                for(vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                    if(vert_citer->get_id() == start_vertex)
                        vert_citer->priority_field = 0.0;
                    else
                        vert_citer->priority_field = INFINITY;
                    vert_citer->pred_id = -1;
                }

                for(size_t i = 1; i < nr_vertices; ++i){
                    for(vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                        unordered_set<neighbor, hasher<neighbor>>::const_iterator nbr_citer;
                        for(nbr_citer = vert_citer->get_neighbors().begin(); nbr_citer != vert_citer->get_neighbors().end(); ++nbr_citer){
                            unordered_set<vertex, hasher<vertex>>::const_iterator complimentry_vert_iter = vertices.find(nbr_citer->get_id());
                            if(complimentry_vert_iter != vertices.end()){
                                if(complimentry_vert_iter->get_priority_field() > vert_citer->get_priority_field() + nbr_citer->get_weight()){
                                    complimentry_vert_iter->priority_field = vert_citer->get_priority_field() + nbr_citer->get_weight();
                                    complimentry_vert_iter->pred_id = vert_citer->get_id();
                                }
                            }
                        }
                    }
                }

                for(vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                    unordered_set<neighbor, hasher<neighbor>>::const_iterator nbr_citer;
                    for(nbr_citer = vert_citer->get_neighbors().begin(); nbr_citer != vert_citer->get_neighbors().end(); ++nbr_citer){
                        unordered_set<vertex, hasher<vertex>>::const_iterator complimentry_vert_iter = vertices.find(nbr_citer->get_id());
                        if(complimentry_vert_iter != vertices.end()){
                            if(complimentry_vert_iter->get_priority_field() > vert_citer->get_priority_field() + nbr_citer->get_weight())
                                throw graph_negative_cycle();
                        }
                    }
                }

                std::cout << "Bellman-Ford : Shortest Path : Source Vertex : " << start_vertex << std::endl;
                for(vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer)
                    print_shortest_path(*vert_citer);
            }

            void prim(int start_vertex) const{
                unordered_set<vertex, hasher<vertex>>::const_iterator start_citer;
                unordered_set<vertex, hasher<vertex>>::const_iterator min_vert_citer;
                priority_queue<vertex, vector<vertex>, vertex_comparator> pq_vertices;
                double weight;

                unordered_set<vertex, hasher<vertex>>::const_iterator vert_citer;
                for(vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                    if(vert_citer->get_id() == start_vertex){
                        start_citer = vert_citer;
                        vert_citer->priority_field = 0.0;
                    }
                    else
                        vert_citer->priority_field = INFINITY;
                    vert_citer->pred_id = -1;
                    vert_citer->col = WHITE;
                }

                pq_vertices.push(*start_citer);

                while(!pq_vertices.empty()){
                    vert_citer = vertices.find(pq_vertices.top().get_id());

                    min_vert_citer = vert_citer;
                    pq_vertices.pop();

                    if(min_vert_citer->col != WHITE)
                        continue;
                    min_vert_citer->col = GRAY;
                    
                    unordered_set<neighbor, hasher<neighbor>>::const_iterator nbr_citer;
                    for(nbr_citer = min_vert_citer->get_neighbors().begin(); nbr_citer != min_vert_citer->get_neighbors().end(); ++nbr_citer){
                        vert_citer = vertices.find(nbr_citer->get_id());
                        if(vert_citer == vertices.end())
                            throw graph_corrupted();
                        weight = nbr_citer->get_weight();
                        
                        if(vert_citer->col == WHITE && weight < vert_citer->get_priority_field()){
                            vert_citer->priority_field = weight;
                            vert_citer->pred_id = min_vert_citer->get_id();
                            pq_vertices.push(*vert_citer);
                        }
                    }
                }

                weight = 0.0;
                std::cout << "Prim : Minimum spanning tree : Source Vertex : " << start_vertex << std::endl;
                std::cout << "[START]<->";
                for(vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer) {
                    if(vert_citer->pred_id != -1){
                        std::cout << "[" << vert_citer->pred_id << "-" << vert_citer->get_id() << "]<->";
                        weight += vert_citer->get_priority_field();
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

                unordered_set<vertex, hasher<vertex>>::const_iterator vert_citer;
                unordered_set<neighbor, hasher<neighbor>>::const_iterator nbr_citer;
                for(vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                    for(nbr_citer = vert_citer->get_neighbors().begin(); nbr_citer != vert_citer->get_neighbors().end(); ++nbr_citer){
                        nbr_citer->col = WHITE;
                    }
                }

                for(vert_citer = vertices.begin(); vert_citer != vertices.end(); ++vert_citer){
                    for(nbr_citer = vert_citer->get_neighbors().begin(); nbr_citer != vert_citer->get_neighbors().end(); ++nbr_citer){
                        if(nbr_citer->get_color() != GRAY){
                            nbr_citer->col = GRAY;

                            unordered_set<vertex, hasher<vertex>>::const_iterator complimentry_vert_iter = vertices.find(nbr_citer->get_id());
                            if(complimentry_vert_iter != vertices.end()){
                                unordered_set<neighbor, hasher<neighbor>>::const_iterator complimentry_nbr_iter = complimentry_vert_iter->get_neighbors().find(vert_citer->get_id());
                                if(complimentry_nbr_iter != complimentry_vert_iter->get_neighbors().end())
                                    complimentry_nbr_iter->col = GRAY;
                            }
                            edges.push(edge(vert_citer->get_id(), nbr_citer->get_id(), nbr_citer->get_weight()));
                        }
                    }
                    d.push_back(vert_citer->get_id());
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
                    std::cout << "[" << iter->get_start_id() << "-" << iter->get_end_id() << "]<->";
                    weight += iter->get_weight();
                }
                std::cout << "[END] : weight : " << weight << std::endl;
            }

        private:
            void print_shortest_path(const vertex& vert) const{
                unordered_set<vertex, hasher<vertex>>::const_iterator citer;
                stack<vertex> st_vertices;
                int pred_id;

                std::cout << "Shortest path to " << vert.get_id() << ", [COST : " << vert.get_priority_field() << "] : ";

                pred_id = vert.pred_id;
                st_vertices.push(vert);

                while(pred_id != -1){
                    citer = vertices.find(pred_id);
                    if(citer == vertices.end())
                        throw graph_vertex_invalid();
                    st_vertices.push(*citer);
                    pred_id = citer->pred_id;
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
                
                unordered_set<vertex, hasher<vertex>>::const_iterator vert_citer;
                unordered_set<neighbor, hasher<neighbor>>::const_iterator nbr_citer;
                for(nbr_citer = vert.get_neighbors().begin(); nbr_citer != vert.get_neighbors().end(); ++nbr_citer){
                    vert_citer = vertices.find(nbr_citer->get_id());
                    if(vert_citer != vertices.end() && vert_citer->get_color() == WHITE)
                        _dfs(*vert_citer);
                }
            }

            void _bfs(const vertex& vert)const{
                queue<vertex> queue;

                vert.col = GRAY;
                queue.push(vert);

                unordered_set<vertex, hasher<vertex>>::const_iterator vert_citer;
                unordered_set<neighbor, hasher<neighbor>>::const_iterator nbr_citer;

                while(!queue.empty()){
                    std::cout << "[" << queue.front().get_id() << "]<->";
                    for(nbr_citer = queue.front().get_neighbors().begin(); nbr_citer != queue.front().get_neighbors().end(); ++nbr_citer){
                        vert_citer = vertices.find(nbr_citer->get_id());
                        if(vert_citer != vertices.end() && vert_citer->get_color() == WHITE){
                            vert_citer->col = GRAY;
                            queue.push(*vert_citer);
                        }
                    }
                    queue.pop();
                }
            }

            void _reset() const{
                unordered_set<vertex, hasher<vertex>>::const_iterator citer;
                for(citer = vertices.begin(); citer != vertices.end(); ++citer)
                    citer->col = WHITE;
            }
    };
}

#endif // _GRAPH_HPP
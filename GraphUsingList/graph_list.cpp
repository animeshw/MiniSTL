#include <iostream>
#include "graph.hpp"

#define NR_INIT_VERTICES 8
#define NR_INIT_EDGES 12 

void test1(){
    ani::graph g;
    for(int i = 1; i < 7; ++i)
        g.add_vertex(i);

    int edges[][2] = { 
                        {1, 2}, {1, 6}, 
                        {2, 6}, {2, 5}, {2, 3},
                        {3, 5}, {3, 4},
                        {4, 5},
                        {5, 6}
                    };

    for(int i = 0; i < sizeof(edges) / sizeof(edges[0]); ++i)
        g.add_edge(edges[i][0], edges[i][1]);

    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    g.print("Intial graph");
    
    g.remove_edge(1, 6);
    g.remove_edge(5, 3);

    g.print("Graph after removing edges {1,6}, {5,3}");

    g.remove_vertex(2);
    g.print("Graph after removing vertex 2");

    g.add_vertex(7);

    g.add_edge(1, 7);
    g.add_edge(1, 4);
    g.add_edge(3, 7);
    g.add_edge(5, 7);

    g.print("Graph after adding vertex 7 and edges {1, 7}, {1, 4}, {3, 7}, {5, 7}");
    puts("");

    g.dfs(1);
    puts("");

    g.bfs(1);
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
}

void test2(){
    ani::graph g;
    int start_vert = 1;

    for(int i = 1; i <= NR_INIT_VERTICES; ++i)
        g.add_vertex(i);

    int edges[][3] =    {
							{1, 6, 2}, {1, 2, 1}, {2, 7, 5}, {2, 3, 2}, 
							{6, 7, 3}, {5, 7, 2}, {7, 3, 1}, {7, 8, 3}, 
							{3, 8, 3}, {5, 8, 4}, {5, 4, 2}, {3, 4, 1} 
						};

    for(int i = 0; i < NR_INIT_EDGES; ++i)
        g.add_edge(edges[i][0], edges[i][1], edges[i][2]);

    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    g.print("Intial graph : ");
    puts("");

    g.bfs(1);
    puts("");

    g.dfs(1);
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
}

void test3(){
    ani::graph g;
    int start_vert = 1;

    for(int i = 1; i <= NR_INIT_VERTICES; ++i)
        g.add_vertex(i);

    int edges[][3] =    {
							{1, 6, 2}, {1, 2, 1}, {2, 7, 5}, {2, 3, 2}, 
							{6, 7, 3}, {5, 7, 2}, {7, 3, 1}, {7, 8, 3}, 
							{3, 8, 3}, {5, 8, 4}, {5, 4, 2}, {3, 4, 1} 
						};

    for(int i = 0; i < NR_INIT_EDGES; ++i)
        g.add_edge(edges[i][0], edges[i][1], edges[i][2]);

    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    g.print("Intial graph : ");
    puts("");
	
	g.dijkstra(start_vert);
    puts("");

    g.bellman_ford(start_vert);
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
}

void test4(){
	ani::graph g;
    int start_vert = 1;

	for(int i = 1; i <= 7; ++i)
		g.add_vertex(i);
	
	int edges[][3] =    {
                            {1, 2, 2}, {2, 3, 3}, {3, 4, 2}, {4, 5, 2}, 
                            {5, 6, 4}, {6, 7, 1}, {7, 1, 4}, {3, 7, 1}, 
                            {5, 7, 2}, {4, 6, 1}
                        };

	for(int i = 0; i < 10; ++i) 
		g.add_edge(edges[i][0], edges[i][1], edges[i][2]);

    std::cout << "-------------------------------------------------------------------------------" << std::endl;
	g.print("Intial graph : ");
    puts("");
	
	g.dijkstra(start_vert);
    puts("");

    g.bellman_ford(start_vert);
    puts(""); 

    start_vert = 5;
	g.dijkstra(start_vert);
    puts("");

    g.bellman_ford(start_vert);
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
}

void test5(){
    ani::graph g;
    int start_vert = 1;

    for(int i = 1; i <= NR_INIT_VERTICES; ++i)
        g.add_vertex(i);

    int edges[][3] =    {
							{1, 6, 2}, {1, 2, 1}, {2, 7, 5}, {2, 3, 2}, 
							{6, 7, 3}, {5, 7, 2}, {7, 3, 1}, {7, 8, 3}, 
							{3, 8, 3}, {5, 8, 4}, {5, 4, 2}, {3, 4, 1} 
						};

    for(int i = 0; i < NR_INIT_EDGES; ++i)
        g.add_edge(edges[i][0], edges[i][1], edges[i][2]);
    
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    g.print("Intial graph : ");
    puts("");

	g.prim(start_vert);
    puts("");

    g.krushkal();
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
}

void test6(){
    ani::graph g;
    int start_vert = 0;

    for(int i = 0; i < 9; ++i)
        g.add_vertex(i);

    int edges[][3] =    {
							{0, 1, 4}, {0, 7, 8}, {1, 2, 8}, {1, 7, 11}, 
							{2, 3, 7}, {2, 8, 2}, {2, 5, 4}, {3, 4, 9}, 
							{3, 5, 14}, {4, 5, 10}, {5, 6, 2}, {6, 7, 1},
                            {6, 8, 6}, {7, 8, 7}
						};

    for(int i = 0; i < 14; ++i)
        g.add_edge(edges[i][0], edges[i][1], edges[i][2]);

    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    g.print("Intial graph : ");
    puts("");

	g.prim(start_vert);
    puts("");

    g.krushkal();
    puts("");

    start_vert = 5;
    g.prim(start_vert);
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
}

int main(){
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    puts("Success");
    return 0;
}
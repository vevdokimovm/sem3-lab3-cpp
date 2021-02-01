#pragma once


#include "testGraph.hpp"


void interface(){
    std::cout << "if you see this message tests done!" << std::endl;
    int amount_vertexes = 0;
    std::cout << "enter how many vertexes in your graph: ";
    std::cin >> amount_vertexes;
    if (amount_vertexes < 0)
        throw std::out_of_range(IndexOutOfRangeEx);
    std::cout << "enter adjacency matrix" << std::endl;
    // matrix smezhnosti
    int* array = new int[amount_vertexes * amount_vertexes];
    for (int i = 0; i < amount_vertexes; i++) {
        for (int j = 0; j < amount_vertexes; j++) {
            int cur;
            std::cin >> cur;
            array[i + j * amount_vertexes] = cur;
        }
        std::cout << std::endl;
    }
    Graph* my_graph = new Graph(array, amount_vertexes);
    int flag = 1;
    while (flag) {
        std::cout << "1. to find the shortest path" << std::endl;
        std::cout << "2. to check ranges from current vertex to other" << std::endl;
        std::cout << "0. to exit" << std::endl;
        std::cin >> flag;
        if (flag == 1) {
            std::cout << "enter start vertex: ";
            int start_vertex;
            std::cin >> start_vertex;
            std::cout << "enter end vertex: ";
            int end_vertex;
            std::cin >> end_vertex;
            Sequence<int>* path = my_graph->Dijkstra(start_vertex, end_vertex);
            std::cout << "path: ";
            for (int i = 0; i < path->GetLength(); i++) {
                std::cout << path->Get(i);
                if (path->Get(i) != end_vertex)
                    std::cout << " --> ";
            }
            std::cout << std::endl;
            std::cout << "path distance = " << my_graph->path_distance(path) << std::endl << std::endl;
        }
        else if (flag == 2) {
            std::cout << "enter current vertex: ";
            int start_vertex;
            std::cin >> start_vertex;
            Sequence<int>* short_dist = my_graph->Ranges(start_vertex);
            for (int i = 0; i < short_dist->GetLength(); i++) {
                std::cout << "from " << start_vertex << " to " << i << ":  " << short_dist->Get(i) << std::endl;
            }
            std::cout << std::endl;
        }
    }
}

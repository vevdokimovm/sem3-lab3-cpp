#include <iostream>

#include "Graph.hpp"

Graph::Graph(int* arr, int n) {
    graph = new ArraySequence<int>(n * n);
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            graph->Set(j + i * n, arr[j + i * n]);
            if (arr[j + i * n])
                count++;
        }
    }  // copy matrix 
    this->n = n;
}

void Graph::print_matrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << graph->Get(j + i * n) << "  ";
        }
        std::cout << std::endl;
    }
}

int Graph::min_path(Sequence<int>* short_dist, Sequence<bool>* visited_vertexes) {
    int min_index;
    int min = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (!visited_vertexes->Get(i) && (short_dist->Get(i) <= min)) {
            min = short_dist->Get(i);// from visited take minimum
            min_index = i;
        }
    }
    return min_index;
}

Sequence<int>* Graph::find_path(Sequence<int>* past_vertexes_path,
    Sequence<int>* short_dist,
    int start_vertex, int end_vertex) {
    Sequence<int>* finded_path = new ArraySequence<int>;
    int cur = end_vertex;
    finded_path->Append(cur);
    while (cur != start_vertex) {
        if (short_dist->Get(cur) == INT_MAX) {
            finded_path = new ArraySequence<int>;
            return finded_path;
        }
        cur = past_vertexes_path->Get(cur);
        finded_path->Prepend(cur);
    }
    return finded_path;
}

Sequence<int>* Graph::Dijkstra(int start_vertex, int end_vertex) {
    if (start_vertex < 0 || start_vertex >= n ||
        end_vertex < 0 || end_vertex >= n)
        throw std::out_of_range(IndexOutOfRangeEx);
    // just check edges

    Sequence<int>* short_dist = new ArraySequence<int>(n);
    Sequence<bool>* visited_vertexes = new ArraySequence<bool>(n);
    Sequence<int>* past_vertexes_path = new ArraySequence<int>(n);

    for (int i = 0; i < n; i++) {
        short_dist->Set(i, INT_MAX);
        visited_vertexes->Set(i, 0);
    }

    short_dist->Set(start_vertex, 0);

    // fill seq path past vertexes, for start it`s start_vertex
    for (int i = 0; i < n; i++) {
        past_vertexes_path->Set(i, start_vertex);
    }


    for (int i = 0; i + 1 < n; i++) {
        // cycle n - 1 times
        // i < n - 1  <=>  i + 1 < n
        // index of short branch
        int min = min_path(short_dist, visited_vertexes);
        // min`s vertexes isn`t free anymore 
        // min - index of the shortest path
        visited_vertexes->Set(min, 1);

        for (int j = 0; j < n; j++) {
            if (!visited_vertexes->Get(j) &&
                // it wasn`t visited
                (graph->Get(j + min * n)) &&
                // it isn`t zero
                (short_dist->Get(min) != INT_MAX) &&
                // if it = INT_MAX then it illogical
                (short_dist->Get(min) + graph->Get(j + min * n) < short_dist->Get(j))) {
                // if this path less than past
                // this if for fill path
                past_vertexes_path->Set(j, min);
                // this if to find distance
                short_dist->Set(j, short_dist->Get(min) + graph->Get(j + min * n));
            }
        }
    }

    return find_path(past_vertexes_path, short_dist, start_vertex, end_vertex);
}

Sequence<int>* Graph::Ranges(int start_vertex) {
    if (start_vertex < 0 || start_vertex >= n)
        throw std::out_of_range(IndexOutOfRangeEx);
    // just check edges

    Sequence<int>* short_dist = new ArraySequence<int>(n);
    Sequence<bool>* visited_vertexes = new ArraySequence<bool>(n);

    for (int i = 0; i < n; i++) {
        short_dist->Set(i, INT_MAX);
        visited_vertexes->Set(i, 0);
    }

    short_dist->Set(start_vertex, 0);


    for (int i = 0; i + 1 < n; i++) {
        // cycle n - 1 times
        // i < n - 1  <=>  i + 1 < n
        // index of short branch
        int min = min_path(short_dist, visited_vertexes);
        // min`s vertexes isn`t free anymore 
        // min - index of the shortest path
        visited_vertexes->Set(min, 1);

        for (int j = 0; j < n; j++) {
            if (!visited_vertexes->Get(j) &&
                // it wasn`t visited
                (graph->Get(j + min * n)) &&
                // it isn`t zero
                (short_dist->Get(min) != INT_MAX) &&
                // if it = INT_MAX then it illogical
                (short_dist->Get(min) + graph->Get(j + min * n) < short_dist->Get(j))) {
                // if this path less than past
                // this if to find distance
                short_dist->Set(j, short_dist->Get(min) + graph->Get(j + min * n));
            }
        }
    }
    //short_dist have all ranges to start_vertex, just return it
    return short_dist;
}

int Graph::path_distance(Sequence<int>* path) {
    if (!path->GetLength()) {
        return INT_MAX;
    }
    else if (path->GetLength() == 1) {
        return 0;
    }
    else {
        int path_length = 0;
        for (int i = 0; i + 1 < path->GetLength(); i++) {
            // i < x - 1  <=> i + 1 < x
            path_length += this->graph->Get(path->Get(i) + path->Get(i + 1) * n);
        }
        return path_length;
    }
}
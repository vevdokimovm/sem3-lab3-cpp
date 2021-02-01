cmake_minimum_required(VERSION 3.17)
project(sem3_lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(sem3_lab3 ArraySequence.hpp DynamicArray.hpp Graph.cpp Graph.hpp Interface.hpp main.cpp
               LinkedList.hpp ListSequence.hpp Sorts.hpp Sequence.hpp testGraph.hpp)
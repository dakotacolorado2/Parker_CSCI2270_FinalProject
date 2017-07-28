#include <iostream>
#include <string>
#include <vector>
#include "utility_code.cpp"

#ifndef FINAL_CODE_H
#define FINAL_CODE_H

using namespace std;


class final_project{
    public:
        graph * main = new graph(5,5,5,true);//This is a graph that holds all the city nodes

        void printGraph();//    #1     This function prints the graph and its weights                                       *THIS USES A GRAPH WITH TOWNS AS THE NODES
        void changeGraph();//   #2     This opens a menu for adjusting the graphs settings
        void findPath();//      #3     This opens a menu for implementing one of two shortest path algorithms               **THIS USES A QUEUE WITH CITYS AS THE NODES
        void runTaxi();//       #4     This runs a function that takes people on a taxi ride on the shortest possible path  **THIS USES A QUEUE WITH PEOPLE AS THE NODES
        void run();//           #5     This is the main function to run the menu

        final_project();//      #6     Constructor that builds the graph and prints staring information
        ~final_project();//     #7     Destructor that deletes the graph and exits
};

#endif

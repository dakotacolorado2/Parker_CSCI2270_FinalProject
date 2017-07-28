# Parker_CSCI2270_FinalProject
Dakota Parker
July 28, 2017

Quick Run Through Recommendation:
(If you have to grade 100 of these this might make testing mine go quicker)
Compile and run the main.cpp in g++11.  Maximize the terminal!  Enter 1 to print the graph. Enter 2 to open the graph settings menu.  Change the graph size (I recommend 4x6) or the weights range (Allowing negative weights disables most features so it if you change this feature you will need to go back and reset it).  Exit the graph settings menu.  Enter 1 to print the graph again.  Enter 3 to go into the shortest path program.  Try the Dijkstra's and then try Bellman-Ford’s.  Once back at the main menu  enter 4 to run the taxi program.  Select a number (5 takes awhile, I recommend 2 or 3) and enjoy.  Enter 5 to exit.  Done.    

Summary:
This program is designed to show basic implementation of graphs, linked lists, and queues.  It builds a graph where each node has 4 neighbors with weighted edges.  Each node is identified by its row and column location in the matrix.  The graph can be rebuilt according to user given parameters; they can change the range of the weights,  the shape of the matrix, or turn off or on negative weights.  After construction of the graph the user can run two main functions: a shortest path algorithm and a taxi service algorithm.  The shortest path algorithm takes two user given nodes on the graph and finds the shortest distance between them.  The user can choose to do this with Dijkstra’s algorithm or Bellman-Ford’s algorithm (Bellman-Ford works on negative weights).  The other function, taxi service, creates a queue of people who requested a taxi ride.  The program moves the taxi about the graph picking up and dropping of customers while taking the shortest possible path.  An animation makes for a fun taxi ride between nodes.

How To Run:
To run the program all four files saved in the same location.  Compile the main function in g++ 11 and then run it.  The main menu will be the second thing to come up after some introductory text.  In this text it states to make sure the terminal is maximized.  This is very important or else none of the print functions will properly display.  
At this point the user has 5 options: 
1.	Print Graph
2.	Edit Graph
3.	Shortest Path
4. 	Taxi Service
5.	Exit

Print Graph-This function simply prints the graph
Edit Graph-This function opens another menu that has 3 options on editing the graph.
Shortest Path-This function prompts the user to choose a path finding algorithm and to choose two points to run the algorithm on.
Taxi Service-This function asks the user for how many people it should transport then runs the graphics and transportation without further input.
Exit-Exits the program and clears the graph.	

Dependencies:
All the libraries used are from the c++ standard libraries.  These were included in order to implement sleep functions and to use cin.getline().   

System Requirements:
This was built on a linux VM and compiled in g++11.  This code has not been tested outside linux but it has no OS specific libraries so it should work on Windows or iOS.

Open Bugs:
There are some issues with providing incorrect input.  If the user is prompted for a number but enters a letter, the program crashes.
There are also some issues with the queue sorting of the Bellman-Ford algorithms when there are negative weights.


*PHASE1 
Final Project Overview:
  My project will be a program that randomly generates a undirected weighted graph with 100 nodes, each with 4 adjacent verticies.  It then will implement two (maybe three) different shortest path algorithms (Bellman Ford, Dijkstra, Floyd-Warshall) to find the shortest distance between two given points.  The algorithm will count the number of steps required to find the shortest path and will then print out the results.  In the implementation of these algorithms there will be a queue data structure. It will have options to refresh the graph, print the graph, and print the shortest path (with number of steps taken).  


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class person{
    public:
        std::string name;
        void id();

        person * behind;
        person * ahead;
        //Current location coordinates
        int loc_row;
        int loc_col;
        //Destination location coordinates
        int des_row;
        int des_col;

        bool at_desitnation;
        void check_location();

        person(int i1, int j1, int i2,int j2);
};

class taxi{
    public:
        person * first_passenger;
        int row;
        int col;
        string print[30];
        int ground[10];
        void shift_terrain();
        void end_terrain();
        void add_hills();
        void town(int,string);
        void hill(int,int);
        void reset();
        void add_taxi(string,int);
        void print_taxi(string);
        void play_animation(string,string,string,int);
        taxi();

};

class town{
    public:
        //Head to linked list of people in town
        person * mayor;
        void remove_person(string n);
        void add_person(person * n);

        //Location on 10x10 grid
        int row;
        int col;

        void id();

        //Graph Properties
        int n,e,s,w;
        town *north;
        town *east;
        town *south;
        town *west;

        //Queue Properties
        town *behind;
        town *ahead;

        //Other Properties
        bool queued;
        int distance;

        void reset();

        town(int i ,int j);
};

class graph{
    public:
        //Graph Properties
        town * root;
        bool positive_weights;
        int range;
        int number_rows;
        int number_cols;

        void generate_graph();
        int generate_graph_helper_rand();

        void print_graph();

        graph(int,int,int,bool);

        ///Shortest Path Algorithms

        void print_distance_grid();
        town * find_town(int,int);

        void bellman_ford(town *,town *);

        void dijkstra(town *, town *);
        int dijkstra2(town *, town *);
        void sort_queue(town *);
};

class final_project{
    public:
        graph * main = new graph(5,5,5,true);

        void printGraph();
        void changeGraph();
        void findPath();
        void runTaxi();
        void run();
        //void

        final_project();
};

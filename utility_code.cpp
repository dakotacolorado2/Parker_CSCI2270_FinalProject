#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <istream>
#include <unistd.h>
#ifndef UTILITY_CODE_H
#define UTILITY_CODE_H



using namespace std;


class person{//Class to hold information for people requesting a taxi
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
class taxi{//Class to hold information about the taxi and methods to print graphics
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
class town{//Class to hold information about weights for towns and location
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
class graph{//Class to hold together all the towns and provide methods for shortest path
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

///person class
void person::id(){//Prints the name of the person
    cout << name << endl;
}
void person::check_location(){//checks if the person had arrived at their destination
    if(loc_row==des_row&&loc_col==des_col)
        at_desitnation = true;
    else
        at_desitnation = false;
}
person::person(int i1, int j1, int i2,int j2){//Constructor that takes coordinates for where the person started and where they want to go
    loc_row = i1;
    loc_col = j1;
    des_col = i2;
    des_row = j2;
    check_location();
}

///taxi class
void taxi::shift_terrain(){//Shifts all the terrain in the array
    for(int i = 0;i<9;i++){
        ground[i]=ground[i+1];
    }
    if(ground[8]==0){
        ground[9] = rand() % 3;
    }
    else if(ground[8]>3){
        ground[9] = ground[8]+3-(rand()%6);
    }
    else if(ground[8]>10){
        ground[9] = ground[8]-(rand()%3);
    }
    else{
        ground[9] = ground[8]+(rand()%3);
    }
}
void taxi::end_terrain(){//Brings the terrain back down to ground level
    for(int i = 0;i<9;i++){
        ground[i]=ground[i+1];
    }
    if(ground[8]>2)
        ground[9] = ground[8]-3;
    else
        ground[9] = 0;
}
void taxi::town(int loc,string name){//Adds a town image to the string array
    int k = name.length();
    loc = loc*20;
    for(int h = 0; h <14-k;h++){//7 need 20
        name = name + " ";
    }
    print[18].replace(loc,20,"--------------------");
    for(int j = 17;j>15;j--){
        print[j].replace(loc,20,"|                  |");
    }
    print[15].replace(loc,20,"|  " + name + "  |");
    for(int j = 14;j>12;j--){
        print[j].replace(loc,20,"|                  |");
    }
    print[12].replace(loc,20,"--------------------");
}
void taxi::hill(int loc,int height){//Adds a hill image to the string array
    for(int j = 30;j<(30+height);j++){
        print[j-height].replace(loc,20,"MMMMMMMMMMMMMMMMMMMM");
    }
}
void taxi::add_hills(){//Adds all the hill images by using the hill() function and the heights given by the ground array
    for(int i = 0;i<10;i++){
        hill(20*i,ground[i]);
    }
}
void taxi::reset(){//Resets the string array to all blank space
    for(int j = 0;j<30;j++){//200 Wide
        print[j] = "                                                                                                                                                                                                        ";
    }
}
void taxi::add_taxi(string title,int n){//Adds a taxi image to the string array
    int h1  = ground[n];
    int k = title.length();
    for(int h = 0; h <12-k;h++){//7 need 20
        title = title + " ";
    }
    print[23-h1].replace(20*n,20,"  _______________   ");//15 wide
    print[24-h1].replace(20*n,20,"  |             |   ");
    print[25-h1].replace(20*n,20,"  |             |   ");
    print[26-h1].replace(20*n,20,"  | "+title+"|   ");
    print[27-h1].replace(20*n,20,"  |             |   ");
    print[28-h1].replace(20*n,20,"  |_____________|   ");
    print[29-h1].replace(20*n,20,"   00         00    ");
}
void taxi::print_taxi(string in){//Prints the entire string array line by line
    for(int h = 0;h<1000;h++){
        cout << endl;
    }
    cout << in <<endl;
    for(int i = 0;i<30;i++){
        cout << print[i] <<endl;
    }
}
void taxi::play_animation(string t1,string t2,string name ,int len){//Time evolves the landscape and prints the animation
    int c1 = 9;
    int c2 = 5;
    string in;
    for(int i = 0;i<len+20;i++){
        if(i == 0 && name == "None")
            in = "Going to pick up next passenger at " + t2 + " , " + to_string(len) +" units away";
        if(i==0 && name != "None")
            in = "Going to drop off " + name + " at " + t2 + " , " + to_string(len) +" units away";
        if(c1==5 && name == "None")
            in = "Picking up passenger now";
        if(c1==5 && name != "None")
            in = "Dropping off " + name;
        if(i<len){
            if(c2!=-1){
            add_hills();
            town(c2,t1);
            add_taxi(name,5);
            shift_terrain();
            print_taxi(in);
            usleep(500000);
            reset();
            c2--;
            }
            else{
                add_hills();
                add_taxi(name,5);
                shift_terrain();
                print_taxi(in);
                usleep(500000);
                reset();
            }
        }
        else{
            if(ground[3]!=0){
                add_hills();
                add_taxi(name,5);
                end_terrain();
                print_taxi(in);
                usleep(500000);
                reset();
            }
            else if(c1!=4){
                add_hills();
                add_taxi(name,5);
                end_terrain();
                town(c1,t2);
                print_taxi(in);
                usleep(500000);
                reset();
                c1--;
            }
            else{
                return;
            }
        }
    }

}
taxi::taxi(){//Constructor that zeros the ground height array
    reset();
    for(int i = 0;i<10;i++){
        ground[i] = 0;
    }
}

///town class
void town::remove_person(string n){//Removes a person from the city when they get on a taxi  **THIS USES A LINKED LIST WITH PEOPLE AS THE NODES
            person * temp1 = mayor;
            person * temp2 = mayor->behind;
            if(mayor==NULL){//No one is in the town
                return;
            }
            if(mayor->name == n){//The mayor is the person being removed
                delete temp1;
                mayor == temp2;
                return;
            }
            while(temp2!=NULL){
                if(temp2->name == n){
                    temp1->behind = temp2->behind;
                    delete temp2;
                    return;
                }
                temp1 =temp1->behind;
                temp2 = temp2->behind;
            }


        }
void town::add_person(person * n){//Adds a person to the city when they get off the taxi    **THIS USES A LINKED LIST WITH PEOPLE AS THE NODES
    person * temp = mayor;
    if(temp==NULL){//Empty City
        mayor = n;
        return;
    }
    while(temp->behind!=NULL){
            temp = temp->behind;
    }
    temp->behind = n;

}
void town::id(){//Prints the coordinates of the city in the graph
    cout << "(" << row << "," << col << ") ";
}
void town::reset(){//Clears any queue properties or distance properties of the town but preserves its name and people
    behind = NULL;
    queued = false;
    distance = 99;
}
town::town(int i ,int j){//Constructor that assigns the coordinates to the town
    row = i;
    col = j;
    queued = false;
    behind = NULL;
    ahead = NULL;
    distance = 99;
}

///graph class
void graph::generate_graph(){//Builds the graph given the specific properties
    town * first_in_row = NULL;
    town * town_above = NULL;
    town * town_left = NULL;
    for(int i = 0; i < number_rows;i++){//Goes through ten rows
        town * new_town = new town(i,0);
        if(i==0)
            root = new_town;
        first_in_row = new_town;
        if(town_above!=NULL)//Assigns the new towns north distance to the above towns south distance
            new_town->n = town_above->s;
        new_town->north = town_above;
        new_town->e = generate_graph_helper_rand();//Assigns a random value to the towns east distance
        if(i!=(number_rows-1))
            new_town->s = generate_graph_helper_rand();//Assigns a random value to the towns south distance
        else//If the town is at the bottom of the 10x10 grid
            new_town->s = 0;//Assign the south distance to 0
        if(town_above!=NULL)
            town_above->south = new_town;
        for(int j = 1;j<number_cols;j++){//Goes through all the columns
            town * town_right = new town(i,j);
            if(town_above!=NULL)//If the town above is not empty
                town_above = town_above->east;
            town_left = new_town;//shifts towns left
            new_town = town_right;
            if(j!=(number_cols-1))//Assigns east distance
                new_town->e = generate_graph_helper_rand();
            else//If it is on the last column
                new_town->e = 0;
            if(i!=(number_rows-1))//Assigns the south distance
                new_town->s = generate_graph_helper_rand();
            else//If it is on the last row
                new_town->s = 0;
            if(town_left!=NULL){//Assigns the west distance to the east distance of its west node
                town_left->east = new_town;
                new_town->w=town_left->e;
            }
            new_town->west = town_left;
            if(town_above!=NULL){//Assigns the north distance to the south distance of its north node
                town_above->south = new_town;
                new_town->n = town_above->s;
            }
            new_town->north = town_above;
        }
    town_above = first_in_row;
    }
}
int graph::generate_graph_helper_rand(){//Returns a random number to help assign weights to the graph
    if(positive_weights)
        return rand() % range;
    else
        return (range-(rand() % (range*2)));
}
void graph::print_graph(){//prints the graphs nodes and weights
    town * main = root;
    town * first = root;
    while(main != NULL){
        if(main->west!=NULL){
            if(main->w>-1)
                cout <<"-  "<< main->w << "  - ";
            else
                cout <<"- "<< main->w << "  - ";
        }
        main->id();
        main = main->east;
    }
    cout << endl;
    first = first->south;
    main = first;
    while (first!=NULL){
            for(int j = 0;j<number_cols;j++){
                cout  << "   |          ";
            }
            cout << endl;
            while(main != NULL){//Prints out all the north values in a row while moving east
                if(main->n>=0)
                    cout  << "   " << main->n << "          ";
                else
                    cout  << "  " << main->n << "          ";
                main = main->east;
            }
            cout << endl;
            for(int j = 0;j<number_cols;j++){
                cout  << "   |          ";
            }
            cout << endl;
            main = first;
            while(main != NULL){//prints out all the west values in a row while moving east
                if(main->west!=NULL){
                    if(main->w>-1||main->w==0)
                        cout <<"-  "<< main->w << "  - ";
                    else
                        cout <<"- "<< main->w << "  - ";
                }
                main->id();
                main = main->east;
            }
            cout << endl;
            first = first->south;
            main = first;

        }
}
graph::graph(int r, int c, int ro, bool p){//Constructs the graph given the size, weight range, and if the weights can be negative or not
    positive_weights = p;
    range = ro;
    number_cols = c;
    number_rows = r;
    generate_graph();
}
void graph::print_distance_grid(){//Prints the distance variables of all the nodes in the graph
    town * temp1 = root;
    while(temp1!=NULL){
        town * temp2 = temp1;
        while(temp1!=NULL){
                if(temp1->distance<10&&temp1->distance>-1)
                    cout << "  " << temp1->distance << "  ";
                else if(temp1->distance<-9)
                    cout << " " << temp1->distance << " ";
                else if(temp1->distance<0)
                    cout << "  " << temp1->distance << " ";
                else if(temp1->distance ==99)
                    cout << "  *  ";
                else
                    cout << "  " << temp1->distance << " ";
            temp1=temp1->east;
        }
        cout << endl;
        temp1=temp2->south;
    }
}
town * graph::find_town(int i,int j){//Returns the node with given coordinates
    town * temp = root;
    while(temp->row<i)
        temp=temp->south;
    while(temp->col<j)
        temp=temp->east;
    return temp;
}
void graph::bellman_ford(town * start, town * ending){//Runs the bellman ford shortest path algorithm with printed steps                                *THIS USES A QUEUE WITH TOWNS AS THE NODES
    town * temp1 = root;
    while(temp1!=NULL){//Clear all the distances on the grid
        town * temp2 = temp1;
        while(temp1!=NULL){
            temp1->reset();
            temp1=temp1->east;
        }
        temp1=temp2->south;
    }

    int steps = 0;
    start->distance = 0;
    start->queued = true;
    temp1 = start;
    town * head = start;
    do{
        cout << "PRESS ENTER TO EVOLVE THROUGH THE STEPS" << endl;
        char line[256];
        cin.getline(line , 256);
        for(int p = 0;p<1000;p++){
            cout << endl;
        }
        print_distance_grid();
        temp1 = head;
        cout << "Queue: ";
        while(temp1->behind!=NULL){
            temp1->id();
            temp1 =temp1->behind;
        }
        temp1->id();
        int current_len = head->distance;
        cout << endl<<"Added: ";
        if(head->north!=NULL){//If the heads north neighbor is not NULL
            if(!head->north->queued){//If the north town has not been queued
                temp1->behind = head->north;///Add the north town to the queue
                temp1->behind->ahead = temp1;
                temp1 = temp1->behind;///Moves temp1 to end of queue
                temp1->id();//prints ID
                temp1->queued=true;
            }
            steps++;
            if((current_len + head->n)<head->north->distance||head->north->distance==99){//If the distance of the north node is less than the distance to the head + the north distance
                head->north->distance = current_len + head->n;
            }
        }
        if(head->east!=NULL){//Same as above but for east
            if(!head->east->queued){
                temp1->behind = head->east;
                temp1->behind->ahead = temp1;
                temp1 = temp1->behind;
                temp1->id();
                temp1->queued=true;
            }
            steps++;
            if((current_len + head->e)<head->east->distance||head->east->distance==99){
                head->east->distance = current_len + head->e;
            }
        }
        if(head->south!=NULL){//For south
            if(!head->south->queued){
                temp1->behind = head->south;
                temp1->behind->ahead = temp1;
                temp1 = temp1->behind;
                temp1->id();
                temp1->queued=true;
            }
            steps++;
            if((current_len + head->s)<head->south->distance||head->south->distance==99){
                head->south->distance = current_len + head->s;
            }
        }
        if(head->west!=NULL){//For west
            if(!head->west->queued){
                temp1->behind = head->west;
                temp1->behind->ahead = temp1;
                temp1 = temp1->behind;
                temp1->id();
                temp1->queued=true;
            }
            steps++;
            if((current_len + head->w)<head->west->distance||head->west->distance==99){
                head->west->distance = current_len + head->w;
            }
        }
        cout << endl;
        head = head->behind;
        if(head!=NULL)
            head->ahead=NULL;
        sort_queue(head);
        cout << "Steps Taken: " << steps << endl;
    }while(head!=NULL);
    for(int p = 0;p<1000;p++){cout << endl;}
    cout << "Final Array of Distances from the Point "; start->id();
    cout << endl<< endl;
    print_distance_grid();
    cout << "Total Steps: " << steps << endl;




    cout << "The Shortest Distance from "; start->id(); cout << "to "; ending->id(); cout << " is " << ending->distance << " units."<<endl;
}
void graph::dijkstra(town * start, town * ending){//Runs the Dijkstra shortest path algorithm with printed steps                                        *THIS USES A QUEUE WITH TOWNS AS THE NODES
    town * temp1 = root;
    while(temp1!=NULL){//Clear all the distances on the grid
        town * temp2 = temp1;
        while(temp1!=NULL){
            temp1->reset();
            temp1=temp1->east;
        }
        temp1=temp2->south;
    }

    int steps = 0;
    start->distance = 0;
    start->queued = true;
    temp1 = start;
    town * head = start;
    do{
        cout << "PRESS ENTER TO EVOLVE THROUGH THE STEPS" << endl;
        char line[256];
        cin.getline(line , 256);
        for(int p = 0;p<1000;p++){
            cout << endl;
        }
        cout << "Finding distance from "; start->id(); cout << "to "; ending->id(); cout << endl;
        print_distance_grid();
        temp1 = head;
        cout << "Queue: ";
        while(temp1->behind!=NULL){
            temp1->id();
            temp1 =temp1->behind;
        }
        temp1->id();
        int current_len = head->distance;
        cout << endl<<"Added: ";
        if(head->north!=NULL){//If the heads north neighbor is not NULL
            if(!head->north->queued){//If the north town has not been queued
                temp1->behind = head->north;///Add the north town to the queue
                temp1->behind->ahead = temp1;
                temp1 = temp1->behind;///Moves temp1 to end of queue
                temp1->id();//prints ID
                temp1->queued=true;
            }
            steps++;
            if((current_len + head->n)<head->north->distance||head->north->distance==99){//If the distance of the north node is less than the distance to the head + the north distance
                head->north->distance = current_len + head->n;
            }
        }
        if(head->east!=NULL){//Same as above but for east
            if(!head->east->queued){
                temp1->behind = head->east;
                temp1->behind->ahead = temp1;
                temp1 = temp1->behind;
                temp1->id();
                temp1->queued=true;
            }
            steps++;
            if((current_len + head->e)<head->east->distance||head->east->distance==99){
                head->east->distance = current_len + head->e;
            }
        }
        if(head->south!=NULL){//For south
            if(!head->south->queued){
                temp1->behind = head->south;
                temp1->behind->ahead = temp1;
                temp1 = temp1->behind;
                temp1->id();
                temp1->queued=true;
            }
            steps++;
            if((current_len + head->s)<head->south->distance||head->south->distance==99){
                head->south->distance = current_len + head->s;
            }
        }
        if(head->west!=NULL){//For west
            if(!head->west->queued){
                temp1->behind = head->west;
                temp1->behind->ahead = temp1;
                temp1 = temp1->behind;
                temp1->id();
                temp1->queued=true;
            }
            steps++;
            if((current_len + head->w)<head->west->distance||head->west->distance==99){
                head->west->distance = current_len + head->w;
            }
        }
        cout << endl;
        if(head == ending)
            break;
        head = head->behind;
        if(head!=NULL)
            head->ahead=NULL;
        sort_queue(head);

        cout << "Steps Taken: " << steps << endl;
    }while(head!=NULL);
    for(int p = 0;p<1000;p++){cout << endl;}
    cout << "==============================" <<endl;
    cout << "DONE" <<endl;
    cout << "=============================="<< endl;
    cout << "Final Array of Distances from the Point "; start->id();
    cout << endl<< endl;
    print_distance_grid();
    cout << "Total Steps: " << steps << endl;




    cout << "The Shortest Distance from "; start->id(); cout << "to "; ending->id(); cout << " is " << ending->distance << " units."<<endl;
    cout << endl << endl << endl;
}
int graph::dijkstra2(town * start, town * ending){////Runs the bellman ford shortest path algorithm WITHOUT printed steps and returns the distance      *THIS USES A QUEUE WITH TOWNS AS THE NODES
    town * temp1 = root;
    while(temp1!=NULL){//Clear all the distances on the grid
        town * temp2 = temp1;
        while(temp1!=NULL){
            temp1->reset();
            temp1=temp1->east;
        }
        temp1=temp2->south;
    }

    int steps = 0;
    start->distance = 0;
    start->queued = true;
    temp1 = start;
    town * head = start;
    do{

        temp1 = head;
        while(temp1->behind!=NULL){
            temp1 =temp1->behind;
        }
        int current_len = head->distance;
        if(head->north!=NULL){//If the heads north neighbor is not NULL
            if(!head->north->queued){//If the north town has not been queued
                temp1->behind = head->north;///Add the north town to the queue
                temp1->behind->ahead = temp1;
                temp1 = temp1->behind;///Moves temp1 to end of queue
                temp1->queued=true;
            }
            steps++;
            if((current_len + head->n)<head->north->distance||head->north->distance==99){//If the distance of the north node is less than the distance to the head + the north distance
                head->north->distance = current_len + head->n;
            }
        }
        if(head->east!=NULL){//Same as above but for east
            if(!head->east->queued){
                temp1->behind = head->east;
                temp1->behind->ahead = temp1;
                temp1 = temp1->behind;
                temp1->queued=true;
            }
            steps++;
            if((current_len + head->e)<head->east->distance||head->east->distance==99){
                head->east->distance = current_len + head->e;
            }
        }
        if(head->south!=NULL){//For south
            if(!head->south->queued){
                temp1->behind = head->south;
                temp1->behind->ahead = temp1;
                temp1 = temp1->behind;
                temp1->queued=true;
            }
            steps++;
            if((current_len + head->s)<head->south->distance||head->south->distance==99){
                head->south->distance = current_len + head->s;
            }
        }
        if(head->west!=NULL){//For west
            if(!head->west->queued){
                temp1->behind = head->west;
                temp1->behind->ahead = temp1;
                temp1 = temp1->behind;
                temp1->queued=true;
            }
            steps++;
            if((current_len + head->w)<head->west->distance||head->west->distance==99){
                head->west->distance = current_len + head->w;
            }
        }
        if(head == ending)
            break;
        head = head->behind;
        if(head!=NULL)
            head->ahead=NULL;
        sort_queue(head);
    }while(head!=NULL);
    return ending->distance;
}
void graph::sort_queue(town * head){//Helper function to sort the queue used in the sorting algorithms
    town * h = head;
    town * temp1 = head;
    if(temp1==NULL)
        return;
    if(temp1->behind==NULL)
        return;
    temp1 = head;
    bool sorted = false;
    while(!sorted){
        sorted = true;
        temp1 = head;
        while(temp1->behind!=NULL){
            town * temp2 = temp1->behind;
            if(temp2->distance<temp1->distance){
                sorted = false;
                if(temp1 == h)
                    h = temp2;
                if(temp2->behind!=NULL)
                    temp2->behind->ahead = temp1;
                if(temp1->ahead!=NULL)
                    temp1->ahead->behind = temp2;
                temp2->ahead = temp1->ahead;
                temp1->behind = temp2->behind;
                temp1->ahead = temp2;
                temp2->behind = temp1;
            }
            else{
                temp1 = temp1->behind;
            }
        }
    }
    temp1 = head;
    cout << "Queue Node Distances:";
    while(temp1!=NULL){
        cout << temp1->distance << ", ";
        temp1 = temp1->behind;
    }
    cout <<endl;
}

#endif

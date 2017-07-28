#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <istream>
#include <unistd.h>
#include "finalproject.h"


using namespace std;

//person class
void person::id(){
    cout << name << endl;
}
void person::check_location(){
    if(loc_row==des_row&&loc_col==des_col)
        at_desitnation = true;
    else
        at_desitnation = false;
}
person::person(int i1, int j1, int i2,int j2){
    loc_row = i1;
    loc_col = j1;
    des_col = i2;
    des_row = j2;
    check_location();
}

void taxi::shift_terrain(){
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
void taxi::end_terrain(){
    for(int i = 0;i<9;i++){
        ground[i]=ground[i+1];
    }
    if(ground[8]>2)
        ground[9] = ground[8]-3;
    else
        ground[9] = 0;
}
void taxi::town(int loc,string name){
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
void taxi::hill(int loc,int height){
    for(int j = 30;j<(30+height);j++){
        print[j-height].replace(loc,20,"MMMMMMMMMMMMMMMMMMMM");
    }
}
void taxi::add_hills(){
    for(int i = 0;i<10;i++){
        hill(20*i,ground[i]);
    }
}
void taxi::reset(){
    for(int j = 0;j<30;j++){//200 Wide
        print[j] = "                                                                                                                                                                                                        ";
    }
}
void taxi::add_taxi(string title,int n){
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
void taxi::print_taxi(string in){
    for(int h = 0;h<1000;h++){
        cout << endl;
    }
    cout << in <<endl;
    for(int i = 0;i<30;i++){
        cout << print[i] <<endl;
    }
}
void taxi::play_animation(string t1,string t2,string name ,int len){
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
taxi::taxi(){
    reset();
    for(int i = 0;i<10;i++){
        ground[i] = 0;
    }
}

//town class
void town::remove_person(string n){
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
void town::add_person(person * n){
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
void town::id(){
    cout << "(" << row << "," << col << ") ";
}
void town::reset(){
    behind = NULL;
    queued = false;
    distance = 99;
}
town::town(int i ,int j){
    row = i;
    col = j;
    queued = false;
    behind = NULL;
    ahead = NULL;
    distance = 99;
}

//graph class
void graph::generate_graph(){
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
int graph::generate_graph_helper_rand(){
    if(positive_weights)
        return rand() % range;
    else
        return (range-(rand() % (range*2)));
}
void graph::print_graph(){
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
graph::graph(int r, int c, int ro, bool p){
    positive_weights = p;
    range = ro;
    number_cols = c;
    number_rows = r;
    generate_graph();
}
void graph::print_distance_grid(){
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
town * graph::find_town(int i,int j){
    town * temp = root;
    while(temp->row<i)
        temp=temp->south;
    while(temp->col<j)
        temp=temp->east;
    return temp;
}
void graph::bellman_ford(town * start, town * ending){
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
void graph::dijkstra(town * start, town * ending){
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
int graph::dijkstra2(town * start, town * ending){
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
void graph::sort_queue(town * head){
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

//final class
void final_project::printGraph(){
    main->generate_graph();
    cout <<endl;
    cout << "======================" <<endl << endl;
    cout << "Current Graph Settings" << endl;
    cout << "Negative Weights: ";
    if(main->positive_weights)
        cout << "true";
    else
        cout << "false";
    cout << endl;
    int k = 0;
    cout << "Weight Range: [0 - "<< main->range <<"]" <<endl;
    cout << "Graph Dimensions " << main->number_rows << "x" << main->number_cols << endl;
    cout << endl;
    cout << "======Generated Graph=====" << endl <<endl;
    main->print_graph();
    cout << endl;
}
void final_project::changeGraph(){
    int range = main->range;
    bool sign = main->positive_weights;
    cout << endl << endl;
    cout << "======================" <<endl << endl;
    cout << "Current Graph Settings" << endl;
    cout << "Negative Weights: ";
    if(sign)
        cout << "true";
    else
        cout << "false";
    cout << endl;
    int k = 0;
    cout << "Weight Range: [0 - "<< range <<"]" <<endl;
    cout << "Graph Dimensions " << main->number_rows << "x" << main->number_cols << endl;
    int menu_location;
    char line[256];
    while(1){
        cout << endl;
        cout << "Choose an option:"                              << endl;
        cout << "1.   Change the weight range"                   << endl;
        cout << "2.   Turn off or on negative weights"           << endl;
        cout << "3.   Change graph dimensions"                   << endl;
        cout << "4.   BACK"                                      << endl;
        cin.getline(line , 256);
        menu_location=(int(line[0])-48);
        if(menu_location==1){
            cout << "Enter weight range (0-9)" << endl;
            cin.getline(line , 256);
            main->range = stoi(line);
        }
        else if(menu_location==2){
            if(main->positive_weights ==true){
                cout << "Turning ON negative weights "<< endl;
                main->positive_weights = false;
            }
            else{
                cout << "Turning OFF negative weights "<< endl;
                main->positive_weights = true;
            }

        }
        else if(menu_location==3){
            cout << "Enter number of rows (0-9):" << endl;
            cin.getline(line , 256);
            main->number_rows = stoi(line);
            cout << "Enter number of columns (0-9):" << endl;
            cin.getline(line , 256);
            main->number_cols = stoi(line);
        }
        else if(menu_location==4)
        {
            break;
        }
        else{
            cout << "Enter a number please" << endl;
        }
        cout << endl << "Current Graph Settings" << endl;
        cout << "Negative Weights: ";
        if(sign)
            cout << "true";
        else
            cout << "false";
        cout << endl;
        int k = 0;
        cout << "Weight Range: [0-"<< main->range <<"]" <<endl;
        cout << "Graph Dimensions " << main->number_rows << "x" << main->number_cols << endl << endl;

    }
    main->generate_graph();
}
void final_project::findPath(){
    int menu_location;
    char line[256];
    int x1,x2,y1,y2;
    int jo = 0;
    bool sign = main->positive_weights;
    int range = main->range;
    cout << "==========" << endl << endl;
    while(1){
        cout << "Choose an option:"                 << endl;
        cout << "1.   Dijkstra Algorithm (positive weights)"   << endl;
        cout << "2.   Bellman-Ford Algorithm (positive or negative weights)"      << endl;
        cin.getline(line , 256);
        menu_location=(int(line[0])-48);
        if(menu_location==1){
            jo=1;
            if(!main->positive_weights){
                cout << "If you want to run the dijkstra algorithm please change the graph settings to have positive weights" << endl;
                return;
            }
            break;
        }
        else if(menu_location==2){
            jo=2;
            break;
        }
        else{
            cout << "Enter a number please" << endl;
        }
    }
    cout <<endl;
    while(1){
        cout << "Choose an option:"                 << endl;
        cout << "1.   Enter your own coordinates"   << endl;
        cout << "2.   Random coordinates"           << endl;
        cin.getline(line , 256);
        menu_location=(int(line[0])-48);
        if(menu_location==2){
            if(sign){
                x1 = rand()%range, x2 = rand()%range;
                y1 = rand()%range, y2 = rand()%range;
            }
            else{
                x1 = range/2-rand()%range, x2 = range/2-rand()%range;
                y1 = range/2-rand()%range, y2 = range/2-rand()%range;
            }
            cout << "Random coordinates generated: (" << x1<<","<<x2 << ") --> (" << y1 << "," << y2 << ")"<<endl;
            break;
        }
        else if(menu_location==1){
            while(1){
                int k = 0;
                cout << "Enter coordinates in the form 'x,y'" <<endl <<"Remember the coordinates should be in the range [0"<<"-"<< range-1 <<"]"<<endl<<endl;
                cout << "Enter the first coordinate:" << endl;
                char line2[256];
                cin.getline(line2,256);
                x1 = int(line2[0])-48;
                x2 = int(line2[2])-48;
                cout << "Enter the second coordinate:" << endl;
                cin.getline(line2,256);
                y1 = int(line2[0])-48;
                y2 = int(line2[2])-48;
                cout << "Coordinates selected: (" << x1<<","<<x2 << ") --> (" << y1 << "," << y2 << ")"<<endl;
                cout << "Is this correct? (1/0)" << endl;
                cin.getline(line2,256);
                if(line2[0]=='1'){
                    break;
                }
                else{
                    cout << endl;
                }
            }
            break;
        }
        else{
            cout << "Enter a number please" << endl;
        }
    }
    cout << "Distance from (" << x1<<","<<x2 << ") to (" << y1 << "," << y2 << ")"<<endl;
    if(jo == 1)
        main->dijkstra(main->find_town(x1,x2),main->find_town(y1,y2));
    if(jo == 2)
        main->bellman_ford(main->find_town(x1,x2),main->find_town(y1,y2));

    usleep(1000000);
}
void final_project::runTaxi(){
    if(!main->positive_weights){
        cout << "If you want to run the taxi program please change the graph settings to have positive weights" << endl;
        return;
    }
    cout << "===============" << endl;
    char line[256];
    cout << "Enter the number of people requesting a taxi (0-5):" <<endl;
    cin.getline(line , 256);
    int requests = stoi(line);
    person * first_request;
    person * last_request;
    string names[] = {"Tyrion" , "Jon Snow", "Joffrey", "Daenerys","Sansa"};
    for(int i = 0;i<requests;i++){
        int m = rand() % main->number_rows;
        int n = rand() % main->number_cols;
        int o = rand() % main->number_rows;
        while(o==n){
            o = rand() % main->number_rows;
        }
        int p = rand() % main->number_cols;
        while(p==m){
            p = rand() % main->number_rows;
        }
        town * temp = main->find_town(m,n);
        person * dude = new person(m,n,o,p);
        dude->name = names[i];
        if(i == 0){
            first_request = dude;
            last_request = dude;
        }
        else{
            last_request->behind = dude;
            dude->ahead = last_request;
            last_request = dude;
        }
    }
    cout << "====================" <<endl;
    cout << endl << "Starting the taxi "<<endl;
    person * temp = first_request;
    while(temp!=NULL){
        cout << endl;
        cout << "Taxi request from " << temp->name << endl;
        cout << "    Pick-up at (" << temp->loc_row << "," << temp->des_col << ") going to (";
        cout << temp->des_row << "," << temp->des_col << ")" << endl;
        temp = temp->behind;
    }
    usleep(5000000);
    taxi * T = new taxi;
    T->row = rand() % main->number_rows;
    T->col = rand() % main->number_cols;
    while(first_request!=NULL){
        string t1 = "("+to_string(T->row) + "," + to_string(T->col) + ")";
        string t2 = "("+to_string(first_request->loc_row) + "," + to_string(first_request->loc_col) + ")";
        int distance = main->dijkstra2(main->find_town(T->row,T->col),main->find_town(first_request->loc_row,first_request->loc_col));
        T->play_animation(t1,t2,"None",distance);
        usleep(5000000);
        T->row = first_request->loc_row;
        T->col = first_request->loc_col;
        t1 = "("+to_string(T->row) + "," + to_string(T->col) + ")";
        t2 = "("+to_string(first_request->des_row) + "," + to_string(first_request->des_col) + ")";
        distance = main->dijkstra2(main->find_town(T->row,T->col),main->find_town(first_request->des_row,first_request->des_col));
        T->play_animation(t1,t2,first_request->name,distance);
        usleep(5000000);
        T->row = first_request->des_row;
        T->col = first_request->des_col;
        first_request->loc_col =first_request->des_col;
        first_request->loc_row =first_request->des_row;
        first_request = first_request->behind;
    }



}
void final_project::run(){
///PRESENTS A MAIN MENU WITH FUNCTIONS THAT CAN BE RUN ON THE BST

    while(1){

        ///Prints menu options
        cout << "======Main Menu======"                         <<endl;
        cout << "1. Print Graph"                                <<endl;
        cout << "2. Change Graph Properties"                    <<endl;
        cout << "3. Find Shortest Path Between Points"          <<endl;
        cout << "4. Run the Taxi"                               <<endl;
        cout << "5. Quit"                                       <<endl;

        ///Takes letter input from user and converts it to and int
        int menu_location;
        char line[256];
        cin.getline(line , 256);
        menu_location=(int(line[0])-48);

        ///Selects a function based off the given input
        switch(menu_location){
            case 1:
                printGraph();
                break;
            case 2:
                changeGraph();
                break;
            case 3:
                findPath();
                break;
            case 4:
                runTaxi();
                break;
            case 5:
                cout << "Goodbye!" <<endl;
                return;
            default:
                    cout << endl << "Enter a number input please." << endl << endl;
                break;
}}}
final_project::final_project(){
    cout << "Dakota Parker" <<endl;
    cout << "July 28, 2017" <<endl;
    cout << "Welcome to my final project" <<endl;
    cout << "Please set the terminal to FULL SCREEN" << endl << endl;
    //main->print_graph();
}


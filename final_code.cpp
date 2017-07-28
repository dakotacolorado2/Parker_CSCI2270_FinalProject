#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <istream>
#include <unistd.h>
#include "final_code.hpp"
#include "utility_code.cpp"

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
final_project::~final_project(){
    cout << "Deleting Graph" <<endl;
    town * temp1 = main->root;
    town * temp2 = main->root;
    town * temp3 = main->root;
    while(temp2!=NULL){
            temp2 = temp1->south;
        while(temp1!=NULL){
            temp3 = temp1;
            temp1 = temp1->east;
            cout << "Deleting "; temp3->id(); cout <<endl;
            delete temp3;
        }
        temp1 = temp2;
    }
}

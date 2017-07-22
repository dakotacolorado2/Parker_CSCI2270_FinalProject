#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <istream>
#include <unistd.h>

using namespace std;



class node{
public:
    //Location Identity
    int row;
    int col;

    void ID(){
        cout << "(" << row << "," << col << ") ";
    }

    //Graph Properties
    int dNorth;
    int dEast;
    int dSouth;
    int dWest;
    node * north;
    node * east;
    node * south;
    node * west;

    //Queue Properties
    node * behind;

    //Bellman Ford Properties
    bool poped;
    int distance;

    void clearNode(){
        behind = NULL;
        poped = false;
        distance = -1;
    }


    node(int i,int j){
        row = i;
        col = j;
        behind = NULL;
        poped = false;
        distance = -1;
    }
};

class MAIN{
    public:
        node * root;
        node * findNode(int, int);
        void printGraph();
        MAIN();

        void findPath();

        void bellman_ford(node *,node *);
        void bellman_ford_helper(node *);
        void bellman_ford_print();
};

MAIN::MAIN(){

    node * first = NULL;
    node * up = NULL;
    node * left = NULL;
    int c =1;
    for(int i = 0;i<10;i++){
        node * current = new node(i,0);
        if(i==0)
            root = current;
        first = current;
        if(up!=NULL)//Assigns the new nodes north distance to the up nodes south distance
                current->dNorth = up->dSouth;
        current->north=up;
        current->dEast = rand() % 10;
        if(i!=9)
            current->dSouth = rand() % 10;
        else
            current->dSouth = 0;
        if(up!=NULL)
            up->south = current;
        /*if(up!=NULL)
            cout << "Node #: "<< c << " has north node (" << up->row << "," << up->col << ")" << endl;
        else{
            cout << "Node #: "<< c << " has north node NULL"<<endl;
            cout << "Node #: "<< c << " has west node NULL"<<endl;
        }
        */
        for(int j = 1;j<10;j++){
            c++;
            node * right = new node(i,j);
            if(up!=NULL)//The new up is the up's east
                up=up->east;
            left = current;//The left is the old current
            current = right;//The new current is the new right
            if(j!=9)
                current->dEast = rand() % 10;
            else
                current->east = 0;
            if(i!=9)
                current->dSouth = rand() % 10;
            else
                current->dSouth = 0;
            //cout << "Node #: " << c <<" E: " << current->dEast << " S: " << current->dSouth << endl;

            if(left!=NULL)//Assigns the new nodes west distance to the left nodes east distance
            {
                left->east = current;
                current->dWest=left->dEast;
                //cout << "Node #: "<< c << " has west node (" << left->row << "," << left->col << ")" << endl;
            }
            current->west = left;

            if(up!=NULL)//Assigns the new nodes north distance to the up nodes south distance
            {
                up->south =current;
                current->dNorth = up->dSouth;
                //cout << "Node #: "<< c << " has north node (" << up->row << "," << up->col << ")" << endl;
            }
                //cout << "Node #: "<< c << " has north node NULL"<<endl;
            current->north = up;
        }
        up = first;
    }
}

void MAIN::bellman_ford_print(){
    node * temp1 = root;
    while(temp1!=NULL){
        node * temp2 = temp1;
        while(temp1!=NULL){
                if(temp1->distance<10&&temp1->distance!=-1)
                    cout << " 0" << temp1->distance << " ";
                else
                    cout << " " << temp1->distance << " ";
            temp1=temp1->east;
        }
        cout << endl;
        temp1=temp2->south;
    }

}

void MAIN::bellman_ford(node * start, node * ending){
    node * temp1 = root;
    while(temp1!=NULL){
        node * temp2 = temp1;
        while(temp1!=NULL){
            temp1->clearNode();
            temp1=temp1->east;
        }
        temp1=temp2->south;
    }
    bellman_ford_helper(start);
    cout << "The Shortest Distance from "; start->ID(); cout << "to "; ending->ID(); cout << " is " << ending->distance << " units."<<endl;
}

void MAIN::bellman_ford_helper(node * start){
    int s = 0;
    start->distance = 0;
    start->poped = true;
    node * last = start;
    node * h = start;
    do{
    /*
    cout << "PRESS ENTER TO EVOLVE THROUGH THE STEPS" << endl;
    char line[256];
    cin.getline(line , 256);
    */
    usleep(500000);
    for(int p = 0;p<1000;p++){
        cout << endl;
    }
    bellman_ford_print();
        last = h;
        cout << "Queue: ";
        last->ID();
        int t = 0;
        while(last->behind!=NULL&&t<100){
            last =last->behind;
            last->ID();
            t++;
        }
        cout << endl<<"Added: ";
        if(h->north!=NULL){
            if(!h->north->poped){
                last->behind = h->north;
                last = last->behind;
                last->ID();
                last->poped=true;
            }
        }
        if(h->east!=NULL){
            if(!h->east->poped){
                last->behind = h->east;
                last = last->behind;
                last->ID();
                last->poped=true;
            }
        }
        if(h->south!=NULL){
            if(!h->south->poped){
                last->behind = h->south;
                last = last->behind;
                last->ID();
                last->poped=true;
            }
        }
        if(h->west!=NULL){
            if(!h->west->poped){
                last->behind = h->west;
                last = last->behind;
                last->ID();
                last->poped=true;
            }
        }
        cout << endl;
        int current_len = h->distance;
        if(h->north!=NULL){
            s++;
            if((current_len + h->dNorth)<h->north->distance||h->north->distance==-1){
                h->north->distance = current_len + h->dNorth;
            }
        }
        if(h->east!=NULL){
            s++;
            if((current_len + h->dEast)<h->east->distance||h->east->distance==-1){
                h->east->distance = current_len + h->dEast;
            }
        }
        if(h->south!=NULL){
            s++;
            if((current_len + h->dSouth)<h->south->distance||h->south->distance==-1){
                h->south->distance = current_len + h->dSouth;
            }
        }
        if(h->west!=NULL){
            s++;
            if((current_len + h->dWest)<h->west->distance||h->west->distance==-1){
                h->west->distance = current_len + h->dWest;
            }
        }
        h = h->behind;
        cout << "Steps Taken: " << s << endl;
    }while(h!=NULL);
    for(int p = 0;p<1000;p++){
        cout << endl;
    }
    cout << "Final Array of Distances from the Point "; start->ID();
    cout << endl<< endl;
    bellman_ford_print();
    cout << "Total Steps: " << s << endl;
}

node * MAIN::findNode(int i,int j){
    node * temp = root;
    while(temp->row<i)
        temp=temp->south;
    while(temp->col<j)
        temp=temp->east;
    return temp;
}

void MAIN::printGraph(){
    cout << "Graph with 100 vertices and weighted undirected edges" << endl << endl;
    node * main = root;
    node * first = root;
    while (first!=NULL){
            while(main != NULL){
                cout  << "    " << main->dNorth << "     ";
                main = main->east;
            }
            cout << endl;
            main = first;
            while(main != NULL){
                cout << main->dWest << " ";
                cout << "(" << main->row << "," << main->col << ") ";
                cout << main->dEast << " ";
                main = main->east;
            }
            main = first;
            cout << endl;
            while(main != NULL){
                cout  << "    " << main->dSouth << "     ";
                main = main->east;
            }
            first = first->south;
            main = first;
            cout << endl;

        }
}

void MAIN::findPath(){
    bellman_ford(findNode(3,3),findNode(4,4));
}

/////////////////////////////////

int main(){
    char line[256];
    cin.getline(line , 256);
    MAIN main;
    main.printGraph();
    cin.getline(line , 256);
    main.findPath();
}

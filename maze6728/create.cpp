#include "create.h"
#include <ctime>
#include <random>
#include <iostream>

const int x_size = 39;
const int y_size = 19;
char arr[y_size][x_size+1]; //maze
bool path_check[y_size][x_size]; //check the path

/*
    1. initialize all the stuff
    2. random dfs (randomly pick path) to create a maze
*/

//1.
void mazeInitialize() {
    //initialize the maze like this ('#' means wall)
    /*
        #######
        # # # #
        #######
        # # # #
        #######
    */

    //maze even column
    for(int i=0; i<y_size; i+=2) {
        for(int j=0; j<x_size; j++) {
            arr[i][j] = '#';
        }
    }

    //maze odd column
    for(int i=1; i<y_size; i+= 2) {
        for(int j=0; j<x_size; j+=2) {
            arr[i][j] = '#';
        }
    }

    //initialize path_check
    for(int i=0; i<y_size; i++) {
        for(int j=0; j<x_size; j++) {
            path_check[i][j] = false;
        }
    }

    arr[1][1] = '@'; //starting point
    arr[y_size-2][x_size-2] = '%'; //ending point
}

//2.
/* The idea is to erase the wall to make it a maze

    ###########
    #@# # # # #
    ###########
    # # # # # #   =>
    ###########
    # # # # # #
    ###########

    ###########
    #@  # # # #
    ###########
    # # # # # #   =>
    ###########
    # # # # # #
    ###########

    ###########
    #@  # # # #
    ### #######
    # # # # # #   ======>
    ###########
    # # # # # #
    ###########

    ###########
    #@  #!    #
    ### ### # #
    #   # # # #
    ### # ### #
    #         #
    ###########
*/


std::mt19937 mt(time(NULL));
void mazeCreation(int i, int j) {
    path_check[i][j] = true;

    //random dfs
    while(true) {
        int choice = mt() % 4;

        //if all path is not available, stop the loop
        if(!( ((j+2 < x_size && !path_check[i][j+2]) || (j-2 > 0 && !path_check[i][j-2])) ||
              ((i+2 < y_size && !path_check[i+2][j]) || (i-2 > 0 && !path_check[i-2][j])) )) {
            return;
        }

        switch(choice) {
            case 0:
                if(j+2 < x_size && !path_check[i][j+2]) {
                    arr[i][j+1] = ' ';  //clear the path
                    mazeCreation(i, j+2); //dfs
                }
                break;
            case 1:
                if(j-2 > 0 && !path_check[i][j-2]) {
                    arr[i][j-1] = ' '; //clear the path
                    mazeCreation(i, j-2);  //dfs
                }
                break;
            case 2:
                if(i+2 < y_size && !path_check[i+2][j]) {
                    arr[i+1][j] = ' '; //clear the path
                    mazeCreation(i+2, j); //dfs
                }
                break;
            case 3:
                if(i-2 > 0 && !path_check[i-2][j]) {
                    arr[i-1][j] = ' '; //clear the path
                    mazeCreation(i-2, j); //dfs
                }
                break;
        }
    }
}


std::vector<std::string> getMaze() {
    std::vector<std::string> v;
    std::string str;

    for(int i=0; i<y_size; i++) {
        for(int j=0; j<x_size; j++) {
            str += arr[i][j];
        }

        v.push_back(str);
        str.clear();
    }

    return v;
}

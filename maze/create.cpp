#include "create.h"
//#include <iostream>
#include <ctime>
#include <random>

const int maze_size = 21;
char arr[maze_size][maze_size]; //original maze
bool path_check[maze_size][maze_size]; //check the path

/*
    1. initialize all the shit
    2. random dfs (randomly pick path) to create a maze
    3. set spawn point & use bfs to find the furthest point off spawn (set that point the end)
*/

//1.
void mazeInitialize() {
    //let maze become like this ('#' means wall)
    /*
        #######
        # # # #
        #######
        # # # #
        #######
    */

    //maze even column
    for(int i=0; i<maze_size; i+=2) {
        for(int j=0; j<maze_size; j++) {
            arr[i][j] = '#';
        }
    }

    //maze odd column
    for(int i=1; i<maze_size; i+= 2) {
        for(int j=0; j<maze_size; j+=2) {
            arr[i][j] = '#';
        }
    }


    //initialize path_check
    for(int i=0; i<maze_size; i++) {
        for(int j=0; j<maze_size; j++) {
            path_check[i][j] = false;
        }
    }
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

void mazeCreation(int i, int j) {
    //pick random spot to go
    std::random_device rd; //random seed
    std::mt19937 generator( rd() );

    //yeah yeah
    std::uniform_real_distribution<float> unif(0, 4);


    //check if choice is valid
    bool repeat_check[4];
    for(int i=0; i<4; i++)
        repeat_check[i] = false;


    //already in the path
    path_check[i][j] = true;


    //random dfs
    while(true) {
        int choice = unif(generator); //choice to pick (up)(down)(left)(right)


        //if all path is not available, stop the loop
        if(repeat_check[0] && repeat_check[1] && repeat_check[2] && repeat_check[3]) {
            return;
        }

        //choice pick
        switch(choice) {
            case 0:

                if(j+2 < maze_size && !path_check[i][j+2]) {
                    arr[i][j+1] = ' ';  //clear the path
                    mazeCreation(i, j+2); //dfs
                }
                else
                    repeat_check[0] = true; //is repeating

                break;
            case 1:

                if(j-2 > 0 && !path_check[i][j-2]) {
                    arr[i][j-1] = ' '; //clear the path
                    mazeCreation(i, j-2);  //dfs
                }
                else
                    repeat_check[1] = true;

                break;
            case 2:

                if(i+2 < maze_size && !path_check[i+2][j]) {
                    arr[i+1][j] = ' '; //clear the path
                    mazeCreation(i+2, j); //dfs
                }
                else
                    repeat_check[2] = true;

                break;
            case 3:

                if(i-2 > 0 && !path_check[i-2][j]) {
                    arr[i-1][j] = ' '; //clear the path
                    mazeCreation(i-2, j); //dfs
                }
                else
                    repeat_check[3] = true;

                break;
        }
    }
}

void spawnSelection() {
    //will randomized in the near future
    /*
    std::random_device rd; //random seed
    std::mt19937 generator( rd() );

    //yeah yeah
    std::uniform_real_distribution<float> unif(0, maze_size/2);
    int x = unif(generator);
    int y = unif(generator);
    if(x != maze_size/2 && y != maze_size/2) {
        arr[x*2+1][y*2+1] = '@';
    }

    checkPath(x*2+1, y*2+1);
    */

    arr[1][1] = '@';
    arr[maze_size-2][maze_size-2] = '%';
}

std::vector<std::string> getMaze() {
    std::vector<std::string> v;
    std::string str;

    for(int i=0; i<maze_size; i++) {
        for(int j=0; j<maze_size; j++) {
            str += arr[i][j];
        }

        v.push_back(str);
        str.clear();
    }

    return v;
}

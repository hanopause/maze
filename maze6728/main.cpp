#include <iostream>
#include <windows.h>
#include <conio.h>
#include "create.h"

//declarion
std::vector<std::string> maze;
bool isOver = false;

//draw maze
void draw() {
    for(auto& it: maze) {
        std::cout<<it<<std::endl;
    }
    std::cout<<"Controls: W to go up, A to go left, S to go down, D to go right"<<std::endl;
    std::cout<<"Goal is to reach '@' without touching '#'"<<std::endl;
}

//x pos and y pos
int x_pos = 1, y_pos = 1;
void getUserInput() {
/*
    1. detect user input by using kbhit()
    2. A player loses the game if they accidentally bump into a wall.
    3. A player wins the game once they successfully reaches the '@' letter
    4. if a player is not winning or losing, just simply changes his position and puts '.' on the path he visits before
*/
    char input;

    if(kbhit()) {
        input = getch();


        switch(input) {
        case 'w':
            //move up
            if(maze[y_pos-1][x_pos] == '#') {
                //step 2
                std::cout<<"You loss!!!\n";
                isOver = true;
            }
            else {
                if(maze[y_pos-1][x_pos] == '%') {
                    //step 3
                    std::cout<<"Congrats!!!\n";
                    isOver = true;
                }

                //step 4
                maze[y_pos][x_pos] = '.';
                maze[y_pos-1][x_pos] = '@';
                y_pos--;
            }

            break;

        case 'a':
            //move left
            if(maze[y_pos][x_pos-1] == '#') {
                std::cout<<"You loss!!!\n";
                isOver = true;
            }
            else {
                if(maze[y_pos][x_pos-1] == '%') {
                    std::cout<<"Congrats!!!\n";
                    isOver = true;
                }
                maze[y_pos][x_pos] = '.';
                maze[y_pos][x_pos-1] = '@';
                x_pos--;
            }

            break;

        case 's':
            //move down
            if(maze[y_pos+1][x_pos] == '#') {
                std::cout<<"You loss!!!\n";
                isOver = true;
            }
            else {
                if(maze[y_pos+1][x_pos] == '%') {
                    std::cout<<"Congrats!!!\n";
                    isOver = true;
                }
                maze[y_pos][x_pos] = '.';
                maze[y_pos+1][x_pos] = '@';
                y_pos++;
            }

            break;

        case 'd':
            //move right
            if(maze[y_pos][x_pos+1] == '#') {
                std::cout<<"You loss!!!\n";
                isOver = true;
            }
            else {
                if(maze[y_pos][x_pos+1] == '%') {
                    std::cout<<"Congrats!!!\n";
                    isOver = true;
                }
                maze[y_pos][x_pos] = '.';
                maze[y_pos][x_pos+1] = '@';
                x_pos++;
            }

            break;
        }

    }

}

int main() {
    //create a maze & check possiblities
    mazeInitialize();
    mazeCreation(1, 1);
    maze = getMaze();


    /*
        1. call getUserInput()
        3. set cursor to {0, 0}
        4. draw maze again
    */


    //user maze needs to update
    draw(); //draw it first time

    //create a handle
    HANDLE win_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    while(!isOver) {
        //action
        getUserInput();

        //draw
        SetConsoleCursorPosition(win_handle, {0, 0});
        draw();

    }


    return 0;
}

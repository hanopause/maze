#include <iostream>
#include "create.h"
using std::cin;
using std::cout;

std::vector<std::string> maze;
int main() {
    //create a maze & check possiblities
    mazeInitialize();
    mazeCreation(1, 1);
    spawnSelection();
    maze = getMaze();
    cout<<"\n";

    /*
    for(auto& it: maze) {
        std::cout<<it;
        cout<<"\n";
    }
    */

    //if it's possible, let player start the game
    /*
        1. coords which record the pos
        2. if (WASD) -> change the coords
        3. clean screen
        4. print the new array(vector...)
    */
}

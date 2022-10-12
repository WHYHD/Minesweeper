#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include "tiles.h"
#include "board.h"
#include "TextureManger.h"
#include "Random.h"


using namespace std;

void readConfig(string filename) { //Read CFG file and draw baord accordingly
    ifstream inFile(filename);

    string width;
    string height;
    string mineCount;


    getline(inFile, width);
    getline(inFile, height);
    getline(inFile, mineCount);
        
    board defaultB(stoi(width), stoi(height), stoi(mineCount), stoi(mineCount));
    defaultB.draw();
    
}


int main()
{
    readConfig("boards/config.cfg");

    return 0;
}
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "tiles.h"
#include "Random.h"
#include "TextureManger.h"
using namespace std;


class board
{
	int width;
	int height;
	int numMines;
	int mines;
	//vector<vector<tiles>> col;
	//vector<int> x;


public:

	board();
	board(int w, int h, int numMines, int mines);

	void draw();
	vector<vector<tiles>> newBoard(int& numMines, int& num1, int& num2, int& num3, int& numFlag, bool& gameOver, sf::Sprite& sadFace, sf::Sprite& coolFace);
	vector<vector<tiles>> readTestBoard(string fileName, int& numMines, int& num1, int& num2, int& num3, int& numFlag, bool& gameOver, sf::Sprite& sadFace, sf::Sprite& coolFace); //to future me ---> why r all the variable passed as refrence(&), so that data passed in change outside function.
	void getNeighbors(vector<vector<tiles>>& boardTiles);

	int getW();
	int getH();
	int getNumMines();



	//void findAdjacentTiles(vector<vector<tiles>>& boardTiles);


};


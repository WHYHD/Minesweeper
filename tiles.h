#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <map>
#include "tiles.h"
//#include "board.h" YYYYYYYYYYOOOOOOOOOOOO NEVER DO THIS AGAIN --- FUCKING BREAKS SHIT BIG TIME
#include "Random.h"
#include "TextureManger.h"

class tiles
{
	int status; 
	bool isMine;
	int x;
	int y;
	vector<tiles*> adjacentTiles;
	sf::Sprite mine;
	sf::Sprite tileHidden;
	sf::Sprite tileRevealed;
	sf::Sprite flag;
	sf::Sprite number;

	map<string, bool> activeLayers; //Pass through setter methods -- if layer needed == T change opacity to 255 


public:
	tiles();
	tiles(int status);
	
	/*---------Getters---------*/
	sf::Sprite getSpriteMine();
	sf::Sprite getSpriteTileHidden();
	sf::Sprite getSpriteTileRevealed();
	sf::Sprite getSpriteFlag();
	sf::Sprite getSpriteNumber();
	bool getIsMine();
	vector<tiles*> getAdjacentTiles();
	int getX();
	sf::Sprite getSprite1();
	map<string, bool> getActiveLayers();

	int getSurroundingMines();
	


	/*---------Setters---------*/
	void setSpritePos(int x, int y);
	void setIsMine(bool x);

	void setSpriteMineTransparent();
	void setSpriteTileHiddenTransparent();
	void setSpriteTileRevealedTransparent();
	void setSpriteFlagTransparent();
	void setSpriteNumberTransparent();

	void setSpriteMineVisible();
	void setSpriteTileHiddenVisible();
	void setSpriteTileRevealedVisible();
	void setSpriteFlagVisible();
	void setSpriteNumberVisible();

	void setactiveLayers(string name, bool active);
	void addAdjacentTiles(tiles* Tile);
	void setStatus(int x);
	void revealTiles();
	void setColor();

};

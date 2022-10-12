#include "tiles.h"
tiles::tiles() {
	status = 1;
}
tiles::tiles(int status) {
	this->status = status;
	isMine = false;
	if (status == 0) {
		isMine = true;
		activeLayers["mine"] = true;
	}

	tileHidden.setTexture(TextureManger::GetTexture("tile_hidden")); // tile is hidden

	tileRevealed.setTexture(TextureManger::GetTexture("tile_revealed")); // tile is revealed 
	
	flag.setTexture(TextureManger::GetTexture("flag")); //tile flagged

	mine.setTexture(TextureManger::GetTexture("mine")); // tile is mine

	number.setTexture(TextureManger::GetTexture("number_1"));

	activeLayers.emplace("mine", false);
	activeLayers.emplace("tile_hidden", true);
	activeLayers.emplace("tile_revealed", false);
	activeLayers.emplace("flag", false);

	setSpriteFlagTransparent();
	setSpriteMineTransparent();
	setSpriteTileRevealedTransparent();
	setSpriteNumberTransparent();

}


/*---------Getters---------*/

sf::Sprite tiles::getSpriteMine() {
	return mine;
}
sf::Sprite tiles::getSpriteNumber() {
	return number;
}
sf::Sprite tiles::getSpriteTileHidden() {
	return tileHidden;
}
sf::Sprite tiles::getSpriteTileRevealed() {
	return tileRevealed;
}
sf::Sprite tiles::getSpriteFlag() {
	return flag;
}
bool tiles::getIsMine() {
	return isMine;
}
vector<tiles*> tiles::getAdjacentTiles() {
	return adjacentTiles;
}
int tiles::getX() {
	return x;
}
map<string, bool> tiles::getActiveLayers() {
	return activeLayers;
}
int tiles::getSurroundingMines() {
	int tempNumMines = 0;
	for (int i = 0; i < adjacentTiles.size(); i++) {
		if (adjacentTiles[i]->activeLayers["mine"]) {
			tempNumMines++;
		}
	}
	return tempNumMines;
}



/*---------Setters---------*/
void tiles::setSpriteMineTransparent() {
	mine.setColor(sf::Color(255, 255, 255, 0));
}
void tiles::setSpriteTileHiddenTransparent() {
	tileHidden.setColor(sf::Color(255, 255, 255, 0));
}
void tiles::setSpriteTileRevealedTransparent() {
	tileRevealed.setColor(sf::Color(255, 255, 255, 0));
}
void tiles::setSpriteFlagTransparent() {
	flag.setColor(sf::Color(255, 255, 255, 0));
}
void tiles::setSpriteNumberTransparent() {
	number.setColor(sf::Color(255, 255, 255, 0));
}


void tiles::setSpriteMineVisible() {
	mine.setColor(sf::Color(255, 255, 255, 255));
}
void tiles::setSpriteTileHiddenVisible() {
	tileHidden.setColor(sf::Color(255, 255, 255, 255));
}
void tiles::setSpriteTileRevealedVisible() {
	tileRevealed.setColor(sf::Color(255, 255, 255, 255));
}
void tiles::setSpriteFlagVisible() {
	flag.setColor(sf::Color(255, 255, 255, 255));
}
void tiles::setSpriteNumberVisible() {
	number.setColor(sf::Color(255, 255, 255, 255));
}

void tiles::setColor() {//used for testing

	tileHidden.setColor(sf::Color(0, 255, 0));
}


void tiles::setStatus(int x) {
	status = x;
}

void tiles::setSpritePos(int x, int y){
	this->x = x;
	this->y = y;
	mine.setPosition(x, y);
	tileHidden.setPosition(x, y);
	tileRevealed.setPosition(x, y);
	flag.setPosition(x, y);
	number.setPosition(x, y);
}
void tiles::setIsMine(bool x) {
	isMine = x;
}
void tiles::setactiveLayers(string name, bool active) {
	activeLayers[name] = active;
}


void tiles::addAdjacentTiles(tiles* Tile) {
	//check multiD vec at i(width) +-1 and j(height) +-1 if space is a tile
	//vector sub out of range for tiles on the edge of board --- need to account for that
	//confirm tile exsits--> add tile* to vector
	adjacentTiles.push_back(Tile);

}

//this is gonna hurt

void tiles::revealTiles() {
	int surrMines = getSurroundingMines();
	number.setTexture(TextureManger::GetTexture("number_" + to_string(surrMines)));
	for (unsigned int i = 0; i < adjacentTiles.size(); i++) {
		if (!(adjacentTiles[i]->activeLayers["tile_revealed"]) && !(adjacentTiles[i]->activeLayers["flag"]) && !(adjacentTiles[i]->activeLayers["mine"])) {
			if (surrMines > 0) {
				
				setSpriteTileHiddenTransparent();
				setSpriteTileRevealedVisible();
				setactiveLayers("tile_hidden", false);
				setactiveLayers("tile_revealed", true);
				setSpriteNumberVisible();

			}
			else if (surrMines == 0) {
				setSpriteTileHiddenTransparent();
				setSpriteTileRevealedVisible();
				adjacentTiles[i]->setactiveLayers("tile_revealed", true);
				adjacentTiles[i]->setSpriteTileHiddenTransparent();
				adjacentTiles[i]->setSpriteTileRevealedVisible();
				adjacentTiles[i]->revealTiles();
			}

			//adjacentTiles[i]->revealTiles();
		}
		else {
			setSpriteTileHiddenTransparent();
			setSpriteTileRevealedVisible();
			setactiveLayers("tile_hidden", false);
			setactiveLayers("tile_revealed", true);
			if (surrMines == 8 || surrMines == 7 || surrMines == 6 || surrMines == 5 || surrMines == 4 || surrMines == 3 || surrMines == 2 || surrMines == 1) {
				setSpriteNumberVisible();
			}
			cout << "thats a mine" << endl;
		}
	}
}
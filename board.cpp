#include "board.h"

board::board() {
	width = -1;
	height = -1;
	numMines = -1;
}
board::board(int w, int h, int numMines, int mines) {
	width = w;
	height = h;
	this->numMines = numMines;
    this->mines = mines;
}

//void board::findAdjacentTiles(vector<vector<tiles>>& boardTiles) {
   //for (int i = 0; i < height; i++) {
   //    for (int j = 0; j < width; j++) {
   //        boardTiles[i][j]
   //    }
   //}
//}

vector<vector<tiles>> board::newBoard(int& numMines, int& num1, int& num2, int& num3, int& numFlag, bool& gameOver, sf::Sprite& sadFace, sf::Sprite& coolFace) {
    vector<vector<tiles>> boardTiles;
    numFlag = 0;
    numMines = mines;
    gameOver = false;
    sadFace.setColor(sf::Color(255, 255, 255, 0));
    coolFace.setColor(sf::Color(255, 255, 255, 0));

    /*------------Building and drawing mine feild------------*/
    for (int i = 0; i < height; i++) { //muliD Vec creating and storing tiles for the game board
        vector<tiles> row;
        for (int j = 0; j < width; j++) {
            tiles Tile(1);
            row.push_back(Tile);
        }
        boardTiles.push_back(row);
    }

    /*Assigning X amount of mines*/
   //boardTiles[0][0].setactiveLayers("mine", true);
    for (unsigned int i = 0; i < mines; i++) {
        int ranX = Random::Int(0, height - 1);
        int ranY = Random::Int(0, width - 1);
        boardTiles[ranX][ranY].setactiveLayers("mine", true);
        boardTiles[ranX][ranY].setIsMine(true);
    }
    num3 = ((mines / 10) / 10);
    num1 = (mines / 10) % 10;
    num2 = (mines % 10);
    return boardTiles;
}

void board::getNeighbors(vector<vector<tiles>>& boardTiles) {
    for (int a = 0; a < height; a++) {
        for (int b = 0; b < width; b++) {
            if (((a) >= 0 && (a) < height) && ((b + 1) >= 0 && (b + 1) < width)) { //(a, b + 1)
                tiles* x = &boardTiles[a][b + 1];
                boardTiles[a][b].addAdjacentTiles(x);
            }
            if (((a) >= 0 && (a) < height) && ((b - 1) >= 0 && (b - 1) < width)) {//(a , b - 1)
                tiles* x = &boardTiles[a][b - 1];
                boardTiles[a][b].addAdjacentTiles(x);
            }
            if (((a + 1) >= 0 && (a + 1) < height) && ((b) >= 0 && (b) < width)) {//(a + 1, b)
                tiles* x = &boardTiles[a + 1][b];
                boardTiles[a][b].addAdjacentTiles(x);
            }
            if (((a - 1) >= 0 && (a - 1) < height) && ((b) >= 0 && (b) < width)) {//(a - 1, b)
                tiles* x = &boardTiles[a - 1][b];
                boardTiles[a][b].addAdjacentTiles(x);
            }
            if (((a + 1) >= 0 && (a + 1) < height) && ((b - 1) >= 0 && (b - 1) < width)) {//(a + 1, b - 1)
                tiles* x = &boardTiles[a + 1][b - 1];
                boardTiles[a][b].addAdjacentTiles(x);
            }
            if (((a - 1) >= 0 && (a - 1) < height) && ((b + 1) >= 0 && (b + 1) < width)) {//(a - 1, b + 1)
                tiles* x = &boardTiles[a - 1][b + 1];
                boardTiles[a][b].addAdjacentTiles(x);
            }
            if (((a - 1) >= 0 && (a - 1) < height) && ((b - 1) >= 0 && (b - 1) < width)) {//(a - 1, b - 1)
                tiles* x = &boardTiles[a - 1][b - 1];
                boardTiles[a][b].addAdjacentTiles(x);
            }
            if (((a + 1) >= 0 && (a + 1) < height) && ((b + 1) >= 0 && (b + 1) < width)) {//(a + 1, b + 1)
                tiles* x = &boardTiles[a + 1][b + 1];
                boardTiles[a][b].addAdjacentTiles(x);
            }

        }
    }
}


vector<vector<tiles>> board::readTestBoard(string fileName, int& numMines, int& num1, int& num2, int& num3, int& numFlag, bool& gameOver, sf::Sprite& sadFace, sf::Sprite& coolFace) {
    vector<vector<tiles>> boardTiles;
    ifstream inFile(fileName);
    numMines = 0;
    numFlag = 0;
    gameOver = false;
    sadFace.setColor(sf::Color(255, 255, 255, 0));
    coolFace.setColor(sf::Color(255, 255, 255, 0));

    vector<string> vectorLine;
    
    for (int i = 0; i < height; i++) {
        string line;
        getline(inFile, line);
        vectorLine.push_back(line);
    }

   // cout << (int)vectorLine[0][0] << endl;

    for (int a = 0; a < height; a++) {
        vector<tiles> tilesWidth;
        for (int b = 0; b < width; b++) {
            if (int(vectorLine[a][b]) == 49) {
                tiles Tile(0);
                tilesWidth.push_back(Tile);
                numMines++;
                cout << "Mine Found" << endl;
            }
            else {
                tiles Tile(1);
                tilesWidth.push_back(Tile);
                cout << "no mine found" << endl;
            }
        }
        boardTiles.push_back(tilesWidth);
    }
    num3 = ((numMines / 10) / 10);
    num1 = (numMines / 10) % 10;
    num2 = (numMines % 10);
    return boardTiles;
}

void board::draw() {
    sf::RenderWindow window(sf::VideoMode((width * 32), ((height) * 32) + 88), "Minesweeper");
    int w = ((width) * 32);
    int h = ((height) * 32) + 88;


    bool showinMines = false;
    bool gameOver;
    int numFlag = 0;

    // run the program as long as the window is open
    sf::Sprite happyFace(TextureManger::GetTexture("face_happy"));
    sf::Sprite sadFace(TextureManger::GetTexture("face_lose"));
    sf::Sprite coolFace(TextureManger::GetTexture("face_win"));
    sf::Sprite test3(TextureManger::GetTexture("test_3"));
    sf::Sprite test2(TextureManger::GetTexture("test_2"));
    sf::Sprite test1(TextureManger::GetTexture("test_1"));
    sf::Sprite debug(TextureManger::GetTexture("debug"));
    sf::Sprite digitsNegative(TextureManger::GetTexture("digits"));
    sf::Sprite digits1(TextureManger::GetTexture("digits"));
    sf::Sprite digits2(TextureManger::GetTexture("digits"));
    sf::Sprite digits3(TextureManger::GetTexture("digits"));

    digitsNegative.setColor(sf::Color(255, 255, 255, 0)); //transparent 
    

    int num1;
    int num2;
    int num3;

    
    /*------------Building and drawing mine feild------------*/
   
    vector<vector<tiles>> boardTiles = newBoard(numMines, num1, num2, num3, numFlag, gameOver, sadFace, coolFace);

   /*--------------Finding neighbors--------------*/
    getNeighbors(boardTiles);

 //for (int i = 0; i < boardTiles[10][10].getAdjacentTiles().size(); i++) {
 //
 //    cout << "Tile: (" << 0 << ", " << 0 << ") " << boardTiles[10][10].getAdjacentTiles()[i] << endl;
 //    boardTiles[10][10].getAdjacentTiles()[i]->setSprite();
 //
 //    if (boardTiles[10][10].getAdjacentTiles()[i]->getIsMine())
 //        cout << "mine" << endl;
 //    else
 //        cout << "no mines" << endl;
 //   // boardTiles[10][10].getAdjacentTiles()[i]->setSprite();
 //}
  
      
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            
            //Mouse was pressed
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) { //Left Click happned somewhere -- find out where and respone accordingly

                        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                        auto bounds = debug.getGlobalBounds();

                    if (!gameOver) {

                        /*--------Debug Button--------*/
                        if (bounds.contains(localPosition.x, localPosition.y)) {
                      
                            if (!showinMines) {
                                for (int i = 0; i < height; i++) {
                                    for (int j = 0; j < width; j++) {
                               
                                        if (!boardTiles[i][j].getActiveLayers()["mine"]) {//not a mine
                                           //boardTiles[i][j].setSpriteMineTransparent();//hide mine
                                           //boardTiles[i][j].setSpriteFlagTransparent();
                                        }
                                        else {
                                            boardTiles[i][j].setSpriteMineVisible();
                                            boardTiles[i][j].setSpriteTileHiddenVisible();
                                            showinMines = true;
                                        }
                                  }
                               }
                            }
                            else {
                                for (int i = 0; i < height; i++) {
                                    for (int j = 0; j < width; j++) {
                                        if (!boardTiles[i][j].getActiveLayers()["mine"]) {//not a mine
                                           //boardTiles[i][j].setSpriteMineTransparent();//hide mine
                                           //boardTiles[i][j].setSpriteFlagTransparent();
                                        }
                                        else {
                                            boardTiles[i][j].setSpriteMineTransparent();
                                            //boardTiles[i][j].setSpriteFlagTransparent();
                                            boardTiles[i][j].setSpriteTileHiddenVisible();
                                            showinMines = false;
                                        }
                                    }
                                }
                            }
                        } 


                        /*--------Tiles--------*/
                        for (int i = 0; i < height; i++) {
                            for (int j = 0; j < width; j++) {
                                bounds = boardTiles[i][j].getSpriteTileHidden().getGlobalBounds();
                                if (bounds.contains(localPosition.x, localPosition.y)) {
                                    if (!boardTiles[i][j].getActiveLayers()["flag"]) {
                                        
                                        if (boardTiles[i][j].getActiveLayers()["mine"]) {
                                            gameOver = true;
                                            sadFace.setColor(sf::Color(255, 255, 255, 255));

                                                    if (boardTiles[i][j].getActiveLayers()["mine"]) {
                                                        boardTiles[i][j].setSpriteMineVisible();
                                                        boardTiles[i][j].setSpriteFlagTransparent();
                                                        boardTiles[i][j].setSpriteTileRevealedVisible();
                                                        boardTiles[i][j].setSpriteTileHiddenTransparent();
                                                        //boardTiles[i][j].setSpriteNumberTransparent();

                                                    }
                                            
                                            showinMines = true;
                                            cout << "Game Failed" << endl;
                                        }
                                        else {
                                            boardTiles[i][j].revealTiles();
                                            int counter = 0;
                                            for (int i = 0; i < height; i++) {
                                                for (int j = 0; j < width; j++) {
                                                    if (boardTiles[i][j].getActiveLayers()["tile_revealed"]) {
                                                        counter++;
                                                    }
                                                }
                                            }

                                            if (counter == (width * height) - (numMines)) {
                                                gameOver = true;
                                                coolFace.setColor(sf::Color(255, 255, 255, 255));
                                                cout << "You won" << endl;
                                            }
                                            cout << "Shit worked homie" << endl;
                                        }
                                   
                                    }
                                }
                            }
                        }
                    }

                    /*--------New Board Button--------*/
                    bounds = happyFace.getGlobalBounds();
                    if (bounds.contains(localPosition.x, localPosition.y)) {
                        digitsNegative.setColor(sf::Color(255, 255, 255, 0));
                        boardTiles = newBoard(numMines, num1, num2, num3, numFlag, gameOver, sadFace, coolFace);
                        getNeighbors(boardTiles);
                        cout << "Yup you touched the face" << endl;
                    }

                    /*--------Test Board 1--------*/
                    bounds = test1.getGlobalBounds();
                    if (bounds.contains(localPosition.x, localPosition.y)) {
                        digitsNegative.setColor(sf::Color(255, 255, 255, 0));
                        boardTiles = readTestBoard("boards/testboard1.brd", numMines, num1, num2, num3, numFlag, gameOver, sadFace, coolFace);
                        getNeighbors(boardTiles);
                        cout << "Yup you clicked on test 1" << endl;
                    }
                    /*--------Test Board 2--------*/
                    bounds = test2.getGlobalBounds();
                    if (bounds.contains(localPosition.x, localPosition.y)) {
                        digitsNegative.setColor(sf::Color(255, 255, 255, 0));
                        boardTiles = readTestBoard("boards/testboard2.brd", numMines, num1, num2, num3, numFlag, gameOver, sadFace, coolFace);
                        getNeighbors(boardTiles);
                        cout << "Yup you clicked on test 2" << endl;
                    }
                    /*--------Test Board 3--------*/
                    bounds = test3.getGlobalBounds();
                    if (bounds.contains(localPosition.x, localPosition.y)) {
                        digitsNegative.setColor(sf::Color(255, 255, 255, 0));
                        boardTiles = readTestBoard("boards/testboard3.brd", numMines, num1, num2, num3, numFlag, gameOver, sadFace, coolFace);
                        getNeighbors(boardTiles);
                        cout << "Yup you clicked on test 3" << endl;
                    }

                }
                
                else if(event.mouseButton.button == sf::Mouse::Right) { //FFLLLLLLLLLLAAAAAAAAAAAAGGGGGGGGGGSSSSSSSSSSS

                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    auto bounds = debug.getGlobalBounds();
                if(!gameOver){
                    for (int i = 0; i < height; i++) {
                        for (int j = 0; j < width; j++) {
                            bounds = boardTiles[i][j].getSpriteTileHidden().getGlobalBounds();
                            if (bounds.contains(localPosition.x, localPosition.y)) {
                                if (!boardTiles[i][j].getActiveLayers()["flag"]) {
                                    boardTiles[i][j].setSpriteFlagVisible();
                                    boardTiles[i][j].setactiveLayers("flag", true);
                                    cout << "Flag has been placed homie" << endl;
                                    numMines--;
                                        if (numMines < 0) {
                                            digitsNegative.setColor(sf::Color(255, 255, 255, 255)); //visable 
                                            numFlag++;
                                            num3 = ((numFlag / 10) / 10);
                                            num1 = (numFlag / 10) % 10;
                                            num2 = numFlag % 10;
                                            }
                                        else {
                                            num3 = ((numMines / 10) / 10);
                                            num1 = (numMines / 10) % 10;
                                            num2 = numMines % 10;
                                        }
                                    digits1.setTextureRect(sf::IntRect((21 * num3), 0, 21, 32));
                                    digits2.setTextureRect(sf::IntRect((21 * num1), 0, 21, 32));
                                    digits3.setTextureRect(sf::IntRect((21 * num2), 0, 21, 32));
                                    
                                }
                                else if (boardTiles[i][j].getActiveLayers()["flag"]) {
                                    boardTiles[i][j].setSpriteFlagTransparent();
                                    boardTiles[i][j].setactiveLayers("flag", false);
                                    cout << "Flag has been REMOVED homie" << endl;
                                    numMines++;
                                    if (numMines > 0) {
                                        digitsNegative.setColor(sf::Color(255, 255, 255, 0)); //transparent 
                                        num3 = ((numMines / 10) / 10);
                                        num1 = (numMines / 10) % 10;
                                        num2 = numMines % 10;
                                    }
                                    else {
                                        numFlag--;
                                        num3 = ((numFlag / 10) / 10);
                                        num1 = (numFlag / 10) % 10;
                                        num2 = numFlag % 10;
                                    }
                                    digits1.setTextureRect(sf::IntRect((21 * num3), 0, 21, 32));
                                    digits2.setTextureRect(sf::IntRect((21 * num1), 0, 21, 32));
                                    digits3.setTextureRect(sf::IntRect((21 * num2), 0, 21, 32));
                                }
                            }

                        }
                    }
                }
                }
            }


        }
       

        window.clear(sf::Color::White);

       // window.draw(digits)
       // digits.setTextureRect(sf::IntRect(10, 10, 0, 32));


 /*------------Building and drawing menu------------*/
       happyFace.setOrigin(64, 64);
       sadFace.setOrigin(64, 64);
       coolFace.setOrigin(64, 64);
       test3.setOrigin(64, 64);
       test2.setOrigin(64, 64);
       test1.setOrigin(64, 64);
       debug.setOrigin(64, 64);
       //digits.setOrigin(21, 32);

       digitsNegative.setTextureRect(sf::IntRect((21 * 10), 0, 21, 32));
       digits1.setTextureRect(sf::IntRect((21 * num3), 0, 21, 32));
       digits2.setTextureRect(sf::IntRect((21 * num1), 0, 21, 32));
       digits3.setTextureRect(sf::IntRect((21 * num2), 0, 21, 32));

       happyFace.setPosition((w / 2), h - 27);
       sadFace.setPosition((w / 2), h - 27);
       coolFace.setPosition((w / 2), h - 27);
       test3.setPosition(w, h - 27);
       test2.setPosition((w - 64), h - 27);
       test1.setPosition((w - 128), h - 27);
       test1.setPosition((w - 128), h - 27);
       debug.setPosition((w - 192), h - 27);
       digitsNegative.setPosition(0, h - 88);
       digits1.setPosition(21, h - 88);
       digits2.setPosition(42, h - 88);
       digits3.setPosition(63, h - 88);

       window.draw(happyFace);
       window.draw(sadFace);
       window.draw(coolFace);
       window.draw(test3);
       window.draw(test2);
       window.draw(test1);
       window.draw(debug);
       window.draw(digitsNegative);
       window.draw(digits1);
       window.draw(digits2);
       window.draw(digits3);


      /*Drawing to board ---- Last thing before window.display()*/
      for (int i = 0; i < height; i++) { 
          for (int j = 0; j < width; j++) {
              boardTiles[i][j].setSpritePos((j * 32), (i * 32));
              window.draw(boardTiles[i][j].getSpriteTileRevealed());
              window.draw(boardTiles[i][j].getSpriteTileHidden());
              window.draw(boardTiles[i][j].getSpriteFlag());
              window.draw(boardTiles[i][j].getSpriteMine());
              window.draw(boardTiles[i][j].getSpriteNumber());
          }
      }
      
     
        window.display();
    }
}

int board::getW() {
    return width;
}
int board::getH() {
    return height;
}
int board::getNumMines() {
    return numMines;
}
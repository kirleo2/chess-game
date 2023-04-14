//
//  Game.cpp
//  chess
//
//  Created by Kirill on 04.05.2022.
//

#include "Game.hpp"
#include "GameEvent.h"

#include "Queen.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Castle.hpp"
#include <typeinfo>

Game::Game(Player * p1, Player * p2):
player1(p1),
player2(p2)
{
    newGame = true;
    gameBoard = new ChessBoard();
    gameBoard->setStart();
    
    player1->setBoard(gameBoard);
    player2->setBoard(gameBoard);
    
    encodeGame();
    
    gameBoard->print_board();
}
Game::Game(const string & savePath):
player1(nullptr),
player2(nullptr){
    newGame = false;
    gameBoard = new ChessBoard();
    gameBoard->setStart();
    
    loadGame(savePath);
    
    player1->setBoard(gameBoard);
    player2->setBoard(gameBoard);
    
    gameBoard->print_board();
    
}


void Game::encodeGame() {
    // encode players according their type
    uint8_t firstPlayer;
    uint8_t secondPlayer;
    if (typeid(*player1) == typeid(LocalPlayer)) {
        firstPlayer = LOCAL_PLAYER;
    }
    else if (typeid(*player1) == typeid(DummyComputerPlayer)) {
        firstPlayer = DUMMY;
    }
    else if (typeid(*player1) == typeid(MediumComputerPlayer)) {
        firstPlayer = MEDIUM;
    }
    else firstPlayer = AI;
    
    if (typeid(*player2) == typeid(LocalPlayer)) {
        secondPlayer = LOCAL_PLAYER;
    }
    else if (typeid(*player2) == typeid(DummyComputerPlayer)) {
        secondPlayer = DUMMY;
    }
    else if (typeid(*player2) == typeid(MediumComputerPlayer)) {
        secondPlayer = MEDIUM;
    }
    else secondPlayer = AI;
    
    gameBoard->moveEncoder.putBit(player1->getColour());
    gameBoard->moveEncoder.put3BitNumber(firstPlayer);
    
    gameBoard->moveEncoder.putBit(player2->getColour());
    gameBoard->moveEncoder.put3BitNumber(secondPlayer);
}

void Game::serializeMove(const Move & move) {
    /*
     Encoding each move according the description in header file.
     */
    
    bool bit = false;
    if (move.moveInfo == IS_TRANSFORMATION) {
        bit = true;
    }
    gameBoard->moveEncoder.putBit(bit);
    uint8_t figureCode = NO_FIGURE;
    if (bit) {
        Figure * figure = gameBoard->getBoard()[move.to.y_pos][move.to.x_pos].figure;
        
        if (typeid(*figure) == typeid(Knight)) {
            figureCode = KNIGHT;
        }
        else if(typeid(*figure) == typeid(Bishop)) {
            figureCode = BISHOP;
        }
        else if(typeid(*figure) == typeid(Queen)) {
            figureCode = QUEEN;
        }
        else if(typeid(*figure) == typeid(Castle)) {
            figureCode = CASTLE;
        }
    }
    gameBoard->moveEncoder.put3BitNumber(figureCode);
    gameBoard->moveEncoder.put3BitNumber((uint8_t)move.from.x_pos);
    gameBoard->moveEncoder.put3BitNumber((uint8_t)move.from.y_pos);
    gameBoard->moveEncoder.put3BitNumber((uint8_t)move.to.x_pos);
    gameBoard->moveEncoder.put3BitNumber((uint8_t)move.to.y_pos);
    
}

void Game::loadGame(const string & filename) {
    Deserializer moveDecoder (filename);
    
    if (!moveDecoder.isFileOpen() || moveDecoder.isFileEmpty()) throw runtime_error("Error while reading saved game: Corrupted file");
    // first byte encodes two players and their colours
    bool p1Colour = moveDecoder.getNextBit();
    uint8_t p1Type = moveDecoder.getNext3Bit();
    
    bool p2Colour = moveDecoder.getNextBit();
    uint8_t p2Type = moveDecoder.getNext3Bit();
    
    if (p2Type > AI || p1Type > AI || p1Colour == p2Colour) throw runtime_error("Error while reading saved game: Corrupted file");
    
    if (p1Type == LOCAL_PLAYER) {
        player1 = new LocalPlayer (p1Colour == WHITE ? "Bile" : "Cerne", p1Colour);
    }
    else if (p1Type == DUMMY) {
        player1 = new DummyComputerPlayer ("Lehky pocitac", p1Colour);
    }
    else if (p1Type == MEDIUM) {
        player1 = new MediumComputerPlayer ("Prumerny pocitac", p1Colour);
    }
    else player1 = new AIComputerPlayer ("Umela inteligence", p1Colour);
    
    
    if (p2Type == LOCAL_PLAYER) {
        player2 = new LocalPlayer (p2Colour == WHITE ? "Bile" : "Cerne", p2Colour);
    }
    else if (p2Type == DUMMY) {
        player2 = new DummyComputerPlayer ("Lehky pocitac", p2Colour);
    }
    else if (p2Type == MEDIUM) {
        player2 = new MediumComputerPlayer ("Prumerny pocitac", p2Colour);
    }
    else player2 = new AIComputerPlayer ("Umela inteligence", p2Colour);
    
    encodeGame();
    
    /*
     Load all moves according to the encoding.
     If any coordinate is greater than 7 or the move is incorrect -
     then save file is corrupted
     */
    while (moveDecoder.isBytesLeft()) {
        uint8_t from_x;
        uint8_t from_y;
        uint8_t to_x;
        uint8_t to_y;
        
        Ceil from;
        Ceil to;
        
        bool isTransformed;
        uint8_t figure;
        isTransformed = moveDecoder.getNextBit();
        figure = moveDecoder.getNext3Bit();
        
        from_x = moveDecoder.getNext3Bit();
        from_y = moveDecoder.getNext3Bit();
        
        to_x = moveDecoder.getNext3Bit();
        
        to_y = moveDecoder.getNext3Bit();
        if (from_y > 7 || from_x > 7 || to_y > 7 || to_x > 7 || (figure != NO_FIGURE && figure != KNIGHT
                                                                 && figure != QUEEN && figure != CASTLE
                                                                 && figure != BISHOP)) {
            throw runtime_error("Error while reading saved game: Corrupted file");
        }
        
        from = gameBoard->getBoard()[from_y][from_x];
        if (!from.figure) {
            throw runtime_error("Error while reading saved game: Corrupted file");
        }
        to = gameBoard->getBoard()[to_y][to_x];
        Move move(from, to, from.figure->getColour());
        if (isTransformed) {
            move.moveInfo = IS_TRANSFORMATION;
        }
        move.figureCode = figure;
        if (!gameBoard->isValidMove(move.from, move.to)) {
            throw runtime_error("Error while reading saved game: Corrupted file");
        }
        addMove(move);
    }
    
}

void Game::addMove(Move & move) {
    
    gameBoard->addMove(move);
    
    serializeMove(move);
    
}
void Game::checkDraw(){
    int i = 0;
    for (Figure * f : gameBoard->getFigures()) {
        if (f->isAlive()) {
            i++;
        }
    }
    if (i == 2) {
        throw GameEvent(DRAW_WITHOUT_PATE);
    }
}

    

void Game::startGame() {
    /*
     Game continues until it catches excepction that signalizes the end of a game.
     */
    Player * currentPlayer;
    bool currentColour;
    if (newGame) {
        currentColour = WHITE;
    }
    else {
        if (gameBoard->getMoveHistory().size() > 0) {
            currentColour = !gameBoard->getMoveHistory().back().playerColour;
        }
        else currentColour = WHITE;
    }
    while (true) {
        try {
            checkDraw();
            currentPlayer = player1->getColour() == currentColour ? player1 : player2;
            cout << "Chodi : " << currentPlayer->name << endl;
            Move move = currentPlayer->move();
            addMove(move);
            gameBoard->print_board();
            if (gameBoard->kingIsUnderCheck(!currentColour)) {
                cout << "Sach!" << endl;
            }
            currentColour = !currentColour;
        }
        catch (GameEvent & ge) {
            if (ge.getStatus() == CHECKMATE) {
                cout << "Konec hry : Mat " << (ge.getPlayerColour() == WHITE ? "bilym" : "cernym") << endl;
               
            }
            else if (ge.getStatus() == DRAW) {
                
                cout << "Konec hry : Pat " << (ge.getPlayerColour() == WHITE ? "bilym" : "cernym") << endl;
            }
            else if (ge.getStatus() == DRAW_WITHOUT_PATE) {
                cout << "Konec hry : Remize" << endl;
            }
            else if (ge.getStatus() == SAVE_GAME) {
                string currentDate;
                time_t rawtime;
                struct tm * timeinfo;
                char buffer [80];
                
                time (&rawtime);
                timeinfo = localtime (&rawtime);
                strftime (buffer,80,"%F %H-%M-%S",timeinfo);
                
                currentDate = buffer;
                
                string saveName = "./examples/save " + currentDate + ".chess";
                if (gameBoard->moveEncoder.makeOutputFile(saveName)) cout << "Hra byla uspesne ulozena." << endl;
                else {
                    cout << "Nastala chyba pri ukladani hry." << endl;
                }
            }

            break;
        }
     

    }
}



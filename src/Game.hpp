//
//  Game.hpp
//  chess
//
//  Created by Kirill on 04.05.2022.
//

#ifndef Game_hpp
#define Game_hpp

#include "Board.hpp"
#include "Move.h"
#include "DummyComputerPlayer.hpp"
#include "LocalPlayer.hpp"
#include "MediumComputerPlayer.hpp"
#include "AIComputerPlayer.hpp"

#include "Serialization.hpp"


enum PlayerTypes : uint8_t {
    LOCAL_PLAYER = 0,
    DUMMY = 1,
    MEDIUM = 2,
    AI = 3
};

/**
 * \brief   Class that represents the Game Engine
 *
 * \details It has:
 *          player1, player2 - pointers on 2 players (they can be Local or Computer),
 *          gameboard - pointer on chess board,
 *          status - current game status,
 *          moveEncoder - instance of class Serializer that is necessary to encode all game moves
 */
class Game {
public:
    Game(Player * p1, Player * p2);
    
    Game (const string & savePath);
    ~Game() {
        for (Figure * f : gameBoard->getFigures()) {
            delete f;
        }
        delete gameBoard;
        delete player1;
        delete player2;
    }
    /**
     * \brief   The function to add a record of last move
     *
     * \param[in]    move instace of class Move
     *
     */
    void addMove(Move & move);
    /**
     * \brief   Function starts an infinite cycle and asks each player for move
     *
     */
    void startGame();
    
    
    /**
     * \brief   The function load a game from a binary file
     *
     * \details It will try to load moves one by one from a file and repeat a game
     * \param[in]  filename name of a bianary save file
     */
    void loadGame(const string & filename);
    
private:
    bool newGame;
    Player * player1;
    Player * player2;
    ChessBoard * gameBoard;
    //Serializer moveEncoder;

private:
    /**
     * \brief   The function serialize players move into 2 bytes
     *
     * \details 16 bits (2 bytes) are representing players move.
     *          First bit - if a move was pawn transformation, next 3 bits to which figure, next 6 bits x and y coordinates of start ceil and last
     *          6 bits are x and y coordinates of end ceil. T FFF XXX YYY XXX YYY
     * \param[in]  move instance of class Move
     */
    void serializeMove(const Move & move);
    /**
     * \brief   The function encodes necessery game info into binary file
     *
     * \details Function encodes types of two players and their figures colour and puts that info as first byte into save file
     */
    void encodeGame();
    /**
     * \brief   The function checks if on board left only two king - that means draw
     *
     */
    void checkDraw();
};

#endif /* Game_hpp */

//
//  Player.hpp
//  chess
//
//  Created by Kirill on 06.05.2022.
//

#ifndef Player_hpp
#define Player_hpp

#include "GameEvent.h"
#include <string>
#include "Figure.h"
#include <typeinfo>


#include "Board.hpp"
#include "Move.h"

using namespace std;

/**
 * \brief   Abstract class that represents Player
 *
 * \details It has:
 *          gameBoard - pointer on Board,
 *          colour - colour of players figures
 *          It can be LocalPlayer (user) or Computer Player with different difficulty
 */
class Player {
public:
    string name;
    Player(const string & name, bool colour) :
    name(name),
    colour(colour),
    gameBoard(nullptr)
    {
        
    }
    Player(bool colour, ChessBoard * gameBoard) :
    colour(colour),
    gameBoard(gameBoard)
    {
        
    }
    virtual ~Player() = default;
    /**
     * \brief   Function to make a players move
     *
     * \details This function has different implementation in each Players heir
     *
     * \retval  Instance of class Move
     */
    virtual Move move() = 0;
    
    void setBoard(ChessBoard * board){
        gameBoard = board;
    }
    
    /**
     * \brief   Function to get all moves with status checking
     *
     * \details If player has no moves and his king is under check, that means player lost otherwise it is draw
     *          Will be thrown appropriate exception and it will be processed in game cycle
     */
    vector<Move> getMovesAndCheckLose() const;
    
    vector<Figure *> getFigures() const;
    /**
     * \brief   Find all possible moves.
     *
     * \details This function tries to move each players figure on all chess board ceils.
     *
     * \retval  Vector of instances of class Move.
     */
    vector<Move> getPossibleMoves() const;
    
    bool getColour() const {
        return colour;
    }
    
protected:
    virtual int transfromPawn() const = 0;
    bool colour;
    ChessBoard * gameBoard;
    
};

#endif /* Player_hpp */

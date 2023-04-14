//
//  King.cpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#include "King.hpp"
#include "GameEvent.h"

#ifndef Castle_hpp
#include "Castle.hpp"
#endif

bool King::canMove(Ceil from, Ceil to) const  {
    /*
     If the castling position is detected will be thrown exception
     to make easier its processing without needless "ifs".
     For castling we should check if a castle is on a right position
     and if it is its first move and if the way is free of another figures
     */
    if (from == to) {
        return false;
    }
    int changeX = abs(to.x_pos - from.x_pos);
    int changeY = abs(to.y_pos - from.y_pos);
    if (changeX <= 1 && changeY <= 1) {
        if (!to.figure || to.figure->getColour() != colour) {
            return true;
        }
    }
    
    if (isFirstMove) {
        auto & board = chessBoard->getBoard();
        int y_pos = (colour == WHITE) ? 0 : 7;
        if (to.x_pos == 6 && to.y_pos == y_pos) {
            if (board[y_pos][7].figure) {
                Figure * potencialCastle = board[y_pos][7].figure;
                if ((typeid(*potencialCastle) == typeid(Castle)) && potencialCastle->isFirstMove) {
                    if (potencialCastle->canMove(board[y_pos][7], board[y_pos][5])) {
                        throw GameEvent(IS_SHORT_CASTLING, colour);
                    }
                }
                
            }
        }
        else if (to.x_pos == 2 && to.y_pos == y_pos) {
            if (board[y_pos][0].figure) {
                Figure * potencialCastle = board[y_pos][0].figure;
                if ((typeid(*potencialCastle) == typeid(Castle)) && potencialCastle->isFirstMove) {
                    if (potencialCastle->canMove(board[y_pos][0], board[y_pos][3])) {
                        throw GameEvent(IS_LONG_CASTLING, colour);
                    }
                }
            }
        }
   
    }
    
    return false;
}

//
//  Move.h
//  chess
//
//  Created by Kirill on 06.05.2022.
//

#ifndef Move_h
#define Move_h
#include "Ceil.h"
//#include "Player.hpp"


enum moves : int {
    DEFAULT_MOVE = 0,
    IS_TRANSFORMATION = 1, // signal to transform a pawn
    IS_SHORT_CASTLING = 2, // signal to short castling
    IS_LONG_CASTLING = 3, // signal to long castling
    IS_EN_PASSANT = 4 // signal for "en passant"
};

/**
 * \brief   Class  that represents a move of figure.
 *
 * \details It has two ceils (from and where was made move),
 *          moveInfo (appropriate signal),
 *          figureCode - if it is signal to pawn transformation - to which figure it should be transformed
 */
class Move {
public:
    Move(){}
    Move(const Ceil & from, const Ceil & to, bool colour):
    from(from),
    to(to),
    playerColour(colour),
    moveInfo(DEFAULT_MOVE),
    figureCode(0)
    {
        
    }
    void setStatus(int status) {
        moveInfo = status;
    }
    
    Ceil from;
    Ceil to;
    bool playerColour;
    int moveInfo;
    uint8_t figureCode;
};


#endif /* Move_h */

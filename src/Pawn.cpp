//
//  Pawn.cpp
//  chess
//
//  Created by Kirill on 19.05.2022.
//

#include "Pawn.hpp"
#include "GameEvent.h"
bool Pawn::canMove(Ceil from, Ceil to) const {
    
    /*
     if pawn tries to beat a non existing figure it should be checked
     for "en passant" state and will be thrown appropriate exception
     to make the final check easier in function isValidMove
     */
    if (from == to) {
        return false;
    }
    
    if (colour == WHITE) {
        if (to.x_pos == from.x_pos && to.y_pos == from.y_pos + 1 && !to.figure) {
            return true;
        }
        if (to.x_pos == from.x_pos && to.y_pos == from.y_pos + 2 && isFirstMove && !to.figure) {
            return true;
        }
        if ((to.x_pos == from.x_pos + 1 || to.x_pos == from.x_pos - 1) && to.y_pos == from.y_pos + 1) {
            
            if (to.figure && to.figure->getColour() != colour) return true;
            if (!to.figure && from.y_pos == 4) {
                Figure * potencialPawn = chessBoard->getBoard()[to.y_pos - 1][to.x_pos].figure;
                
                if (potencialPawn && potencialPawn->getColour() != colour && typeid(*potencialPawn) == typeid (Pawn)) {
                    throw GameEvent(IS_EN_PASSANT, colour);
                }
            }
        }
    }
    else {
        if (to.x_pos == from.x_pos && to.y_pos == from.y_pos - 1 && !to.figure) {
            return true;
        }
        if (to.x_pos == from.x_pos && to.y_pos == from.y_pos - 2 && isFirstMove && !to.figure) {
            return true;
        }
        if ((to.x_pos == from.x_pos + 1 || to.x_pos == from.x_pos - 1) && to.y_pos == from.y_pos - 1) {
            if (to.figure && to.figure->getColour() != colour) return true;
            if (!to.figure && from.y_pos == 3) {
                Figure * potencialPawn = chessBoard->getBoard()[to.y_pos + 1][to.x_pos].figure;
                
                if (potencialPawn && potencialPawn->getColour() != colour && typeid(*potencialPawn) == typeid (Pawn)) {
                    throw GameEvent(IS_EN_PASSANT, colour);
                }
            }
        }
    }

    
    return false;
}

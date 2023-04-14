//
//  Castle.cpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#include "Castle.hpp"

bool Castle::canMove(Ceil from, Ceil to) const {
    /*
     It should can move across the straight line and we must check
     if line is free of other figures
     */
    if (from == to) {
        return false;
    }
    
    int changeX = abs(to.x_pos - from.x_pos);
    int changeY = abs(to.y_pos - from.y_pos);
    Ceil toCopy = to;
    if (changeX == 0) {
        if (changeY > 1) {
            while (changeY != 1) {
                to = chessBoard->getBoard()[to.y_pos - from.y_pos < 0 ? to.y_pos + 1 : to.y_pos - 1][to.x_pos];
                changeY = abs(to.y_pos - from.y_pos);
                if (to.figure) {
                    return false;
                }
            }
        }
    }
    else if (changeY == 0) {
        if (changeX > 1) {
            while (changeX != 1) {
                to = chessBoard->getBoard()[to.y_pos][to.x_pos - from.x_pos < 0 ? to.x_pos + 1 : to.x_pos - 1];
                changeX = abs(to.x_pos - from.x_pos);
                if (to.figure) {
                    return false;
                }
            }
            
        }
    }
    else return false;
    if (!toCopy.figure || toCopy.figure->getColour() != colour) {
        return true;
    }
    return false;
}

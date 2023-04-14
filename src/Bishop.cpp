//
//  Bishop.cpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#include "Bishop.hpp"

bool Bishop::canMove(Ceil from, Ceil to) const{
    /*
     It should can move across the diagonal and we must check
     if diagonal is free of other figures
     */
    if (from == to) {
        return false;
    }
    
    int changeX = to.x_pos - from.x_pos;
    int changeY = to.y_pos - from.y_pos;
    
    Ceil toCopy = to;
    if (changeX == changeY) {
        // checking every ceil on diagonal
            while (abs(changeX) != 1) {
                if (changeX > 0) {
                    
                    to = chessBoard->getBoard()[to.y_pos - 1][to.x_pos - 1];
                }
                else to = chessBoard->getBoard()[to.y_pos + 1][to.x_pos + 1];
                changeX = to.x_pos - from.x_pos;
                if (to.figure) {
                    return false;
                }
            }
        
    }
    else if (abs(changeX) == abs(changeY)) {
        // checking every ceil on diagonal
        while (abs(changeY) != 1) {
            if (changeY > 0) {
                to = chessBoard->getBoard()[to.y_pos - 1][to.x_pos + 1];
            }
            else to = chessBoard->getBoard()[to.y_pos + 1][to.x_pos - 1];
            changeY = to.y_pos - from.y_pos;
            if (to.figure) {
                return false;
            }
        }
    }
    else return false;
    
    if (!toCopy.figure || toCopy.figure->getColour() != colour) {
        return true;
    }

    return false;

}

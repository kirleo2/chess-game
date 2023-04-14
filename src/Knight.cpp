//
//  Knight.cpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#include "Knight.hpp"

bool Knight::canMove(Ceil from, Ceil to) const {
    if (from == to) {
        return false;
    }
    
    int changeX = abs(to.x_pos - from.x_pos);
    int changeY = abs(to.y_pos - from.y_pos);
    if ((changeX == 1 && changeY == 2) || (changeX == 2 && changeY == 1)) {
        if (!to.figure || to.figure->getColour() != colour) {
            return true;
        }
    }
    
    return false;
}

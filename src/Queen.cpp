//
//  Queen.cpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#include "Queen.hpp"
#ifndef Bishop_hpp
#include "Bishop.hpp"
#endif
#ifndef Castle_hpp
#include "Castle.hpp"
#endif

bool Queen::canMove(Ceil from, Ceil to) const {
    /*
     Queen joins moving logic of Castle and Bishop
     So we can easily check if queen can move by creating a temp instance of
     castle and bishop
     */
    if (from == to) {
        return false;
    }
    
    Castle tmp_castle (colour, chessBoard);
    Bishop tmp_bishop (colour, chessBoard);
    return tmp_castle.canMove(from, to) || tmp_bishop.canMove(from, to);
}

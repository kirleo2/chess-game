//
//  Pawn.hpp
//  chess
//
//  Created by Kirill on 19.05.2022.
//

#ifndef Pawn_hpp
#define Pawn_hpp

#ifndef Figure_hpp
#include "Figure.h"
#endif

/**
 * \brief Class representing chess figure - Pawn
 *
 */
class Pawn : public Figure{
    
public:
    Pawn (bool colour, ChessBoard * board, int x = 0, int y = 0) : Figure(colour, board, x, y){
        if (colour) icon = "♙";
        else icon = "♟";
    }
    virtual Figure * clone() const override {
        return new Pawn(*this);
    }
    virtual bool canMove (Ceil from, Ceil to) const override;
};
#endif /* Pawn_hpp */

//
//  Knight.hpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#ifndef Knight_hpp
#define Knight_hpp

#ifndef Figure_hpp
#include "Figure.h"
#endif

/**
 * \brief Class representing chess figure - Knight
 *
 */
class Knight : public Figure{
public:
    Knight (bool colour, ChessBoard * board, int x = 0, int y = 0) : Figure(colour, board, x, y) {
        if (colour) icon = "♘";
        else icon = "♞";
    }
    virtual Figure * clone() const override {
        return new Knight(*this);
    }
    virtual bool canMove (Ceil from, Ceil to) const override;
    
};

#endif /* Knight_hpp */

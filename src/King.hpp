//
//  King.hpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#ifndef King_hpp
#define King_hpp

#ifndef Figure_hpp
#include "Figure.h"
#endif

/**
 * \brief Class representing chess figure - King
 *
 */
class King : public Figure{
public:
    King (bool colour, ChessBoard * board, int x = 0, int y = 0) : Figure(colour, board, x, y) {
        if (colour) icon = "♔";
        else icon = "♚";
    }
    virtual Figure * clone() const override {
        return new King(*this);
    }
    virtual bool canMove (Ceil from, Ceil to) const override;
};
#endif /* King_hpp */

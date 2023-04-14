//
//  Queen.hpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#ifndef Queen_hpp
#define Queen_hpp


#ifndef Figure_hpp
#include "Figure.h"
#endif

/**
 * \brief Class representing chess figure - Queen
 *
 */
class Queen : public Figure{
public:
    Queen (bool colour, ChessBoard * board, int x = 0, int y = 0) : Figure(colour, board, x, y) {
        if (colour) icon = "♕";
        else icon = "♛";
    }
    virtual Figure * clone() const override {
        return new Queen(*this);
    }
    virtual bool canMove (Ceil from, Ceil to) const override;
};
#endif /* Queen_hpp */

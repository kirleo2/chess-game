//
//  Castle.hpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#ifndef Castle_hpp
#define Castle_hpp

#ifndef Figure_hpp
#include "Figure.h"
#endif
/**
 * \brief Class representing chess figure - Castle
 *
 */
class Castle : public Figure{
public:
    Castle (bool colour, ChessBoard * board, int x = 0, int y = 0) : Figure(colour, board, x, y) {
        if (colour) icon = "♖";
        else icon = "♜";
    }
    virtual Figure * clone() const override {
        return new Castle(*this);
    }
    virtual bool canMove (Ceil from, Ceil to) const override;
};

#endif /* Castle_hpp */

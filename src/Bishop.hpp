
#ifndef Bishop_hpp
#define Bishop_hpp

#ifndef Figure_hpp
#include "Figure.h"
#endif

/**
 * \brief Class representing chess figure - Bishop
 *
 */
class Bishop : public Figure{
public:
    Bishop (bool colour, ChessBoard * board, int x = 0, int y = 0) : Figure(colour, board, x, y) {
        if (colour) icon = "♗";
        else icon = "♝";
    }
    virtual Figure * clone() const override {
        return new Bishop(*this);
    }
    virtual bool canMove (Ceil from, Ceil to) const override;
};



#endif

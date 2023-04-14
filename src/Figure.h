//
//  Figure.hpp
//  chess
//
//  Created by Kirill on 25.03.2022.
//

#ifndef Figure_hpp
#define Figure_hpp
#include <string>
#include <typeinfo>

#ifndef Board_hpp
#include "Board.hpp"
#endif


using namespace std;
enum colours : bool {
    BLACK=false,
    WHITE=true
};

/**
 * \brief   Abstract class  that represents a chess Figure.
 *
 * \details It has :
 * icon - fugure's icon
 * isFirstMove - flag if figure has moved
 * chessBoard - pointer to Board. It is necessary for canMove logic
 * colour - colour of the figure
 * is_alive - flag if figure has been killed
 * currentPosition - pair of x and y coordinates
 *
 *
 */
class Figure {
public:
    
    string icon;
    bool isFirstMove;
    Figure(bool colour, class ChessBoard * board, int x = 0, int y = 0):
    chessBoard(board),
    colour(colour)
    {
        is_alive = true;
        isFirstMove = true;
        updateCurrentPosition(x, y);
    };
    virtual ~Figure() = default;
    /**
     * \brief   The function to check if figure can be moved
     *
     * \details For each figure it has it own implementation.
     *          It is important to have a pointer on board to check if
     *          other figures are on the way
     *
     * \param[in]    from instance of class Ceil (start ceil)
     * \param[in]    to instance of class Ceil (end ceil)
     *
     * \return        The boolean value.
     *
     * \retval        TRUE   The figure can move
     * \retval        FALSE    The figure can not move
     */
    virtual bool canMove(class Ceil from, Ceil to) const = 0;
    
    /**
     * \brief   The function to make a copy of figure
     *
     * \return        Pointer on class Figure, that is a copy of itself
     */
    virtual Figure * clone() const = 0;
    /**
     * \brief   The function to get figures colour
     *
     * \return        The boolean value.
     *
     * \retval        TRUE   The colour is WHITE
     * \retval        FALSE    The figure is BLACK
     */
    bool getColour() const {
        return colour;
    }
    /**
     * \brief   The function to update current figures position
     */
    void updateCurrentPosition(int x, int y) {
        current_position.first = x;
        current_position.second = y;
    }
    /**
     * \brief   The function get current figures position
     */
    pair<int, int> getCurrentPosition() const{
        return current_position;
    }
    /**
     * \brief   The function to kill figure
     */
    void kill() {
        is_alive = false;
    }
    /**
     * \brief   The function to revive figure (it is necessecary to undo the board changed by move validation)
     */
    void revive() {
        is_alive = true;
    }
    /**
     * \brief   The function to check if figure is alive
     */
    bool isAlive() const{
        return is_alive;
    }
    
protected:
    ChessBoard * chessBoard;
    bool is_alive;
    bool colour;
    
    pair<int, int> current_position;
    
};



#endif

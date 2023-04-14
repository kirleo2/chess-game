//
//  Board.hpp
//  chess
//
//  Created by Kirill on 25.03.2022.
//

#ifndef Board_hpp
#define Board_hpp
#include <vector>
#include <iostream>
#include "Ceil.h"
#include "Move.h"
#include "Serialization.hpp"
#include <typeinfo>
using namespace std;


enum FigureCodes : uint8_t {
    NO_FIGURE = 0,
    KNIGHT = 1,
    BISHOP = 2,
    QUEEN = 3,
    CASTLE = 4,
    KING = 5
};
/**
 * \brief Class representing chess board
 *
 */
class ChessBoard{
public:
    Serializer moveEncoder;
    ChessBoard(){}
    ~ChessBoard(){}
    /**
     * \brief   The function to prepare a chess board.
     *
     * \details This function gets recieves two Ceils on chess board and validates, if
     *          a figure can be moved and if move corresponds with game rules. At first it checks
     */
    void setStart();
    
    /**
     * \brief   The function to print a chess board into terminal.
     *
     */
    void print_board() const;
    
    /**
     * \brief   The function to validate players move.
     *
     * \details This function gets recieves two Ceils on chess board and validates, if
     *          a figure can be moved and if move corresponds with game rules. At first it checks
     *          if the figure can move and the if a King is under the check.
     *
     *
     * \param[in]    from    Instance of class Ceil represents from where the figure is being moved.
     * \param[in]    to     Instance of class Ceil represents where to the figure is being moved
     *
     * \return        The boolean value.
     *
     * \retval        TRUE   The move is correct.
     * \retval        FALSE    The move is not correct.
     */
    
    bool isValidMove(const Ceil & from, const Ceil & to);
    
    
    vector<vector <Ceil> > & getBoard() {
        return board;
    }
    /**
     * \brief   The function to add players move.
     *
     * \details This function gets an instance of class Move and makes all necessary changes on board.
     *
     * \param[in]    move instance of class Move
     *
     */
    
    void addMove(const Move & move);
    /**
     * \brief   The function to process players move
     *
     * \details This function gets an instance of class Move and sets a move status depending on constants in Move.h
     *
     * \param[in]    move instance of class Move
     *
     */
    void processMove(Move & move) const;
    /**
     * \brief   The function to check if players ceil is under attack
     *
     * \details This function gets an instance of class Ceil and checks if any of opponents figure can move there.
     *
     * \param[in]    ceil instance of class Ceil (players ceil)
     * \param[in]    attackColour colour of opponent
     *
     * \return        The boolean value.
     *
     * \retval        TRUE   The ceil is under attack
     * \retval        FALSE    The ceil is not under attack
     */
    bool ceilIsUnderAttack(const Ceil & ceil, bool attackColour) const;
    /**
     * \brief   The function get a reference on a vector of all Figures on board
     *
     *
     * \return        Vector of Figures
     */
    const vector<Figure * > & getFigures () const {
        return figures;
    }
    /**
     * \brief   The function to check if King is under check
     *
     * \details This function checks every opponents figure if it can move on the ceil where the King is.
     *
     * \param[in]    kingColour colour of King
     *
     * \return        The boolean value.
     *
     * \retval        TRUE   The King is under check
     * \retval        FALSE    The King is not under check
     *
     */
    bool kingIsUnderCheck(bool kingColour) const;
    
    /**
     * \brief   The function build a ceil with Figure
     *
     *
     * \param[in]    figure pointer on Figure
     
     * \return        Instance of class Ceil with pointer on figure and its coordinates.
     */
    Ceil getFigureCeil(Figure * figure) const;
    
    /**
     * \brief   The function undo last Move
     *
     *
     * \details This function is "opposite" of addMove because it is trying to undo all changes that was made with last move.
     */
    void undoBoard();
    
    const vector<Move> & getMoveHistory() {
        return moveHistory;
    }
    Move getLastMove() {
        return moveHistory.back();
    }

private:
    vector<Move> moveHistory;
    vector<vector <Ceil> > board;
    vector<Figure *> figures;

private:
    /**
     * \brief   The function to get a pointer on King
     *
     *
     * \param[in]    colour colour of King
     
     * \return        Pointer on King
     */
    Figure * getKing(bool colour) const;
    
    /**
     * \brief   The function to add a new Figure on board
     *
     * \details This function gets a pointer on Figure and adds it to vector
     *
     * \param[in]    figure pointer on class Figure
     *
     */
    void addFigure(Figure * figure);
    
};
#endif

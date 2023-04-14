//
//  AIComputerPlayer.hpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#ifndef AIComputerPlayer_hpp
#define AIComputerPlayer_hpp

#ifndef MediumComputerPlayer_hpp
#include "MediumComputerPlayer.hpp"
#endif

/**
 * \brief Class representing AI Computer
 *
 * \details This class represents AI Computer that can find best move in MINIMAX_DEPTH + 1 depth using minimax algorithm
 *          It heirs from MediumComputerPlayer to get function evaluateBoard and its constants.
 *
 */
class AIComputerPlayer: public MediumComputerPlayer  {
public:
    AIComputerPlayer (const string & name, bool colour) : MediumComputerPlayer(name, colour) {}
    AIComputerPlayer (bool colour, ChessBoard * gameBoard) : MediumComputerPlayer(colour, gameBoard) {}
    /**
     * \brief Function to make computers move
     *
     * \details Using minimax function will be found best move in depth MINIMAX_DEPTH + 1.
     *          If it will be more than 1, then it will be chosen randomly to make a game unique.
     * \retval  Instance of class Move
     */
    virtual Move move() override;
    

private:
    const int MINIMAX_DEPTH = 2;
    /**
     * \brief Function to evaluate move in any depth
     *
     * \details  Using recursion algorithm will try to find the best move.
                 As current player we want to make a best move, but opponent
                 also will try to make a best move for him (worst for current player).
                 So we need to maximize value of current player move and minimize value
                 of opponents move (pretending opponent is trying to do his best too).
     * \retval  Integer - value of move
     */
    int minimax(int depth, bool playerColour);
};

#endif /* AIComputerPlayer_hpp */

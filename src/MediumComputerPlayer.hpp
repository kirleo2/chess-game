//
//  MediumComputerPlayer.hpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#ifndef MediumComputerPlayer_hpp
#define MediumComputerPlayer_hpp


#ifndef Player_hpp
#include "Player.hpp"
#endif

/**
 * \brief Class representing Medium Computer
 *
 * \details This class represents Medium Computer that always will beat opponents figure if has possibility,
 *          otherwise logic is as Dummy Computer
 *
 */
class MediumComputerPlayer: public Player {
public:
    MediumComputerPlayer (const string & name, bool colour) : Player(name, colour) {}
    MediumComputerPlayer (bool colour, ChessBoard * gameBoard) : Player(colour, gameBoard) {}
    
    /**
     * \brief Function to make computers move
     *
     * \details Will be evaluated all moves and it will choose random best
     *
     * \retval  Instance of class Move
     */
    
    virtual Move move() override;
    
    virtual int transfromPawn() const override {
        return QUEEN;
    };

protected:
    
    const int MIN_VALUE = -9999;
    const int MAX_VALUE = 9999;
    
    // constants to evaluate position after move
    enum figure_prices : int {
        PAWN_PRICE = 10,
        KNIGHT_PRICE = 30,
        BISHOP_PRICE = 30,
        CASTLE_PRICE = 50,
        QUEEN_PRICE = 90,
        KING_PRICE = 900,
        CHECK_PRICE = 9,
        CASTLING_PRICE = 5
    };
protected:
/**
 * \brief Function to evaluate position after move
 *
 * \details Will be added all players figure prices and substracted all opponents figure prices
 *
 * \retval  Integer - current average position value
 */
    int evaluateBoard();
};



#endif /* MediumComputerPlayer_hpp */

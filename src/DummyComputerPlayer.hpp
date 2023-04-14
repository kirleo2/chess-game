//
//  DummyComputerPlayer.hpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#ifndef DummyComputerPlayer_hpp
#define DummyComputerPlayer_hpp

#ifndef Player_hpp
#include "Player.hpp"
#endif

/**
 * \brief Class representing Dummy Computer
 *
 * \details This class represents Dummy Computer that makes only random moves
 *
 */
class DummyComputerPlayer: public Player {
public:
    DummyComputerPlayer (const string & name, bool colour) : Player(name, colour) {}
    /**
     * \brief   Make DummyComputers move
     *
     * \details This function will make random move
     *
     * \retval       Instances of class Move.
     */
    virtual Move move() override;
    /**
     * \brief   Function to transform Pawn into another figure
     *
     * \details This function will always return code of the Queen
     *
     * \retval       Integer - code of Queen
     */
    virtual int transfromPawn() const override {
        return QUEEN;
    }
};

#endif /* DummyComputerPlayer_hpp */

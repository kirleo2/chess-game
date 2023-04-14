

#ifndef LocalPlayer_hpp
#define LocalPlayer_hpp

#ifndef Player_hpp
#include "Player.hpp"
#endif
#include <unordered_map>

/**
 * \brief Class representing Local Player
 *
 * \details This class allows to user making moves by console input
 *
 */
class LocalPlayer: public Player {
public:
    LocalPlayer (const string & name, bool colour) : Player(name, colour) {}
    
    /**
     * \brief   Make Players move.
     *
     * \details This function gets coordinates from user to make a move.
     *
     * \retval        Instance of class Move.
     */
    virtual Move move() override;
    /**
     * \brief   Function to transform a pawn into another Figure
     *
     * \details This function gets coordinates from user to make a move.
     *
     * \retval  integer - the code of Figure
     */
private:
    virtual int transfromPawn() const override;
};
#endif

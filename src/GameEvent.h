//
//  GameEvent.h
//  chess
//
//  Created by Kirill on 17.05.2022.
//

#ifndef GameEvent_h
#define GameEvent_h
#include <stdexcept>
using namespace std;


enum status : int {
    CHECKMATE = 1,
    DRAW = 2,
    SAVE_GAME = 3,
    END_GAME = 4,
    DRAW_WITHOUT_PATE
};
/**
 * \brief   Class representing a game event
 *
 * \details It is used primary to throw and catch exceptions in program functions.
 *          For example to declare defeat or draw.
 */
class GameEvent : public exception {
    int status;
    bool playerColour;
public:
    GameEvent(int status, bool playerColour=true) :
    status(status),
    playerColour(playerColour)
    {
        
    }
    int getStatus() {
        return status;
    }
    int getPlayerColour() {
        return playerColour;
    }

};


#endif /* GameEvent_h */

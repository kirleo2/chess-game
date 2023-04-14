//
//  DummyComputerPlayer.cpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#include "DummyComputerPlayer.hpp"
#include "GameEvent.h"


Move DummyComputerPlayer::move(){
    
    auto moves = getMovesAndCheckLose();
    
    int randomMove = rand() % moves.size();

    Move move = moves[randomMove];
    gameBoard->processMove(move);
    if (move.moveInfo == IS_TRANSFORMATION) {
        move.figureCode = transfromPawn();
    }

    return move;
}


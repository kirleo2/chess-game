//
//  AIComputerPlayer.cpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#include "AIComputerPlayer.hpp"
#include "GameEvent.h"


Move AIComputerPlayer::move() {
    
    auto moves = getMovesAndCheckLose();
    
    int value = MIN_VALUE - 1;
    vector<Move> bestMoves;
    /*
     Each potencial move will be evaluated in depth MINIMAX_DEPTH.
     All best moves will be collected into vector and then randomly chosen.
     */
    for (Move & move : moves) {
        gameBoard->processMove(move);
        if (move.moveInfo==IS_TRANSFORMATION) {
            move.figureCode = transfromPawn();
        }
        gameBoard->addMove(move);
        int moveValue = minimax(MINIMAX_DEPTH, !colour);
        if (moveValue > value) {
            value = moveValue;
            bestMoves.clear();
            bestMoves.push_back(move);
        }
        else if (moveValue == value) bestMoves.push_back(move);
        gameBoard->undoBoard();
    }
    
    int randomMove = rand() % bestMoves.size();
    Move bestMove = bestMoves[randomMove];
    
    return bestMove;
}

int AIComputerPlayer::minimax(int depth, bool playerColour) {
    /*
     We change player colour one by one and trying to maximaze or minimize value of position.
     */
    if (depth == 0) {
        return evaluateBoard();
    }
    
    if (playerColour == colour) {
        int value = MIN_VALUE;
        for (Move & move : getPossibleMoves()) {
            gameBoard->processMove(move);
            if (move.moveInfo == IS_TRANSFORMATION) {
                move.figureCode = transfromPawn();
            }
            gameBoard->addMove(move);
            // recursevily call minimax with substracted depth for each move that has producted and change player colour
            value = max(value, minimax(depth - 1, !playerColour));
            gameBoard->undoBoard();
        }
        return value;
    }
    else {
        int value = MAX_VALUE;
        AIComputerPlayer opponent (playerColour, gameBoard);
        for (Move & move : opponent.getPossibleMoves()) {
            gameBoard->processMove(move);
            if (move.moveInfo==IS_TRANSFORMATION) {
                move.figureCode = transfromPawn();
            }
            gameBoard->addMove(move);
            // recursevily call minimax with substracted depth for each move that has producted and change player colour
            value = min (value, minimax(depth - 1, !playerColour));
            gameBoard->undoBoard();
            
        }
        if (value == MAX_VALUE && !gameBoard->kingIsUnderCheck(!colour)) {
            // it will return MAX_VALUE if opponent has no moves but draw is not a good end
            return MIN_VALUE;
        }
         
        return value;
    }
}

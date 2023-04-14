//
//  MediumComputerPlayer.cpp
//  chess
//
//  Created by Kirill on 20.05.2022.
//

#include "MediumComputerPlayer.hpp"
#include "GameEvent.h"
#include "King.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"
#include "Castle.hpp"
#include "Pawn.hpp"
#include "Knight.hpp"
#include "math.h"


Move MediumComputerPlayer::move() {
    auto moves = getMovesAndCheckLose();
    
    int value = MIN_VALUE;
    vector<Move> bestMoves;
    
    for (Move & move : moves) {
        gameBoard->processMove(move);
        if (move.moveInfo==IS_TRANSFORMATION) {
            move.figureCode = transfromPawn();
        }
        gameBoard->addMove(move);
        // evaluate each move and make a vector of best to choose randomly (this is necessary to make every game unique)
        int moveValue = evaluateBoard();
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


int MediumComputerPlayer::evaluateBoard() {
    MediumComputerPlayer opponent (!colour, gameBoard);
    int value = 0;
    /*
     Current board position will be evaluated according to evaluating constants.
     */
    Figure * from = gameBoard->getLastMove().from.figure;
    if (typeid (*from) == typeid(King)) {
        value -= CASTLING_PRICE;
    }
    if (gameBoard->getLastMove().moveInfo == IS_LONG_CASTLING || gameBoard->getLastMove().moveInfo == IS_LONG_CASTLING) {
        value += CASTLING_PRICE;
    }
    if (gameBoard->kingIsUnderCheck(!colour)) {
        value += CHECK_PRICE;
    }
    if (gameBoard->kingIsUnderCheck(colour)) {
        value -= CHECK_PRICE;
    }
    
    for (Figure * f : getFigures()) {
        if (f->isAlive()) {
            if (typeid(*f) == typeid(King)) {
                value += KING_PRICE;
            }
            else if (typeid(*f) == typeid(Bishop)) {
                value += BISHOP_PRICE;
            }
            else if (typeid(*f) == typeid(Queen)) {
                value += QUEEN_PRICE;
            }
            else if (typeid(*f) == typeid(Castle)) {
                value += CASTLE_PRICE;
            }
            else if (typeid(*f) == typeid(Pawn)) {
                value += PAWN_PRICE;
            }
            else if (typeid(*f) == typeid(Knight)) {
                value += KNIGHT_PRICE;
            }
        }
    }
    for (Figure * f : opponent.getFigures()) {
        if (f->isAlive()) {
            if (typeid(*f) == typeid(King)) {
                value -= KING_PRICE;
            }
            else if (typeid(*f) == typeid(Bishop)) {
                value -= BISHOP_PRICE;
            }
            else if (typeid(*f) == typeid(Queen)) {
                value -= QUEEN_PRICE;
            }
            else if (typeid(*f) == typeid(Castle)) {
                value -= CASTLE_PRICE;
            }
            else if (typeid(*f) == typeid(Pawn)) {
                value -= PAWN_PRICE;
            }
            else if (typeid(*f) == typeid(Knight)) {
                value -= KNIGHT_PRICE;
            }
        }
    }
    return value;
}

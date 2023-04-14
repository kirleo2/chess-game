//
//  Player.cpp
//  chess
//
//  Created by Kirill on 22.05.2022.
//

#include "Player.hpp"

vector<Move> Player::getMovesAndCheckLose() const {
    auto moves = getPossibleMoves();
    if (moves.size() == 0) {
        if (gameBoard->kingIsUnderCheck(colour)) {
            throw GameEvent(CHECKMATE, colour);
        }
        throw GameEvent(DRAW, colour);
    }
    return moves;
}

vector<Figure *> Player::getFigures() const {
    vector<Figure *> playerFigures;
    for (Figure * f : gameBoard->getFigures()) {
        if (f->getColour() == colour) {
            playerFigures.push_back(f);
        }
    }
    return playerFigures;
}

vector<Move> Player::getPossibleMoves() const {
    vector<Move> allMoves;
    for (Figure * f : getFigures()) {
        if (f->isAlive()) {
            Ceil from = gameBoard->getFigureCeil(f);
            for (int i = 0; i < 8; i++) {
                for (int k = 0; k < 8; k++) {
                    if (gameBoard->isValidMove(from, gameBoard->getBoard()[i][k])) {
                        Move possibleMove = Move(from, gameBoard->getBoard()[i][k], colour);
                        allMoves.push_back(possibleMove);
                    }
                }
            }
        }
    }
    return allMoves;
}

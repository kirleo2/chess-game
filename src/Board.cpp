//
//  Board.cpp
//  chess
//
//  Created by Kirill on 25.03.2022.
//

#include "Board.hpp"
#include "Ceil.h"
#include "GameEvent.h"

#include "Pawn.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Castle.hpp"


bool ChessBoard::isValidMove(const Ceil & from, const Ceil & to) {
    
    bool returnValue = true;
    
    if (from == to) {
        return false;
    }
    if (!from.figure) {
        return false;
    }
    // figure that is being moved
    Figure * figure = from.figure;
    
    // colour of current player, negation is an opponents colour
    bool colour = figure->getColour();
    
    try {
        if (!from.figure->canMove(from, to)) {
            return false;
        }
    }
    // function canMove will throw exception, to get rid of useless "ifs" here
    catch (GameEvent & ge) {
        if (ge.getStatus() == IS_SHORT_CASTLING) {
            int y_pos = (ge.getPlayerColour() == WHITE) ? 0 : 7;
           
            for (int x_pos = 4; x_pos < 8; x_pos++) {
                if (ceilIsUnderAttack(Ceil(x_pos, y_pos), !colour)) {
                    return false;
                }
            }
        }
        else if (ge.getStatus() == IS_LONG_CASTLING ) {
            int y_pos = (ge.getPlayerColour() == WHITE) ? 0 : 7;
           
            for (int x_pos = 0; x_pos < 4; x_pos++) {
                if (ceilIsUnderAttack(Ceil(x_pos, y_pos), !colour)) {
                    return false;
                }
            }
        }
        else if (ge.getStatus() == IS_EN_PASSANT) {
            Move lastMove = moveHistory.back();
            if (abs(lastMove.from.y_pos - lastMove.to.y_pos) == 2 && typeid(*lastMove.from.figure) == typeid(Pawn) && lastMove.from.x_pos == to.x_pos ) {
                return true;
            }
            else return false;
        }
        return true;
    }
    // backup board
    auto boardCopy = board;
    
    
    figure->updateCurrentPosition(to.x_pos, to.y_pos);
    // figure that is under attack
    Figure * killed = to.figure;
    if (killed) {
        killed->kill();
    }
    
    board[from.y_pos][from.x_pos].figure = nullptr;
    board[to.y_pos][to.x_pos].figure = figure;
    
    // if a King was left under check (the opponents figure can move on ceil, where the King is)
    
    if (kingIsUnderCheck(colour)) {
        returnValue = false;
    }
    
    // undo board changed
    if (killed) {
        killed->revive();
    }
    figure->updateCurrentPosition(from.x_pos, from.y_pos);
    board = boardCopy;
    return returnValue;
}

void ChessBoard::processMove(Move & move) const{
    Ceil from = move.from;
    Ceil to = move.to;
    
    if (from.figure) {
        if (typeid(*from.figure) == typeid(Pawn) ) {
            // if pawn reachs 7 or 0 y coordinate it must be transformed
            if ((to.y_pos == 0 || to.y_pos == 7)) move.setStatus(IS_TRANSFORMATION);
            else if (abs(to.x_pos - from.x_pos) == 1 && !to.figure) move.setStatus(IS_EN_PASSANT);
        }
        else if (typeid (*from.figure) == typeid (King)) {
            // if king want to move on 2 or 6 x coordinate and it is its first move then it is castling
            if (from.figure->isFirstMove && (to.x_pos == 2 || to.x_pos == 6)) {
                if (to.x_pos == 2) move.setStatus(IS_LONG_CASTLING);
                else move.setStatus(IS_SHORT_CASTLING);
            }
            
        }
    }
}

void ChessBoard::addMove(const Move & move)  {
    moveHistory.push_back(move);
    Figure * figure = move.from.figure;
    /*
     if castling then additionaly move castle
     if pawn transformation then make a new figure that player decided to choose
     if it is en passant then kill a pawn
     */
    if (move.moveInfo == IS_SHORT_CASTLING) {
        int y_pos = (move.playerColour == WHITE) ? 0 : 7;
        Figure * castle = board[y_pos][7].figure;
        castle->isFirstMove = false;
        board[y_pos][7].figure = nullptr;
        board[y_pos][5].figure = castle;
        castle->updateCurrentPosition(5, y_pos);
    }
    else if (move.moveInfo == IS_LONG_CASTLING) {
        int y_pos = (move.playerColour == WHITE) ? 0 : 7;
        Figure * castle = board[y_pos][0].figure;
        castle->isFirstMove = false;
        board[y_pos][0].figure = nullptr;
        board[y_pos][3].figure = castle;
        castle->updateCurrentPosition(3, y_pos);
    }
    else if (move.moveInfo == IS_TRANSFORMATION) {
        figure->kill();
        uint8_t figureCode = move.figureCode;
        if (figureCode == KNIGHT) {
            figure = new Knight(move.playerColour, this);
        }
        else if (figureCode == BISHOP) {
            figure = new Bishop(move.playerColour, this);
        }
        else if (figureCode == QUEEN) {
            figure = new Queen(move.playerColour, this);
        }
        else if (figureCode == CASTLE) {
            figure = new Castle(move.playerColour, this);
        }
        
        addFigure(figure);
        
    }
    else if(move.moveInfo == IS_EN_PASSANT) {
        int y_pos = move.playerColour == WHITE ? move.to.y_pos - 1 : move.to.y_pos + 1;
        Figure * killedPawn = board[y_pos][move.to.x_pos].figure;
        killedPawn->kill();
        board[y_pos][move.to.x_pos].figure = nullptr;
        
    }
    
    board[move.from.y_pos][move.from.x_pos].figure = nullptr;
    
    if (move.to.figure) {
        move.to.figure->kill();
    }
    
    

    board[move.to.y_pos][move.to.x_pos].figure = figure;

    figure->updateCurrentPosition(move.to.x_pos, move.to.y_pos);
    figure->isFirstMove = false;
}

bool ChessBoard::ceilIsUnderAttack(const Ceil & ceil, bool attackColour) const {
    for (Figure * f : figures) {
        if (f->getColour() == attackColour && f->isAlive()) {
            if (f->canMove(getFigureCeil(f), ceil)) {
                return true;
            }
        }
    }
    return false;
}
bool ChessBoard::kingIsUnderCheck(bool kingColour) const {
    
    for (Figure * f : figures) {
        if (f->getColour() == !kingColour && f->isAlive()) {
            if (f->canMove(getFigureCeil(f), getFigureCeil(getKing(kingColour)))) {
       
                return true;
            }
        }
    }
    return false;
    
}

Figure * ChessBoard::getKing(bool colour) const {
    for (Figure * f : figures) {
        if (typeid(*f) == typeid(King) && f->getColour() == colour ) {
            return f;
        }
    }
    return nullptr;
}
Ceil ChessBoard::getFigureCeil(Figure * figure) const {
    
    return Ceil (figure->getCurrentPosition().first, figure->getCurrentPosition().second, figure);
}
void ChessBoard::setStart() {
    
    for (int i = 0; i < 8; i++) {
        board.push_back(vector<Ceil> (8));
        for (int k = 0; k < 8; k++) {
            board[i][k] = Ceil(k, i);
        }
        
    }
    for (int i = 0; i < 8; i++){
        board[1][i] = Ceil(i, 1, new Pawn(true, this, i, 1));
        board[6][i] = Ceil(i, 6, new Pawn(false, this, i, 6));
    }
    board[0][0] = Ceil(0, 0, new Castle(true, this, 0, 0));
    board[0][7] = Ceil(7, 0, new Castle(true, this, 7, 0));
    board[0][1] = Ceil(1, 0, new Knight(true, this, 1, 0));
    board[0][6] = Ceil(6, 0, new Knight(true, this, 6, 0));
    board[0][2] = Ceil(2, 0,  new Bishop(true, this, 2, 0));
    board[0][5] = Ceil(5, 0,  new Bishop(true, this, 5, 0));

    board[0][3] = Ceil(3, 0, new Queen(true, this, 3, 0));
    board[0][4] = Ceil(4, 0, new King(true, this, 4, 0));

    board[7][0] = Ceil(0, 7, new Castle(false, this, 0, 7));
    board[7][7] = Ceil(7, 7, new Castle(false, this, 7, 7));
    board[7][1] = Ceil(1, 7, new Knight(false, this, 1, 7));
    board[7][6] = Ceil(6, 7, new Knight(false, this, 6, 7));
    board[7][2] = Ceil(2, 7, new Bishop(false, this, 2, 7));
    board[7][5] = Ceil(5, 7, new Bishop(false, this, 5, 7));

    board[7][3] = Ceil(3, 7, new Queen(false, this, 3, 7));
    board[7][4] = Ceil(4, 7, new King(false, this, 4, 7));
    
    
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 8; k++) {
            if (board[i][k].figure) {
                figures.push_back(board[i][k].figure);
            }
        }
    }
    
  
}


void ChessBoard::addFigure(Figure * figure) {
    figures.push_back(figure);
}


void ChessBoard::print_board() const{
    //system("clear");
    for (int i = 7; i >= 0; i--) {
        cout << i + 1 << "|";
        for (int k = 0; k < 8; k++) {
            if (board[i][k].figure) cout << board[i][k].figure->icon << " ";
            else {
                if (i % 2 != 0) {
                    if (k % 2 != 0) cout << " " << " ";
                    else cout << "#" << " ";
                }
                else {
                    if (k % 2 == 0) cout << " "<< " ";
                    else cout << "#"<< " ";
                } 
            }
        }
        cout << endl;
    }
    cout << "  ";
    for (char i = 'a'; i < 'i'; i++) {
        cout << "--";
    }
    cout << endl;
    cout << "  ";
    for (char i = 'a'; i < 'i'; i++) {
        
        cout << i << " ";
    }
    cout << endl;
}


void ChessBoard::undoBoard() {
    if (!moveHistory.size()) {
        return;
    }
    
    Move lastMove = moveHistory.back();
    /*
     Check last move status to properly undo all changes
     */
    
    if (lastMove.moveInfo == IS_TRANSFORMATION) {
        // if it was transformation we need to revive pawn and delete newly made figure
        lastMove.from.figure->revive();
        Figure * transformed = board[lastMove.to.y_pos][lastMove.to.x_pos].figure;
        for (auto iter = figures.begin(); iter != figures.end(); iter++) {
            if (*iter == transformed) {
                figures.erase(iter);
                break;
            }
        }
        
        delete transformed;
    }
    else if (lastMove.moveInfo == IS_SHORT_CASTLING) {
        // if it was castling we need to undo castle move too
        int y_pos = lastMove.playerColour == WHITE ? 0 : 7;
        Figure * castle = board[y_pos][5].figure;
        castle->isFirstMove = true;
        board[y_pos][7].figure = castle;
        board[y_pos][5].figure = nullptr;
        castle->updateCurrentPosition(7, y_pos);
        
    }
    else if (lastMove.moveInfo == IS_LONG_CASTLING) {
        // if it was castling we need to undo castle move too
        int y_pos = lastMove.playerColour == WHITE ? 0 : 7;
        Figure * castle = board[y_pos][3].figure;
        castle->isFirstMove = true;
        board[y_pos][0].figure = castle;
        board[y_pos][3].figure = nullptr;
        castle->updateCurrentPosition(0, y_pos);
    }
    else if (lastMove.moveInfo == IS_EN_PASSANT) {
        // if it was "en passant" we need to revive beaten pawn
        int y_pos = lastMove.playerColour == WHITE ? lastMove.to.y_pos - 1 : lastMove.to.y_pos + 1;
        int x_pos = lastMove.to.x_pos;
        Figure * killedPawn = nullptr;
        for (Figure * f : figures) {
            if (f->getCurrentPosition().first == x_pos && f->getCurrentPosition().second == y_pos) {
                killedPawn = f;
                break;
            }
        }
        board[y_pos][x_pos].figure = killedPawn;
        killedPawn->revive();
    }
    
    moveHistory.pop_back();
    // the main thing is to revive beaten figure and put it back on the board
    board[lastMove.from.y_pos][lastMove.from.x_pos].figure = lastMove.from.figure;
    board[lastMove.to.y_pos][lastMove.to.x_pos].figure = lastMove.to.figure;
    if (lastMove.to.figure) {
        lastMove.to.figure->revive();
    }
    lastMove.from.figure->updateCurrentPosition(lastMove.from.x_pos, lastMove.from.y_pos);
    
    // we need to restore flag isFirstMove so we looking for move of that figure in history
    for (Move & move : moveHistory) {
        if (move.from.figure == lastMove.from.figure) {
            return;
        }
    }
    lastMove.from.figure->isFirstMove = true;
}

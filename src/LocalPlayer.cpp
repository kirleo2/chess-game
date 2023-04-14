//
//  Player.cpp
//  chess
//
//  Created by Kirill on 06.05.2022.
//

#include "LocalPlayer.hpp"
#include "GameEvent.h"
#include <string>

static unordered_map<char, int> boardXLetters { {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5},
    {'g', 6}, {'h', 7}
};
Move LocalPlayer::move() {
    // throws exception if player has no moves
    getMovesAndCheckLose();
    
    Ceil from;
    Ceil to;
    //cin.clear();
    while(true) {
        
        /*
         move must contain 5 symboles. for example e2 e4
         we read chars one by one into cx1 cy1 cx2 cy2 and then using asci code (- 48) table assigns to integer to get coordinates
         */
        string userInput;
//        cin.clear();
        // ignore empty input
        while (!userInput.length()) {
            getline(cin, userInput);
            if (cin.eof()) {
                break;
            }
        }
        
        
      
        if (userInput == "save") {
            throw GameEvent(SAVE_GAME, colour);
        }
        else if (userInput == "konec" || cin.eof() ) {
            throw GameEvent(END_GAME, colour);
        }
        if (userInput.length() != 5) {
            cout << "Nevalidni tah" << endl;
            continue;
        }
        
        int x1, y1, x2, y2;
        char cx1, cy1, cx2, cy2;
        
        cx1 = tolower(userInput[0]);
        if (boardXLetters.find(cx1) == boardXLetters.end()) {
            cout << "Nevalidni tah" << endl;
            continue;
        }
        x1 = boardXLetters[cx1];
        cy1 = userInput[1];
        y1 = cy1 - 49;
        
        cx2 = tolower(userInput[3]);
        if (boardXLetters.find(cx2) == boardXLetters.end()) {
            cout << "Nevalidni tah" << endl;
            continue;
        }
        x2 = boardXLetters[cx2];
        cy2 = userInput[4];
        
        y2 = cy2 - 49;
        
        if (y2 < 0 || y1 < 0 || y1 > 7 || y2 > 7) {
            cout << "Nevalidni tah" << endl;
            continue;
        }
        
        
        from = gameBoard->getBoard()[y1][x1];
        to = gameBoard->getBoard()[y2][x2];
        if (gameBoard->isValidMove(from, to) && (!from.figure || from.figure->getColour()==colour)) {
            break;
        }
        else cout << "Nevalidni tah" << endl;
    }
    Move move (from, to, colour);
    gameBoard->processMove(move);
    if (move.moveInfo == IS_TRANSFORMATION) {
        move.figureCode = transfromPawn();
    }
    
    return move;
}

int LocalPlayer::transfromPawn() const  {

    return QUEEN;
}
 

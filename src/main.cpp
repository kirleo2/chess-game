
#include <iostream>
#include "Game.hpp"
#include "time.h"
#include<dirent.h>


using namespace std;

enum userStates : int {
    waitingForMode = 0,
    waitingForComputerType = 1,
    waitingForColour = 2,
    waitingForFileDest = 3,
    waitingForEnd = 4
    
};
const static string error = "Nespravne cislo polozky.\nZkuste to znovu\n";
const static string savesError = "Zadne save soubory nebyly nalezeny\n";
const static string chooseClue = "Vyberte rezim tim, ze napisete cislo polozky\n";
const static string startMenu = "Sachovy program v1. Konzolove rozhrani\n"
"Je k dispozici:\n"
"1: Nova hra Hrac proti pocitaci\n"
"2: Nova hra Hrac proti hraci\n"
"3: Nacist rozehranou hru\n";

const static string computerChoose = "Je k dispozici 3 slozitosti pocitace:\n"
"1: Lehky\n"
"2: Prumerny\n"
"3: Umela inteligence\n";
const static string colourChoose = "Vyberte barvu:\n"
"1: BILA\n"
"2: CERNA\n";

const static string gameOver = "\n\n1: Vratit se do hlavniho menu\n"
"2: Zavrit hru\n";

const static string helpMessage = "Pravidla:\n"
"Abyste udelali tah musite napsat zacatecni a konecni bunku (Zkratku figury neuvadet!)\n"
"Napriklad: e2 e4 nebo e1 g1 (probehla by rosada)\n"
"Mate rovnez moznost ulozit hru prikazem: save\n"
"Skoncit hru prikazem: konec\n";


bool endsWith(const string &mainStr, const string &toMatch)
{
    if(mainStr.size() >= toMatch.size() &&
            mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
            return true;
        else
            return false;
}

void userLoop (int status, bool & exitFlag) {
    int userState = status;

    
    int userInput;
    Player * firstPlayer = nullptr;
    Player * secondPlayer = nullptr;
    uint8_t typeOfOpponent = LOCAL_PLAYER;
    vector<string> saves;
    
    string savePath;
    while (true) {
        if (userState == waitingForMode) {
            cout << startMenu;
            cout << chooseClue;
        }
        cin >> userInput;
        if (cin.eof()) {
            exitFlag = true;
            break;
        }
        while (!cin) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << error;
            cin >> userInput;
            if (cin.eof()) {
                exitFlag = true;
                break;
            }
        }
        if (userState == waitingForMode) {
            if (userInput > 3 || userInput < 1) {
                cout << error;
                continue;
            }
            if (userInput == 1) {
                cout << computerChoose;
                cout << chooseClue;
                userState = waitingForComputerType;
            }
            else if (userInput == 2) {
                firstPlayer =  new LocalPlayer ("Bile", WHITE);
                secondPlayer =  new LocalPlayer ("Cerne", BLACK);
                typeOfOpponent = LOCAL_PLAYER;
                break;
            }
            else {
                string path = "./examples";
                int i = 1;
                saves.clear();
            
                struct dirent *d;
                DIR *dr;
                dr = opendir(path.c_str());
                if(dr)
                    {
                        for(d=readdir(dr); d; d=readdir(dr))
                        {
                            if (endsWith(d->d_name, ".chess")) {
                                cout << i <<  ": " << d->d_name << endl;
                                saves.push_back(d->d_name);
                                i++;
                            }
                                
                        }
                        closedir(dr);
                    }
                else {
                    cout<< savesError;
                    continue;
                }
                if (i == 1) {
                    cout<< savesError;
                    continue;
                }
                        
                userState = waitingForFileDest;
            }
        }
        
        else if (userState == waitingForComputerType) {
            if ( userInput > 3 || userInput < 1) {
                cout << error;
                continue;
            }
            cout << colourChoose;
            cout << chooseClue;
            userState = waitingForColour;
            if (userInput == 1) {
                typeOfOpponent = DUMMY;
            }
            else if (userInput == 2) {
                typeOfOpponent = MEDIUM;
            }
            else typeOfOpponent = AI;
        }
        else if (userState == waitingForColour) {
            if (userInput > 2 || userInput < 1) {
                cout << error;
                continue;
            }
            bool colour;
            if (userInput == 1) {
                colour = WHITE;
            }
            else colour = BLACK;
            firstPlayer =  new LocalPlayer (colour == WHITE ? "Bile" : "Cerne", colour);
            if (typeOfOpponent == DUMMY) {
                secondPlayer = new DummyComputerPlayer("Lehky pocitac", !colour);
            }
            else if (typeOfOpponent == MEDIUM) {
                
                secondPlayer = new MediumComputerPlayer ("Prumerny pocitac", !colour);
            }
            else secondPlayer = new AIComputerPlayer ("Umela inteligence", !colour);
            break;
        }
        else if (userState == waitingForFileDest) {
                size_t num = userInput;
                if (num > saves.size() || num == 0) {
                    cout << error;
                    continue;
                }
                savePath = "./examples/" + saves[num - 1];
            break;
        }
        else if (userState == waitingForEnd) {
            if (userInput == 1) {
                userState = waitingForMode;
                
            }
            else if (userInput == 2) {
                exitFlag = true;
                return;
            }
            else cout << error;
        }
    }
    if (!cin.eof()) {
        system("clear");
        cout << helpMessage;
        
        if (firstPlayer) {

            cout << "Hra zacina :" << endl;
            Game game = Game(firstPlayer, secondPlayer);
            game.startGame();
        }
        else {
            try {
                Game game = Game (savePath);
                game.startGame();
            }
            catch (runtime_error & re) {
                cout << re.what() << endl;;
            }
        }
        cout << gameOver;
    }
}



int main(int argc, const char * argv[]) {
    
    bool exitFlag = false;
    srand(time(NULL));
    system("clear");
    userLoop(waitingForMode, exitFlag);
    while (!exitFlag) {
        userLoop(waitingForEnd, exitFlag);
    }
    

    return 0;
}


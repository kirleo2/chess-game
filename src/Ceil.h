//
//  Ceil.hpp
//  chess
//
//  Created by Kirill on 06.05.2022.
//


#ifndef Ceil_hpp
#define Ceil_hpp
#ifndef Figure_hpp
#include "Figure.h"
#endif


/**
 * \brief   Class  that represents the ceil on the ChessBoard.
 *
 * \details It has x, y coordinates and pointer to abstarct class Figure.
 *
 */

class Ceil {
    
public:
    Ceil (){
        figure = nullptr;
    }
    
    Ceil (int x, int y):
    x_pos(x),
    y_pos(y),
    figure(nullptr)
    {}
    Ceil(int x, int y, class Figure * f):
    x_pos(x),
    y_pos(y),
    figure(f)
    {}
    
    int x_pos;
    int y_pos;
    Figure * figure;
    
    friend bool operator==(const Ceil & first, const Ceil & second){
        return first.x_pos == second.x_pos && first.y_pos==second.y_pos;
    }
};
#endif



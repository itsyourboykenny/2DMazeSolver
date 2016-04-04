  //
//  Coordinates.h
//  Maze
//
//  Created by Ken Ishiguro on 10/11/15.
//  Copyright © 2015 Ken Ishiguro. All rights reserved.
//

#ifndef Coordinates_h
#define Coordinates_h

#pragma once
class Coordinates
{
private:
    int row;
    int col;
public:
    Coordinates(){ row = 0; col = 0; }
    Coordinates(int r, int c){ row = r; col = c; }
    void setRow(int r){ row = r; }
    void setCol(int c){ col = c; }
    int getRow(){return row;}
    int getCol(){return col;}
};

#endif /* Coordinates_h */

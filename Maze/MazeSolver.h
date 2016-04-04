//
//  MazeSolver.h
//  Maze
//
//  Created by Ken Ishiguro on 10/11/15.
//  Copyright © 2015 Ken Ishiguro. All rights reserved.
//

#ifndef MazeSolver_h
#define MazeSolver_h
using namespace std;
#include <fstream>
#include "Maze.h"
#include "Coordinates.h"

class MazeSolver{
    
private:
    MazeSolver *next;
    MazeSolver *back;

public:
    
    Coordinates *coord = nullptr;
    
    MazeSolver(){
        coord = new Coordinates;
        next = nullptr;
        back = nullptr;
    }

    MazeSolver(Coordinates *temp){
        coord = new Coordinates(temp->getRow(),temp->getCol());
    }
    MazeSolver(int row, int col){
        coord = new Coordinates(row,col);
    }
    ~MazeSolver(){
        delete next;
        delete back;
        delete coord;
    }
    
    void setStart(Coordinates *start){
        coord->setRow(start->getRow());
        coord->setCol(start->getCol());
    }

    Coordinates *getChoord(){return coord;}
    Coordinates returnCoord(){return *coord;}
    MazeSolver *getBack(){return back;}
    MazeSolver *getNext(){return next;}
    
    void setNext(MazeSolver *nxt){next = nxt;}
    void setBack(MazeSolver *bk){back = bk;}
    
    void printcoords(){cout << coord->getRow() << ' ' << coord->getCol() << endl;}

};

#endif /* MazeSolver_h */

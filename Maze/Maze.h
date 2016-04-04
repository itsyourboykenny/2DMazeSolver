//
//  Maze.h
//  Maze
//
//  Created by Ken Ishiguro on 10/11/15.
//  Copyright © 2015 Ken Ishiguro. All rights reserved.
//

#ifndef Maze_h
#define Maze_h

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Coordinates.h"
#include "MazeSolver.h"
using namespace std;

class Maze: public MazeSolver{
    
private:
    char **maze;
    int rowSize, colSize;
    
    void eraseMaze()
    {
        for (int row = 0; row < rowSize; ++row)
            delete maze[row];
        delete maze;
    }
    
    MazeSolver *headPtr;
    MazeSolver *tailPtr;
    
public:
    Maze(){ maze = 0; rowSize = colSize = 0; }
    Maze(ifstream &infile)
    {
        allocateAndRead(infile);
    }
    
    Maze(Maze &sourceMaze) // copy constructor
    {
        rowSize = sourceMaze.rowSize;
        colSize = sourceMaze.colSize;
        maze = new char*[rowSize];
        for (int row = 0; row < rowSize; ++row)
        {
            maze[row] = new char[colSize];
            for (int col = 0; col < colSize; ++col)
                maze[row][col] = sourceMaze.maze[row][col];
        }
    }
    ~Maze()
    {
        eraseMaze();
    }
    
    bool setCoordinatesValue(Coordinates *pcoord, char val)
    {
        int row, col;
        
        row = pcoord->getRow();
        col = pcoord->getCol();
        if (row < rowSize && col < colSize)
        {
            maze[row][col] = val;
            return true;
        }
        return false;
    }
    
    
    //FUNTION TO CHECK SPACE TO REDUCE REDUNDANCY
    bool isPath(Coordinates *pcoord, int row = 0, int col = 0){
        if (pcoord->getRow()+row < 0 || pcoord->getCol()+col < 0) {
            return false;
        }
        else{
            if (maze[(pcoord->getRow()+row)][(pcoord->getCol()+col)] == ' ') {
                pcoord->setRow(pcoord->getRow()+row);
                pcoord->setCol(pcoord->getCol()+col);
                maze[pcoord->getRow()][pcoord->getCol()] = '.';
                return true;
            }
            else{
                return false;
            }
        }
    }
    
    
    //CHECKS IF NEXT SPACE IS A SPACE, OTHERWISE RETURNS 0
    Coordinates *getNextCoordinates(Coordinates *pcoord)
    {
        /*
         YOU WRITE, so you return a new Coordinates
         for going East, South, West, then North, if
         the element is still in the maze and equals ' '
         */
        
        Coordinates *temp = new Coordinates(pcoord->getRow(),pcoord->getCol());
        
        if (isPath(temp, 1, 0)) { //South
            return *&temp;
        }
        else if (isPath(temp, 0, 1)){ //East
            return *&temp;
        }
        else if (isPath(temp, -1, 0)){ //North
            return *&temp;
        }
        else if (isPath(temp, 0, -1)){ //West
            return *&temp;
        }
        else{
            delete temp;
            return 0; // can't move, return 0
        }
        
    }
    
    bool isEmpty(char temp){
        if (temp == ' ') {
            return true;
        }
        else{
            return false;
        }
    }
    
    void allocateAndRead(ifstream &infile)
    {
        
        if (maze != 0) // already allocated a 2-dim. array?
            eraseMaze();

        // Determine map size
        
        rowSize = 0;
        colSize = 0;
        string inputLine, inputPeek1, inputPeek2;
        
        getline(infile, inputLine);
        getline(infile, inputPeek1);
        getline(infile, inputPeek2);
        
        //Use longest string as colSize
    
        if (inputLine.length() > inputPeek2.length()) {
            colSize = (int)inputLine.length();
        }
        else{
            colSize = (int)inputPeek1.length();
        }
        if (inputPeek2.length() > colSize) {
            colSize = (int)inputPeek2.length();
        }
        
        //colSize--;
        
        //Read all row
        infile.seekg(0);
        while (getline(infile, inputLine)) {
            rowSize++;
        }
        
        cout << "Row: " << rowSize << ' ' << "Col: " <<colSize << endl;
        
        maze = new char * [rowSize];
        for (int count =0; count < rowSize; count++) {
            maze[count]= new char [colSize];
        }
        
        // read maze:
        infile.clear();
        infile.seekg(0);
        for (int row = 0; row < rowSize; row++)
        {
            getline(infile, inputLine);
            for (int col = 0; col < colSize; col++)
            {
                maze[row][col] = inputLine[col];
            }
        }

    } // end allocateAndRead
    
    Coordinates * getStartCoordinates()
    {
        for (int row = 0; row < rowSize; ++row)
        {
            if (maze[row][0] == ' ')
                return new Coordinates(row, 0);
        }
        for (int col = 0; col < colSize; ++col){
            if (maze[0][col] == ' ')
                return new Coordinates(0, col);
        }
        return 0; // none at left or top edge, so not solvable
    } // end getStartCoordinates
    
    bool isEndingEdgeCoordinates(Coordinates *pcoord)
    {
        if (pcoord->getRow() == (rowSize-1) || pcoord->getCol() == (colSize-1)) {
            return true;
        }
        else{
            return false;
        }
    }
    
    
    //USES ALL OF THE FUNCTIONS TO SOLVE MAZE, RETURNS IT'S BOOL
    bool solveIt(){
        headPtr = new MazeSolver(getStartCoordinates());
        tailPtr = headPtr;
        setCoordinatesValue(headPtr->getChoord(), '.');
        while(!isEndingEdgeCoordinates(headPtr->getChoord())){
            Coordinates *tmp = getNextCoordinates(headPtr->getChoord());
            if (tmp!=0) {
                MazeSolver *temp = new MazeSolver(tmp);
                setCoordinatesValue(headPtr->getChoord(), '.');
                temp->setBack(headPtr);
                headPtr->setNext(temp);
                headPtr = temp;
            }
            else{
                setCoordinatesValue(headPtr->getChoord(), 'V');
                headPtr = headPtr->getBack();
            }
        }
        return true;
    }
    
    void display()
    {
        if (maze == 0)
        {
            cout << "No maze to display\n";
            return;
        }
        for (int row = 0; row < rowSize; row++)
        {
            for (int col = 0; col < colSize; col++)
                cout << maze[row][col];
            cout << endl;
        }
        
        cout << endl;
        
        if (solveIt()) {
            for (int row = 0; row < rowSize; ++row)
            {
                for (int col = 0; col < colSize; ++col)
                    cout << maze[row][col];
                cout << endl;
            }
        }
        else{
            cout << "Something is wrong so fix it..." << endl;
        }
    }
    
};


#endif /* Maze_h */

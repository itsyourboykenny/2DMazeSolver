//Maze Solver
//Kenichi Ishiguro
//October 7, 2015
//OSX 10.10
//Xcode 7.0.1

#include <iostream>
#include <fstream>
#include <string>
#include "Maze.h"
using namespace std;

bool openInputFile(ifstream &ifs)
{
//    string filename;
//    
//    cout << "Enter the input filename: ";
//    getline(cin, filename);
//    
//    if (filename.back() == '\r' || filename.back() == '\n' || filename.back() == ' ')
//        filename.pop_back();
//    
//    ifs.open(filename.c_str());

    ifs.open("/Users/itsyourboykenny/Library/Developer/Xcode/DerivedData/Maze-bwpsaxloufhqxyciaoetbmijvthf/Build/Products/Debug/test.txt");
    return ifs.is_open();
}


int main() {
    
    ifstream mazeFile;
    openInputFile(mazeFile);
    Maze theMaze(mazeFile);
    theMaze.display();
    return 0;
}

//HW1_TestInput1.txt
//Row: 8 Col: 8
//########
//#
//# # # ##
//#   #  #
//# ######
//#   #
//#      #
//########
//
//########
//..     #
//#.# # ##
//#.  #  #
//#.######
//#.  # ..
//#......#
//########

//HW1_TestInput2.txt
//Row: 7 Col: 9
//000 00000
//0 0     0
//00000 000
//0       0
//0 0 00000
//0 0     0
//000000 00
//
//000.00000
//0 0...  0
//00000.000
//0  ...VV0
//0 0.00000
//0 0.... 0
//000000.00

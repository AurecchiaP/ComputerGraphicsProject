#ifndef TRACKGENERATOR_H
#define TRACKGENERATOR_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>


using std::vector;
using std::pair;

class TrackGenerator
{
public:
    TrackGenerator();
    vector<char> & generateCircuit(int nOfPieces);
private:
    vector<char> allPieces;
    char curvesIndicator = 0; // 0 -> no angle, >0 -> leftAngle, <0 -> rightAngle
    unsigned int piecesCounter = 0;
    vector<char> pieces; // 0 -> Straight, 1 -> Right, 2 -> Left.
    vector<unsigned int> piecesIdxs[7];
    vector<char> straights;
    int randNum();
    void addLeftCurve();
    void addRightCurve();
    void addStraight();
    void randomPiece();
    void addIndex() {        
        if (abs(curvesIndicator)!=3){
        piecesIdxs[curvesIndicator+3].push_back(static_cast<unsigned int>(pieces.size()));
        } else {piecesIdxs[0].push_back(static_cast<unsigned int>(pieces.size()));}
    }
    void addPiece(int n);


};

#endif // TRACKGENERATOR_H

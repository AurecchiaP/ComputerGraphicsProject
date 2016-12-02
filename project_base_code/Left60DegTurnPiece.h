#ifndef LEFT60DEGTURNPIECE_H
#define LEFT60DEGTURNPIECE_H

#include "AbstractTrackPiece.h"

#define LEFT_60_TURN_X 2.5
#define LEFT_60_TURN_Z 2.5
#define LEFT_60_ANGLE PI/3.0

class Left60DegTurnPiece : public AbstractTrackPiece
{
private:
    static ObjModel model;
public:
    Left60DegTurnPiece();
    virtual void applyTransforms();
    virtual void draw();
};

#endif // LEFT60DEGTURNPIECE_H

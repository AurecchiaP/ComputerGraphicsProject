#ifndef STRAIGHTTRACKPIECE_H
#define STRAIGHTTRACKPIECE_H

#include "AbstractTrackPiece.h"

#define STRAIGHT_PIECE_LENGTH 5.0

class StraightTrackPiece : public AbstractTrackPiece
{
private:
    static ObjModel model;
public:
    StraightTrackPiece();
    virtual void applyTransforms();
    virtual void draw();
};

#endif // STRAIGHTTRACKPIECE_H

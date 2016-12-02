#ifndef STRAIGHTPIECE_H
#define STRAIGHTPIECE_H

#include "AbstractTrackPiece.h"

#define STRAIGHT_PIECE_X 5.0

class StraightPiece : public AbstractTrackPiece
{
private:
    static ObjModel model;
public:
    StraightPiece();
    virtual void applyTransforms();
    virtual void draw();
};

#endif // STRAIGHTPIECE_H

#ifndef STRAIGHTTRACKPIECE_H
#define STRAIGHTTRACKPIECE_H

#include "AbstractTrackPiece.h"

class StraightTrackPiece : public AbstractTrackPiece
{
private:
    static const GLdouble mat[16];
    static ObjModel model;
public:
    StraightTrackPiece();
    virtual const GLdouble * getTransformationMatrix();
    virtual void draw();

};

#endif // STRAIGHTTRACKPIECE_H

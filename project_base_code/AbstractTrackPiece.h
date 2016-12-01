#ifndef ABSTRACTTRACKPIECE_H
#define ABSTRACTTRACKPIECE_H

#include <QtOpenGL>
#include "Base.h"
#include "ObjModel.h"


class AbstractTrackPiece
{
public:
    AbstractTrackPiece();
    virtual const GLdouble * getTransformationMatrix() = 0;
    virtual void draw() = 0;
};

#endif // ABSTRACTTRACKPIECE_H

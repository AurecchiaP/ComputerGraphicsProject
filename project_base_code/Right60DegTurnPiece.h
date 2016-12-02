#ifndef RIGHT60DEGTURNPIECE_H
#define RIGHT60DEGTURNPIECE_H

#include "AbstractTrackPiece.h"


#define RIGHT_60_TURN_X 2.5
#define RIGHT_60_TURN_Z -2.5
#define RIGHT_60_ANGLE -PI/3.0

class Right60DegTurnPiece : public AbstractTrackPiece
{
private:
    static ObjModel model;
public:
    Right60DegTurnPiece();
    virtual void applyTransforms();
    virtual void draw();
};

#endif // RIGHT60DEGTURNPIECE_H

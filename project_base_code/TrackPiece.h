#ifndef TRACKPIECE_H
#define TRACKPIECE_H

#include "TrackPieceType.h"

class TrackPiece
{
private:
    TrackPieceType & type;
public:
    TrackPiece(TrackPieceType & type);
    void draw();
    void applyTransforms();
    void applyTransforms(double fraction);
};

#endif // TRACKPIECE_H

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
};

#endif // TRACKPIECE_H

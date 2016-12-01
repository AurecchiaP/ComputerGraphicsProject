#include "StraightTrackPiece.h"


const GLdouble StraightTrackPiece::mat[16] = { 0, 0, 0, 0,
                                               0, 0, 0, 0,
                                               0, 0, 0, 0,
                                               0, 0, 0, 0 };

ObjModel StraightTrackPiece::model("models/straight_track.obj");


StraightTrackPiece::StraightTrackPiece() {}

const GLdouble * StraightTrackPiece::getTransformationMatrix() {
    return StraightTrackPiece::mat;
}

void StraightTrackPiece::draw() {
    StraightTrackPiece::model.draw();
}


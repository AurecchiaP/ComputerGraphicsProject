#include "StraightTrackPiece.h"

ObjModel StraightTrackPiece::model("models/straight_track.obj");


StraightTrackPiece::StraightTrackPiece() {}

void StraightTrackPiece::applyTransforms() {
    glTranslated(STRAIGHT_PIECE_LENGTH, 0.0, 0.0);
}

void StraightTrackPiece::draw() {
    StraightTrackPiece::model.draw();
}

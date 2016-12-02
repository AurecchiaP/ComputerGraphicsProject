#include "StraightPiece.h"

ObjModel StraightPiece::model("models/straight_track.obj");


StraightPiece::StraightPiece() {}

void StraightPiece::applyTransforms() {
    glTranslated(STRAIGHT_PIECE_X, 0.0, 0.0);
}

void StraightPiece::draw() {
    StraightPiece::model.draw();
}

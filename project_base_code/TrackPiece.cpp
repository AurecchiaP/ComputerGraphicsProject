#include "TrackPiece.h"

TrackPiece::TrackPiece(TrackPieceType & type) : type(type) {}

void TrackPiece::draw() {
    type.draw();
}

void TrackPiece::applyTransforms() {
    type.applyTransforms();
}

void TrackPiece::applyPartialTransforms(double fraction) {
    type.applyPartialTransforms(fraction);
}

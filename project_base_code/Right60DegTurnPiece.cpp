#include "Right60DegTurnPiece.h"


ObjModel Right60DegTurnPiece::model("models/straight_track.obj");

Right60DegTurnPiece::Right60DegTurnPiece() { }

void Right60DegTurnPiece::applyTransforms() {
    glTranslated(RIGHT_60_TURN_X, 0.0, RIGHT_60_TURN_Z);
    glRotated(RIGHT_60_ANGLE, 0, 1, 0);
}

void Right60DegTurnPiece::draw() {
    Right60DegTurnPiece::model.draw();
}


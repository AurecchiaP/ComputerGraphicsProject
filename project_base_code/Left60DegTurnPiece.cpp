#include "Left60DegTurnPiece.h"


ObjModel Left60DegTurnPiece::model("models/straight_track.obj");

Left60DegTurnPiece::Left60DegTurnPiece() {}

void Left60DegTurnPiece::applyTransforms() {
    glTranslated(LEFT_60_TURN_X, 0.0, LEFT_60_TURN_Z);
    glRotated(LEFT_60_ANGLE, 0, 1, 0);
}

void Left60DegTurnPiece::draw() {
    Left60DegTurnPiece::model.draw();
}

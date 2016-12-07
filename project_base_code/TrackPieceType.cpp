#include "TrackPieceType.h"

TrackPieceType::TrackPieceType (const std::string & filename, GLdouble * src_mat) : model(filename) {
    memcpy(mat, src_mat, sizeof(GLdouble) * 16);
}

TrackPieceType::TrackPieceType (const std::string & filename) : model(filename) {}

void TrackPieceType::draw() {
    model.draw();
}

void TrackPieceType::applyTransforms() {
    glMultMatrixd(mat);
}

void TrackPieceType::init() {
    model.init();
}

void TrackPieceType::copyMatrix(GLdouble * src_matrix) {
    memcpy(mat, src_matrix, sizeof(GLdouble) * 16);
}

GLdouble * TrackPieceType::getMatrix() {
    return mat;
}

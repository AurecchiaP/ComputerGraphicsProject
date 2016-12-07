#ifndef TRACKPIECETYPE_H
#define TRACKPIECETYPE_H

#include <string>
#include <functional>
#include "ObjModel.h"

class TrackPieceType
{
private:
    ObjModel model;
    GLdouble mat[16];
public:
    TrackPieceType(const std::string & filename, GLdouble * src_mat);
    TrackPieceType(const std::string & filename);
    void draw();
    void applyTransforms();
    void init();
    void copyMatrix(GLdouble * src_mat);
    GLdouble * getMatrix();
};

#endif // TRACKPIECETYPE_H

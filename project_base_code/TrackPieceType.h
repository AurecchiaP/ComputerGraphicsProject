#ifndef TRACKPIECETYPE_H
#define TRACKPIECETYPE_H

#include <string>
#include <functional>
#include "ObjModel.h"

class TrackPieceType
{
private:
    ObjModel model;
    const std::function<void(double)> transform;
public:
    TrackPieceType(const std::string & filename, std::function<void(double)> transform);
    void draw();
    void applyTransforms();
    void applyTransforms(double fraction);
    void init();
};

#endif // TRACKPIECETYPE_H

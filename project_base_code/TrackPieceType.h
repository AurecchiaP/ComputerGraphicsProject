#ifndef TRACKPIECETYPE_H
#define TRACKPIECETYPE_H

#include <string>
#include <functional>
#include "ObjModel.h"

class TrackPieceType
{
private:
    ObjModel model;
    const std::function<void()> transform;
public:
    TrackPieceType(const std::string & filename, std::function<void()> transform);
    void draw();
    void applyTransforms();
    void init();
};

#endif // TRACKPIECETYPE_H

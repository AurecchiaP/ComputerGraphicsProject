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
    const std::function<void(double)> partial_transform;
public:
    TrackPieceType(const std::string & filename, std::function<void()> transform, std::function<void(double)> partal_transform);
    void draw();
    void applyTransforms();
    void applyPartialTransforms(double fraction);
    void init();
};

#endif // TRACKPIECETYPE_H

#ifndef TRAINPIECETYPE_H
#define TRAINPIECETYPE_H

#include <string>
#include "ObjModel.h"

class TrainPieceType
{
private:
    ObjModel model;
public:
    const double len;
    TrainPieceType(const std::string & filename, double len);
    void draw();
    void init();
};

#endif // TRAINPIECETYPE_H

#include "TrainPieceType.h"

TrainPieceType::TrainPieceType(const std::string & filename, double len) :
    model(filename), len(len) {}

void TrainPieceType::draw() {
    model.draw();
}

void TrainPieceType::init() {
    model.init();
}

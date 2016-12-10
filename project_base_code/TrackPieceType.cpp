#include "TrackPieceType.h"

TrackPieceType::TrackPieceType
( double len, const std::string & filename, std::function<void(double)> transform) :
    model(filename), transform(transform), len(len) {}

void TrackPieceType::draw() {
    model.draw();
}

void TrackPieceType::applyTransforms() {
    transform(1.0);
}

void TrackPieceType::applyTransforms(double tau) {
    transform(tau);
}

void TrackPieceType::init() {
    model.init();
}

#include "TrackPieceType.h"

TrackPieceType::TrackPieceType
( double len, const std::string & filename, std::function<void(double, bool)> transform) :
    model(filename), transform(transform), len(len) {}

void TrackPieceType::draw() {
    model.draw();
}

void TrackPieceType::applyTransforms() {
    transform(1.0, false);
}

void TrackPieceType::applyTransforms(double tau) {
    transform(tau, false);
}

void TrackPieceType::invertTransforms() {
    transform(1.0, true);
}

void TrackPieceType::invertTransforms(double tau) {
    transform(tau, true);
}


void TrackPieceType::init() {
    model.init();
}

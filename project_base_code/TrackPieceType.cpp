#include "TrackPieceType.h"

TrackPieceType::TrackPieceType
(const std::string & filename, std::function<void()> transform, std::function<void(double)> partial_transform) :
    model(filename), transform(transform), partial_transform(partial_transform) {}

void TrackPieceType::draw() {
    model.draw();
}

void TrackPieceType::applyTransforms() {
    transform();
}

void TrackPieceType::applyPartialTransforms(double tau) {
    partial_transform(tau);
}

void TrackPieceType::init() {
    model.init();
}

#include "TrackPieceType.h"

TrackPieceType::TrackPieceType
(const std::string & filename, std::function<void()> transform) :
    model(filename), transform(transform) {}

void TrackPieceType::draw() {
    model.draw();
}

void TrackPieceType::applyTransforms() {
    transform();
}

void TrackPieceType::init() {
    model.init();
}

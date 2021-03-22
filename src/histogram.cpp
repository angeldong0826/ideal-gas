#include "histogram.h"
#include "cinder/gl/gl.h"

using std::vector;

namespace idealgas {

Histogram::Histogram(const std::vector<Particle>& particles)
    : particles_(const_cast<std::vector<Particle>&>(particles)) {
  particles_ = particles;
}

void Histogram::Display() const {
  // Display charts
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(chart_pink_);
  ci::gl::drawStrokedRect(chart_white_);
  ci::gl::drawStrokedRect(chart_teal_);
}

void Histogram::AdvanceOneFrame() {
  CreateMap();
}

void Histogram::CreateMap() {
  for (auto& particle : particles_) {
    double speed = glm::length(particle.GetVelocity());

    if (particle.GetColor() == "pink") {
      FillInMap(map_pink_, speed, pink_speed_range);
    } else if (particle.GetColor() == "white") {
      FillInMap(map_white_, speed, white_speed_range);
    } else if (particle.GetColor() == "teal") {
      FillInMap(map_teal_, speed, teal_speed_range);
    }
  }
}

void Histogram::FillInMap(std::map<double, int>& map, double speed,
                          vector& range) {
  for (size_t i = 0; i < range.size() - 1; i++) {
    if (speed < range[0]) {
      map[range[0]] += 1;
    } else if (speed >= range[i] && speed < range[i + 1]) {
      map[range[i]] += 1;
    } else if (speed >= range[i]) {
      map[range[i + 1]] += 1;
    }
  }
}

//void Histogram::DrawGraph() {}


} // namespace idealgas
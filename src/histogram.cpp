#include "histogram.h"

#include "cinder/gl/gl.h"

using std::vector;

namespace idealgas {

Histogram::Histogram() {}

void Histogram::Display() {
  // Display histograms
  DrawGraph(ci::Color("pink"));
  DrawGraph(ci::Color("white"));
  DrawGraph(ci::Color("teal"));

  // Display chart outlines
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(chart_pink_, static_cast<float>(histogram_border_width_) + 1);
  ci::gl::drawStrokedRect(chart_white_, static_cast<float>(histogram_border_width_) + 1);
  ci::gl::drawStrokedRect(chart_teal_, static_cast<float>(histogram_border_width_) + 1);

  // Display axis
  DrawAxis("pink");
  DrawAxis("white");
  DrawAxis("teal");
}

void Histogram::AdvanceOneFrame(const std::vector<GasParticle> &particles) {
  particles_ = particles;
  CreateMap();
}

void Histogram::CreateMap() {
  map_pink_.clear();
  map_white_.clear();
  map_teal_.clear();

  for (auto &particle : particles_) {
    double speed = glm::length(particle.GetVelocity()); // speed of particle

    if (particle.GetColor() == "pink") {
      FillInMap(map_pink_, speed);
    } else if (particle.GetColor() == "teal") {
      FillInMap(map_teal_, speed);
    } else if (particle.GetColor() == "white") {
      FillInMap(map_white_, speed);
    }`
  }
}

void Histogram::FillInMap(std::map<double, size_t> &map, double speed) {
  double max_speed = CalculateMaxSpeed(); // maximum speed of particle

  for (size_t i = 0; i < kBarNumbers; ++i) {
    if (speed <= ((i + 1.0) / kBarNumbers) * max_speed) {
      map[i] += 1;
      break;
    }
  }
}

void Histogram::DrawGraph(const ci::Color &color) const {
  double top_left_ = chart_pink_.getUpperLeft().x;  // top left coordinate of all histogram charts

  if (color == ci::Color("pink")) {

    for (const auto &particle : map_pink_) {
      size_t count = particle.second;
      ci::gl::color(color);
      ci::gl::drawStrokedRect(ci::Rectf(
          glm::vec2{top_left_,
                    pink_bottom_right_coordinate_ - count * y_scale_},
          glm::vec2{top_left_ + x_scale_, pink_bottom_right_coordinate_}),
                              histogram_border_width_);
      top_left_ += x_scale_;
    }

  } else if (color == ci::Color("white")) {

    for (const auto &particle : map_white_) {
      size_t count = particle.second;
      ci::gl::color(color);
      ci::gl::drawStrokedRect(ci::Rectf(
          glm::vec2{top_left_,
                    white_bottom_right_coordinate_ - count * y_scale_},
          glm::vec2{top_left_ + x_scale_, white_bottom_right_coordinate_}),
                              histogram_border_width_);
      top_left_ += x_scale_;
    }

  } else if (color == ci::Color("teal")) {

    for (const auto &particle : map_teal_) {
      size_t count = particle.second;
      ci::gl::color(color);
      ci::gl::drawStrokedRect(ci::Rectf(
          glm::vec2{top_left_,
                    teal_bottom_right_coordinate_ - count * y_scale_},
          glm::vec2{top_left_ + x_scale_, teal_bottom_right_coordinate_}),
                              histogram_border_width_);
      top_left_ += x_scale_;
    }
  }
}

void Histogram::DrawAxis(const cinder::Color &color) const {
  if (color == ci::Color("pink")) {
    ci::gl::drawStringCentered(
        "Pink Particle Speed",
        glm::vec2{(histogram_top_left_coordinate_.x +
                   histogram_bottom_right_coordinate_.x) /
                      2,
                  (pink_bottom_right_coordinate_ +
                   pink_bottom_right_coordinate_ + histogram_margin_) /
                      2});
    ci::gl::drawStringCentered(
        "1/λ", glm::vec2{window_length_ - container_margin_ / (1.25),
                         2 * histogram_margin_ + histogram_width_ +
                             histogram_width_ / 2});

  } else if (color == ci::Color("white")) {
    ci::gl::drawStringCentered(
        "White Particle Speed",
        glm::vec2{(histogram_top_left_coordinate_.x +
                   histogram_bottom_right_coordinate_.x) /
                      2,
                  (white_bottom_right_coordinate_ +
                   white_bottom_right_coordinate_ + histogram_margin_) /
                      2});
    ci::gl::drawStringCentered(
        "1/λ", glm::vec2{window_length_ - container_margin_ / (1.25),
                         histogram_margin_ + histogram_width_ / 2});

  } else if (color == ci::Color("teal")) {
    ci::gl::drawStringCentered(
        "Teal Particle Speed",
        glm::vec2{(histogram_top_left_coordinate_.x +
                   histogram_bottom_right_coordinate_.x) /
                      2,
                  (teal_bottom_right_coordinate_ + window_width_) / 2});
    ci::gl::drawStringCentered(
        "1/λ",
        glm::vec2{window_length_ - container_margin_ / (1.25),
                  window_width_ - histogram_margin_ - histogram_width_ / 2});
  }
}

std::map<double, size_t> Histogram::GetHistogramMap(const ci::Color& color) const {
  if (color == "pink") {
    return map_pink_;
  } else if (color == "white") {
    return map_white_;
  } else {
    return map_teal_;
  }
}

double Histogram::CalculateMaxSpeed() {
  double max_speed = 0;
  for (const auto &i : particles_) {
    double speed = glm::length(i.GetVelocity());
    if (speed > max_speed) {
      max_speed = speed;
    }
  }

  return max_speed;
}

}  // namespace idealgas
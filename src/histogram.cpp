#include "histogram.h"

#include "cinder/gl/gl.h"

using std::vector;

namespace idealgas {

Histogram::Histogram(const std::vector<Particle> &particles)
    : particles_(const_cast<std::vector<Particle> &>(particles)) {
  particles_ = particles;
}

void Histogram::Display() {
  // Display chart outlines
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(chart_pink_);
  ci::gl::drawStrokedRect(chart_white_);
  ci::gl::drawStrokedRect(chart_teal_);

  // Display histograms
  DrawGraph(map_pink_, ci::Color("pink"));
  DrawGraph(map_white_, ci::Color("white"));
  DrawGraph(map_teal_, ci::Color("teal"));
}

void Histogram::AdvanceOneFrame() {
  CreateMap();
}

void Histogram::CreateMap() {
  for (auto &particle : particles_) {
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

void Histogram::FillInMap(std::map<double, int> &map, double speed,
                          vector<double> &range) {
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

 void Histogram::DrawGraph(std::map<double, int> map, ci::Color color) {
   if (color == "pink") {
     ci::gl::color(color);

     for (size_t i = 0; i < map_pink_.size(); i++) {
       size_t amount = map_pink_.at(i);
       ci::gl::drawSolidRect(ci::Rectf(glm::vec2 {top_left_coordinate_, pink_bottom_right_coordinate_ - amount * y_scale_},
                                          glm::vec2 {top_left_coordinate_ + x_scale_, pink_bottom_right_coordinate_}));
       top_left_coordinate_ += x_scale_;
     }

   } else if (color == "white") {
     ci::gl::color(color);

     for (size_t i = 0; i < map_white_.size(); i++) {
       size_t amount = map_white_.at(i);
       ci::gl::drawSolidRect(ci::Rectf(glm::vec2 {top_left_coordinate_, white_bottom_right_coordinate_ - amount * y_scale_},
                                          glm::vec2 {top_left_coordinate_ + x_scale_, white_bottom_right_coordinate_}));
       top_left_coordinate_ += x_scale_;
     }

   } else if (color == "teal") {
     ci::gl::color(color);

     for (size_t i = 0; i < map_teal_.size(); i++) {
       size_t amount = map_teal_.at(i);
       ci::gl::drawSolidRect(ci::Rectf(glm::vec2 {top_left_coordinate_, teal_bottom_right_coordinate_ - amount * y_scale_},
                                       glm::vec2 {top_left_coordinate_ + x_scale_, teal_bottom_right_coordinate_}));
       top_left_coordinate_ += x_scale_;
     }
   }
 }

}  // namespace idealgas
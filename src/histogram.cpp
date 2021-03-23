#include "histogram.h"

#include "cinder/gl/gl.h"

using std::vector;

namespace idealgas {

Histogram::Histogram() {}

void Histogram::Display() {
  // Display chart outlines
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(chart_pink_);
  ci::gl::drawStrokedRect(chart_white_);
  ci::gl::drawStrokedRect(chart_teal_);

  // Display histograms
  DrawGraph(ci::Color("pink"));
  DrawGraph(ci::Color("white"));
  DrawGraph(ci::Color("teal"));
}

void Histogram::AdvanceOneFrame(const std::vector<Particle> &particles) {
  particles_ = particles;
  CreateMap();
}

void Histogram::CreateMap() {
  map_pink_.clear();
  map_white_.clear();
  map_teal_.clear();

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

void Histogram::FillInMap(std::map<double, int>& map, double speed,
                          const vector<double>& range) {
//  if (speed < range[0]) {
//    map[range[0]] += 1;
//  }
//  for (size_t i = 0; i < range.size() - 1; i++) {
//    if (speed >= range[i] && speed < range[i+1]) {
//      map[range[i]] += 1;
//    } else if (speed >= range[i-1])
//  }
//  for (size_t i = 0; i < range.size() - 1; i++) {
//    if (speed < range[0]) {
//      map[range[0]] += 1;
//    } else if (speed >= range[i] && speed < range[i + 1]) {
//      map[range[i]] += 1;
//    } else if (speed >= range[i]) {
//      map[range[i + 1]] += 1;
//    }
//  }
  if (speed <= range[0]) {
    map[range[0]] += 1;
  } else if (range[0] <= speed && speed < range[1]) {
    map[range[1]] += 1;
  } else if (range[1] <= speed && speed < range[2]) {
    map[range[2]] += 1;
  } else if (range[2] <= speed && speed < range[3]) {
    map[range[3]] += 1;
  } else if (range[3] <= speed && speed < range[4]) {
    map[range[4]] += 1;
  } else if (range[4] <= speed && speed < range[5]) {
    map[range[5]] += 1;
  } else if (range[5] <= speed && speed < range[6]) {
    map[range[6]] += 1;
  } else if (range[6] <= speed && speed < range[7]) {
    map[range[7]] += 1;
  } else if (range[7] <= speed && speed < range[8]) {
    map[range[8]] += 1;
  } else if (range[8] <= speed) {
    map[range[9]] += 1;
  }
}

 void Histogram::DrawGraph(const ci::Color& color) {
   double top_left_coordinate_ = chart_pink_.getUpperLeft().x; // top left coordinate of all histogram charts

   if (color == ci::Color("pink")) {
     for (const auto &particle : map_pink_) {
       size_t amount = particle.second;
       ci::gl::color(color);
       std::cout<<pink_bottom_right_coordinate_<<std::endl;
       std::cout<<top_left_x_coordinate_<<std::endl;
       ci::gl::drawSolidRect(ci::Rectf(glm::vec2 {top_left_coordinate_, pink_bottom_right_coordinate_ - amount * y_scale_},
                                          glm::vec2 {top_left_coordinate_ + x_scale_, pink_bottom_right_coordinate_}));
       top_left_coordinate_ += x_scale_;
     }

   } else if (color == ci::Color("white")) {
     for (const auto &particle : map_white_) {
       size_t amount = particle.second;
       ci::gl::color(color);
       ci::gl::drawSolidRect(ci::Rectf(glm::vec2 {top_left_coordinate_, white_bottom_right_coordinate_ - amount * y_scale_},
                                          glm::vec2 {top_left_coordinate_ + x_scale_, white_bottom_right_coordinate_}));
       top_left_coordinate_ += x_scale_;
     }

   } else if (color == ci::Color("teal")) {
     for (const auto &particle : map_teal_) {
       size_t amount = particle.second;
       ci::gl::color(color);
       ci::gl::drawSolidRect(ci::Rectf(glm::vec2 {top_left_coordinate_, teal_bottom_right_coordinate_ - amount * y_scale_},
                                          glm::vec2 {top_left_coordinate_ + x_scale_, teal_bottom_right_coordinate_}));
       top_left_coordinate_ += x_scale_;
     }
   }
 }

}  // namespace idealgas
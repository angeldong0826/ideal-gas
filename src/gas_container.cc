#include "gas_container.h"
#include "cinder/gl/gl.h"

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(const glm::vec2& top_left_corner,
                           const glm::vec2& bottom_right_corner)
    : calculation_(Calculation(top_left_corner, bottom_right_corner)) {
  top_left_coordinate_ = top_left_corner;
  bottom_right_coordinate_ = bottom_right_corner;
}

void GasContainer::Display() const {
  // Display container
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(
      ci::Rectf(top_left_coordinate_, bottom_right_coordinate_), border_width_);

  // Display particle
  //  ci::gl::color(ci::Color("pink"));
  //  ci::gl::drawSolidCircle(vec2(dummy_variable_, 200), 10);
  for (const auto& particle : particle_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
}

void GasContainer::AdvanceOneFrame() {
  ++dummy_variable_;
}

size_t GasContainer::RandomNumberGenerator(size_t lower_bound, size_t upper_bound) {
  size_t random_number_ = (lower_bound + (rand() % (upper_bound - lower_bound + 1)));
  return random_number_;
}

//void GasContainer::GenerateParticle() {
//  size_t x_ = RandomNumberGenerator(top_left_coordinate_.x, bottom_right_coordinate_.x);
//  size_t y_ = RandomNumberGenerator(top_left_coordinate_.y, bottom_right_coordinate_.y);
//}

}  // namespace idealgas
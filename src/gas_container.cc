#include "gas_container.h"

#include "cinder/gl/gl.h"

namespace idealgas {

GasContainer::GasContainer(const glm::vec2& top_left_coordinate,
                           const glm::vec2& bottom_right_coordinate)
    : particle_manager_(
          ParticleManager(top_left_coordinate, bottom_right_coordinate)) {
  top_left_coordinate_ = top_left_coordinate;
  bottom_right_coordinate_ = bottom_right_coordinate;

  GenerateParticle();
}

void GasContainer::Display() const {
  // Display container
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(
      ci::Rectf(top_left_coordinate_, bottom_right_coordinate_),
      kContainerBorderWidth);

  // Display particle
  for (const auto& particle : particle_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
}

void GasContainer::AdvanceOneFrame() {
  particle_manager_.CollidesWithParticle(particle_);
  particle_manager_.CollidesWithWall(particle_);

  // set resulting and updating velocity as new velocity of i
  for (auto& i : particle_) {
    particle_manager_.CalculatePostCollisionPosition(i);
  }
}

size_t GasContainer::RandomNumberGenerator(size_t lower_bound,
                                           size_t upper_bound) {
  size_t random_number_ =
      (lower_bound + (rand() % (upper_bound - lower_bound + 1)));

  return random_number_;
}

void GasContainer::GenerateParticle() {
  for (size_t particle = 0; particle < kParticleAmount; ++particle) {
    // generates random position for spawning

    double random_position_x_ =
        RandomNumberGenerator(top_left_coordinate_.x + kPinkRadius,
                              bottom_right_coordinate_.x - kPinkRadius);
    double random_position_y_ =
        RandomNumberGenerator(top_left_coordinate_.y + kPinkRadius,
                              bottom_right_coordinate_.y - kPinkRadius);
    glm::vec2 random_position_ = {
        random_position_x_,
        random_position_y_};  // random position particles spawn at

    // generates new particle and adds to particle_ vector
    if (particle % 3 == 0) {
      GasParticle pink_particle(kPinkMass, kPinkRadius, random_position_,
                                kPinkInitialVelocity, kPinkColor);
      particle_.push_back(pink_particle);

    } else if (particle % 3 == 1) {
      GasParticle purple_particle(kWhiteMass, kWhiteRadius, random_position_,
                                  kWhiteInitialVelocity, kWhiteColor);
      particle_.push_back(purple_particle);

    } else if (particle % 3 == 2) {
      GasParticle teal_particle(kTealMass, kTealRadius, random_position_,
                                kTealInitialVelocity, kTealColor);
      particle_.push_back(teal_particle);
    }
  }
}

std::vector<GasParticle> GasContainer::GetParticles() const {
  return particle_;
}
void GasContainer::SlowDown() {
  for (auto& particle : particle_) {
    particle.SetVelocity(particle.GetVelocity() * glm::vec2{0.1, 0.1});
  }
}

void GasContainer::SpeedUp() {
  for (auto& particle : particle_) {
    particle.SetVelocity(particle.GetVelocity() * glm::vec2{2.0, 2.0});
  }
}

}  // namespace idealgas
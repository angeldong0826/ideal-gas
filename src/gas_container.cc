#include "gas_container.h"

#include "cinder/gl/gl.h"

namespace idealgas {

GasContainer::GasContainer(const glm::vec2& top_left_coordinate,
                           const glm::vec2& bottom_right_coordinate)
    : particle_manager(
          ParticleManager(top_left_coordinate, bottom_right_coordinate)) {
  top_left_coordinate_ = top_left_coordinate;
  bottom_right_coordinate_ = bottom_right_coordinate;

  GenerateParticle();
}

void GasContainer::Display() const {
  // Display container
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(
      ci::Rectf(top_left_coordinate_, bottom_right_coordinate_), border_width_);

  // Display particle
  for (const auto& particle : particle_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
}

void GasContainer::AdvanceOneFrame() {
  // particle colliding with other particles
  for (size_t i = 0; i < particle_.size(); i++) {
    for (size_t j = i + 1; j < particle_.size(); j++) {
      // determines resulting velocity if i collides with another
      if (particle_manager.IsParticleCollision(particle_.at(i),
                                               particle_.at(j))) {
        glm::vec2 velocity_1 =
            particle_manager.CalculatePostParticleCollisionVelocity(
                particle_.at(i), particle_.at(j));
        glm::vec2 velocity_2 =
            particle_manager.CalculatePostParticleCollisionVelocity(
                particle_.at(j), particle_.at(i));

        particle_[i].SetVelocity(velocity_1);
        particle_[j].SetVelocity(velocity_2);
      }
    }
  }

  // i colliding with wall
  for (auto& i : particle_) {
    // i collides with corner, calculates and updates new velocity
    if (particle_manager.IsWallCollision(i, 'x') &&
        particle_manager.IsWallCollision(i, 'y')) {
      particle_manager.CalculatePostWallCollisionVelocity(i, 'x');
      particle_manager.CalculatePostWallCollisionVelocity(i, 'y');

      // i collides with top or bottom wall of container
      // calculates and updates new velocity
    } else if (particle_manager.IsWallCollision(i, 'x')) {
      particle_manager.CalculatePostWallCollisionVelocity(i, 'x');

      // i collides with left or right wall of container
      // calculates and updates new velocity
    } else if (particle_manager.IsWallCollision(i, 'y')) {
      particle_manager.CalculatePostWallCollisionVelocity(i, 'y');
    }
  }

  // set resulting and updating velocity as new velocity of i
  for (auto& i : particle_) {
    particle_manager.CalculatePostCollisionPosition(i);
  }
}

size_t GasContainer::RandomNumberGenerator(size_t lower_bound,
                                           size_t upper_bound) {
  size_t random_number_ =
      (lower_bound + (rand() % (upper_bound - lower_bound + 1)));

  return random_number_;
}

void GasContainer::GenerateParticle() {
  for (size_t particle = 0; particle < kParticleAmount; particle++) {
    // generates random position for spawning

    double random_position_x_ =
        RandomNumberGenerator(top_left_coordinate_.x + kPinkRadius,
                              bottom_right_coordinate_.x - kPinkRadius);
    double random_position_y_ =
        RandomNumberGenerator(top_left_coordinate_.y + kPinkRadius,
                              bottom_right_coordinate_.y - kPinkRadius);
    glm::vec2 random_position_ = {random_position_x_, random_position_y_};

    // generates new particle and adds to particle_ vector
    if (particle % 3 == 0) {
      Particle pink_particle(kPinkMass, kPinkRadius, random_position_,
                             kPinkInitialVelocity, kPinkColor);
      particle_.push_back(pink_particle);

    } else if (particle % 3 == 1) {
      Particle purple_particle(kWhiteMass, kWhiteRadius, random_position_,
                               kWhiteInitialVelocity, kWhiteColor);
      particle_.push_back(purple_particle);

    } else if (particle % 3 == 2) {
      Particle teal_particle(kTealMass, kTealRadius, random_position_,
                             kTealInitialVelocity, kTealColor);
      particle_.push_back(teal_particle);
    }
  }
}

const std::vector<Particle> GasContainer::GetParticles() const {
  return particle_;
}

}  // namespace idealgas
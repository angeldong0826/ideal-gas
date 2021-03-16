#include "gas_container.h"
#include "cinder/gl/gl.h"

namespace idealgas {

GasContainer::GasContainer(const glm::vec2& top_left_coordinate,
                           const glm::vec2& bottom_right_coordinate) :
    calculation_(Calculation(top_left_coordinate, bottom_right_coordinate)) {

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
  for (const auto & particle : particle_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
}

void GasContainer::AdvanceOneFrame() {
  // particle colliding with other particles
  for (size_t i = 0; i < particle_.size(); i++) {
    for (size_t j = i + 1; j < particle_.size(); j++) {

      // determines resulting velocity if i collides with another
      if (calculation_.CollideWithParticle(particle_.at(i), particle_.at(j))) {

        glm::vec2 velocity_1 = calculation_.PostParticleCollisionVelocity(particle_.at(i),particle_.at(j));
        glm::vec2 velocity_2 = calculation_.PostParticleCollisionVelocity(particle_.at(j),particle_.at(i));

        particle_[i].SetVelocity(velocity_1);
        particle_[j].SetVelocity(velocity_2);

      }
    }
  }

   // i colliding with wall
  for (auto & i : particle_) {

    // i collides with corner, calculates and updates new velocity
    if (calculation_.CollideWithWall(i, 'x') &&
        calculation_.CollideWithWall(i, 'y')) {

      calculation_.PostWallCollisionVelocity(i, 'x');
      calculation_.PostWallCollisionVelocity(i, 'y');

    // i collides with top or bottom wall of container
    // calculates and updates new velocity
    } else if (calculation_.CollideWithWall(i, 'x')) {
      calculation_.PostWallCollisionVelocity(i, 'x');

    // i collides with left or right wall of container
    // calculates and updates new velocity
    } else if (calculation_.CollideWithWall(i, 'y')) {
      calculation_.PostWallCollisionVelocity(i, 'y');
    }
  }

  // set resulting and updating velocity as new velocity of i
  for (auto & i : particle_) {
    calculation_.PostCollisionPosition(i);
  }
}

size_t GasContainer::RandomNumberGenerator(size_t lower_bound, size_t upper_bound) {
  size_t random_number_ = (lower_bound + (rand() % (upper_bound - lower_bound + 1)));

  return random_number_;
}

void GasContainer::GenerateParticle() {
  for (size_t particle = 0; particle < kParticleAmount; particle++) {

    // generates random position for spawning
    double random_position_x_ = RandomNumberGenerator(top_left_coordinate_.x + kParticleRadius,
                                                      bottom_right_coordinate_.x - kParticleRadius);
    double random_position_y_ = RandomNumberGenerator(top_left_coordinate_.y + kParticleRadius,
                                                      bottom_right_coordinate_.y - kParticleRadius);
    vec2 random_position_ = {random_position_x_, random_position_y_};

    // generates new particle and adds to particle_ vector
    Particle generate_particle(kParticleMass, kParticleRadius, random_position_,
                               kParticleInitialVelocity, color);
    particle_.push_back(generate_particle);
  }

//  FOR WEEK 2
//  double x_ = RandomNumberGenerator(top_left_coordinate_.x + kPinkRadius,
//                                    bottom_right_coordinate_.x - kPinkRadius);
//  double y_ = RandomNumberGenerator(top_left_coordinate_.y + kPinkRadius,
//                                    bottom_right_coordinate_.y - kPinkRadius);
//
//  if (particle_color == ci::Color("pink")) {
//    Particle pink_particle(kPinkMass, kPinkRadius, glm::vec2 {x_, y_},
//                             kPinkInitialVelocity, particle_color);
//
//    particle_.push_back(pink_particle);
//
//  } else if (particle_color == ci::Color("purple")) {
//    Particle purple_particle(kPurpleMass, kPurpleRadius, glm::vec2 {x_, y_},
//                             kPurpleInitialVelocity, particle_color);
//
//    particle_.push_back(purple_particle);
//
//  } else if (particle_color == ci::Color("orange")) {
//    Particle orange_particle(kOrangeMass, kOrangeRadius, glm::vec2 {x_, y_},
//                             kOrangeInitialVelocity, particle_color);
//
//    particle_.push_back(orange_particle);
//
//  } else {
//    Particle pink_particle(kPinkMass, kPinkRadius, glm::vec2 {x_, y_},
//                           kPinkInitialVelocity, particle_color);
//
//    particle_.push_back(pink_particle);
//  }
}

}  // namespace idealgas
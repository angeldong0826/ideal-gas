#include "gas_container.h"
#include "cinder/gl/gl.h"

namespace idealgas {

using glm::vec2;

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
  for (size_t particle = 0; particle < particle_.size(); particle++) {
    for (size_t target_particle = particle + 1; target_particle < particle_.size();
                                                target_particle++) {

      // determines resulting velocity if particle collides with another
      if (calculation_.CollideWithParticle(particle_.at(particle),
                                      particle_.at(target_particle))) {
        calculation_.PostParticleCollisionVelocity(particle_.at(particle),particle_.at(target_particle));

        // set resulting velocity as new velocity of particle
        calculation_.PostCollisionPosition(particle_.at(particle));
        calculation_.PostCollisionPosition(particle_.at(target_particle));
      }
    }

   // particle colliding with wall

    // particle collides with corner, calculates and updates new velocity
    if (calculation_.CollideWithWall(particle_.at(particle), 'x') &&
        calculation_.CollideWithWall(particle_.at(particle), 'y')) {

      calculation_.PostWallCollisionVelocity(particle_.at(particle), 'x');
      calculation_.PostWallCollisionVelocity(particle_.at(particle), 'y');

    // particle collides with top or bottom wall of container
    // calculates and updates new velocity
    } else if (calculation_.CollideWithWall(particle_.at(particle), 'x')) {
      calculation_.PostWallCollisionVelocity(particle_.at(particle), 'x');

    // particle collides with left or right wall of container
    // calculates and updates new velocity
    } else if (calculation_.CollideWithWall(particle_.at(particle), 'y')) {
      calculation_.PostWallCollisionVelocity(particle_.at(particle), 'y');
    }

    // updates new position after collision
    calculation_.PostCollisionPosition(particle_.at(particle));
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
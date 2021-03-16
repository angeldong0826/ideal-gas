#include "calculation.h"

#include <glm/vec2.hpp>

namespace idealgas {

Calculation::Calculation(const glm::vec2 top_left_, const glm::vec2 bottom_right_) {
  top_left_coordinate_ = top_left_;
  bottom_right_coordinate_ = bottom_right_;
}

bool Calculation::CollideWithParticle(Particle particle, Particle target_particle) {

  // storing velocity and position difference as vectors
  glm::vec2 velocity_difference = particle.GetVelocity() - target_particle.GetVelocity();
  glm::vec2 position_difference = particle.GetPosition() - target_particle.GetPosition();

  // conditions to meet to determine if particles have collided with each other
  if (((glm::distance(particle.GetPosition(), target_particle.GetPosition())) <=
      (particle.GetRadius() + target_particle.GetRadius())) &&
      (glm::dot(velocity_difference, position_difference) < 0)) {
    return true;
  }

  return false;
}

bool Calculation::CollideWithWall(Particle& particle, char axis) {
  // lower-cases all input axis
  char wall_direction = towlower(axis);

  // if particle collides with top or bottom wall of container
  if (wall_direction == 'x') {
    if ((particle.GetVelocity().y < 0) && particle.GetPosition().y -
         particle.GetRadius() <= top_left_coordinate_.y) {
      return true;
    } else if ((particle.GetVelocity().y > 0) && particle.GetPosition().y +
         particle.GetRadius() >= bottom_right_coordinate_.y) {
      return true;
    }

    return false;
  }

  // if particle collides with left or right wall of container
  if (wall_direction == 'y') {
    if ((particle.GetVelocity().x < 0) && particle.GetPosition().x -
         particle.GetRadius() <= top_left_coordinate_.x) {
      return true;
    } else if ((particle.GetVelocity().x > 0) && particle.GetPosition().x +
         particle.GetRadius() >= bottom_right_coordinate_.x) {
      return true;
    } return false;
  }

  return false;
}

void Calculation::PostCollisionPosition(Particle& particle) {
  // change in position = velocity * time
  particle.SetPosition(particle.GetPosition() + particle.GetVelocity());
}

glm::vec2 Calculation::PostParticleCollisionVelocity(Particle& particle, Particle& target_particle) {

  // Calculating the constant in the equation that calculates new particle
  // velocity after collision with another particle
  double mass_ratio = 2 * target_particle.GetMass() / (particle.GetMass() + target_particle.GetMass());
  double constant_in_velocity_equation = mass_ratio * ((glm::dot(particle.GetVelocity() -
       target_particle.GetVelocity(), particle.GetPosition() -
       target_particle.GetPosition())) / (pow(glm::length(particle.GetPosition() -
       target_particle.GetPosition()), 2)));

  // finishes calculating resulting velocity
  glm::vec2 resulting_velocity = glm::vec2(constant_in_velocity_equation * (particle.GetPosition().x - target_particle.GetPosition().x),
                          constant_in_velocity_equation * (particle.GetPosition().y - target_particle.GetPosition().y));

  return particle.GetVelocity() - resulting_velocity;
}

void Calculation::PostWallCollisionVelocity(Particle& particle, char axis) {

  // Separate out x and y directions of input particle's velocity and store
  // them as doubles
  double x_velocity = particle.GetVelocity().x;
  double y_velocity = particle.GetVelocity().y;

  // lower-case all input axis values
  char wall_direction = towlower(axis);

  // if particle hits the left of right wall of container
  if (wall_direction == 'y') {
    x_velocity *= -1;
  }
  // if particle hits the top or bottom wall of container
  if (wall_direction == 'x') {
    y_velocity *= -1;
  }

  // update particle velocity
  particle.SetVelocity(glm::vec2(x_velocity, y_velocity));
}

} // namespace idealgas
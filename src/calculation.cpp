#include "calculation.h"

#include <glm/vec2.hpp>

namespace idealgas {

Calculation::Calculation(const glm::vec2 top_left_, const glm::vec2 bottom_right_) {
  top_left_coordinate_ = top_left_;
  bottom_right_coordinate_ = bottom_right_;
}

bool Calculation::CollideWithParticle(Particle particle, Particle target_particle) {

  // storing velocity and position difference as vectors
  glm::vec2 velocity_difference_ = particle.GetVelocity() - target_particle.GetVelocity();
  glm::vec2 position_difference_ = particle.GetPosition() - target_particle.GetPosition();

  // conditions to meet to determine if particles have collided with each other
  if (((glm::distance(particle.GetPosition(), target_particle.GetPosition())) <
      (particle.GetRadius() + target_particle.GetRadius())) &&
      (glm::dot((velocity_difference_), (position_difference_)) < 0)) {
    return true;
  }
  return false;
}

bool Calculation::CollideWithWall(Particle& particle, char axis) {
  // lower-cases all input axis
  char wall_direction = towlower(axis);

  // if particle collides with top or bottom wall of container
  if (wall_direction == 'x') {
    if ((particle.GetVelocity().x < 0) && particle.GetPosition().x -
         particle.GetRadius() <= top_left_coordinate_.x) {
      return true;
    } else if ((particle.GetVelocity().x > 0) && particle.GetPosition().x +
         particle.GetRadius() >= bottom_right_coordinate_.x) {
      return true;
    } return false;
  }

  // if particle collides with left or right wall of container
  if (wall_direction == 'y') {
    if ((particle.GetVelocity().y < 0) && particle.GetPosition().y -
         particle.GetRadius() <= top_left_coordinate_.y) {
      return true;
    } else if ((particle.GetVelocity().y > 0) && particle.GetPosition().y +
         particle.GetRadius() >= bottom_right_coordinate_.y) {
      return true;
    } return false;
  }

  return false;
}

void Calculation::PostCollisionPosition(Particle& particle) {
  // change in position = velocity * time
  particle.SetPosition(particle.GetPosition() + particle.GetVelocity());
}

void Calculation::PostParticleCollisionVelocity(Particle& particle, Particle& target_particle) {

  // Calculating the constant in the equation that calculates new particle
  // velocity after collision with another particle
  double constant_in_velocity_equation = ((2 * target_particle.GetMass())/(particle.GetMass() +
       target_particle.GetMass())) * ((glm::dot(particle.GetVelocity() -
       target_particle.GetVelocity(), particle.GetPosition() -
       target_particle.GetPosition())) / (pow(glm::length(particle.GetPosition() -
       target_particle.GetPosition()), 2)));

  // finishes calculating and setting resulting velocity to particle collided
  particle.SetVelocity(particle.GetVelocity() -
      (glm::vec2(particle.GetPosition().x * constant_in_velocity_equation,
                 particle.GetPosition().y * constant_in_velocity_equation)) +
      (glm::vec2(target_particle.GetPosition().x * constant_in_velocity_equation,
                 particle.GetPosition().y * constant_in_velocity_equation)));
}

void Calculation::PostWallCollisionVelocity(Particle& particle, char axis) {

  // Separate out x and y directions of input particle's velocity and store
  // them as doubles
  double x_velocity = particle.GetVelocity().x;
  double y_velocity = particle.GetVelocity().y;

  // lower-case all input axis values
  char wall_direction = towlower(axis);

  if (wall_direction != 'x' && wall_direction != 'y') {
    return;
  }

  // if particle hits the top of bottom wall of container
  if (wall_direction == 'x') {
    x_velocity = -1 * particle.GetVelocity().x;
  }
  // if particle hits the left or right wall of container
  if (wall_direction == 'y') {
    y_velocity = -1 * particle.GetVelocity().y;
  }

  // update particle velocity
  particle.SetVelocity(glm::vec2{x_velocity, y_velocity});
}

} // namespace idealgas
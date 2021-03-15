#include "calculation.h"

#include <glm/vec2.hpp>

namespace idealgas {

Calculation::Calculation(const glm::vec2 top_left_, const glm::vec2 bottom_right_) {
  top_left_coordinate_ = top_left_;
  bottom_right_coordinate_ = bottom_right_;
}

bool Calculation::CollideWithParticle(Particle particle,
                                      Particle target_particle) {
  if ((glm::distance(particle.GetPosition(), target_particle.GetPosition())) <=
      (particle.GetRadius() + target_particle.GetRadius()) &&
      (glm::dot((particle.GetVelocity() - target_particle.GetVelocity()),
                (particle.GetPosition() - target_particle.GetPosition())) < 0)) {
    return true;
  }
  return false;
}

bool Calculation::CollideWithWall(Particle& particle, char axis) {
  char wall_direction = towlower(axis);

  if (wall_direction == 'x') {
    if ((particle.GetVelocity().x < 0) && particle.GetPosition().x -
         particle.GetRadius() <= top_left_coordinate_.x) {
      return true;
    } else if ((particle.GetVelocity().x > 0) && particle.GetPosition().x +
         particle.GetRadius() >= bottom_right_coordinate_.x) {
      return true;
    } return false;
  }

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
  particle.SetPosition(particle.GetPosition() + particle.GetVelocity());
}



void Calculation::PostParticleCollisionVelocity(Particle& particle, Particle& target_particle) {
  double constant_in_velocity_equation = ((2 * target_particle.GetMass())/(particle.GetMass() +
       target_particle.GetMass())) * ((glm::dot(particle.GetVelocity() -
       target_particle.GetVelocity(),particle.GetPosition() -
       target_particle.GetPosition())) / (pow(glm::length(particle.GetPosition() -
       target_particle.GetPosition()), 2)));

  particle.SetVelocity(particle.GetVelocity() -
      (glm::vec2(particle.GetPosition().x * constant_in_velocity_equation,
                 particle.GetPosition().y * constant_in_velocity_equation)) +
      (glm::vec2(target_particle.GetPosition().x * constant_in_velocity_equation,
                 particle.GetPosition().y * constant_in_velocity_equation)));
}

void Calculation::PostWallCollisionVelocity(Particle& particle, char axis) {
  double x_velocity = particle.GetVelocity().x;
  double y_velocity = particle.GetVelocity().y;

  char wall_direction = towlower(axis);

  if (wall_direction != 'x' && wall_direction != 'y') {
    return;
  }

  if (wall_direction == 'x') {
    x_velocity *= -1;
  }
  if (wall_direction == 'y') {
    y_velocity *= -1;
  }

  // update particle velocity
  particle.SetVelocity(glm::vec2{x_velocity, y_velocity});
}

} // namespace idealgas
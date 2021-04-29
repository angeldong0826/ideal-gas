#include "particle_manager.h"

#include <glm/vec2.hpp>

namespace idealgas {

ParticleManager::ParticleManager(const glm::vec2& top_left_,
                                 const glm::vec2& bottom_right_) {
  top_left_coordinate_ = top_left_;
  bottom_right_coordinate_ = bottom_right_;
}

bool ParticleManager::IsParticleCollision(GasParticle& particle,
                                          GasParticle& target_particle) const {
  // storing velocity and position difference as vectors
  glm::vec2 velocity_difference =
      particle.GetVelocity() - target_particle.GetVelocity();
  glm::vec2 position_difference =
      particle.GetPosition() - target_particle.GetPosition();

  // conditions to meet to determine if particles have collided with each other
  if (((glm::distance(particle.GetPosition(), target_particle.GetPosition())) <=
       (particle.GetRadius() + target_particle.GetRadius())) &&
      (glm::dot(velocity_difference, position_difference) < 0)) {
    return true;
  }

  return false;
}

bool ParticleManager::IsWallCollision(GasParticle& particle, bool axis) const {
  // if particle collides with top or bottom wall of container
  if (axis) {
    if ((particle.GetVelocity().y < 0) &&
        particle.GetPosition().y - particle.GetRadius() <=
            top_left_coordinate_.y) {
      return true;
    } else if ((particle.GetVelocity().y > 0) &&
               particle.GetPosition().y + particle.GetRadius() >=
                   bottom_right_coordinate_.y) {
      return true;
    }

    return false;
  }

  // else if particle collides with left or right wall of container
  if ((particle.GetVelocity().x < 0) &&
      particle.GetPosition().x - particle.GetRadius() <=
          top_left_coordinate_.x) {
    return true;
  } else if ((particle.GetVelocity().x > 0) &&
             particle.GetPosition().x + particle.GetRadius() >=
                 bottom_right_coordinate_.x) {
    return true;
  }
  return false;
}

void ParticleManager::CalculatePostCollisionPosition(GasParticle& particle) {
  // change in position = velocity * time
  particle.SetPosition(particle.GetPosition() + particle.GetVelocity());
}

glm::vec2 ParticleManager::CalculatePostParticleCollisionVelocity(
    GasParticle& particle, GasParticle& target_particle) const {
  // Calculating the constant in the equation that calculates new particle
  // velocity after collision with another particle
  double mass_ratio = 2 * target_particle.GetMass() /
                      (particle.GetMass() + target_particle.GetMass());
  double constant_in_velocity_equation =
      mass_ratio *
      ((glm::dot(particle.GetVelocity() - target_particle.GetVelocity(),
                 particle.GetPosition() - target_particle.GetPosition())) /
       (pow(glm::length(particle.GetPosition() - target_particle.GetPosition()),
            2)));

  // finishes calculating resulting velocity
  glm::vec2 resulting_velocity = glm::vec2(
      constant_in_velocity_equation *
          (particle.GetPosition().x - target_particle.GetPosition().x),
      constant_in_velocity_equation *
          (particle.GetPosition().y - target_particle.GetPosition().y));

  return particle.GetVelocity() - resulting_velocity;
}

void ParticleManager::CalculatePostWallCollisionVelocity(GasParticle& particle,
                                                         bool axis) {
  // Separate out x and y directions of input particle's velocity and store
  // them as doubles
  double x_velocity = particle.GetVelocity().x;
  double y_velocity = particle.GetVelocity().y;

  // if particle hits the left of right wall of container
  if (!axis) {
    x_velocity *= -1;
  }
  // if particle hits the top or bottom wall of container
  if (axis) {
    y_velocity *= -1;
  }

  // update particle velocity
  particle.SetVelocity(glm::vec2(x_velocity, y_velocity));
}

void ParticleManager::CollidesWithParticle(std::vector<GasParticle>& particle) {
  for (size_t i = 0; i < particle.size(); ++i) {
    for (size_t j = i + 1; j < particle.size(); ++j) {
      // determines resulting velocity if i collides with another
      if (IsParticleCollision(particle[i], particle[j])) {
        glm::vec2 velocity_1 =
            CalculatePostParticleCollisionVelocity(particle[i], particle.at(j));
        glm::vec2 velocity_2 =
            CalculatePostParticleCollisionVelocity(particle[j], particle.at(i));

        particle[i].SetVelocity(velocity_1);
        particle[j].SetVelocity(velocity_2);
      }
    }
  }
}
void ParticleManager::CollidesWithWall(std::vector<GasParticle>& particle) {
  for (auto& i : particle) {
    // i collides with corner, calculates and updates new velocity
    if (IsWallCollision(i, true) && IsWallCollision(i, false)) {
      CalculatePostWallCollisionVelocity(i, true);
      CalculatePostWallCollisionVelocity(i, false);

      // i collides with top or bottom wall of container
      // calculates and updates new velocity
    } else if (IsWallCollision(i, true)) {
      CalculatePostWallCollisionVelocity(i, true);

      // i collides with left or right wall of container
      // calculates and updates new velocity
    } else if (IsWallCollision(i, false)) {
      CalculatePostWallCollisionVelocity(i, false);
    }
  }
}

}  // namespace idealgas
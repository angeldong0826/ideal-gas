#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

namespace idealgas {

/**
 * Class that calculates the physics behind the simulation.
 */
class ParticleManager {
 public:
  /**
   * Constructor that initializes container and takes in container boundaries.
   *
   * @param top_left_corner of set container
   * @param bottom_right_corner of set container
   */
  ParticleManager(glm::vec2 top_left_coordinate, glm::vec2 bottom_right_coordinate);

  /**
   * Method that determines whether or not particle collides with another particle.
   *
   * @param particle
   * @param target_particle
   * @return true if collided
   */
  bool IsParticleCollision(Particle particle, Particle target_particle) const;

  /**
   * Method that determines whether or not particle collides with wall.
   *
   * @param particle to be collided
   * @param x or y direction of wall, x true y false
   * @return true if collided
   */
  bool IsWallCollision(Particle particle, bool axis) const;

  /**
   * Method that calculates new particle position after collision.
   *
   * @param particle collided
   */
  void CalculatePostCollisionPosition(Particle& particle);

  /**
   * Method that calculates velocity after particle collision.
   *
   * @param particle collided
   * @param target_particle particle collided with first particle
   * @return new calculated velocity after collision as a vector
   */
  glm::vec2 CalculatePostParticleCollisionVelocity(Particle& particle, Particle& target_particle) const;

  /**
   * Method that calculates velocity after particle-wall collision.
   *
   * @param particle collided
   * @param axis wall that particle collide with, x true y false
   */
  void CalculatePostWallCollisionVelocity(Particle& particle, bool axis);

 private:
  glm::vec2 top_left_coordinate_; // top left corner of container
  glm::vec2 bottom_right_coordinate_; // bottom right corner of container
};

} // namespace idealgas
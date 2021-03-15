#pragma once

#include "cinder/gl/gl.h"
#include "gas_particle.h"

namespace idealgas {

class Calculation {
 public:
  /**
   * Constructor that initializes container and takes in container boundaries.
   *
   * @param top_left_corner of set container
   * @param bottom_right_corner of set container
   */
  Calculation(glm::vec2 top_left_coordinate, glm::vec2 bottom_right_coordinate);

  /**
   * Method that determines whether or not particle collides with another particle.
   *
   * @param particle
   * @param target_particle
   * @return true if collided
   */
  bool CollideWithParticle(Particle particle, Particle target_particle);

  /**
   * Method that determines whether or not particle collides with wall.
   *
   * @param particle to be collided
   * @param x or y direction of wall
   * @return true if collided
   */
  bool CollideWithWall(Particle& particle, char axis);

  /**
   * Method that calculates new particle position after collision.
   *
   * @param particle collided
   */
  void PostCollisionPosition(Particle& particle);

  /**
   * Method that calculates velocity after particle collision.
   *
   * @param particle collided
   * @param target_particle particle collided with first particle
   */
  void PostParticleCollisionVelocity(Particle& particle, Particle& target_particle);

  /**
   * Method that calculates velocity after particle-wall collision.
   *
   * @param particle collided
   * @param axis wall that particle collide with
   */
  void PostWallCollisionVelocity(Particle& particle, char axis);

 private:
  glm::vec2 top_left_coordinate_; // top left corner of container
  glm::vec2 bottom_right_coordinate_; // bottom right corner of container
};

} // namespace idealgas
#pragma once

#include "calculation.h"
#include "cinder/gl/gl.h"
#include "gas_particle.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * Constructor that takes in the boundaries of container and initializes container.
   *
   * @param top_left_corner coordinates of top left corner of container
   * @param bottom_right_corner coordinates of bottom right corner of container
   */
  GasContainer(const glm::vec2& top_left_corner, const glm::vec2& bottom_right_corner);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  /**
   * Method that generates a random number between the lower and upper input bounds.
   *
   * @param lower_bound as a double
   * @param upper_bound as a double
   * @return randomly generated number as a double
   */
  size_t RandomNumberGenerator(size_t lower_bound, size_t upper_bound);

  /**
   * Method that generates a new particle to be added to the container.
   */
  void GenerateParticle();

 private:

  glm::vec2 top_left_coordinate_; // top left corner of container
  glm::vec2 bottom_right_coordinate_; // bottom right corner of container
  glm::vec2 kParticleInitialVelocity = {1.0,1.0}; // particle's initial velocity
  const size_t border_width_ = 8; // border width of container
  const size_t kParticleAmount = 30; // amount of particles in container
  const double kParticleRadius = 7.0; // particle radius
  const double kParticleMass = 1.0; // particle mass
  const ci::Color color = "pink"; // particle color

  Calculation calculation_; // calculation purposes
  std::vector<Particle> particle_; // vector of particles in container

//  // pink particles attributes
//  const double kPinkMass = 10.0;
//  const double kPinkRadius = 10.0;
//  const glm::vec2 kPinkInitialVelocity = {20.0,1.0};
//
//  // purple particles attributes
//  const double kPurpleMass = 22.0;
//  const double kPurpleRadius = 22.0;
//  const glm::vec2 kPurpleInitialVelocity = {10.5, -0.85};
//
//  // orange particles attributes
//  const double kOrangeMass = 40.0;
//  const double kOrangeRadius = 40.0;
//  const glm::vec2 kOrangeInitialVelocity = {-6.0, -0.6};
};

}  // namespace idealgas

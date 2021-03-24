#pragma once

#include "cinder/gl/gl.h"
#include "gas_particle.h"
#include "particle_manager.h"

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * Constructor that takes in the boundaries of container and initializes
   * container.
   *
   * @param top_left_corner coordinates of top left corner of container
   * @param bottom_right_corner coordinates of bottom right corner of container
   */
  GasContainer(const glm::vec2& top_left_corner,
               const glm::vec2& bottom_right_corner);

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
   * Method that generates a random number between the lower and upper input
   * bounds.
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

  /**
   * Getter method to retrieve vector of particles in container.
   * @return vector of particles in container
   */
  std::vector<GasParticle> GetParticles() const;

  /**
   * Method that slows down particle velocity.
   */
  void SlowDown();

  /**
   * Method that speeds up particle velocity.
   */
  void SpeedUp();

 private:
  // container attributes
  const size_t kContainerBorderWidth = 5;  // border width of container
  const size_t kParticleAmount = 42;       // amount of particles in container

  // pink particles attributes
  const double kPinkMass = 5.0;         // pink particle mass
  const double kPinkRadius = 7.0;       // pink particle radius
  const ci::Color kPinkColor = "pink";  // pink particle color
  const glm::vec2 kPinkInitialVelocity = {
      6.0, 6.0};  // pink particle initial velocity

  // teal particles attributes
  const double kTealMass = 20.0;        // teal particle mass
  const double kTealRadius = 20.0;      // teal particle radius
  const ci::Color kTealColor = "teal";  // teal particle color
  const glm::vec2 kTealInitialVelocity = {
      4.0, -4.0};  // teal particle initial velocity

  // white particles attributes
  const double kWhiteMass = 30.0;         // white particle mass
  const double kWhiteRadius = 30.0;       // white particle radius
  const ci::Color kWhiteColor = "white";  // white particle color
  const glm::vec2 kWhiteInitialVelocity = {
      1.4, 1.4};  // white particle initial velocity

  glm::vec2 top_left_coordinate_;      // top left corner of container
  glm::vec2 bottom_right_coordinate_;  // bottom right corner of container

  std::vector<GasParticle> particle_;  // vector of particles in container
  ParticleManager particle_manager_;   // calculation purposes
};

}  // namespace idealgas

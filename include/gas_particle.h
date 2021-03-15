#pragma once

#include <cinder/Color.h>

#include <string>
#include <vector>

//#include "calculation.h"

namespace idealgas {

class Particle {
 public:
  /**
   * Constructor that initializes particle characteristics.
   *
   * @param mass particle mass as a double
   * @param radius particle radius as a double
   * @param position particle position as a vec2
   * @param velocity particle velocity as a vec2
   * @param color particle color as a Color
   **/
  Particle(double mass, double radius, glm::vec2 position, glm::vec2 velocity,
           ci::Color color);

  // Getters
  double GetMass();
  double GetRadius() const;
  glm::vec2 GetPosition() const;
  glm::vec2 GetVelocity();
  ci::Color GetColor() const;
  // double GetSpeed();

  // Setters
  void SetMass(double mass);
  void SetRadius(double radius);
  void SetPosition(glm::vec2 position);
  void SetVelocity(glm::vec2 velocity);
  void SetColor(ci::Color color);

 private:
  double mass_; // particle mass
  double radius_; // particle radius
  glm::vec2 position_; // particle position
  glm::vec2 velocity_; // particle velocity
  ci::Color color_; // particle color
};

} // namespace idealgas
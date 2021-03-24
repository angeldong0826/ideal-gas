#include "gas_particle.h"

namespace idealgas {

GasParticle::GasParticle(double mass, double radius, const glm::vec2 position,
                         const glm::vec2 velocity, const ci::Color color) {
  mass_ = mass;
  radius_ = radius;
  position_ = position;
  velocity_ = velocity;
  color_ = color;
}

// Getters
double GasParticle::GetMass() const {
  return mass_;
}
double GasParticle::GetRadius() const {
  return radius_;
}
glm::vec2 GasParticle::GetPosition() const {
  return position_;
}
glm::vec2 GasParticle::GetVelocity() const {
  return velocity_;
}
ci::Color GasParticle::GetColor() const {
  return color_;
}

// Setters
void GasParticle::SetPosition(glm::vec2 position) {
  position_ = position;
}
void GasParticle::SetVelocity(glm::vec2 velocity) {
  velocity_ = velocity;
}

}  // namespace idealgas
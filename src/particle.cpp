#include "particle.h"

namespace idealgas {

Particle::Particle(double mass, double radius, const glm::vec2 position, const glm::vec2 velocity, ci::Color color) {
  mass_ = mass;
  radius_ = radius;
  position_ = position;
  velocity_ = velocity;
  color_ = color;
}

// Getters
double Particle::GetMass() const {
  return mass_;
}
double Particle::GetRadius() const {
  return radius_;
}
glm::vec2 Particle::GetPosition() const {
  return position_;
}
glm::vec2 Particle::GetVelocity() const {
  return velocity_;
}
ci::Color Particle::GetColor() const {
  return color_;
}

// Setters
void Particle::SetMass(double mass) {
  mass_ =  mass;
}
void Particle::SetRadius(double radius) {
  radius_ = radius;
}
void Particle::SetPosition(glm::vec2 position) {
  position_ = position;
}
void Particle::SetVelocity(glm::vec2 velocity) {
  velocity_ = velocity;
}
void Particle::SetColor(ci::Color color) {
  color_ = color;
}

} // namespace idealgas
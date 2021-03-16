#include <catch2/catch.hpp>

#include <gas_container.h>
#include <calculation.h>

using idealgas::GasContainer;
using idealgas::Calculation;
using idealgas::Particle;

TEST_CASE("Particles colliding with other particles") {
  Calculation calculation(glm::vec2 {0.0,0.0}, glm::vec2 {200.0,200.0});
  Particle particle(1.0, 1.0, glm::vec2 {19.9,20.0}, glm::vec2 {0.1,0}, "pink");
  Particle target_particle(1.0, 1.0, glm::vec2 {21.5, 21.4}, glm::vec2 {-0.1,0}, "pink");

  SECTION("Particle does not collide with particle") {

  }

  SECTION("Particle collides with particle on right") {
    REQUIRE(calculation.CollideWithParticle(particle, target_particle));
  }

  SECTION("Particle collides with particle on left") {

  }

  SECTION("Particle collides with particle on top") {

  }

  SECTION("Particle collides with particle on bottom") {

  }

  SECTION("Particle collides with particle diagonally") {

  }
}

TEST_CASE("Particle colliding with container wall") {
  SECTION("Particle does not collide with wall") {

  }

  SECTION("Particle collides with right wall") {

  }

  SECTION("Particle collides with left wall") {

  }

  SECTION("Particle collides with top wall") {

  }

  SECTION("Particle collides with bottom wall") {

  }

  SECTION("Particle collides with corner") {

  }
}

/*
TODO: Rename this test file. You'll also need to modify CMakeLists.txt.

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

TODO Delete this comment and the placeholder test before submitting your code.
*/

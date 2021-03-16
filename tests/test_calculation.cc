#include <catch2/catch.hpp>

#include <gas_container.h>
#include <calculation.h>

using idealgas::GasContainer;
using idealgas::Calculation;
using idealgas::Particle;

glm::vec2 top_left_coordinate = {0.0, 0.0};
glm::vec2 bottom_right_coordinate = {200.0, 200.0};
Calculation calculation(top_left_coordinate, bottom_right_coordinate);

TEST_CASE("Particles colliding with other particles") {
  Particle particle_moving_right(1.0, 1.0, glm::vec2 {100.0,100.0}, glm::vec2 {1.0,0.0}, "pink");
  Particle particle_moving_left(1.0, 1.0, glm::vec2 {100.0,100.0}, glm::vec2 {-1.0,0.0}, "pink");
  Particle particle_moving_up(1.0, 1.0, glm::vec2 {100.0,100.0}, glm::vec2 {0.0,1.0}, "pink");
  Particle particle_moving_down(1.0, 1.0, glm::vec2 {100.0,100.0}, glm::vec2 {0.0,-1.0}, "pink");
  Particle particle_moving_diagonally(1.0, 1.0, glm::vec2 {100.0,100.0}, glm::vec2 {1.0,1.0}, "pink");
  Particle particle_moving_antidiagonally(1.0, 1.0, glm::vec2 {100.0,100.0}, glm::vec2 {-1.0,-1.0}, "pink");

  SECTION("Particle does not collide with particle") {
    Particle target_particle(1.0, 1.0, glm::vec2 {101.1,100.0}, glm::vec2 {1.0,0}, "pink");
    REQUIRE_FALSE(calculation.CollideWithParticle(particle_moving_right, target_particle));
  }

  SECTION("Particle collides with particle on right") {
    Particle target_particle(1.0, 1.0, glm::vec2 {101.0, 100.0}, glm::vec2 {-1.0,0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_right, target_particle));
  }

  SECTION("Particle collides with particle on left") {
    Particle target_particle(1.0,1.0,glm::vec2 {99.0, 100.0}, glm::vec2 {1.0,0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_left, target_particle));
  }

  SECTION("Particle collides with particle on top") {
    Particle target_particle(1.0,1.0,glm::vec2 {100.0,101.0}, glm::vec2 {0.0,-1.0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_up, target_particle));
  }

  SECTION("Particle collides with particle on bottom") {
    Particle target_particle(1.0,1.0,glm::vec2 {100.0,99.0}, glm::vec2 {0.0,1.0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_down, target_particle));
  }

  SECTION("Particle collides with particle diagonally") {
    Particle target_particle(1.0,1.0,glm::vec2 {101.0,101.0}, glm::vec2 {-1.0,-1.0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_diagonally, target_particle));
  }

  SECTION("Particle collides with particle anti-diagonally") {
    Particle target_particle(1.0,1.0,glm::vec2 {99.0,99.0}, glm::vec2 {1.0,1.0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_antidiagonally, target_particle));
  }
}

TEST_CASE("Particle colliding with container wall") {
  SECTION("Particle does not collide with left wall") {
    Particle particle(1.0,1.0,glm::vec2 {198.9,100.0}, glm::vec2 {1.0,0.0}, "pink");
    REQUIRE_FALSE(calculation.CollideWithWall(particle, 'y'));
  }

  SECTION("Particle does not collide with right wall") {
    Particle particle(1.0,1.0,glm::vec2 {1.1,100.0}, glm::vec2 {-1.0,0.0}, "pink");
    REQUIRE_FALSE(calculation.CollideWithWall(particle, 'y'));
  }

  SECTION("Particle collides with right wall") {
    Particle particle(1.0,1.0,glm::vec2 {199.0,100.0}, glm::vec2 {1.0,0.0}, "pink");
    REQUIRE(calculation.CollideWithWall(particle,'y'));
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

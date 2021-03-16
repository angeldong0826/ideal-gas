#include <catch2/catch.hpp>

#include <gas_container.h>
#include <calculation.h>

using idealgas::Calculation;
using idealgas::Particle;

glm::vec2 top_left_coordinate = {0.0, 0.0};
glm::vec2 bottom_right_coordinate = {200.0, 200.0};
Calculation calculation(top_left_coordinate, bottom_right_coordinate);

// pre-made particles for testing convenience
Particle particle_moving_right(1.0, 1.0, glm::vec2 {100.0,100.0}, glm::vec2 {1.0,0.0}, "pink");
Particle particle_moving_left(1.0, 1.0, glm::vec2 {100.0,100.0}, glm::vec2 {-1.0,0.0}, "pink");
Particle particle_moving_up(1.0, 1.0, glm::vec2 {100.0,100.0}, glm::vec2 {0.0,1.0}, "pink");
Particle particle_moving_down(1.0, 1.0, glm::vec2 {100.0,100.0}, glm::vec2 {0.0,-1.0}, "pink");
Particle particle_moving_diagonally(1.0, 1.0, glm::vec2 {100.0,100.0}, glm::vec2 {1.0,1.0}, "pink");
Particle particle_moving_antidiagonally(1.0, 1.0, glm::vec2 {100.0,100.0}, glm::vec2 {-1.0,-1.0}, "pink");

TEST_CASE("Particles colliding with other particles") {

  SECTION("Particle does not collide with particle") {
    Particle target_particle(1.0, 1.0, glm::vec2 {101.1,100.0}, glm::vec2 {1.0,0}, "pink");
    REQUIRE_FALSE(calculation.CollideWithParticle(particle_moving_right, target_particle));
  }

  SECTION("Collision from right") {
    Particle target_particle(1.0, 1.0, glm::vec2 {101.0, 100.0}, glm::vec2 {-1.0,0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_right, target_particle));
  }

  SECTION("Collision from left") {
    Particle target_particle(1.0,1.0,glm::vec2 {99.0, 100.0}, glm::vec2 {1.0,0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_left, target_particle));
  }

  SECTION("Collision from top") {
    Particle target_particle(1.0,1.0,glm::vec2 {100.0,101.0}, glm::vec2 {0.0,-1.0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_up, target_particle));
  }

  SECTION("Collision from bottom") {
    Particle target_particle(1.0,1.0,glm::vec2 {100.0,99.0}, glm::vec2 {0.0,1.0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_down, target_particle));
  }

  SECTION("Diagonal collision") {
    Particle target_particle(1.0,1.0,glm::vec2 {101.0,101.0}, glm::vec2 {-1.0,-1.0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_diagonally, target_particle));
  }

  SECTION("Anti-diagonal collision") {
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

  SECTION("Particle does not collide with top wall") {
    Particle particle(1.0,1.0,glm::vec2 {100.0,198.9}, glm::vec2 {0.0,1.0}, "pink");
    REQUIRE_FALSE(calculation.CollideWithWall(particle, 'x'));
  }

  SECTION("Particle does not collide with bottom wall") {
    Particle particle(1.0,1.0,glm::vec2 {100.0,198.9}, glm::vec2 {0.0,-1.0}, "pink");
    REQUIRE_FALSE(calculation.CollideWithWall(particle, 'x'));
  }

  SECTION("Right wall collision") {
    Particle particle(1.0,1.0,glm::vec2 {199.0,100.0}, glm::vec2 {1.0,0.0}, "pink");
    REQUIRE(calculation.CollideWithWall(particle,'y'));
  }

  SECTION("Left wall collision") {
    Particle particle(1.0,1.0,glm::vec2 {1.0,100.0}, glm::vec2 {-1.0,0.0}, "pink");
    REQUIRE(calculation.CollideWithWall(particle, 'y'));
  }

  SECTION("Top wall collision") {
    Particle particle(1.0,1.0,glm::vec2 {100.0,0.9}, glm::vec2 {0.0,-1.0}, "pink");
    REQUIRE(calculation.CollideWithWall(particle, 'x'));
  }

  SECTION("Bottom wall collision") {
    Particle particle(1.0,1.0,glm::vec2 {100.0,199.1}, glm::vec2 {0.0,1.0}, "pink");
    REQUIRE(calculation.CollideWithWall(particle, 'x'));
  }

  SECTION("Top right corner collision") {
    Particle particle(1.0,1.0,glm::vec2 {200.0,0.0}, glm::vec2 {1.0,-1.0}, "pink");
    REQUIRE(calculation.CollideWithWall(particle, 'x'));
    REQUIRE(calculation.CollideWithWall(particle, 'y'));
  }

  SECTION("Top left corner collision") {
    Particle particle(1.0,1.0,glm::vec2 {0.0,0.0}, glm::vec2 {-1.0,-1.0}, "pink");
    REQUIRE(calculation.CollideWithWall(particle, 'x'));
    REQUIRE(calculation.CollideWithWall(particle, 'y'));
  }

  SECTION("Bottom right corner collision") {
    Particle particle(1.0,1.0,glm::vec2 {200.0,200.0}, glm::vec2 {1.0,1.0}, "pink");
    REQUIRE(calculation.CollideWithWall(particle, 'x'));
    REQUIRE(calculation.CollideWithWall(particle, 'y'));
  }

  SECTION("Bottom left corner collision") {
    Particle particle(1.0,1.0,glm::vec2 {0.0,200.0}, glm::vec2 {-1.0,1.0}, "pink");
    REQUIRE(calculation.CollideWithWall(particle, 'x'));
    REQUIRE(calculation.CollideWithWall(particle, 'y'));
  }
}

TEST_CASE("Particle position after particle-particle collision") {

  SECTION("Collision from right") {
    Particle target_particle(1.0, 1.0, glm::vec2 {101.0, 100.0}, glm::vec2 {-1.0,0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_right, target_particle));

    calculation.PostCollisionPosition(particle_moving_right);
    calculation.PostCollisionPosition(target_particle);

    REQUIRE(particle_moving_right.GetPosition().x == 101.0);
    REQUIRE(particle_moving_right.GetPosition().y == 100.0);
    REQUIRE(target_particle.GetPosition().x == 100.0);
    REQUIRE(target_particle.GetPosition().y == 100.0);
  }

  SECTION("Collision from left") {
    Particle target_particle(1.0,1.0,glm::vec2 {99.0, 100.0}, glm::vec2 {1.0,0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_left, target_particle));

    calculation.PostCollisionPosition(particle_moving_left);
    calculation.PostCollisionPosition(target_particle);

    REQUIRE(particle_moving_left.GetPosition().x == 99.0);
    REQUIRE(particle_moving_left.GetPosition().y == 100.0);
    REQUIRE(target_particle.GetPosition().x == 100.0);
    REQUIRE(target_particle.GetPosition().y == 100.0);
  }

  SECTION("Collision from top") {
    Particle target_particle(1.0,1.0,glm::vec2 {100.0,101.0}, glm::vec2 {0.0,-1.0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_up, target_particle));

    calculation.PostCollisionPosition(particle_moving_up);
    calculation.PostCollisionPosition(target_particle);

    REQUIRE(particle_moving_up.GetPosition().x == 100.0);
    REQUIRE(particle_moving_up.GetPosition().y == 101.0);
    REQUIRE(target_particle.GetPosition().x == 100.0);
    REQUIRE(target_particle.GetPosition().y == 100.0);
  }

  SECTION("Collision from bottom") {
    Particle target_particle(1.0,1.0,glm::vec2 {100.0,99.0}, glm::vec2 {0.0,1.0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_down, target_particle));

    calculation.PostCollisionPosition(particle_moving_down);
    calculation.PostCollisionPosition(target_particle);

    REQUIRE(particle_moving_down.GetPosition().x == 100.0);
    REQUIRE(particle_moving_down.GetPosition().y == 99.0);
    REQUIRE(target_particle.GetPosition().x == 100.0);
    REQUIRE(target_particle.GetPosition().y == 100.0);
  }

  SECTION("Diagonal collision") {
    Particle target_particle(1.0,1.0,glm::vec2 {101.0,101.0}, glm::vec2 {-1.0,-1.0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_diagonally, target_particle));

    calculation.PostCollisionPosition(particle_moving_diagonally);
    calculation.PostCollisionPosition(target_particle);

    REQUIRE(particle_moving_diagonally.GetPosition().x == 101.0);
    REQUIRE(particle_moving_diagonally.GetPosition().y == 101.0);
    REQUIRE(target_particle.GetPosition().x == 100.0);
    REQUIRE(target_particle.GetPosition().y == 100.0);
  }

  SECTION("Anti-diagonal collision") {
    Particle target_particle(1.0,1.0,glm::vec2 {99.0,99.0}, glm::vec2 {1.0,1.0}, "pink");
    REQUIRE(calculation.CollideWithParticle(particle_moving_antidiagonally, target_particle));

    calculation.PostCollisionPosition(particle_moving_antidiagonally);
    calculation.PostCollisionPosition(target_particle);

    REQUIRE(particle_moving_antidiagonally.GetPosition().x == 99.0);
    REQUIRE(particle_moving_antidiagonally.GetPosition().y == 99.0);
    REQUIRE(target_particle.GetPosition().x == 100.0);
    REQUIRE(target_particle.GetPosition().y == 100.0);
  }
}

TEST_CASE("Particle position after particle-wall collision") {

  SECTION("Collision with top wall") {

  }

  SECTION("Collision with bottom wall") {

  }

  SECTION("Collision with right wall") {

  }

  SECTION("Collision with left wall") {

  }

  SECTION("Collision with top left corner") {

  }

  SECTION("Collision with top right corner") {

  }

  SECTION("Collision with bottom left corner") {

  }

  SECTION("Collision with bottom right corner") {

  }
}

/*
TODO: Rename this test file. You'll also need to modify CMakeLists.txt.
*/

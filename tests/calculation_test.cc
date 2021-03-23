#include <particle_manager.h>

#include <catch2/catch.hpp>

using idealgas::Particle;
using idealgas::ParticleManager;

glm::vec2 top_left_coordinate = {0.0, 0.0};
glm::vec2 bottom_right_coordinate = {200.0, 200.0};
ParticleManager calculation(top_left_coordinate, bottom_right_coordinate);

TEST_CASE("Particle bounces off of other particles") {

  // set particles with specific characteristics for testing convenience
  Particle particle_moving_right(1.0, 1.0, glm::vec2{100.0, 100.0},
                                 glm::vec2{1.0, 0.0}, "pink");
  Particle particle_moving_left(1.0, 1.0, glm::vec2{100.0, 100.0},
                                glm::vec2{-1.0, 0.0}, "pink");
  Particle particle_moving_up(1.0, 1.0, glm::vec2{100.0, 100.0},
                              glm::vec2{0.0, 1.0}, "pink");
  Particle particle_moving_down(1.0, 1.0, glm::vec2{100.0, 100.0},
                                glm::vec2{0.0, -1.0}, "pink");
  Particle particle_moving_diagonally(1.0, 1.0, glm::vec2{100.0, 100.0},
                                      glm::vec2{1.0, 1.0}, "pink");
  Particle particle_moving_antidiagonally(1.0, 1.0, glm::vec2{100.0, 100.0},
                                          glm::vec2{-1.0, -1.0}, "pink");

  SECTION("Collision from right") {
    Particle target_particle(1.0, 1.0, glm::vec2{101.0, 100.0},
                             glm::vec2{-1.0, 0}, "pink");
    REQUIRE(calculation.IsParticleCollision(particle_moving_right,
                                            target_particle));
  }

  SECTION("Collision from left") {
    Particle target_particle(1.0, 1.0, glm::vec2{99.0, 100.0},
                             glm::vec2{1.0, 0}, "pink");
    REQUIRE(
        calculation.IsParticleCollision(particle_moving_left, target_particle));
  }

  SECTION("Collision from top") {
    Particle target_particle(1.0, 1.0, glm::vec2{100.0, 101.0},
                             glm::vec2{0.0, -1.0}, "pink");
    REQUIRE(
        calculation.IsParticleCollision(particle_moving_up, target_particle));
  }

  SECTION("Collision from bottom") {
    Particle target_particle(1.0, 1.0, glm::vec2{100.0, 99.0},
                             glm::vec2{0.0, 1.0}, "pink");
    REQUIRE(
        calculation.IsParticleCollision(particle_moving_down, target_particle));
  }

  SECTION("Diagonal collision") {
    Particle target_particle(1.0, 1.0, glm::vec2{101.0, 101.0},
                             glm::vec2{-1.0, -1.0}, "pink");
    REQUIRE(calculation.IsParticleCollision(particle_moving_diagonally,
                                            target_particle));
  }

  SECTION("Anti-diagonal collision") {
    Particle target_particle(1.0, 1.0, glm::vec2{99.0, 99.0},
                             glm::vec2{1.0, 1.0}, "pink");
    REQUIRE(calculation.IsParticleCollision(particle_moving_antidiagonally,
                                            target_particle));
  }
}

TEST_CASE("Particle not bouncing off of other particles when not moving towards each other") {

  // middle particle at the center of container for testing convenience
  Particle middle_particle(1.0, 1.0, glm::vec2{100.0, 100.0},
                           glm::vec2{0.0, 0.0}, "pink");

  SECTION("Does not bounce from right") {
    Particle target_particle(1.0, 1.0, glm::vec2{101.0, 100.0},
                             glm::vec2{1.0, 0.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }

  SECTION("Does not bounce from left") {
    Particle target_particle(1.0, 1.0, glm::vec2{99.0, 100.0},
                             glm::vec2{-1.0, 0.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }

  SECTION("Does not bounce from top") {
    Particle target_particle(1.0, 1.0, glm::vec2{100.0, 99.0},
                             glm::vec2{0.0, -1.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }

  SECTION("Does not bounce from bottom") {
    Particle target_particle(1.0, 1.0, glm::vec2{100.0, 101.0},
                             glm::vec2{0.0, 1.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }

  SECTION("Does not bounce diagonally") {
    Particle target_particle(1.0, 1.0, glm::vec2{101.0, 99.0},
                             glm::vec2{1.0, -1.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }

  SECTION("Does not bounce anti-diagonally") {
    Particle target_particle(1.0, 1.0, glm::vec2{99.0, 101.0},
                             glm::vec2{-1.0, 1.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }

  SECTION("Does not bounce when still") {
    Particle target_particle(1.0, 1.0, glm::vec2{100.0, 101.0},
                             glm::vec2{0.0, 0.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }
}

TEST_CASE("Particle bounces off of container wall") {

  SECTION("Particle does not collide with right wall") {
    Particle particle(1.0, 1.0, glm::vec2{198.9, 100.0}, glm::vec2{1.0, 0.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Particle does not collide with left wall") {
    Particle particle(1.0, 1.0, glm::vec2{1.1, 100.0}, glm::vec2{-1.0, 0.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Particle does not collide with top wall") {
    Particle particle(1.0, 1.0, glm::vec2{100.0, 198.9}, glm::vec2{0.0, 1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
  }

  SECTION("Particle does not collide with bottom wall") {
    Particle particle(1.0, 1.0, glm::vec2{100.0, 198.9}, glm::vec2{0.0, -1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
  }

  SECTION("Right wall collision") {
    Particle particle(1.0, 1.0, glm::vec2{199.0, 100.0}, glm::vec2{1.0, 0.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Left wall collision") {
    Particle particle(1.0, 1.0, glm::vec2{1.0, 100.0}, glm::vec2{-1.0, 0.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Top wall collision") {
    Particle particle(1.0, 1.0, glm::vec2{100.0, 0.9}, glm::vec2{0.0, -1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
  }

  SECTION("Bottom wall collision") {
    Particle particle(1.0, 1.0, glm::vec2{100.0, 199.1}, glm::vec2{0.0, 1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
  }

  SECTION("Top right corner collision") {
    Particle particle(1.0, 1.0, glm::vec2{200.0, 0.0}, glm::vec2{1.0, -1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Top left corner collision") {
    Particle particle(1.0, 1.0, glm::vec2{0.0, 0.0}, glm::vec2{-1.0, -1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Bottom right corner collision") {
    Particle particle(1.0, 1.0, glm::vec2{200.0, 200.0}, glm::vec2{1.0, 1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Bottom left corner collision") {
    Particle particle(1.0, 1.0, glm::vec2{0.0, 200.0}, glm::vec2{-1.0, 1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));
  }
}

TEST_CASE("Particle not bouncing off of container wall when moving in different directions") {

  SECTION("Does not bounce off right wall") {
    Particle particle(1.0, 1.0, glm::vec2{199.0, 100.0}, glm::vec2{-1.0, 0.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Does not bounce off left wall") {
    Particle particle(1.0, 1.0, glm::vec2{1.0, 100.0}, glm::vec2{1.0, 0.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Does not bounce off top wall") {
    Particle particle(1.0, 1.0, glm::vec2{100.0, 1.0}, glm::vec2{0.0, 1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
  }

  SECTION("Does not bounce off bottom wall") {
    Particle particle(1.0, 1.0, glm::vec2{100.0, 199.0}, glm::vec2{0.0, -1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
  }

  SECTION("Does not bounce off top right corner") {
    Particle particle(1.0, 1.0, glm::vec2{199.0, 1.0}, glm::vec2{-1.0, 1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Does not bounce off top left corner") {
    Particle particle(1.0, 1.0, glm::vec2{1.0, 1.0}, glm::vec2{1.0, 1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Does not bounce off bottom right corner") {
    Particle particle(1.0, 1.0, glm::vec2{199.0, 199.0}, glm::vec2{-1.0, -1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Does not bounce off bottom left corner") {
    Particle particle(1.0, 1.0, glm::vec2{1.0, 199.0}, glm::vec2{1.0, -1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Does not bounce off when still") {
    Particle particle(1.0, 1.0, glm::vec2{100.0, 100.0}, glm::vec2{0.0, 0.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }
}

TEST_CASE("Velocity update after particle-particle collision") {

  SECTION("Collision from right") {
    Particle particle_moving_right(1.0, 1.0, glm::vec2{100.0, 100.0},
                                   glm::vec2{1.0, 0.0}, "pink");
    Particle target_particle(1.0, 1.0, glm::vec2{101.0, 100.0},
                             glm::vec2{-1.0, 0}, "pink");
    REQUIRE(calculation.IsParticleCollision(particle_moving_right,
                                            target_particle));

    particle_moving_right.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            particle_moving_right, target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            target_particle, particle_moving_right));

    REQUIRE(particle_moving_right.GetVelocity().x == -1.0f);
    REQUIRE(particle_moving_right.GetVelocity().y == 0.0f);
    REQUIRE(target_particle.GetVelocity().x == -1.0f);
    REQUIRE(target_particle.GetVelocity().y == 0.0f);
  }

  SECTION("Collision from left") {
    Particle particle_moving_left(1.0, 1.0, glm::vec2{100.0, 100.0},
                                  glm::vec2{-1.0, 0.0}, "pink");
    Particle target_particle(1.0, 1.0, glm::vec2{99.0, 100.0},
                             glm::vec2{1.0, 0}, "pink");
    REQUIRE(
        calculation.IsParticleCollision(particle_moving_left, target_particle));

    particle_moving_left.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(particle_moving_left,
                                                           target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            target_particle, particle_moving_left));

    REQUIRE(particle_moving_left.GetVelocity().x == 1.0f);
    REQUIRE(particle_moving_left.GetVelocity().y == 0.0f);
    REQUIRE(target_particle.GetVelocity().x == 1.0f);
    REQUIRE(target_particle.GetVelocity().y == 0.0f);
  }

  SECTION("Collision from top") {
    Particle particle_moving_up(1.0, 1.0, glm::vec2{100.0, 100.0},
                                glm::vec2{0.0, 1.0}, "pink");
    Particle target_particle(1.0, 1.0, glm::vec2{100.0, 101.0},
                             glm::vec2{0.0, -1.0}, "pink");
    REQUIRE(
        calculation.IsParticleCollision(particle_moving_up, target_particle));

    particle_moving_up.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(particle_moving_up,
                                                           target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(target_particle,
                                                           particle_moving_up));

    REQUIRE(particle_moving_up.GetVelocity().x == 0.0f);
    REQUIRE(particle_moving_up.GetVelocity().y == -1.0f);
    REQUIRE(target_particle.GetVelocity().x == 0.0f);
    REQUIRE(target_particle.GetVelocity().y == -1.0f);
  }

  SECTION("Collision from bottom") {
    Particle particle_moving_down(1.0, 1.0, glm::vec2{100.0, 100.0},
                                  glm::vec2{0.0, -1.0}, "pink");
    Particle target_particle(1.0, 1.0, glm::vec2{100.0, 99.0},
                             glm::vec2{0.0, 1.0}, "pink");
    REQUIRE(
        calculation.IsParticleCollision(particle_moving_down, target_particle));

    particle_moving_down.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(particle_moving_down,
                                                           target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            target_particle, particle_moving_down));

    REQUIRE(particle_moving_down.GetVelocity().x == 0.0f);
    REQUIRE(particle_moving_down.GetVelocity().y == 1.0f);
    REQUIRE(target_particle.GetVelocity().x == 0.0f);
    REQUIRE(target_particle.GetVelocity().y == 1.0f);
  }

  SECTION("Diagonal collision") {
    Particle particle_moving_diagonally(1.0, 1.0, glm::vec2{100.0, 100.0},
                                        glm::vec2{1.0, 1.0}, "pink");
    Particle target_particle(1.0, 1.0, glm::vec2{101.0, 101.0},
                             glm::vec2{-1.0, -1.0}, "pink");
    REQUIRE(calculation.IsParticleCollision(particle_moving_diagonally,
                                            target_particle));

    particle_moving_diagonally.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            particle_moving_diagonally, target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            target_particle, particle_moving_diagonally));

    REQUIRE(particle_moving_diagonally.GetVelocity().x == -1.0f);
    REQUIRE(particle_moving_diagonally.GetVelocity().y == -1.0f);
    REQUIRE(target_particle.GetVelocity().x == -1.0f);
    REQUIRE(target_particle.GetVelocity().y == -1.0f);
  }

  SECTION("Anti-diagonal collision") {
    Particle particle_moving_antidiagonally(1.0, 1.0, glm::vec2{100.0, 100.0},
                                            glm::vec2{-1.0, -1.0}, "pink");
    Particle target_particle(1.0, 1.0, glm::vec2{99.0, 99.0},
                             glm::vec2{1.0, 1.0}, "pink");
    REQUIRE(calculation.IsParticleCollision(particle_moving_antidiagonally,
                                            target_particle));

    particle_moving_antidiagonally.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            particle_moving_antidiagonally, target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            target_particle, particle_moving_antidiagonally));

    REQUIRE(particle_moving_antidiagonally.GetVelocity().x == 1.0f);
    REQUIRE(particle_moving_antidiagonally.GetVelocity().y == 1.0f);
    REQUIRE(target_particle.GetVelocity().x == 1.0f);
    REQUIRE(target_particle.GetVelocity().y == 1.0f);
  }
}

TEST_CASE("Position update after particle-particle collision") {

  // set particles with specific characteristics for testing convenience
  Particle particle_moving_right(1.0, 1.0, glm::vec2{100.0, 100.0},
                                 glm::vec2{1.0, 0.0}, "pink");
  Particle particle_moving_left(1.0, 1.0, glm::vec2{100.0, 100.0},
                                glm::vec2{-1.0, 0.0}, "pink");
  Particle particle_moving_up(1.0, 1.0, glm::vec2{100.0, 100.0},
                              glm::vec2{0.0, 1.0}, "pink");
  Particle particle_moving_down(1.0, 1.0, glm::vec2{100.0, 100.0},
                                glm::vec2{0.0, -1.0}, "pink");
  Particle particle_moving_diagonally(1.0, 1.0, glm::vec2{100.0, 100.0},
                                      glm::vec2{1.0, 1.0}, "pink");
  Particle particle_moving_antidiagonally(1.0, 1.0, glm::vec2{100.0, 100.0},
                                          glm::vec2{-1.0, -1.0}, "pink");

  SECTION("Collision from right") {
    Particle target_particle(1.0, 1.0, glm::vec2{101.0, 100.0},
                             glm::vec2{-1.0, 0}, "pink");

    // checks to make sure there is collision
    REQUIRE(calculation.IsParticleCollision(particle_moving_right,
                                            target_particle));

    // calculates and updates velocity of particle after collision first
    particle_moving_right.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            particle_moving_right, target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            target_particle, particle_moving_right));

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle_moving_right);
    calculation.CalculatePostCollisionPosition(target_particle);

    REQUIRE(particle_moving_right.GetPosition().x == 99.0f);
    REQUIRE(particle_moving_right.GetPosition().y == 100.0f);
    REQUIRE(target_particle.GetPosition().x == 100.0f);
    REQUIRE(target_particle.GetPosition().y == 100.0f);
  }

  SECTION("Collision from left") {
    Particle target_particle(1.0, 1.0, glm::vec2{99.0, 100.0},
                             glm::vec2{1.0, 0}, "pink");

    // checks to make sure there is collision
    REQUIRE(
        calculation.IsParticleCollision(particle_moving_left, target_particle));

    // calculates and updates velocity of particle after collision first
    particle_moving_left.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(particle_moving_left,
                                                           target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            target_particle, particle_moving_left));

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle_moving_left);
    calculation.CalculatePostCollisionPosition(target_particle);

    REQUIRE(particle_moving_left.GetPosition().x == 101.0f);
    REQUIRE(particle_moving_left.GetPosition().y == 100.0f);
    REQUIRE(target_particle.GetPosition().x == 100.0f);
    REQUIRE(target_particle.GetPosition().y == 100.0f);
  }

  SECTION("Collision from top") {
    Particle target_particle(1.0, 1.0, glm::vec2{100.0, 101.0},
                             glm::vec2{0.0, -1.0}, "pink");

    // checks to make sure there is collision
    REQUIRE(
        calculation.IsParticleCollision(particle_moving_up, target_particle));

    // calculates and updates velocity of particle after collision first
    particle_moving_up.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(particle_moving_up,
                                                           target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(target_particle,
                                                           particle_moving_up));

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle_moving_up);
    calculation.CalculatePostCollisionPosition(target_particle);

    REQUIRE(particle_moving_up.GetPosition().x == 100.0f);
    REQUIRE(particle_moving_up.GetPosition().y == 99.0f);
    REQUIRE(target_particle.GetPosition().x == 100.0f);
    REQUIRE(target_particle.GetPosition().y == 100.0f);
  }

  SECTION("Collision from bottom") {
    Particle target_particle(1.0, 1.0, glm::vec2{100.0, 99.0},
                             glm::vec2{0.0, 1.0}, "pink");

    // checks to make sure there is collision
    REQUIRE(
        calculation.IsParticleCollision(particle_moving_down, target_particle));

    // calculates and updates velocity of particle after collision first
    particle_moving_down.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(particle_moving_down,
                                                           target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            target_particle, particle_moving_down));

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle_moving_down);
    calculation.CalculatePostCollisionPosition(target_particle);

    REQUIRE(particle_moving_down.GetPosition().x == 100.0f);
    REQUIRE(particle_moving_down.GetPosition().y == 101.0f);
    REQUIRE(target_particle.GetPosition().x == 100.0f);
    REQUIRE(target_particle.GetPosition().y == 100.0f);
  }

  SECTION("Diagonal collision") {
    Particle target_particle(1.0, 1.0, glm::vec2{101.0, 101.0},
                             glm::vec2{-1.0, -1.0}, "pink");

    // checks to make sure there is collision
    REQUIRE(calculation.IsParticleCollision(particle_moving_diagonally,
                                            target_particle));

    // calculates and updates velocity of particle after collision first
    particle_moving_diagonally.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            particle_moving_diagonally, target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            target_particle, particle_moving_diagonally));

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle_moving_diagonally);
    calculation.CalculatePostCollisionPosition(target_particle);

    REQUIRE(particle_moving_diagonally.GetPosition().x == 99.0f);
    REQUIRE(particle_moving_diagonally.GetPosition().y == 99.0f);
    REQUIRE(target_particle.GetPosition().x == 100.0f);
    REQUIRE(target_particle.GetPosition().y == 100.0f);
  }

  SECTION("Anti-diagonal collision") {
    Particle target_particle(1.0, 1.0, glm::vec2{99.0, 99.0},
                             glm::vec2{1.0, 1.0}, "pink");

    // checks to make sure there is collision
    REQUIRE(calculation.IsParticleCollision(particle_moving_antidiagonally,
                                            target_particle));

    // calculates and updates velocity of particle after collision first
    particle_moving_antidiagonally.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            particle_moving_antidiagonally, target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            target_particle, particle_moving_antidiagonally));

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle_moving_antidiagonally);
    calculation.CalculatePostCollisionPosition(target_particle);

    REQUIRE(particle_moving_antidiagonally.GetPosition().x == 101.0f);
    REQUIRE(particle_moving_antidiagonally.GetPosition().y == 101.0f);
    REQUIRE(target_particle.GetPosition().x == 100.0f);
    REQUIRE(target_particle.GetPosition().y == 100.0f);
  }
}

TEST_CASE("Velocity update after particle-wall collision") {
  SECTION("Collision with top wall") {
    Particle particle(1.0, 1.0, glm::vec2{100.0, 0.9}, glm::vec2{0.0, -1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    REQUIRE(particle.GetVelocity().x == 0.0f);
    REQUIRE(particle.GetVelocity().y == 1.0f);
  }

  SECTION("Collision with bottom wall") {
    Particle particle(1.0, 1.0, glm::vec2{100.0, 199.1}, glm::vec2{0.0, 1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    REQUIRE(particle.GetVelocity().x == 0.0f);
    REQUIRE(particle.GetVelocity().y == -1.0f);
  }

  SECTION("Collision with right wall") {
    Particle particle(1.0, 1.0, glm::vec2{199.0, 100.0}, glm::vec2{1.0, 0.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == -1.0f);
    REQUIRE(particle.GetVelocity().y == 0.0f);
  }

  SECTION("Collision with left wall") {
    Particle particle(1.0, 1.0, glm::vec2{1.0, 100.0}, glm::vec2{-1.0, 0.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == 1.0f);
    REQUIRE(particle.GetVelocity().y == 0.0f);
  }

  SECTION("Collision with top left corner") {
    Particle particle(1.0, 1.0, glm::vec2{0.0, 0.0}, glm::vec2{-1.0, -1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == 1.0f);
    REQUIRE(particle.GetVelocity().y == 1.0f);
  }

  SECTION("Collision with top right corner") {
    Particle particle(1.0, 1.0, glm::vec2{200.0, 0.0}, glm::vec2{1.0, -1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == -1.0f);
    REQUIRE(particle.GetVelocity().y == 1.0f);
  }

  SECTION("Collision with bottom left corner") {
    Particle particle(1.0, 1.0, glm::vec2{0.0, 200.0}, glm::vec2{-1.0, 1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == 1.0f);
    REQUIRE(particle.GetVelocity().y == -1.0f);
  }

  SECTION("Collision with bottom right corner") {
    Particle particle(1.0, 1.0, glm::vec2{200.0, 200.0}, glm::vec2{1.0, 1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == -1.0f);
    REQUIRE(particle.GetVelocity().y == -1.0f);
  }
}

TEST_CASE("Position update after particle-wall collision") {
  SECTION("Collision with top wall") {
    Particle particle(1.0, 1.0, glm::vec2{100.0, 0.9}, glm::vec2{0.0, -1.0},
                      "pink");

    // checks to make sure there is collision
    REQUIRE(calculation.IsWallCollision(particle, 'x'));

    // calculates and updates velocity of particle after collision first
    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    REQUIRE(particle.GetVelocity().x == 0.0f);
    REQUIRE(particle.GetVelocity().y == 1.0f);

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle);
    REQUIRE(particle.GetPosition().x == 100.0f);
    REQUIRE(particle.GetPosition().y == 1.9f);
  }

  SECTION("Collision with bottom wall") {
    Particle particle(1.0, 1.0, glm::vec2{100.0, 199.1}, glm::vec2{0.0, 1.0},
                      "pink");

    // checks to make sure there is collision
    REQUIRE(calculation.IsWallCollision(particle, 'x'));

    // calculates and updates velocity of particle after collision first
    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    REQUIRE(particle.GetVelocity().x == 0.0f);
    REQUIRE(particle.GetVelocity().y == -1.0f);

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle);
    REQUIRE(particle.GetPosition().x == 100.0f);
    REQUIRE(particle.GetPosition().y == 198.1f);
  }

  SECTION("Collision with right wall") {
    Particle particle(1.0, 1.0, glm::vec2{199.0, 100.0}, glm::vec2{1.0, 0.0},
                      "pink");

    // checks to make sure there is collision
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    // calculates and updates velocity of particle after collision first
    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == -1.0f);
    REQUIRE(particle.GetVelocity().y == 0.0f);

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle);
    REQUIRE(particle.GetPosition().x == 198.0f);
    REQUIRE(particle.GetPosition().y == 100.0f);
  }

  SECTION("Collision with left wall") {
    Particle particle(1.0, 1.0, glm::vec2{1.0, 100.0}, glm::vec2{-1.0, 0.0},
                      "pink");

    // checks to make sure there is collision
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    // calculates and updates velocity of particle after collision first
    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == 1.0f);
    REQUIRE(particle.GetVelocity().y == 0.0f);

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle);
    REQUIRE(particle.GetPosition().x == 2.0f);
    REQUIRE(particle.GetPosition().y == 100.0f);
  }

  SECTION("Collision with top left corner") {
    Particle particle(1.0, 1.0, glm::vec2{0.0, 0.0}, glm::vec2{-1.0, -1.0},
                      "pink");

    // checks to make sure there is collision
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    // calculates and updates velocity of particle after collision first
    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == 1.0f);
    REQUIRE(particle.GetVelocity().y == 1.0f);

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle);
    REQUIRE(particle.GetPosition().x == 1.0f);
    REQUIRE(particle.GetPosition().y == 1.0f);
  }

  SECTION("Collision with top right corner") {
    Particle particle(1.0, 1.0, glm::vec2{200.0, 0.0}, glm::vec2{1.0, -1.0},
                      "pink");

    // checks to make sure there is collision
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    // calculates and updates velocity of particle after collision first
    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == -1.0f);
    REQUIRE(particle.GetVelocity().y == 1.0f);

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle);
    REQUIRE(particle.GetPosition().x == 199.0f);
    REQUIRE(particle.GetPosition().y == 1.0f);
  }

  SECTION("Collision with bottom left corner") {
    Particle particle(1.0, 1.0, glm::vec2{0.0, 200.0}, glm::vec2{-1.0, 1.0},
                      "pink");

    // checks to make sure there is collision
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    // calculates and updates velocity of particle after collision first
    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == 1.0f);
    REQUIRE(particle.GetVelocity().y == -1.0f);

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle);
    REQUIRE(particle.GetPosition().x == 1.0f);
    REQUIRE(particle.GetPosition().y == 199.0f);
  }

  SECTION("Collision with bottom right corner") {
    Particle particle(1.0, 1.0, glm::vec2{200.0, 200.0}, glm::vec2{1.0, 1.0},
                      "pink");

    // checks to make sure there is collision
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    // calculates and updates velocity of particle after collision first
    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == -1.0f);
    REQUIRE(particle.GetVelocity().y == -1.0f);

    // finds the current position at updated velocity and location
    calculation.CalculatePostCollisionPosition(particle);
    REQUIRE(particle.GetPosition().x == 199.0f);
    REQUIRE(particle.GetPosition().y == 199.0f);
  }
}
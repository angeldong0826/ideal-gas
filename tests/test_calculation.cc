#include <particle_manager.h>

#include <catch2/catch.hpp>

using idealgas::GasParticle;
using idealgas::ParticleManager;

glm::vec2 top_left_coordinate = {0.0, 0.0};
glm::vec2 bottom_right_coordinate = {200.0, 200.0};
ParticleManager calculation(top_left_coordinate, bottom_right_coordinate);

TEST_CASE("GasParticle bounces off of other particles") {

  // set particles with specific characteristics for testing convenience
  GasParticle particle_moving_right(1.0, 1.0, glm::vec2{100.0, 100.0},
                                 glm::vec2{1.0, 0.0}, "pink");
  GasParticle particle_moving_left(1.0, 1.0, glm::vec2{100.0, 100.0},
                                glm::vec2{-1.0, 0.0}, "pink");
  GasParticle particle_moving_up(1.0, 1.0, glm::vec2{100.0, 100.0},
                              glm::vec2{0.0, 1.0}, "pink");
  GasParticle particle_moving_down(1.0, 1.0, glm::vec2{100.0, 100.0},
                                glm::vec2{0.0, -1.0}, "pink");
  GasParticle particle_moving_diagonally(1.0, 1.0, glm::vec2{100.0, 100.0},
                                      glm::vec2{1.0, 1.0}, "pink");
  GasParticle particle_moving_antidiagonally(1.0, 1.0, glm::vec2{100.0, 100.0},
                                          glm::vec2{-1.0, -1.0}, "pink");

  SECTION("Collision from right") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{101.0, 100.0},
                             glm::vec2{-1.0, 0}, "pink");
    REQUIRE(calculation.IsParticleCollision(particle_moving_right,
                                            target_particle));
  }

  SECTION("Collision from left") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{99.0, 100.0},
                             glm::vec2{1.0, 0}, "pink");
    REQUIRE(
        calculation.IsParticleCollision(particle_moving_left, target_particle));
  }

  SECTION("Collision from top") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{100.0, 101.0},
                             glm::vec2{0.0, -1.0}, "pink");
    REQUIRE(
        calculation.IsParticleCollision(particle_moving_up, target_particle));
  }

  SECTION("Collision from bottom") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{100.0, 99.0},
                             glm::vec2{0.0, 1.0}, "pink");
    REQUIRE(
        calculation.IsParticleCollision(particle_moving_down, target_particle));
  }

  SECTION("Diagonal collision") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{101.0, 101.0},
                             glm::vec2{-1.0, -1.0}, "pink");
    REQUIRE(calculation.IsParticleCollision(particle_moving_diagonally,
                                            target_particle));
  }

  SECTION("Anti-diagonal collision") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{99.0, 99.0},
                             glm::vec2{1.0, 1.0}, "pink");
    REQUIRE(calculation.IsParticleCollision(particle_moving_antidiagonally,
                                            target_particle));
  }
}

TEST_CASE("GasParticle not bouncing off of other particles when not moving towards each other") {

  // middle particle at the center of container for testing convenience
  GasParticle middle_particle(1.0, 1.0, glm::vec2{100.0, 100.0},
                           glm::vec2{0.0, 0.0}, "pink");

  SECTION("Does not bounce from right") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{101.0, 100.0},
                             glm::vec2{1.0, 0.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }

  SECTION("Does not bounce from left") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{99.0, 100.0},
                             glm::vec2{-1.0, 0.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }

  SECTION("Does not bounce from top") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{100.0, 99.0},
                             glm::vec2{0.0, -1.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }

  SECTION("Does not bounce from bottom") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{100.0, 101.0},
                             glm::vec2{0.0, 1.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }

  SECTION("Does not bounce diagonally") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{101.0, 99.0},
                             glm::vec2{1.0, -1.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }

  SECTION("Does not bounce anti-diagonally") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{99.0, 101.0},
                             glm::vec2{-1.0, 1.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }

  SECTION("Does not bounce when still") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{100.0, 101.0},
                             glm::vec2{0.0, 0.0}, "pink");
    REQUIRE_FALSE(
        calculation.IsParticleCollision(middle_particle, target_particle));
  }
}

TEST_CASE("GasParticle bounces off of container wall") {

  SECTION("GasParticle does not collide with right wall") {
    GasParticle particle(1.0, 1.0, glm::vec2{198.9, 100.0}, glm::vec2{1.0, 0.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("GasParticle does not collide with left wall") {
    GasParticle particle(1.0, 1.0, glm::vec2{1.1, 100.0}, glm::vec2{-1.0, 0.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("GasParticle does not collide with top wall") {
    GasParticle particle(1.0, 1.0, glm::vec2{100.0, 198.9}, glm::vec2{0.0, 1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
  }

  SECTION("GasParticle does not collide with bottom wall") {
    GasParticle particle(1.0, 1.0, glm::vec2{100.0, 198.9}, glm::vec2{0.0, -1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
  }

  SECTION("Right wall collision") {
    GasParticle particle(1.0, 1.0, glm::vec2{199.0, 100.0}, glm::vec2{1.0, 0.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Left wall collision") {
    GasParticle particle(1.0, 1.0, glm::vec2{1.0, 100.0}, glm::vec2{-1.0, 0.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Top wall collision") {
    GasParticle particle(1.0, 1.0, glm::vec2{100.0, 0.9}, glm::vec2{0.0, -1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
  }

  SECTION("Bottom wall collision") {
    GasParticle particle(1.0, 1.0, glm::vec2{100.0, 199.1}, glm::vec2{0.0, 1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
  }

  SECTION("Top right corner collision") {
    GasParticle particle(1.0, 1.0, glm::vec2{200.0, 0.0}, glm::vec2{1.0, -1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Top left corner collision") {
    GasParticle particle(1.0, 1.0, glm::vec2{0.0, 0.0}, glm::vec2{-1.0, -1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Bottom right corner collision") {
    GasParticle particle(1.0, 1.0, glm::vec2{200.0, 200.0}, glm::vec2{1.0, 1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Bottom left corner collision") {
    GasParticle particle(1.0, 1.0, glm::vec2{0.0, 200.0}, glm::vec2{-1.0, 1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));
  }
}

TEST_CASE("GasParticle not bouncing off of container wall when moving in different directions") {

  SECTION("Does not bounce off right wall") {
    GasParticle particle(1.0, 1.0, glm::vec2{199.0, 100.0}, glm::vec2{-1.0, 0.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Does not bounce off left wall") {
    GasParticle particle(1.0, 1.0, glm::vec2{1.0, 100.0}, glm::vec2{1.0, 0.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Does not bounce off top wall") {
    GasParticle particle(1.0, 1.0, glm::vec2{100.0, 1.0}, glm::vec2{0.0, 1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
  }

  SECTION("Does not bounce off bottom wall") {
    GasParticle particle(1.0, 1.0, glm::vec2{100.0, 199.0}, glm::vec2{0.0, -1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
  }

  SECTION("Does not bounce off top right corner") {
    GasParticle particle(1.0, 1.0, glm::vec2{199.0, 1.0}, glm::vec2{-1.0, 1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Does not bounce off top left corner") {
    GasParticle particle(1.0, 1.0, glm::vec2{1.0, 1.0}, glm::vec2{1.0, 1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Does not bounce off bottom right corner") {
    GasParticle particle(1.0, 1.0, glm::vec2{199.0, 199.0}, glm::vec2{-1.0, -1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Does not bounce off bottom left corner") {
    GasParticle particle(1.0, 1.0, glm::vec2{1.0, 199.0}, glm::vec2{1.0, -1.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }

  SECTION("Does not bounce off when still") {
    GasParticle particle(1.0, 1.0, glm::vec2{100.0, 100.0}, glm::vec2{0.0, 0.0},
                      "pink");
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE_FALSE(calculation.IsWallCollision(particle, 'y'));
  }
}

TEST_CASE("Velocity update after particle-particle collision") {

  SECTION("Collision from right") {
    GasParticle particle_moving_right(1.0, 1.0, glm::vec2{100.0, 100.0},
                                   glm::vec2{1.0, 0.0}, "pink");
    GasParticle target_particle(1.0, 1.0, glm::vec2{101.0, 100.0},
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
    GasParticle particle_moving_left(1.0, 1.0, glm::vec2{100.0, 100.0},
                                  glm::vec2{-1.0, 0.0}, "pink");
    GasParticle target_particle(1.0, 1.0, glm::vec2{99.0, 100.0},
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
    GasParticle particle_moving_up(1.0, 1.0, glm::vec2{100.0, 100.0},
                                glm::vec2{0.0, 1.0}, "pink");
    GasParticle target_particle(1.0, 1.0, glm::vec2{100.0, 101.0},
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
    GasParticle particle_moving_down(1.0, 1.0, glm::vec2{100.0, 100.0},
                                  glm::vec2{0.0, -1.0}, "pink");
    GasParticle target_particle(1.0, 1.0, glm::vec2{100.0, 99.0},
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
    GasParticle particle_moving_diagonally(1.0, 1.0, glm::vec2{100.0, 100.0},
                                        glm::vec2{1.0, 1.0}, "pink");
    GasParticle target_particle(1.0, 1.0, glm::vec2{101.0, 101.0},
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
    GasParticle particle_moving_antidiagonally(1.0, 1.0, glm::vec2{100.0, 100.0},
                                            glm::vec2{-1.0, -1.0}, "pink");
    GasParticle target_particle(1.0, 1.0, glm::vec2{99.0, 99.0},
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

  SECTION("Particle collision different masses") {
    GasParticle particle_moving_right(1.0, 1.0, glm::vec2{100.0, 100.0},
                                      glm::vec2{1.0, 0.0}, "pink");
    GasParticle target_particle(6.0, 1.0, glm::vec2{101.0, 100.0},
                                glm::vec2{-1.0, 0}, "pink");

    REQUIRE(calculation.IsParticleCollision(particle_moving_right,
                                            target_particle));

    particle_moving_right.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            particle_moving_right, target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            target_particle, particle_moving_right));

    REQUIRE(particle_moving_right.GetVelocity().x == Approx(-2.42857f));
    REQUIRE(particle_moving_right.GetVelocity().y == 0.0f);
    REQUIRE(target_particle.GetVelocity().x == Approx(-1.40816f));
    REQUIRE(target_particle.GetVelocity().y == 0.0f);
  }

  SECTION("Particle collision different radii") {
    GasParticle particle_moving_right(1.0, 1.0, glm::vec2{100.0, 100.0},
                                      glm::vec2{1.0, 0.0}, "pink");
    GasParticle target_particle(6.0, 6.0, glm::vec2{101.0, 100.0},
                                glm::vec2{-1.0, 0}, "pink");

    REQUIRE(calculation.IsParticleCollision(particle_moving_right,
                                            target_particle));

    particle_moving_right.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            particle_moving_right, target_particle));
    target_particle.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            target_particle, particle_moving_right));

    REQUIRE(particle_moving_right.GetVelocity().x == Approx(-2.42857f));
    REQUIRE(particle_moving_right.GetVelocity().y == 0.0f);
    REQUIRE(target_particle.GetVelocity().x == Approx(-1.40816f));
    REQUIRE(target_particle.GetVelocity().y == 0.0f);
  }

  SECTION("Pair particle collision with more than two particles") {
    GasParticle particle_moving_right(1.0, 1.0, glm::vec2{100.0, 100.0},
                                      glm::vec2{1.0, 0.0}, "pink");
    GasParticle particle_moving_left(1.0, 1.0, glm::vec2{101.0, 100.0},
                                     glm::vec2{-1.0, 0.0}, "pink");
    GasParticle particle_moving_up(1.0, 1.0, glm::vec2{100.0, 100.0},
                                   glm::vec2{0.0, 1.0}, "pink");
    GasParticle particle_moving_down(1.0, 1.0, glm::vec2{100.0, 100.0},
                                     glm::vec2{0.0, -1.0}, "pink");
    GasParticle particle_moving_diagonally(1.0, 1.0, glm::vec2{100.0, 100.0},
                                           glm::vec2{1.0, 1.0}, "pink");
    GasParticle particle_moving_antidiagonally(1.0, 1.0, glm::vec2{101.0, 101.0},
                                               glm::vec2{-1.0, -1.0}, "pink");

    REQUIRE(calculation.IsParticleCollision(particle_moving_right, particle_moving_left));

    particle_moving_right.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            particle_moving_right, particle_moving_left));
    particle_moving_left.SetVelocity(
        calculation.CalculatePostParticleCollisionVelocity(
            particle_moving_left, particle_moving_right));

    REQUIRE(particle_moving_right.GetVelocity().x == -1.0f);
    REQUIRE(particle_moving_right.GetVelocity().y == 0.0f);
    REQUIRE(particle_moving_left.GetVelocity().x == -1.0f);
    REQUIRE(particle_moving_left.GetVelocity().y == 0.0f);

    particle_moving_right.SetPosition(particle_moving_right.GetPosition() + particle_moving_right.GetVelocity());
    particle_moving_left.SetPosition(particle_moving_left.GetPosition() + particle_moving_left.GetVelocity());

    REQUIRE(particle_moving_right.GetVelocity().x == -1.0f);
    REQUIRE(particle_moving_right.GetVelocity().y == 0.0f);
    REQUIRE(particle_moving_left.GetVelocity().x == -1.0f);
    REQUIRE(particle_moving_left.GetVelocity().y == 0.0f);
  }
}

TEST_CASE("Position update after particle-particle collision") {

  // set particles with specific characteristics for testing convenience
  GasParticle particle_moving_right(1.0, 1.0, glm::vec2{100.0, 100.0},
                                 glm::vec2{1.0, 0.0}, "pink");
  GasParticle particle_moving_left(1.0, 1.0, glm::vec2{100.0, 100.0},
                                glm::vec2{-1.0, 0.0}, "pink");
  GasParticle particle_moving_up(1.0, 1.0, glm::vec2{100.0, 100.0},
                              glm::vec2{0.0, 1.0}, "pink");
  GasParticle particle_moving_down(1.0, 1.0, glm::vec2{100.0, 100.0},
                                glm::vec2{0.0, -1.0}, "pink");
  GasParticle particle_moving_diagonally(1.0, 1.0, glm::vec2{100.0, 100.0},
                                      glm::vec2{1.0, 1.0}, "pink");
  GasParticle particle_moving_antidiagonally(1.0, 1.0, glm::vec2{100.0, 100.0},
                                          glm::vec2{-1.0, -1.0}, "pink");

  SECTION("Collision from right") {
    GasParticle target_particle(1.0, 1.0, glm::vec2{101.0, 100.0},
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
    GasParticle target_particle(1.0, 1.0, glm::vec2{99.0, 100.0},
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
    GasParticle target_particle(1.0, 1.0, glm::vec2{100.0, 101.0},
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
    GasParticle target_particle(1.0, 1.0, glm::vec2{100.0, 99.0},
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
    GasParticle target_particle(1.0, 1.0, glm::vec2{101.0, 101.0},
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
    GasParticle target_particle(1.0, 1.0, glm::vec2{99.0, 99.0},
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
    GasParticle particle(1.0, 1.0, glm::vec2{100.0, 0.9}, glm::vec2{0.0, -1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    REQUIRE(particle.GetVelocity().x == 0.0f);
    REQUIRE(particle.GetVelocity().y == 1.0f);
  }

  SECTION("Collision with bottom wall") {
    GasParticle particle(1.0, 1.0, glm::vec2{100.0, 199.1}, glm::vec2{0.0, 1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    REQUIRE(particle.GetVelocity().x == 0.0f);
    REQUIRE(particle.GetVelocity().y == -1.0f);
  }

  SECTION("Collision with right wall") {
    GasParticle particle(1.0, 1.0, glm::vec2{199.0, 100.0}, glm::vec2{1.0, 0.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == -1.0f);
    REQUIRE(particle.GetVelocity().y == 0.0f);
  }

  SECTION("Collision with left wall") {
    GasParticle particle(1.0, 1.0, glm::vec2{1.0, 100.0}, glm::vec2{-1.0, 0.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == 1.0f);
    REQUIRE(particle.GetVelocity().y == 0.0f);
  }

  SECTION("Collision with top left corner") {
    GasParticle particle(1.0, 1.0, glm::vec2{0.0, 0.0}, glm::vec2{-1.0, -1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == 1.0f);
    REQUIRE(particle.GetVelocity().y == 1.0f);
  }

  SECTION("Collision with top right corner") {
    GasParticle particle(1.0, 1.0, glm::vec2{200.0, 0.0}, glm::vec2{1.0, -1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == -1.0f);
    REQUIRE(particle.GetVelocity().y == 1.0f);
  }

  SECTION("Collision with bottom left corner") {
    GasParticle particle(1.0, 1.0, glm::vec2{0.0, 200.0}, glm::vec2{-1.0, 1.0},
                      "pink");
    REQUIRE(calculation.IsWallCollision(particle, 'x'));
    REQUIRE(calculation.IsWallCollision(particle, 'y'));

    calculation.CalculatePostWallCollisionVelocity(particle, 'x');
    calculation.CalculatePostWallCollisionVelocity(particle, 'y');
    REQUIRE(particle.GetVelocity().x == 1.0f);
    REQUIRE(particle.GetVelocity().y == -1.0f);
  }

  SECTION("Collision with bottom right corner") {
    GasParticle particle(1.0, 1.0, glm::vec2{200.0, 200.0}, glm::vec2{1.0, 1.0},
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
    GasParticle particle(1.0, 1.0, glm::vec2{100.0, 0.9}, glm::vec2{0.0, -1.0},
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
    GasParticle particle(1.0, 1.0, glm::vec2{100.0, 199.1}, glm::vec2{0.0, 1.0},
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
    GasParticle particle(1.0, 1.0, glm::vec2{199.0, 100.0}, glm::vec2{1.0, 0.0},
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
    GasParticle particle(1.0, 1.0, glm::vec2{1.0, 100.0}, glm::vec2{-1.0, 0.0},
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
    GasParticle particle(1.0, 1.0, glm::vec2{0.0, 0.0}, glm::vec2{-1.0, -1.0},
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
    GasParticle particle(1.0, 1.0, glm::vec2{200.0, 0.0}, glm::vec2{1.0, -1.0},
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
    GasParticle particle(1.0, 1.0, glm::vec2{0.0, 200.0}, glm::vec2{-1.0, 1.0},
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
    GasParticle particle(1.0, 1.0, glm::vec2{200.0, 200.0}, glm::vec2{1.0, 1.0},
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
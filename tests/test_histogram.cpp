#include <gas_particle.h>
#include <histogram.h>

#include <catch2/catch.hpp>

namespace idealgas {


TEST_CASE("Map size update") {
  Histogram histogram;
  std::vector<GasParticle> particle_;

  SECTION("Wrong color") {
    GasParticle particle(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},
                         "pink");
    particle_.push_back(particle);
    histogram.AdvanceOneFrame(particle_);
    std::map<double, int> map = histogram.GetHistogramMap("teal");
    REQUIRE_FALSE(map.size() == 1);
  }

  SECTION("One pink particle") {
    GasParticle particle(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},
                         "pink");
    particle_.push_back(particle);
    histogram.AdvanceOneFrame(particle_);
    std::map<double, int> map = histogram.GetHistogramMap("pink");
    REQUIRE(map.size() == 1);
  }

  SECTION("Multiple pink particles") {
    GasParticle particle(15.0, 15.0, glm::vec2{90,247}, glm::vec2{0.1,0.1}, "pink");
    GasParticle particle_two(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},"pink");

    particle_.push_back(particle);
    particle_.push_back(particle_two);

    histogram.AdvanceOneFrame(particle_);
    std::map<double, int> map = histogram.GetHistogramMap("pink");
    REQUIRE(map.size() == 2);
  }

  SECTION("One white particle") {
    GasParticle particle(15.0, 15.0, glm::vec2{165.0, 67.0}, glm::vec2{3.0, -3.0},
                         "white");
    particle_.push_back(particle);
    histogram.AdvanceOneFrame(particle_);
    std::map<double, int> map = histogram.GetHistogramMap("white");
    REQUIRE(map.size() == 1);
  }

  SECTION("Multiple white particles") {
    GasParticle particle(15.0, 15.0, glm::vec2{90,247}, glm::vec2{0.1,0.1}, "white");
    GasParticle particle_two(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},"white");

    particle_.push_back(particle);
    particle_.push_back(particle_two);

    histogram.AdvanceOneFrame(particle_);
    std::map<double, int> map = histogram.GetHistogramMap("white");
    REQUIRE(map.size() == 2);
  }

  SECTION("One teal particle") {
    GasParticle particle(15.0, 15.0, glm::vec2{165.0, 67.0}, glm::vec2{3.0, -3.0},
                         "teal");
    particle_.push_back(particle);
    histogram.AdvanceOneFrame(particle_);
    std::map<double, int> map = histogram.GetHistogramMap("teal");
    REQUIRE(map.size() == 1);
  }

  SECTION("Multiple teal particles") {
    GasParticle particle(15.0, 15.0, glm::vec2{90,247}, glm::vec2{0.1,0.1}, "teal");
    GasParticle particle_two(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},"teal");
    GasParticle particle_three(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},"teal");


    particle_.push_back(particle);
    particle_.push_back(particle_two);
    particle_.push_back(particle_three);

    histogram.AdvanceOneFrame(particle_);
    std::map<double, int> map = histogram.GetHistogramMap("teal");
    double particle_speed_ = glm::length(glm::vec2{0.1,0.1});
    double particle_two_speed_ = glm::length(glm::vec2{3.0, 3.0});
    REQUIRE(map.size() == 2);
    REQUIRE(map.at(particle_speed_) == 1);
    REQUIRE(map.at(particle_two_speed_) == 2);
  }
}

TEST_CASE("Bar update") {
  SECTION("Wrong speed range") {

  }

  SECTION("One pink particle") {

  }

  SECTION("Multiple pink particles") {

  }

  SECTION("One white particle") {

  }

  SECTION("Multiple white particles") {

  }

  SECTION("One teal particle") {

  }

  SECTION("Multiple teal particles") {

  }
}

}  // namespace idealgas
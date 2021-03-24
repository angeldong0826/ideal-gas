#include <gas_particle.h>
#include <histogram.h>

#include <catch2/catch.hpp>

namespace idealgas {


TEST_CASE("Map size update") {
  Histogram histogram;
  std::vector<GasParticle> particles_;

  SECTION("Wrong color") {
    GasParticle particle(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},
                         "pink");
    particles_.push_back(particle);
    histogram.AdvanceOneFrame(particles_);
    std::map<double, size_t> map = histogram.GetHistogramMap("teal");
    REQUIRE_FALSE(map.size() == 1);
  }

  SECTION("One pink particle") {
    GasParticle particle(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},
                         "pink");
    particles_.push_back(particle);
    histogram.AdvanceOneFrame(particles_);
    std::map<double, size_t> map = histogram.GetHistogramMap("pink");
    REQUIRE(map.size() == 1);
  }

  SECTION("Multiple pink particles") {
    GasParticle particle(15.0, 15.0, glm::vec2{90,247}, glm::vec2{0.1,0.1}, "pink");
    GasParticle particle_two(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},"pink");

    particles_.push_back(particle);
    particles_.push_back(particle_two);

    histogram.AdvanceOneFrame(particles_);
    std::map<double, size_t> map = histogram.GetHistogramMap("pink");
    REQUIRE(map.size() == 2);
  }

  SECTION("One white particle") {
    GasParticle particle(15.0, 15.0, glm::vec2{165.0, 67.0}, glm::vec2{3.0, -3.0},
                         "white");
    particles_.push_back(particle);
    histogram.AdvanceOneFrame(particles_);
    std::map<double, size_t> map = histogram.GetHistogramMap("white");
    REQUIRE(map.size() == 1);
  }

  SECTION("Multiple white particles") {
    GasParticle particle(15.0, 15.0, glm::vec2{90,247}, glm::vec2{0.1,0.1}, "white");
    GasParticle particle_two(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},"white");

    particles_.push_back(particle);
    particles_.push_back(particle_two);

    histogram.AdvanceOneFrame(particles_);
    std::map<double, size_t> map = histogram.GetHistogramMap("white");
    REQUIRE(map.size() == 2);
  }

  SECTION("One teal particle") {
    GasParticle particle(15.0, 15.0, glm::vec2{165.0, 67.0}, glm::vec2{3.0, -3.0},
                         "teal");
    particles_.push_back(particle);
    histogram.AdvanceOneFrame(particles_);
    std::map<double, size_t> map = histogram.GetHistogramMap("teal");
    REQUIRE(map.size() == 1);
  }

  SECTION("Multiple teal particles") {
    GasParticle particle(15.0, 15.0, glm::vec2{90,247}, glm::vec2{0.1,0.1}, "teal");
    GasParticle particle_two(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},"teal");
    GasParticle particle_three(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},"teal");

    particles_.push_back(particle);
    particles_.push_back(particle_two);
    particles_.push_back(particle_three);

    histogram.AdvanceOneFrame(particles_);
    std::map<double, size_t> map = histogram.GetHistogramMap("teal");
    REQUIRE(map.size() == 2);
  }
}

// I couldn't figure out how to test my bar updates because my map is from double
// to int and values can't be obtained from a double key in a map apparently
TEST_CASE("Histogram Bar update") {
  Histogram histogram;
  std::vector<GasParticle> particles_;

  SECTION("Wrong speed range") {

  }

  SECTION("One pink particle") {
//    GasParticle particle(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},
//                         "pink");
//    particles_.push_back(particle);
//    histogram.AdvanceOneFrame(particles_);
//    std::map<double, size_t> map = histogram.GetHistogramMap("pink");
//    REQUIRE(map.size() == 1);
//    REQUIRE(map.at(glm::length(glm::vec2{3.0, 3.0})) == 1);
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
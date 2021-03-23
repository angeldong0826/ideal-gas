#include <gas_particle.h>
#include <histogram.h>

#include <catch2/catch.hpp>

namespace idealgas {

TEST_CASE("Histogram borders") {

}

TEST_CASE("Pink particle update") {
  Histogram histogram;
  std::vector<GasParticle> particle_;

  SECTION("One pink particle") {
    GasParticle particle(15.0, 15.0, glm::vec2{50.0, 67.0}, glm::vec2{3.0, 3.0},
                         "pink");
    particle_.push_back(particle);
    histogram.AdvanceOneFrame(particle_);
    std::map<double, int> map = histogram.GetHistogramMap("pink");
    REQUIRE(map.size() == 1);
  }

  SECTION("Multiple pink") {
  }
}
}  // namespace idealgas
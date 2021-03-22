#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

namespace idealgas {

/**
 * The histogram charts of all the particles vs. speed graphs. This class takes
 * the particles generated and their speeds and put the information into
 * histograms.
 */
class Histogram {
 public:
  /**
   * Constructor that initializes histogram windows.
   */
  Histogram(const std::vector<Particle> &particles);

  /**
   * Displays the histogram windows.
   */
  void Display();

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  void CreateMap();

  void FillInMap(std::map<double, int> &map, double speed,
                 std::vector<double> &range);

  void DrawGraph(std::map<double, int> map, ci::Color color);

 private:

  // chart 1 attributes
  const ci::Rectf chart_pink_ =
      ci::Rectf(glm::vec2(700, 25), glm::vec2(1200, 225));
  // chart 2 attributes
  const ci::Rectf chart_white_ =
      ci::Rectf(glm::vec2(700, 250), glm::vec2(1200, 450));
  // chart 3 attributes
  const ci::Rectf chart_teal_ =
      ci::Rectf(glm::vec2(700, 475), glm::vec2(1200, 675));

  const glm::vec2 kPinkInitialVelocity = {
      1.4, 1.4};  // pink particle initial velocity
  const glm::vec2 kWhiteInitialVelocity = {
      4.0, -4.0};  // white particle initial velocity
  const glm::vec2 kTealInitialVelocity = {
      6.0, 6.0};  // teal particle initial velocity

  double top_left_coordinate_ = chart_pink_.getUpperLeft().x;
  double top_right_coordinate_ = chart_pink_.getUpperRight().x;
  double pink_bottom_right_coordinate_ = chart_pink_.getLowerRight().y;
  double white_bottom_right_coordinate_ = chart_white_.getLowerRight().y;
  double teal_bottom_right_coordinate_ = chart_teal_.getLowerRight().y;

  std::vector<Particle>& particles_;

  std::map<double, int> map_pink_; // map for pink chart info
  std::map<double, int> map_white_; // map for white chart info
  std::map<double, int> map_teal_; // map for teal chart info

  std::vector<double> pink_speed_range{
      (glm::length(kPinkInitialVelocity) / 10),
      (glm::length(kPinkInitialVelocity) / 10) * 2,
      (glm::length(kPinkInitialVelocity) / 10) * 3,
      (glm::length(kPinkInitialVelocity) / 10) * 4,
      (glm::length(kPinkInitialVelocity) / 10) * 5,
      (glm::length(kPinkInitialVelocity) / 10) * 6,
      (glm::length(kPinkInitialVelocity) / 10) * 7,
      (glm::length(kPinkInitialVelocity) / 10) * 8,
      (glm::length(kPinkInitialVelocity) / 10) * 9,
      (glm::length(kPinkInitialVelocity) / 10) * 10};

  std::vector<double> white_speed_range{
      (glm::length(kWhiteInitialVelocity) / 10),
      (glm::length(kWhiteInitialVelocity) / 10) * 2,
      (glm::length(kWhiteInitialVelocity) / 10) * 3,
      (glm::length(kWhiteInitialVelocity) / 10) * 4,
      (glm::length(kWhiteInitialVelocity) / 10) * 5,
      (glm::length(kWhiteInitialVelocity) / 10) * 6,
      (glm::length(kWhiteInitialVelocity) / 10) * 7,
      (glm::length(kWhiteInitialVelocity) / 10) * 8,
      (glm::length(kWhiteInitialVelocity) / 10) * 9,
      (glm::length(kWhiteInitialVelocity) / 10) * 10};

  std::vector<double> teal_speed_range{
      (glm::length(kTealInitialVelocity) / 10),
      (glm::length(kTealInitialVelocity) / 10) * 2,
      (glm::length(kTealInitialVelocity) / 10) * 3,
      (glm::length(kTealInitialVelocity) / 10) * 4,
      (glm::length(kTealInitialVelocity) / 10) * 5,
      (glm::length(kTealInitialVelocity) / 10) * 6,
      (glm::length(kTealInitialVelocity) / 10) * 7,
      (glm::length(kTealInitialVelocity) / 10) * 8,
      (glm::length(kTealInitialVelocity) / 10) * 9,
      (glm::length(kTealInitialVelocity) / 10) * 10};

  const double x_scale_ = (top_right_coordinate_ - top_left_coordinate_) / pink_speed_range.size();
  const double y_scale_ = particles_.size() / 3;
};
}  // namespace idealgas
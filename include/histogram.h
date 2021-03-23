#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"
#include "gas_container.h"

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
  Histogram();

  /**
   * Displays the histogram windows.
   */
  void Display();

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame(const std::vector<Particle>& particles);

  /**
   * Creates map to store chart info for particles.
   */
  void CreateMap();

  /**
   * Method to fill in histogram information into maps created.
   *
   * @param map to store histogram information
   * @param speed of particles to be sorted
   * @param range of velocities to be displayed
   */
  void FillInMap(std::map<double, int>& map, double speed,
                 const std::vector<double>& range);

  /**
   * Method that draws histograms.
   *
   * @param color of particle
   */
  void DrawGraph(const ci::Color& color);

 private:
  // pink chart borders
  const ci::Rectf chart_pink_ =
      ci::Rectf(glm::vec2(700, 25), glm::vec2(1200, 225));
  // white chart borders
  const ci::Rectf chart_white_ =
      ci::Rectf(glm::vec2(700, 250), glm::vec2(1200, 450));
  // teal chart borders
  const ci::Rectf chart_teal_ =
      ci::Rectf(glm::vec2(700, 475), glm::vec2(1200, 675));

  const glm::vec2 kPinkInitialVelocity = {
      6.0, 6.0};  // pink particle initial velocity
  const glm::vec2 kWhiteInitialVelocity = {
      4.0, -4.0};  // white particle initial velocity
  const glm::vec2 kTealInitialVelocity = {
      1.4, 1.4};  // teal particle initial velocity

  double top_left_x_coordinate_ = chart_pink_.getUpperLeft().x; // top left coordinate of all histogram charts
  const double top_right_x_coordinate_ = chart_pink_.getUpperRight().x; // top right x coordinate of all histogram charts
  const double top_right_y_coordinate_ = chart_pink_.getUpperRight().y; // top right y coordinate of all histogram charts
  const double pink_bottom_right_coordinate_ = chart_pink_.getLowerRight().y; // bottom right coordinate of pink chart
  const double white_bottom_right_coordinate_ = chart_white_.getLowerRight().y; // bottom right coordinate of white chart
  const double teal_bottom_right_coordinate_ = chart_teal_.getLowerRight().y; // bottom right coordinate of teal chart

  std::vector<Particle> particles_; // vector of particles in container

  const size_t x_axis_parts = 10; // number of parts to split x-axis into
  const size_t kParticleAmount = 30; // amount of particles in container
  const size_t kColorAmount = 3; // amount of particle colors in container

  const double x_scale_ = (top_right_x_coordinate_ - top_left_x_coordinate_) / x_axis_parts;
  const double y_scale_ = (pink_bottom_right_coordinate_ - top_right_y_coordinate_) / (kParticleAmount / kColorAmount);

  std::map<double, int> map_pink_; // map for pink chart info
  std::map<double, int> map_white_; // map for white chart info
  std::map<double, int> map_teal_; // map for teal chart info

  const std::vector<double> pink_speed_range{
      (glm::length(kPinkInitialVelocity) / x_axis_parts),
      (glm::length(kPinkInitialVelocity) / x_axis_parts) * 2,
      (glm::length(kPinkInitialVelocity) / x_axis_parts) * 3,
      (glm::length(kPinkInitialVelocity) / x_axis_parts) * 4,
      (glm::length(kPinkInitialVelocity) / x_axis_parts) * 5,
      (glm::length(kPinkInitialVelocity) / x_axis_parts) * 6,
      (glm::length(kPinkInitialVelocity) / x_axis_parts) * 7,
      (glm::length(kPinkInitialVelocity) / x_axis_parts) * 8,
      (glm::length(kPinkInitialVelocity) / x_axis_parts) * 9,
      (glm::length(kPinkInitialVelocity) / x_axis_parts) * 10};

  const std::vector<double> white_speed_range{
      (glm::length(kWhiteInitialVelocity) / x_axis_parts),
      (glm::length(kWhiteInitialVelocity) / x_axis_parts) * 2,
      (glm::length(kWhiteInitialVelocity) / x_axis_parts) * 3,
      (glm::length(kWhiteInitialVelocity) / x_axis_parts) * 4,
      (glm::length(kWhiteInitialVelocity) / x_axis_parts) * 5,
      (glm::length(kWhiteInitialVelocity) / x_axis_parts) * 6,
      (glm::length(kWhiteInitialVelocity) / x_axis_parts) * 7,
      (glm::length(kWhiteInitialVelocity) / x_axis_parts) * 8,
      (glm::length(kWhiteInitialVelocity) / x_axis_parts) * 9,
      (glm::length(kWhiteInitialVelocity) / x_axis_parts) * 10};

  const std::vector<double> teal_speed_range{
      (glm::length(kTealInitialVelocity) / x_axis_parts),
      (glm::length(kTealInitialVelocity) / x_axis_parts) * 2,
      (glm::length(kTealInitialVelocity) / x_axis_parts) * 3,
      (glm::length(kTealInitialVelocity) / x_axis_parts) * 4,
      (glm::length(kTealInitialVelocity) / x_axis_parts) * 5,
      (glm::length(kTealInitialVelocity) / x_axis_parts) * 6,
      (glm::length(kTealInitialVelocity) / x_axis_parts) * 7,
      (glm::length(kTealInitialVelocity) / x_axis_parts) * 8,
      (glm::length(kTealInitialVelocity) / x_axis_parts) * 9,
      (glm::length(kTealInitialVelocity) / x_axis_parts) * 10};
};
}  // namespace idealgas
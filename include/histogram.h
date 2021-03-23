#pragma once

#include "cinder/gl/gl.h"
#include "gas_container.h"
#include "gas_particle.h"

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
  void AdvanceOneFrame(const std::vector<GasParticle>& particles);

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
  void DrawGraph(const ci::Color& color) const;

  /**
   * Method that labels axis on histogram charts.
   *
   * @param color particle color
   */
  void DrawAxis(const ci::Color& color) const;

  /**
   * Getter method that returns a map which stores information of a histogram.
   *
   * @return map with histogram information
   */
  std::map<double, int> GetHistogramMap(ci::Color color) const;

  double CalculateMaxSpeed() const;

 private:
  const size_t histogram_margin_ = 25;   // histogram margin
  const size_t window_length_ = 1300;    // display window length
  const size_t window_width_ = 700;      // display window width
  const size_t container_margin_ = 100;  // container margin
  const double histogram_width_ =
      (window_width_ - 4 * histogram_margin_) / 3;  // histogram width
  const glm::vec2 histogram_top_left_coordinate_ = {
      window_length_ / 2 + container_margin_ / 2,
      histogram_margin_};  // top left corner of histogram
  const glm::vec2 histogram_bottom_right_coordinate_ = {
      window_length_ - container_margin_,
      window_width_ - histogram_margin_};  // bottom right corner of histogram

  // pink chart borders
  const ci::Rectf chart_pink_ =
      ci::Rectf(histogram_top_left_coordinate_,
                glm::vec2{histogram_bottom_right_coordinate_.x,
                          histogram_top_left_coordinate_.y + histogram_width_});
  // white chart borders
  const ci::Rectf chart_white_ =
      ci::Rectf(glm::vec2{histogram_top_left_coordinate_.x,
                          histogram_top_left_coordinate_.y + histogram_width_ +
                              histogram_margin_},
                glm::vec2{histogram_bottom_right_coordinate_.x,
                          histogram_top_left_coordinate_.y +
                              (2 * histogram_width_) + histogram_margin_});
  // teal chart borders
  const ci::Rectf chart_teal_ = ci::Rectf(
      glm::vec2{histogram_top_left_coordinate_.x,
                histogram_bottom_right_coordinate_.y - histogram_width_},
      histogram_bottom_right_coordinate_);

  const glm::vec2 kPinkInitialVelocity = {
      6.0, 6.0};  // pink particle initial velocity
  const glm::vec2 kWhiteInitialVelocity = {
      4.0, -4.0};  // white particle initial velocity
  const glm::vec2 kTealInitialVelocity = {
      1.4, 1.4};  // teal particle initial velocity

  // double top_left_x_coordinate_ = chart_pink_.getUpperLeft().x; // top left
  // coordinate of all histogram charts
  const double top_right_x_coordinate_ =
      chart_pink_.getUpperRight()
          .x;  // top right x coordinate of all histogram charts
  const double top_right_y_coordinate_ =
      chart_pink_.getUpperRight()
          .y;  // top right y coordinate of all histogram charts
  const double pink_bottom_right_coordinate_ =
      chart_pink_.getLowerRight().y;  // bottom right coordinate of pink chart
  const double white_bottom_right_coordinate_ =
      chart_white_.getLowerRight().y;  // bottom right coordinate of white chart
  const double teal_bottom_right_coordinate_ =
      chart_teal_.getLowerRight().y;  // bottom right coordinate of teal chart

  std::vector<GasParticle> particles_;  // vector of particles in container

  const size_t x_axis_parts = 10;     // number of parts to split x-axis into
  const size_t kParticleAmount = 42;  // amount of particles in container
  const size_t kColorAmount = 3;      // amount of particle colors in container

  // scaling factor in x direction depending on number of histogram bars
  const double x_scale_ =
      (top_right_x_coordinate_ - histogram_top_left_coordinate_.x) /
      x_axis_parts;
  // scaling factor in y direction for graph visibility
  const double y_scale_ =
      (pink_bottom_right_coordinate_ - top_right_y_coordinate_) /
      (kParticleAmount / kColorAmount);

  std::map<double, int> map_pink_;   // map for storing pink chart info
  std::map<double, int> map_white_;  // map for storing white chart info
  std::map<double, int> map_teal_;   // map for storing teal chart info

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
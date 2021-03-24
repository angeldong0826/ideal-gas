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
  void FillInMap(std::map<double, int>& map, double speed);

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
  std::map<double, int> GetHistogramMap(const ci::Color& color) const;


  double CalculateMaxSpeed();

 private:
  // display attributes
  const size_t histogram_border_width_ = 2; // histogram border width
  const size_t histogram_margin_ = 25;   // histogram margin
  const size_t window_length_ = 1300;    // display window length
  const size_t window_width_ = 700;      // display window width
  const size_t container_margin_ = 100;  // container margin
  const double histogram_width_ =
      (window_width_ - 4.0 * histogram_margin_) / 3;  // histogram width
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

  // coordinates of histogram charts
  const double top_right_x_coordinate_ =
      chart_pink_.getUpperRight()
          .x;  // top right x corner of all histogram charts
  const double top_right_y_coordinate_ =
      chart_pink_.getUpperRight()
          .y;  // top right y corner of all histogram charts
  const double pink_bottom_right_coordinate_ =
      chart_pink_.getLowerRight().y;  // bottom right corner of pink chart
  const double white_bottom_right_coordinate_ =
      chart_white_.getLowerRight().y;  // bottom right corner of white chart
  const double teal_bottom_right_coordinate_ =
      chart_teal_.getLowerRight().y;  // bottom right corner of teal chart

  const size_t kBarNumbers = 10; // number of bars displayed
  const size_t kParticleAmount = 42; // amount of particles in container
  const size_t kColorAmount = 3; // amount of particle colors in container

  // scaling factor in x direction depending on number of histogram bars
  const double x_scale_ =
      (top_right_x_coordinate_ - histogram_top_left_coordinate_.x) /
      kBarNumbers;
  // scaling factor in y direction for graph visibility
  const double y_scale_ =
      (pink_bottom_right_coordinate_ - top_right_y_coordinate_) /
      (kParticleAmount / kColorAmount);

  std::vector<GasParticle> particles_;  // vector of particles in container

  std::map<double, int> map_pink_;   // map for storing pink chart info
  std::map<double, int> map_white_;  // map for storing white chart info
  std::map<double, int> map_teal_;   // map for storing teal chart info
};

}  // namespace idealgas
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"
#include "histogram.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  /**
   * Constructor that initializes a container for particles to be put in.
   */
  IdealGasApp();

  /**
   * Method that shows the current state of simulator.
   */
  void draw() override;

  /**
   * Method that updates the current state of simulator.
   */
  void update() override;

  /**
   * Method that applies function from keyboard.
   *
   * @param event
   */
  void keyDown(cinder::app::KeyEvent event) override;

 private:
  const size_t kWindowLength = 1300;    // display window length
  const size_t kWindowWidth = 700;      // display window width
  const size_t kContainerMargin = 100;  // container margin
  const glm::vec2 kContainerBottomRightCorner = {
      kWindowLength / 2 - kContainerMargin / 2,
      kWindowWidth - kContainerMargin};  // bottom right corner of container

  GasContainer container_ =
      GasContainer(glm::vec2(kContainerMargin, kContainerMargin),
                   kContainerBottomRightCorner);  // instance of container
  Histogram histogram_; // instance of histogram
};

}  // namespace idealgas

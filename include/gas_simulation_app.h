#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"

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

  const size_t kWindowLength = 2500; // display window length
  const size_t kWindowWidth = 2000; // display window width
  const size_t kMargin = 500; // display margin

 private:
  GasContainer container_; // instance of container
};

}  // namespace idealgas

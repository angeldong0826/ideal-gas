#include "gas_simulation_app.h"

namespace idealgas {

IdealGasApp::IdealGasApp() :
  container_(GasContainer(glm::vec2 (kWindowLength / 5, kMargin),
             glm::vec2(kWindowLength - kMargin, kWindowWidth - kMargin))) {

  ci::app::setWindowSize(kWindowLength, kWindowWidth);
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  container_.Display();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}

}  // namespace idealgas

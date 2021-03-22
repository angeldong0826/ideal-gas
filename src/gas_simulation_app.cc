#include "gas_simulation_app.h"

namespace idealgas {

IdealGasApp::IdealGasApp() :
  container_(GasContainer(glm::vec2 (kMargin, kMargin),
             kBottomRightCorner)),
  histogram_(container_.GetParticles()){

  ci::app::setWindowSize(kWindowLength, kWindowWidth);
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  container_.Display();
  histogram_.Display();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
  histogram_.AdvanceOneFrame();
}

}  // namespace idealgas

#include "gas_simulation_app.h"

namespace idealgas {

IdealGasApp::IdealGasApp() {
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
  histogram_.AdvanceOneFrame(container_.GetParticles());
}

void IdealGasApp::keyDown(cinder::app::KeyEvent event) {
  if (event.getChar() == 'd') {
    container_.SlowDown();
  }
  if (event.getChar() == 'u') {
    container_.SpeedUp();
  }
}

}  // namespace idealgas

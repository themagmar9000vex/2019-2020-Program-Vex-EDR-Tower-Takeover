using namespace vex;

class vacuumClaw{
  private:
  vex::motor clawMotorR = ClawMotorRight;
  vex::motor clawMotorL = ClawMotorLeft;

  double clawSpeed = 100;
  public:

  void setSpeed(double speed) {
    int clawSpeed = speed;
  }
  void moveUp (){
    clawMotorR.spin(vex::directionType::fwd, clawSpeed, vex::velocityUnits::pct);
    clawMotorL.spin(vex::directionType::rev, clawSpeed, vex::velocityUnits::pct);
  }
  void moveDown (){
    clawMotorR.spin(vex::directionType::rev, clawSpeed, vex::velocityUnits::pct);
    clawMotorL.spin(vex::directionType::fwd, clawSpeed, vex::velocityUnits::pct);
  }

  void Stop(vex::brakeType typeOfStop){
    clawMotorR.stop(typeOfStop);
    clawMotorL.stop(typeOfStop);
  }
vacuumClaw() {}
~vacuumClaw() {}
}claw;
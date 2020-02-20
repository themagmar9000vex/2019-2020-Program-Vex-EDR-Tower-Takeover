//---------------------------\\
//-------Enzo's-Library v1.9------\\
//---------------------------\\
//-Contains-Arm class--\\
//---------------------------\\
//--Last-Update:-2/6/2020--\\
//---------------------------\\

//#include "robot_config.h"

// CLASS ARM and PRIVATE INFO here:
class Arm {
  private:
  vex::motor armMotor = ArmMotor;
  double armSpeed = 50;
  double scoringConfiguration = 3; // position for the arm when we score a stack
  double allianceTower = -360; // position for the arm when we score towers rotation to be refined
  double mediumTower = -400; // position for the arm when we score towers
  double armUnfold = -100; // position to unfold
  
  public:
 
  double getAllianceTowerPosition() {
  return (allianceTower);
 }
 double getMediumTowerPosition() {
  return (mediumTower);
 }

  void setSpeed(double speed) {
  armSpeed = speed;
  }
  void moveUp (){
    armMotor.spin(vex::directionType::rev, armSpeed, vex::velocityUnits::pct);
  }
  
  void moveDown (){
     armMotor.spin(vex::directionType::fwd, armSpeed , vex::velocityUnits::pct);
  }
  void stop(){
    armMotor.stop(vex::brakeType::hold);
  }

  double getTorque(){
      return(armMotor.torque(vex::Nm));
    }


  double getPosition(){
  return(armMotor.position(vex::rotationUnits::deg));
    }   
  double getarmUnfoldPosition(){
  return(armUnfold);
    }   
    
/*
void moveToScoringConfiguration(){
armMotor.resetPosition();
//armMotor.setRotation(0, vex::rotationUnits::deg);
while(getPosition() < scoringConfiguration) {
 
  moveUp();
  }
  stop();
}
*/
  Arm () {}
 ~Arm() {}

}arm;


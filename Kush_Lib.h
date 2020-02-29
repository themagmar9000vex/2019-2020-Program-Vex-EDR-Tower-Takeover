//#include "robot_config.h"

class StorageTray{

  private:
    vex::motor StorageTrayMotor =  StorageSliderMotor; 
    vex::pot potentiometerTray = StoragePotentiometer;
    double velocity = 65;  
    int16_t trayScoringPosition = 103; //potentiomer value to Score
    int16_t trayRestingPosition = 13; //potentiomer value for Tray at rest
  
  public:
    void setSpeed(double NewVelocity) {
      velocity = NewVelocity;
    }

    int16_t getTrayScoringPosition() {
      return(trayScoringPosition);
    }

    int16_t getTrayRestingPosition() {
      return(trayRestingPosition);
    }

    double getTrayPotValue() {
      return(potentiometerTray.value(vex::rotationUnits::deg));
    }
    double getTorque(){
      return(StorageTrayMotor.torque(vex::Nm));
    }

    double getMotorRevolutions(){
      double motorPosition = StorageTrayMotor.position(vex::rotationUnits::rev);
      return(motorPosition);
    }

    double getMotorDegrees(){
      double motorPosition = StorageTrayMotor.position(vex::rotationUnits::deg);
      return(motorPosition);
    }

    void RotateTray(vex::directionType direction){
      StorageTrayMotor.spin(direction, velocity, vex::velocityUnits::pct);
    }

    void StopTray(vex::brakeType StoppingType){
      StorageTrayMotor.stop(StoppingType);
    }

   StorageTray() {} 
   ~StorageTray() {} 
}Tray;

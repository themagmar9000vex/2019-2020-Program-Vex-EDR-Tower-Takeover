#include "vex.h"
#include "vex_imu.h"
using namespace vex;
vex::brain       Brain;

vex::motor DTFrontRightMotor(vex::PORT10, vex::gearSetting::ratio18_1, true);
vex::motor DTFrontLeftMotor(vex::PORT12, vex::gearSetting::ratio18_1, true);
vex::motor DTBackRightMotor(vex::PORT20, vex::gearSetting::ratio18_1, true);
vex::motor DTBackLeftMotor(vex::PORT11, vex::gearSetting::ratio18_1, true);
vex::motor StorageSliderMotor(vex::PORT19, vex::gearSetting::ratio36_1, true);
vex::motor ClawMotorLeft(vex::PORT15, vex::gearSetting::ratio18_1, true);
vex::motor ClawMotorRight(vex::PORT17, vex::gearSetting::ratio18_1, true);
vex::motor ArmMotor(vex::PORT13, vex::gearSetting::ratio36_1, true);

vex::inertial InertialSensor(vex::PORT2);
vex::sonar DistanceSensor = vex::sonar(Brain.ThreeWirePort.B);
vex::sonar DistanceSensor2 = vex::sonar(Brain.ThreeWirePort.F);
vex::pot StoragePotentiometer = vex::pot(Brain.ThreeWirePort.D);

vex::gyro GyroHunters = vex::gyro(Brain.ThreeWirePort.G);

vex::controller ControllerA = vex::controller();
vex::controller ControllerB = vex::controller();
#include "DriveTrainH.h"
#include "enzolib.h"
#include "Kush_Lib.h"
#include "claw.h"

// Function combined  in a task so they run concurently 
int ArmUpTrayMedium () {
 double armPosition = arm.getPosition();
  arm.setSpeed(70);
  while (armPosition >= arm.getMediumTowerPosition()){
    arm.moveUp();
    armPosition = arm.getPosition();
   }
   arm.stop();
  return (0);
}

// Function combined  in a task so they run concurently 
int ArmUpTrayAlliance () {
 double armPosition = arm.getPosition();
  arm.setSpeed(70);
  while (armPosition >= arm.getAllianceTowerPosition()){
    arm.moveUp();
    armPosition = arm.getPosition();
   }
   arm.stop();
  return (0);
}
// Function combined  in a task so they run concurently 
int ArmUpTrayPush() {
  double trayPosition = Tray.getTrayPotValue();

  while (trayPosition <= Tray.getTrayArmReleasePosition()){
  Tray.setSpeed(90); 
  Tray.RotateTray(vex::directionType::fwd);
  trayPosition = Tray.getTrayPotValue();
  
  }
 Tray.StopTray(vex::brakeType::hold);
 return(0);
}



int activateClaw() {
  claw.setSpeed(100);
  claw.moveUp();
   return(0);
}
// Run all systems required to score a stack
void scoreStack() {
    double trayPosition = Tray.getTrayPotValue();
    Tray.setSpeed(60); 
    while (trayPosition <= Tray.getTrayScoringPosition()){
    Tray.RotateTray(vex::directionType::fwd);
    trayPosition = Tray.getTrayPotValue();
    if (trayPosition > (Tray.getTrayScoringPosition()*0.7))
    {Tray.setSpeed(30); }
    }
    Tray.StopTray(vex::brakeType::hold);
    vex::wait(500,vex::msec);
    claw.setSpeed(5);
    claw.moveDown();
    vex::wait(400,vex::msec);
    claw.Stop(vex::brakeType::coast);}

void unfold() {
  double trayPosition = Tray.getTrayPotValue();
  double armPosition = arm.getPosition();
  double armStartingPosition = arm.getPosition();

 while (trayPosition <= Tray.getTrayUnfoldingPosition()){
    Tray.RotateTray(vex::directionType::fwd);
    trayPosition = Tray.getTrayPotValue();
 }
    Tray.StopTray(vex::brakeType::hold);
    vex::wait(200,vex::msec);

  while (armPosition >= arm.getarmUnfoldPosition()){
    arm.moveUp();
    armPosition = arm.getPosition();
    }
   arm.stop();
  claw.setSpeed(2);
    claw.moveDown();
    vex::wait(200,vex::msec);
    claw.Stop(vex::brakeType::coast);
    claw.setSpeed(100);
    
  while (armPosition <= armStartingPosition){
    arm.moveDown();
    armPosition = arm.getPosition();
    }
    arm.stop();
 while (trayPosition >= Tray.getTrayRestingPosition()){
    Tray.RotateTray(vex::directionType::rev);
    trayPosition = Tray.getTrayPotValue();
 }
  vex::wait(100,vex::msec);
  Tray.StopTray(vex::brakeType::hold);


      }



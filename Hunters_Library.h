#include "DriveTrainH.h"
#include "Kush_Lib.h"
#include "claw.h"


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

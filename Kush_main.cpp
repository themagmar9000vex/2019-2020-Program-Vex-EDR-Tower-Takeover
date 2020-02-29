#include "robot_config.h"
#include "Hunters_Library.h"
using namespace vex;


int display() { // Centralizes the inf    o printed on the Brain Screen
    Brain.Screen.setFont(fontType::mono20);
    while (1){
    Brain.Screen.printAt(20,60,"Gyro Value: %f", DT.getGyro()); 
    Brain.Screen.printAt(20,40,"Interial Value: %f", DT.getInertialDegrees());
    Brain.Screen.printAt(20,80,"Pitch Value: %f", DT.getPitch());
    Brain.Screen.printAt(20,100,"Roll Value: %f", DT.getRoll());
    Brain.Screen.printAt(20,125,"Yaw Value: %f", DT.getYaw());        
    task::sleep(200); // Printing only 5 times per second
   }

    return(0); // need to return a value to start it as a task
}

int main() {
vex::task brainPrinting(display);
brainPrinting.setPriority(10);
DT.calibrate();

//Get Preload and Sideways
vex::task startClaw(activateClaw);
DT.setSpeed(30);
DT.moveInch(5,'F');
DT.moveInch(5,'B');
DT.sidewaysInch(10,'L');

//Forward And Get Orange Cube
DT.setSpeed(30);
DT.moveInch(16,'F');

//Turn and Foward to get Orange and Purple Cube
DT.InertialTurnRight(90);
wait(250,msec);
DT.setSpeed(30);
DT.moveInch(12,'F');
DT.sidewaysInch(1,'R');
DT.moveInch(15,'F');
wait(750,msec);
task::stop(activateClaw);
claw.Stop(vex::brakeType::hold); 

//Go To Scoring Zone and Score
DT.moveInch(21,'B');
DT.InertialTurnLeft(-180);
DT.setSpeed(30);
wait(500,msec);
DT.sidewaysInch(16,'L');
DT.moveInch(10,'F');
scoreStack();
DT.moveInch(1, 'B');
 claw.moveDown();
 wait(300, msec);
 claw.Stop(vex::brakeType::hold);
 Tray.MoveTray(-0.3);
 DT.moveInch(6, 'B');

}

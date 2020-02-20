//#include "robot_config.h"
//#include "Hunters_Library.h"
int remoteThreshold = 5;
using namespace vex;
//HuntersDT DT =  HuntersDT();
//vacuumClaw claw = vacuumClaw();
// Arm arm = Arm();

int display() { // Centralizes the info printed on the Brain Screen
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(fontType::mono20);
    while (1){
    //Display that the program has started to the screen.
    Brain.Screen.printAt(20,40,"Tray: %6.1f degrees / Pot: %6.1f ", Tray.getMotorDegrees(),Tray.getTrayPotValue());
    Brain.Screen.printAt(20,60,"Gyro Value: %f", DT.getGyro());

    
   Brain.Screen.printAt(20,80,"Inertial - Heading: %6.1f degrees", DT.getHeadingFromInertial());
    //Brain.Screen.printAt(20,60,"Lift Hight: %f rotations", Lift.getHightPosition());
    Brain.Screen.printAt(20,100,"DT inches: %f", DT.getPosition());
   Brain.Screen.printAt(20,125,"Motors DT Temp => FR: %d BR: %d (pct)", DT.getFMTemp(),DT.getBMTemp());
   Brain.Screen.printAt(20,145,"Arm positiom: %6.1f deg / torque: %6.1f nM", arm.getPosition(), arm.getTorque());
  //  Brain.Screen.printAt(20,185,"Arm Angle/value: %d, %d", Tray.getAngle(), Tray.getAngle1());
   // Brain.Screen.printAt(20,185,"Launcher Velocity: %f", Launcher.velocity(velocityUnits::rpm)); 
   Brain.Screen.printAt(20,235,"Dist Back: %6.1f in", DT.getDistanceBack());
  
    vex:task::sleep(100); // Printing only 10 times per second
   }

    return(0); // need to return a value to start it as a task
}


int hunterusercontrol(){
 
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................

double trayPosition = Tray.getTrayPotValue();

// if ((abs(ControllerA.Axis2.value())>remoteThreshold) || (abs(ControllerA.Axis3.value())>remoteThreshold) || (abs(ControllerA.Axis4.value())>remoteThreshold))
 DT.drive(ControllerA.Axis2.value(),ControllerA.Axis1.value(), ControllerA.Axis4.value()*0.8); // Turning speed reduced to 80%

  if (ControllerA.ButtonUp.pressing() && (trayPosition <= Tray.getTrayScoringPosition())  ) {
    Tray.setSpeed(65); 
    Tray.RotateTray(vex::directionType::fwd);
    trayPosition = Tray.getTrayPotValue();
  } 
  //else if (ControllerA.ButtonDown.pressing() ){
  else if (ControllerA.ButtonDown.pressing() && (trayPosition >= Tray.getTrayRestingPosition()) ){
    Tray.setSpeed(100);
    Tray.RotateTray(vex::directionType::rev);
    trayPosition = Tray.getTrayPotValue();
    if (trayPosition < (Tray.getTrayRestingPosition() - 50)) {
       Tray.setSpeed(20);
    }
    
  } else {
  Tray.StopTray(hold);
  }
 

 if (ControllerA.ButtonX.pressing()) {
   scoreStack();
  } 
   else {
  
  }

if (ControllerA.ButtonA.pressing()) {
  vex::task raiseTray(ArmUpTrayPush);
  vex::task raiseArm(ArmUpTrayAlliance);
  raiseTray.setPriority(4);
  raiseArm.setPriority(5);

  } 
   else {
  
  }

 if (ControllerA.ButtonB.pressing()) {
  vex::task raiseTray(ArmUpTrayPush);
  vex::task raiseArm(ArmUpTrayMedium);
  raiseTray.setPriority(4);
  raiseArm.setPriority(5);
  } 
   else {
  
  }

if (ControllerA.ButtonY.pressing()) {
  unfold();
  } 
   else {
  
  }

  if (ControllerA.ButtonL1.pressing()) {
    arm.setSpeed(50); 
    arm.moveUp();
  } 
  else if (ControllerA.ButtonL2.pressing()){
    arm.setSpeed(50);
    arm.moveDown();

  } else {
  arm.stop();
  }

  if (ControllerA.ButtonR1.pressing()) {
      claw.setSpeed(100);
      claw.moveUp();

    } 
  else if (ControllerA.ButtonR2.pressing()){
     claw.setSpeed(100);
    claw.moveDown();

  } else {
     claw.Stop(vex::brakeType::hold);
  }

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
  return(1); // need to return a value to start it as a task
}
  

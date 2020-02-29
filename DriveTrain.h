/*  Ruhi's Library: DRIVETRAIN
        Updated: 01/01/20      */

class HuntersDT {
private:
  vex::motor RFMotor = DTFrontRightMotor;
  vex::motor LFMotor = DTFrontLeftMotor;
  vex::motor RBMotor = DTBackRightMotor;
  vex::motor LBMotor = DTBackLeftMotor;
  vex::gyro Gyro = GyroHunters;
  vex::sonar HunterDist = DistanceSensor;
  vex::sonar HunterDist2 = DistanceSensor2;
  vex::inertial Inertial = huntersInertial;

  // global variables
  double DTSpeed;
  double diameterofWheel;
  double degreePerInch;
  double gearRatio;
  double circumferenceofWheel;
  double inertialRestingValue = -2.4;

public:
  // sets the speed of the R, L, and sideways motors
  void setSpeed(double speed) { DTSpeed = speed; }

  // returns the position of the right front motor
  double getPositionInches() {
    return (RFMotor.rotation(vex::rotationUnits::deg) / degreePerInch);
  }

  double getPositionDegrees(){
    return RFMotor.rotation(vex::rotationUnits::deg);
  }

  // returns the value (in inches) from the front distance sensor
  int getDistanceFront() { return (HunterDist.distance(vex::inches)); }

  // returns the value (in inches) from the back distance sensor
  int getDistanceBack() { return (HunterDist2.distance(vex::inches)); }

  void drive(double speedY, double speedX, double speedR) {
    // SpeedY = backward & forward component (Axis2 of the remote)
    // SpeedX = sideways conmponent (Axis2 of the remote)
    // SpeedR = rotation clockwise/counterClockwise (Axis4 of the remote)
    RFMotor.spin(vex::directionType::rev, -speedY + speedX + speedR, vex::pct);
    LFMotor.spin(vex::directionType::rev, speedY + speedX + speedR, vex::pct);
    RBMotor.spin(vex::directionType::rev, -speedY - speedX + speedR, vex::pct);
    LBMotor.spin(vex::directionType::rev, speedY - speedX + speedR, vex::pct);
  }

  void specificDrive(double speedRF, double speedRB, double speedLF, double speedLB){
    RFMotor.spin(vex::directionType::rev, speedRF, vex::pct);
    LFMotor.spin(vex::directionType::rev, speedLF, vex::pct);
    RBMotor.spin(vex::directionType::rev, speedRB, vex::pct);
    LBMotor.spin(vex::directionType::rev, speedLB, vex::pct);
  }

  // moves the robot forward
  void moveF() { drive(DTSpeed, 0, 0); }

  // moves the robot backward
  void moveB() { drive(-DTSpeed, 0, 0); }

  // moves the robot to the right
  void slideRight() { drive(0, DTSpeed, 0); }

  // moves the robot to the left
  void slideLeft() { drive(0, -DTSpeed, 0); }

  // turns the robot to the right
  void TurnClockwise() { drive(0, 0, DTSpeed); }

  // turns the robot to the left
  void TurnCounterClockwise() { drive(0, 0, -DTSpeed); }

  // spins the R and L motors at different speeds
  void Drive(double speedR, double speedL) {
    RFMotor.spin(vex::directionType::rev, speedR, vex::pct);
    RBMotor.spin(vex::directionType::rev, speedR, vex::pct);
    LFMotor.spin(vex::directionType::fwd, speedL, vex::pct);
    LBMotor.spin(vex::directionType::fwd, speedL, vex::pct);
  }

  // holds the R and L motors
  void stopHold() { stopRL(vex::brakeType::hold); }

  // stops all the motors with a specified type of brake
  void stopRL(vex::brakeType brake) {
    RFMotor.stop(brake);
    RBMotor.stop(brake);
    LFMotor.stop(brake);
    LBMotor.stop(brake);
  }

  // reset the positions of the motors
  void resetPositionDT() {
    RFMotor.setRotation(0, vex::rotationUnits::deg);
    LFMotor.setRotation(0, vex::rotationUnits::deg);
    RBMotor.setRotation(0, vex::rotationUnits::deg);
    LBMotor.setRotation(0, vex::rotationUnits::deg);

    RFMotor.resetRotation();
    LFMotor.resetRotation();
    RBMotor.resetRotation();
    LBMotor.resetRotation();
  }

  // uses the distance sensor to move a specified distance away from a certain
  // object
  void DistF(double distFromObject) {
    int distanceValue = HunterDist.distance(vex::inches);

    while (distanceValue < distFromObject) {
      moveF();

      distanceValue = HunterDist.distance(vex::inches);
      Brain.Screen.printAt(20, 235, "Dist Back: %6.1f in", getDistanceBack());
    }
    stopHold();
  }

  // uses the distance sensor to move a distance to a certain object until a
  // specified distance away
  void DistB(double distFromObject) {
    int distanceValue = HunterDist.distance(vex::inches);

    while (distanceValue > distFromObject) {
      moveB();

      distanceValue = HunterDist.distance(vex::inches);
      Brain.Screen.printAt(20, 235, "Dist Back: %6.1f in", getDistanceBack());
    }

    stopHold();
  }

  // moves using inches without using the distance sensor- forward/backward
  void moveInch(double inches, char direction) {
    double rotations = (inches / circumferenceofWheel) * 360;

    resetPositionDT();

    double rotTraveled = abs(RFMotor.rotation(vex::rotationUnits::deg));

    while (rotations > rotTraveled) {
      if (direction == 'F') {
        moveF();

        rotTraveled = abs(RFMotor.rotation(vex::rotationUnits::deg));
      } else if (direction == 'B') {
        moveB();

        rotTraveled = abs(RFMotor.rotation(vex::rotationUnits::deg));
      }
      Brain.Screen.printAt(20, 80, "DT inches: %f", getPositionInches());
    }
    stopHold();
  }

  // moves using inches without using the distance sensor- Sideways
  void sidewaysInch(double inches, char direction) {
    double rotations = (inches / circumferenceofWheel) * 360;

    resetPositionDT();

    double rotTraveled = abs(RFMotor.rotation(vex::rotationUnits::deg));

    while (rotations > rotTraveled) {
      if (direction == 'R') {
        slideRight();

        rotTraveled = abs(RFMotor.rotation(vex::rotationUnits::deg));
      } else if (direction == 'L') {
        slideLeft();

        rotTraveled = abs(RFMotor.rotation(vex::rotationUnits::deg));
      }
      Brain.Screen.printAt(20, 80, "DT inches: %f", getPositionInches());
    }
    stopHold();
  }

  // coasts the R, L, and sideways motors
  void coastAll() { stopRL(vex::brakeType::coast); }

  // returns the temperature of the R motor
  int getRFMTemp() { return (RFMotor.temperature(vex::pct)); }
  // returns the temperature of the L motor
  int getLFMTemp() { return (LFMotor.temperature(vex::pct)); }

  // returns the temperature of the R motor
  int getRBMTemp() { return (RBMotor.temperature(vex::pct)); }
  // returns the temperature of the L motor
  int getLBMTemp() { return (LBMotor.temperature(vex::pct)); }

  // returns the speed of the R, L, and sideways motors
  double getSpeed() { return (DTSpeed); }

  // returns the value of the Gyro in degrees
  double getGyro() { return Gyro.angle(vex::rotationUnits::deg); }

  // returns the value of the Gyro in degrees
  double getGyro2() {
    double Degrees = Gyro.angle(vex::rotationUnits::deg);
    if (Degrees >= 180) {
      Degrees = Degrees - 360;
    }
    return Degrees;
  }

  // Simple Gyro Turns
  // turns clockwise
  void SimpleTurnRight(double degrees) {
    double current = getGyro();
    while (current < degrees) {
      TurnClockwise();
      current = getGyro();
    }
    stopHold();
  }

  // turns counterclockwise
  void SimpleTurnLeft(double degrees) {
    double current = getGyro();
    while (current > degrees) {
      TurnCounterClockwise();
      current = getGyro();
    }
    stopHold();
  }

  double getHeadingFromInertial() { return Inertial.heading(); }

  // checks whether the turn right completed
  void check1() {
    while (Inertial.heading() == !90) {
      setSpeed(30);
      TurnCounterClockwise();
    }
  }

  // checks whether the turn left completed
  void check2() {
    while (Inertial.heading() == !-90) {
      setSpeed(30);
      TurnClockwise();
    }
  }

  // gets the inertial value in degrees
  double getInertialDegrees() {
    return Inertial.rotation();
    ;
  }

  // calibrates the inertial sensor
  void calibrate() {
    Inertial.startCalibration();
    while (Inertial.isCalibrating()) {
      wait(10, vex::msec);
    }
  }

  // resets the inertial sensor's readings
  void resetIntertialRotation() { Inertial.resetRotation(); }


  void ForwardPID(double speed, double inches, double targetDegrees){
    double targetrotations = (inches / circumferenceofWheel) * 360;
    resetPositionDT();
    resetIntertialRotation();

    double ProportionalConstant = 5;
    double IntegralConsant = 0.01;
    double DerivativeConstant = 1;

    double errorPrevious = 0;
    double currentDegrees = getInertialDegrees();
    double currentRotation = abs(getPositionDegrees());

    double RSpeed = -speed;
    double LSpeed = speed;

    while(currentRotation < targetrotations){
      specificDrive(RSpeed, RSpeed, LSpeed, LSpeed);  

      double error = targetDegrees - currentDegrees;
      double errorTotal = errorTotal+error;
      if(error=0){errorTotal=0;}
      double errorPrediction = errorPrevious - error;
      if(error=0){errorPrediction=0;}
      errorPrevious = error;

      double changeSpeed = ProportionalConstant * error + IntegralConsant * errorTotal + DerivativeConstant * errorPrediction;

      LSpeed += changeSpeed;
      RSpeed -= changeSpeed;

      specificDrive(RSpeed, RSpeed, LSpeed, LSpeed);  

      currentRotation = abs(getPositionDegrees());
      currentDegrees = getInertialDegrees();
      wait(100,vex::msec);
    }
    stopHold();
  }

  // Turn right in degrees using inertial sensor and PID
  void InertialTurnRight(double degrees) {
    resetIntertialRotation();
    double ProportionalConstant = 0.5;
    double IntegralConsant = 0.001;
    double DerivativeConstant = 0.4;

    double errorPrevious = 0;
    double current = getInertialDegrees();

    while (current < degrees) {
      double currentDegrees = current;
      double error = degrees - currentDegrees;
      double errorTotal = errorTotal + error;
      if (error == 0) {
        errorTotal = 0;
      }
      double errorPrediction = errorPrevious - error;
      if (errorPrevious = 0) {
        errorPrediction = 0;
      }
      errorPrevious = error;

      double speedTurn =
          (ProportionalConstant * error + IntegralConsant * errorTotal +
           DerivativeConstant * errorPrediction);

      setSpeed(speedTurn);
      TurnClockwise();
      current = getInertialDegrees();
      wait(100, vex::msec);
    }
    stopHold();
  }

  // Turn left in degrees using intertial sensor and PID
  void InertialTurnLeft(double degrees) {
    resetIntertialRotation();

    double ProportionalConstant = 0.5;
    double IntegralConsant = 0.001;
    double DerivativeConstant = 0.4;

    double errorPrevious = 0;
    double current = getInertialDegrees();

    while (current > degrees) {
      double currentDegrees = current;
      double error = abs(currentDegrees - degrees);
      double errorTotal = errorTotal + error;
      if (error == 0) {
        errorTotal = 0;
      }
      double errorPrediction = errorPrevious - error;
      errorPrevious = error;

      double speedTurn =
          (ProportionalConstant * error + IntegralConsant * errorTotal +
           DerivativeConstant * errorPrediction);

      setSpeed(speedTurn);
      TurnCounterClockwise();
      current = getInertialDegrees();
      wait(100, vex::msec);
    }
    stopHold();
  }

  // gets the inertial roll angle value
  double getInertialValue() {
    double angle = Inertial.orientation(vex::orientationType::roll,
                                        vex::rotationUnits::deg);
    return angle;
  }

  // checks when the z value increases so we know when we approach the scoring
  // zone
  void pitchIncreaseCheck() {
    while (getInertialValue() < inertialRestingValue) {
      setSpeed(30);
      moveF();
    }
    stopHold();
  }

  // Constructors //
  HuntersDT() {
    diameterofWheel = 3.25;
    DTSpeed = 80;
    degreePerInch = 280 / 12;
    circumferenceofWheel = diameterofWheel * 3.14159265359;
  }
  ~HuntersDT() {}
} DT;

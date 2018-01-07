#include "WPILib.h"
#include "curtinfrc/math.h"
#include <iostream>
#include <string>
#include <SmartDashboard/SmartDashboard.h>
#include <PowerDistributionPanel.h>

using namespace frc;
using namespace curtinfrc;
using namespace std;

class Robot : public IterativeRobot {
  XboxController *xbox = new XboxController(0);
  PowerDistributionPanel *pdp = new PowerDistributionPanel(0);
  SendableChooser<int*> *AutoChooser = new SendableChooser<int*>; // Choose auto mode
public:
  string gameData;
  bool A,B,X,Y,LB,RB,back,start,LS,RS;
  double LX,LY,RX,RY,LT,RT,Dpad;
  int Auto;
  void RobotInit() {
    std::cout << "0.5^2 = " << math::square_keep_sign(0.5) << std::endl; //?
    AutoChooser->AddDefault("Cross Baseline",(int*) 0);
    AutoChooser->AddObject("Auto 1",(int*) 1);
    AutoChooser->AddObject("Auto 2",(int*) 2);
    getValues();
    updateDash();
  }

  void getValues() { //Set variables for the xbox controller values for easy coding
    A = xbox->GetRawButton(1);
    B = xbox->GetRawButton(2);
    X = xbox->GetRawButton(3);
    Y = xbox->GetRawButton(4);
    LB = xbox->GetRawButton(5);
    RB = xbox->GetRawButton(6);
    back = xbox->GetRawButton(7);
    start = xbox->GetRawButton(8);
    LS = xbox->GetRawButton(9);
    RS = xbox->GetRawButton(10);
    LX = xbox->GetRawAxis(0);
    LY = xbox->GetRawAxis(1);
    LT = xbox->GetRawAxis(2);
    RT = xbox->GetRawAxis(3);
    RX = xbox->GetRawAxis(4);
    RY = xbox->GetRawAxis(5);
    Dpad = xbox->GetPOV();
  }

  void updateDash() { //Put new controller values to the dashboard
    SmartDashboard::PutNumber("D-Pad", Dpad);
    SmartDashboard::PutNumber("Current Draw", pdp->GetTotalCurrent());
    SmartDashboard::PutBoolean("A", A);
    SmartDashboard::PutBoolean("B", B);
    SmartDashboard::PutBoolean("X", X);
  	SmartDashboard::PutBoolean("Y", Y);
  	SmartDashboard::PutBoolean("Left Bumper", LB);
    SmartDashboard::PutBoolean("Right Bumper", RB);
    SmartDashboard::PutBoolean("Back", back);
    SmartDashboard::PutBoolean("Start", start);
    SmartDashboard::PutBoolean("Left Stick", LS);
  	SmartDashboard::PutBoolean("Right Stick", RS);
    SmartDashboard::PutNumber("Left Stick X", LX);
    SmartDashboard::PutNumber("Right Stick X", RX);
    SmartDashboard::PutNumber("Left Stick Y", LY);
    SmartDashboard::PutNumber("Right Stick Y", RY);
    SmartDashboard::PutNumber("Left Trigger", LT);
    SmartDashboard::PutNumber("Right Trigger", RT);
  }

  void AutonomousInit() {
    gameData = DriverStation::GetInstance().GetGameSpecificMessage(); //Get specific match data
    SmartDashboard::PutString("Alliance Switch:", &gameData[0]);
    SmartDashboard::PutString("Scale:", &gameData[1]);
    SmartDashboard::PutString("Enemy Switch:", &gameData[2]);  //Put data on shuffleboard
    Auto = (int) AutoChooser->GetSelected(); //What auto mode you wanna do
  }
  void AutonomousPeriodic() {
    // gameData will be an array with 3 characters, eg. "LRL"
    // check https://wpilib.screenstepslive.com/s/currentCS/m/getting_started/l/826278-2018-game-data-details
  }

  void TeleopInit() { }
  void TeleopPeriodic() {
    void getValues();
    void updateDash();
  }

  void TestInit() { }
  void TestPeriodic() { }
};

START_ROBOT_CLASS(Robot)

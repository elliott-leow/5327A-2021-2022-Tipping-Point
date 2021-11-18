#include "main.h"
#include "math.h"


void move(int i) {
  FrontRightWheel.tare_position();
  FrontLeftWheel.tare_position();
  BackRightWheel.tare_position();
  BackLeftWheel.tare_position();
  int target = Inertial.get_heading();
  if (i >= 0) {
    while (FrontRightWheel.get_position() < i) {
      //int error = (i - FrontRightWheel.get_position()) * .2;
      int move = 105;
      int leftRotation = 0;
      int rightRotation = 10;
      // if (target-Inertial.get_heading() > 180) { //left
      //   rightRotation = 360 - (target - Inertial.get_heading())/1;
      // } else {
      //   leftRotation = (target-Inertial.get_heading())/1;
      // }
      // if (target-Inertial.get_heading() < 0) { //left
      //   rightRotation = -(target - Inertial.get_heading())/2;
      // } else {
      //   leftRotation = (target-Inertial.get_heading())/2;
      // }

      FrontRightWheel.move(move-rightRotation);
      FrontLeftWheel.move(move-leftRotation);
      BackRightWheel.move(move-rightRotation);
      BackLeftWheel.move(move-leftRotation);

    }
  }
  else if (i < 0) {
    while (FrontRightWheel.get_position() > i) {
      //int error = (FrontRightWheel.get_position() - i)*0.1;
      int move = -105;
      int leftRotation = 0;
      int rightRotation = 10;
      FrontRightWheel.move(move+rightRotation);
      FrontLeftWheel.move(move);
      BackRightWheel.move(move+rightRotation);
      BackLeftWheel.move(move);

    }
  }
  FrontRightWheel.move(0);
  FrontLeftWheel.move(0);
  BackRightWheel.move(0);
  BackLeftWheel.move(0);

}

void turn (int i){
  int tolerance = 26;
  Inertial.tare();
  if(i < 0) i = 360 - i;

  while (!(Inertial.get_heading() > i - tolerance && Inertial.get_heading() < i + tolerance)) {
    //int error = abs((i-Inertial.get_heading()))*1.4;

    int move = i < 180 ? 75 : -75;
    FrontRightWheel.move(-move);
        FrontLeftWheel.move(move);
        BackRightWheel.move(-move);
        BackLeftWheel.move(move);
    // if (i>Inertial.get_rotation()+180 || i < Inertial.get_rotation()) {
    //   FrontRightWheel.move(move);
    //       FrontLeftWheel.move(-move);
    //       BackRightWheel.move(move);
    //       BackLeftWheel.move(-move);
    // }
    // else if (i > Inertial.get_rotation()) {
    //
    // }

  }
  FrontLeftWheel.move(0);
  FrontRightWheel.move(0);
  BackRightWheel.move(0);
  BackLeftWheel.move(0);






    // double k = 1.4;
    // if (i > 0) {
    //   while (Inertial.get_heading() < i) {
    //     int error = (i - Inertial.get_heading())*k;
    //     int move = error > 127 ? 127 : error;
    //     FrontRightWheel.move(-move);
    //     FrontLeftWheel.move(move);
    //     BackRightWheel.move(-move);
    //     BackLeftWheel.move(move);
    //   }
    // } else if (i < 0) {
    //   int r = i;
    //   //while (Inertial.get_heading() > r || Inertial.get_heading() < 180) {
    //     //int error = ((r) - (Inertial.get_heading()+360))*k;
    //     //int move = error < -127 ? -127 : error;
    //     Inertial.tare();
    //
    //     while (Inertial.get_rotation() > i) {
    //         pros::lcd::set_text(2, std::to_string(Inertial.get_rotation()));
    //     FrontRightWheel.move(60);
    //     FrontLeftWheel.move(-60);
    //     BackRightWheel.move(60);
    //     BackLeftWheel.move(-60);
    //   }
    //   }
    }

void autonomous(){
  pros::lcd::initialize();
  Inertial.reset();
  pros::delay(2000);


    RingIntake.move_relative(1500,-127);
    //score ring on mogo on ramp

    pros::delay(2000);
    move(-300);

    turn(60);
    //moves backwards from mogo on ramp and aligns with next mogo

}

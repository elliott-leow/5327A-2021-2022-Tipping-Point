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
      int error = (i - FrontRightWheel.get_position())*0.1;
      int move = error > 127 ? 127 : error;
      int leftRotation = 0;
      int rightRotation = 0;
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
  if (i < 0) {
    while (FrontRightWheel.get_position() > i) {
      int error = (FrontRightWheel.get_position() - i)*0.1;
      int move = error + 30;
      FrontRightWheel.move(move);
      FrontLeftWheel.move(move);
      BackRightWheel.move(move);
      BackLeftWheel.move(move);

    }
  }

}

void turn (int i, int tolerance){
  Inertial.tare();

  while (Inertial.get_rotation() < i - tolerance || Inertial.get_rotation() > i + tolerance) {
    int error = (i-Inertial.get_rotation())*1.4;

    int move = error;
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
  FrontRightWheel.move(0);
  FrontLeftWheel.move(0);
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
  pros::delay(3000);

    move(3000);
    turn(90);
    //pros::delay(3000);
    //turn(-90);

}

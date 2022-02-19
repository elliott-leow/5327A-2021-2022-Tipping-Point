#include "main.h"
#include "math.h"
#include <chrono>
#include <cstdint>
#include <iostream>

#define close_turn 90
#define auton 5
using namespace std;

// GLOBAL POSITION VARIABLES
double x = 0;
double y = 0;
// CURRENT MOTOR ENCODER TICKS
double BL, BR, ML, MR, FL, FR;

//-1 == gilbert's left side autonomous
<<<<<<< Updated upstream
// 0 == elims
=======
<<<<<<< HEAD
// 0 == elims
=======
// 0 == skills
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
// 1 == small and large neutral
// 2 == winpoint auton
// 3 == do nothing
// 4 == prog skills
// double KPBASETURN = 0.2;
double KPBASETURN = 0.2;
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
>>>>>>> Stashed changes
//LV_IMG_DECLARE(gojo);
void initialize() {
//     lv_obj_t * img_src = lv_img_create(lv_scr_act(), NULL); /*Crate an image
//     // object*/ lv_img_set_src(img_src, &gojo);  /*Set the created file as image
//     // (a red fl  ower)*/ lv_obj_set_pos(img_src, 0, 0);      /*Set the
//     // positions*/ lv_obj_set_drag(img_src, true);
<<<<<<< Updated upstream
=======
=======
// LV_IMG_DECLARE(gojo);
void initialize() {
    // lv_obj_t * img_src = lv_img_create(lv_scr_act(), NULL); /*Crate an image
    // object*/ lv_img_set_src(img_src, &gojo);  /*Set the created file as image
    // (a red fl  ower)*/ lv_obj_set_pos(img_src, 0, 0);      /*Set the
    // positions*/ lv_obj_set_drag(img_src, true);
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
    // pros::delay(15000);
    pros::lcd::initialize();
    Inertial.reset();
    pros::delay(3000);
<<<<<<< Updated upstream
    //pros::lcd::set_text(2, "Stop setup");
    //pros::lcd::set_text(3, to_string(auton));
=======
<<<<<<< HEAD
    //pros::lcd::set_text(2, "Stop setup");
    //pros::lcd::set_text(3, to_string(auton));
=======
    pros::lcd::set_text(2, "Stop setup");
    pros::lcd::set_text(3, to_string(auton));
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
}

void competition_initialize() { initialize(); }

double saveHeading = 0;

void movespeed(int i, int angle, int speed) {
    // i = motor speed, angle = angle the robot should turn towards while moving
    FrontRightWheel.tare_position();
    FrontLeftWheel.tare_position();
    BackRightWheel.tare_position();
    BackLeftWheel.tare_position();
    int target = Inertial.get_heading();

    while (abs(FrontRightWheel.get_position()) < abs(i)) {

        int actual_turn = 0;
        int move = i < 0 ? -90 : 90;
        int tolerance = 3;
        int upperAngleBound = angle + tolerance;
        int lowerAngleBound = angle - tolerance;

        int angle_ = (Inertial.get_heading());
        bool specialDown = false;
        bool specialUp = false;
        if (lowerAngleBound < 0) {
            lowerAngleBound = lowerAngleBound + 360;
            specialDown = true;
<<<<<<< Updated upstream
        }
        if (upperAngleBound > 360) {
            upperAngleBound = upperAngleBound - 360;
            specialUp = true;
        }
=======
<<<<<<< HEAD
        }
        if (upperAngleBound > 360) {
            upperAngleBound = upperAngleBound - 360;
            specialUp = true;
        }
=======
        }
        if (upperAngleBound > 360) {
            upperAngleBound = upperAngleBound - 360;
            specialUp = true;
        }
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
        // if the robot is not at the heading
        if ((specialDown == true &&
             ((angle_ < lowerAngleBound && angle_ > angle + 180) ||
              (angle_ > upperAngleBound && angle_ < angle + 180))) ||
            (specialUp == true &&
             ((angle_ > upperAngleBound && angle_ < angle - 180) ||
              (angle_ < lowerAngleBound && angle_ > angle - 180))) ||
            ((specialUp == false && specialDown == false) &&
             (angle_ > upperAngleBound || angle_ < lowerAngleBound))) {
            angle_ = (Inertial.get_heading());

            float turn_difference = angle_ - angle;

            while (turn_difference > 180)
                turn_difference = 360 - turn_difference;
            while (turn_difference < -180)
                turn_difference = 360 + turn_difference;
            if (turn_difference < 0 && turn_difference > -180)
                turn_difference = -turn_difference;

            // Spins in the directions which will allow bot to complete turn
            // fastest
            if (turn_difference > 180)
                turn_difference = 360 - turn_difference;

            // Slows down if close to goal heading and stays fast if it is away
            int turn_speed = 90;
            if (turn_difference < close_turn) {
                actual_turn = (turn_speed *
                               ((turn_difference / (close_turn)) + KPBASETURN));
            } else {
                actual_turn = turn_speed;
            }

            /*Special conditions if angle bounds are less than 0 or greater than
               360 Neccesary for proper turning and calculation*/
            if ((angle > angle_ + 180) ||
                (angle > angle_ - 180 && angle_ > 180 && angle < 180) ||
                (angle < angle_ && angle_ - angle < 180))
                actual_turn = -actual_turn;
        }
        int c = 5;
        if (i < 0) {

            c = -c;
        }

        FrontLeftWheel.move(-move - actual_turn + speed);
        MiddleLeftWheel.move(-move - actual_turn + speed);
        BackLeftWheel.move(+move + actual_turn - speed);
        FrontRightWheel.move(+move - actual_turn - speed);
        MiddleRightWheel.move(+move - actual_turn - speed);
        BackRightWheel.move(-move + actual_turn + speed);

        // move robot foward and turn at same time
        //  FrontRightWheel.move(move-actual_turn+c);
        //  FrontLeftWheel.move(move+actual_turn-c);
        //  BackRightWheel.move(move-actual_turn+c);
        //  BackLeftWheel.move(move+actual_turn-c);
    }

    // Moves the wheels at a certain "move" speed
    FrontRightWheel.move(0);
    FrontLeftWheel.move(0);
    BackRightWheel.move(0);
    BackLeftWheel.move(0);
}

void move(int i) {
    // i = motor speed
    int target = Inertial.get_heading();
    FrontRightWheel.tare_position();
    FrontLeftWheel.tare_position();
    BackRightWheel.tare_position();
    BackLeftWheel.tare_position();
    if (i > 0) {
        while (FrontRightWheel.get_position() < i) {
            int difference = (Inertial.get_heading() - target) * KPBASETURN;

            FrontLeftWheel.move(-127 - difference);
            MiddleLeftWheel.move(-127 - difference);
            BackLeftWheel.move(127 + difference);
            FrontRightWheel.move(127 - difference);
            MiddleRightWheel.move(127 - difference);
            BackRightWheel.move(-127 + difference);

            pros::lcd::set_text(4, std::to_string(difference));
        }
    }
    if (i < 0) {
        while (FrontRightWheel.get_position() > i) {
            int difference = (Inertial.get_heading() - target) * KPBASETURN;

            FrontLeftWheel.move(127 + difference);
            MiddleLeftWheel.move(127 + difference);
            BackLeftWheel.move(-127 - difference);

            FrontRightWheel.move(-127 + difference);
            MiddleRightWheel.move(-127 + difference);
            BackRightWheel.move(127 - difference);

            pros::lcd::set_text(4, std::to_string(difference));
        }
    }
    FrontRightWheel.move(0);
    FrontLeftWheel.move(0);
    MiddleRightWheel.move(0);
    MiddleLeftWheel.move(0);
    BackRightWheel.move(0);
    BackLeftWheel.move(0);
}

void movespeed(int i, int speed) {
    // i = motor speed
    int target = Inertial.get_heading();
    FrontRightWheel.tare_position();
    FrontLeftWheel.tare_position();
    BackRightWheel.tare_position();
    BackLeftWheel.tare_position();
    if (i > 0) {
        while (FrontRightWheel.get_position() < i) {
            int difference = (Inertial.get_heading() - target) * KPBASETURN;

            FrontLeftWheel.move(-127 - difference + speed);
            MiddleLeftWheel.move(-127 - difference + speed);
            BackLeftWheel.move(+127 + difference - speed);
            FrontRightWheel.move(+127 - difference - speed);
            MiddleRightWheel.move(+127 - difference - speed);
            BackRightWheel.move(-127 + difference + speed);

            pros::lcd::set_text(4, std::to_string(difference));
        }
    }
    if (i < 0) {
        while (FrontRightWheel.get_position() > i) {
            int difference = (Inertial.get_heading() - target) * KPBASETURN;

            FrontLeftWheel.move(+127 + difference - speed);
            MiddleLeftWheel.move(+127 + difference - speed);
            BackLeftWheel.move(-127 - difference + speed);

            FrontRightWheel.move(-127 + difference + speed);
            MiddleRightWheel.move(-127 + difference + speed);
            BackRightWheel.move(+127 - difference - speed);

            pros::lcd::set_text(4, std::to_string(difference));
        }
    }
    FrontRightWheel.move(0);
    FrontLeftWheel.move(0);
    MiddleRightWheel.move(0);
    MiddleLeftWheel.move(0);
    BackRightWheel.move(0);
    BackLeftWheel.move(0);
}

void move(int i, int angle) {
    // i = motor speed, angle = angle the robot should turn towards while moving

    FrontRightWheel.tare_position();
    FrontLeftWheel.tare_position();
    BackRightWheel.tare_position();
    BackLeftWheel.tare_position();
    int target = Inertial.get_heading();

    while (std::abs(FrontRightWheel.get_position()) < std::abs(i)) {

        int actual_turn = 0;
        int move = i < 0 ? -90 : 90;
        int tolerance = 3;
        int upperAngleBound = angle + tolerance;
        int lowerAngleBound = angle - tolerance;

        int angle_ = (Inertial.get_heading());
        bool specialDown = false;
        bool specialUp = false;
        if (lowerAngleBound < 0) {
            lowerAngleBound = lowerAngleBound + 360;
            specialDown = true;
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
>>>>>>> Stashed changes
        }
        if (upperAngleBound > 360) {
            upperAngleBound = upperAngleBound - 360;
            specialUp = true;
        }
<<<<<<< Updated upstream
=======
=======
        }
        if (upperAngleBound > 360) {
            upperAngleBound = upperAngleBound - 360;
            specialUp = true;
        }
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
        // if the robot is not at the heading
        if ((specialDown == true &&
             ((angle_ < lowerAngleBound && angle_ > angle + 180) ||
              (angle_ > upperAngleBound && angle_ < angle + 180))) ||
            (specialUp == true &&
             ((angle_ > upperAngleBound && angle_ < angle - 180) ||
              (angle_ < lowerAngleBound && angle_ > angle - 180))) ||
            ((specialUp == false && specialDown == false) &&
             (angle_ > upperAngleBound || angle_ < lowerAngleBound))) {
            angle_ = (Inertial.get_heading());

            float turn_difference = angle_ - angle;

            if (turn_difference > 180)
                turn_difference = 360 - turn_difference;
            if (turn_difference < -180)
                turn_difference = 360 + turn_difference;
            if (turn_difference < 0 && turn_difference > -180)
                turn_difference = -turn_difference;

            // Spins in the directions which will allow bot to complete turn
            // fastest
            if (turn_difference > 180)
                turn_difference = 360 - turn_difference;

            // Slows down if close to goal heading and stays fast if it is away
            int turn_speed = 90;
            if (turn_difference < close_turn) {
                actual_turn = (turn_speed *
                               ((turn_difference / (close_turn)) + KPBASETURN));
            } else {
                actual_turn = turn_speed;
            }

            /*Special conditions if angle bounds are less than 0 or greater than
               360 Neccesary for proper turning and calculation*/
            if ((angle > angle_ + 180) ||
                (angle > angle_ - 180 && angle_ > 180 && angle < 180) ||
                (angle < angle_ && angle_ - angle < 180))
                actual_turn = -actual_turn;
        }
        int c = 5;
        if (i < 0) {

            c = -c;
        }

        FrontLeftWheel.move(-move - actual_turn);
        MiddleLeftWheel.move(-move - actual_turn);
        BackLeftWheel.move(+move + actual_turn);
        FrontRightWheel.move(+move - actual_turn);
        MiddleRightWheel.move(+move - actual_turn);
        BackRightWheel.move(-move + actual_turn);

        // move robot foward and turn at same time
        //  FrontRightWheel.move(move-actual_turn+c);
        //  FrontLeftWheel.move(move+actual_turn-c);
        //  BackRightWheel.move(move-actual_turn+c);
        //  BackLeftWheel.move(move+actual_turn-c);
    }

    // Moves the wheels at a certain "move" speed
    FrontRightWheel.move(0);
    FrontLeftWheel.move(0);
    BackRightWheel.move(0);
    BackLeftWheel.move(0);
}

void moveLift(int i, int angle, int lift) {
    // i = motor speed, angle = angle the robot should turn towards while moving
    TopLift.move_relative(lift, 127);
    FrontRightWheel.tare_position();
    FrontLeftWheel.tare_position();
    BackRightWheel.tare_position();
    BackLeftWheel.tare_position();
    int target = Inertial.get_heading();

    while (std::abs(FrontRightWheel.get_position()) < std::abs(i)) {

        int actual_turn = 0;
        int move = i < 0 ? -90 : 90;
        int tolerance = 3;
        int upperAngleBound = angle + tolerance;
        int lowerAngleBound = angle - tolerance;

        int angle_ = (Inertial.get_heading());
        bool specialDown = false;
        bool specialUp = false;
        if (lowerAngleBound < 0) {
            lowerAngleBound = lowerAngleBound + 360;
            specialDown = true;
<<<<<<< Updated upstream
        }
        if (upperAngleBound > 360) {
            upperAngleBound = upperAngleBound - 360;
            specialUp = true;
        }
=======
        }
        if (upperAngleBound > 360) {
            upperAngleBound = upperAngleBound - 360;
            specialUp = true;
        }
>>>>>>> Stashed changes
        // if the robot is not at the heading
        if ((specialDown == true &&
             ((angle_ < lowerAngleBound && angle_ > angle + 180) ||
              (angle_ > upperAngleBound && angle_ < angle + 180))) ||
            (specialUp == true &&
             ((angle_ > upperAngleBound && angle_ < angle - 180) ||
              (angle_ < lowerAngleBound && angle_ > angle - 180))) ||
            ((specialUp == false && specialDown == false) &&
             (angle_ > upperAngleBound || angle_ < lowerAngleBound))) {
            angle_ = (Inertial.get_heading());

            float turn_difference = angle_ - angle;

            if (turn_difference > 180)
                turn_difference = 360 - turn_difference;
            if (turn_difference < -180)
                turn_difference = 360 + turn_difference;
            if (turn_difference < 0 && turn_difference > -180)
                turn_difference = -turn_difference;

            // Spins in the directions which will allow bot to complete turn
            // fastest
            if (turn_difference > 180)
                turn_difference = 360 - turn_difference;

            // Slows down if close to goal heading and stays fast if it is away
            int turn_speed = 90;
            if (turn_difference < close_turn) {
                actual_turn = (turn_speed *
                               ((turn_difference / (close_turn)) + KPBASETURN));
            } else {
                actual_turn = turn_speed;
            }

            /*Special conditions if angle bounds are less than 0 or greater than
               360 Neccesary for proper turning and calculation*/
            if ((angle > angle_ + 180) ||
                (angle > angle_ - 180 && angle_ > 180 && angle < 180) ||
                (angle < angle_ && angle_ - angle < 180))
                actual_turn = -actual_turn;
        }
        int c = 5;
        if (i < 0) {

            c = -c;
        }
<<<<<<< Updated upstream

        FrontLeftWheel.move(-move - actual_turn);
        MiddleLeftWheel.move(-move - actual_turn);
        BackLeftWheel.move(+move + actual_turn);
        FrontRightWheel.move(+move - actual_turn);
        MiddleRightWheel.move(+move - actual_turn);
        BackRightWheel.move(-move + actual_turn);

        // move robot foward and turn at same time
        //  FrontRightWheel.move(move-actual_turn+c);
        //  FrontLeftWheel.move(move+actual_turn-c);
        //  BackRightWheel.move(move-actual_turn+c);
        //  BackLeftWheel.move(move+actual_turn-c);
    }

    // Moves the wheels at a certain "move" speed
    FrontRightWheel.move(0);
    FrontLeftWheel.move(0);
    BackRightWheel.move(0);
    BackLeftWheel.move(0);
}

void stopHold() {

    FrontLeftWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    FrontRightWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackRightWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackLeftWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    FrontLeftWheel.move(0);
    FrontRightWheel.move(0);
    BackRightWheel.move(0);
    BackLeftWheel.move(0);
}

void turn(int angle, int tolerance, int turn_speed) {

    int upperAngleBound = angle + tolerance;
    int lowerAngleBound = angle - tolerance;

    long begin_time = pros::millis();

    int angle_ = (Inertial.get_heading());

    // Special conditions (If the angle is at 0 for example)

    bool specialDown = false;
    bool specialUp = false;

    if (lowerAngleBound < 0) {
        lowerAngleBound = lowerAngleBound + 360;
        specialDown = true;
    }
    if (upperAngleBound > 360) {
        upperAngleBound = upperAngleBound - 360;
        specialUp = true;
    }

    while ((specialDown == true &&
            ((angle_ < lowerAngleBound && angle_ > angle + 180) ||
             (angle_ > upperAngleBound && angle_ < angle + 180))) ||
           (specialUp == true &&
            ((angle_ > upperAngleBound && angle_ < angle - 180) ||
             (angle_ < lowerAngleBound && angle_ > angle - 180))) ||
           ((specialUp == false && specialDown == false) &&
            (angle_ > upperAngleBound || angle_ < lowerAngleBound))) {

        angle_ = (Inertial.get_heading());

        double turn_difference = angle_ - angle;
        double actual_turn = 0;
        if (turn_difference > 180)
            turn_difference = 360 - turn_difference;
        if (turn_difference < -180)
            turn_difference = 360 + turn_difference;
        if (turn_difference < 0 && turn_difference > -180)
            turn_difference = -turn_difference;

        // Spins in the directions which will allow bot to complete turn fastest
        if (turn_difference > 180)
            turn_difference = 360 - turn_difference;

        // Slows down if close to goal heading and stays fast if it is away
        if (turn_difference < close_turn) {

            actual_turn =
                (turn_speed * ((turn_difference / (close_turn)) + KPBASETURN));
        } else {
            actual_turn = turn_speed;
        }

        /*Special conditions if angle bounds are less than 0 or greater than 360
                Neccesary for proper turning and calculation*/
        if ((angle > angle_ + 180) ||
            (angle > angle_ - 180 && angle_ > 180 && angle < 180) ||
            (angle < angle_ && angle_ - angle < 180))
            actual_turn = -actual_turn;
=======

        FrontLeftWheel.move(-move - actual_turn);
        MiddleLeftWheel.move(-move - actual_turn);
        BackLeftWheel.move(+move + actual_turn);
        FrontRightWheel.move(+move - actual_turn);
        MiddleRightWheel.move(+move - actual_turn);
        BackRightWheel.move(-move + actual_turn);

        // move robot foward and turn at same time
        //  FrontRightWheel.move(move-actual_turn+c);
        //  FrontLeftWheel.move(move+actual_turn-c);
        //  BackRightWheel.move(move-actual_turn+c);
        //  BackLeftWheel.move(move+actual_turn-c);
    }

    // Moves the wheels at a certain "move" speed
    FrontRightWheel.move(0);
    FrontLeftWheel.move(0);
    BackRightWheel.move(0);
    BackLeftWheel.move(0);
}
<<<<<<< HEAD

void stopHold() {

    FrontLeftWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    FrontRightWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackRightWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackLeftWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    FrontLeftWheel.move(0);
    FrontRightWheel.move(0);
    BackRightWheel.move(0);
    BackLeftWheel.move(0);
}

void turn(int angle, int tolerance, int turn_speed) {

    int upperAngleBound = angle + tolerance;
    int lowerAngleBound = angle - tolerance;

    long begin_time = pros::millis();

    int angle_ = (Inertial.get_heading());

    // Special conditions (If the angle is at 0 for example)

    bool specialDown = false;
    bool specialUp = false;

    if (lowerAngleBound < 0) {
        lowerAngleBound = lowerAngleBound + 360;
        specialDown = true;
    }
    if (upperAngleBound > 360) {
        upperAngleBound = upperAngleBound - 360;
        specialUp = true;
    }

    while ((specialDown == true &&
            ((angle_ < lowerAngleBound && angle_ > angle + 180) ||
             (angle_ > upperAngleBound && angle_ < angle + 180))) ||
           (specialUp == true &&
            ((angle_ > upperAngleBound && angle_ < angle - 180) ||
             (angle_ < lowerAngleBound && angle_ > angle - 180))) ||
           ((specialUp == false && specialDown == false) &&
            (angle_ > upperAngleBound || angle_ < lowerAngleBound))) {

        angle_ = (Inertial.get_heading());

        double turn_difference = angle_ - angle;
        double actual_turn = 0;
        if (turn_difference > 180)
            turn_difference = 360 - turn_difference;
        if (turn_difference < -180)
            turn_difference = 360 + turn_difference;
        if (turn_difference < 0 && turn_difference > -180)
            turn_difference = -turn_difference;

        // Spins in the directions which will allow bot to complete turn fastest
        if (turn_difference > 180)
            turn_difference = 360 - turn_difference;

        // Slows down if close to goal heading and stays fast if it is away
        if (turn_difference < close_turn) {

            actual_turn =
                (turn_speed * ((turn_difference / (close_turn)) + KPBASETURN));
        } else {
            actual_turn = turn_speed;
        }

        /*Special conditions if angle bounds are less than 0 or greater than 360
                Neccesary for proper turning and calculation*/
        if ((angle > angle_ + 180) ||
            (angle > angle_ - 180 && angle_ > 180 && angle < 180) ||
            (angle < angle_ && angle_ - angle < 180))
            actual_turn = -actual_turn;
=======

void stopHold() {

    FrontLeftWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    FrontRightWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackRightWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackLeftWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    FrontLeftWheel.move(0);
    FrontRightWheel.move(0);
    BackRightWheel.move(0);
    BackLeftWheel.move(0);
}

void turn(int angle, int tolerance, int turn_speed) {

    int upperAngleBound = angle + tolerance;
    int lowerAngleBound = angle - tolerance;

    long begin_time = pros::millis();

    int angle_ = (Inertial.get_heading());

    // Special conditions (If the angle is at 0 for example)

    bool specialDown = false;
    bool specialUp = false;

    if (lowerAngleBound < 0) {
        lowerAngleBound = lowerAngleBound + 360;
        specialDown = true;
    }
    if (upperAngleBound > 360) {
        upperAngleBound = upperAngleBound - 360;
        specialUp = true;
    }

    while ((specialDown == true &&
            ((angle_ < lowerAngleBound && angle_ > angle + 180) ||
             (angle_ > upperAngleBound && angle_ < angle + 180))) ||
           (specialUp == true &&
            ((angle_ > upperAngleBound && angle_ < angle - 180) ||
             (angle_ < lowerAngleBound && angle_ > angle - 180))) ||
           ((specialUp == false && specialDown == false) &&
            (angle_ > upperAngleBound || angle_ < lowerAngleBound))) {

        angle_ = (Inertial.get_heading());

        double turn_difference = angle_ - angle;
        double actual_turn = 0;
        if (turn_difference > 180)
            turn_difference = 360 - turn_difference;
        if (turn_difference < -180)
            turn_difference = 360 + turn_difference;
        if (turn_difference < 0 && turn_difference > -180)
            turn_difference = -turn_difference;

        // Spins in the directions which will allow bot to complete turn fastest
        if (turn_difference > 180)
            turn_difference = 360 - turn_difference;

        // Slows down if close to goal heading and stays fast if it is away
        if (turn_difference < close_turn) {

            actual_turn =
                (turn_speed * ((turn_difference / (close_turn)) + KPBASETURN));
        } else {
            actual_turn = turn_speed;
        }

        /*Special conditions if angle bounds are less than 0 or greater than 360
                Neccesary for proper turning and calculation*/
        if ((angle > angle_ + 180) ||
            (angle > angle_ - 180 && angle_ > 180 && angle < 180) ||
            (angle < angle_ && angle_ - angle < 180))
            actual_turn = -actual_turn;

        FrontLeftWheel.move(-actual_turn);
        MiddleLeftWheel.move(-actual_turn);
        BackLeftWheel.move(actual_turn);
        FrontRightWheel.move(-actual_turn);
        MiddleRightWheel.move(-actual_turn);
        BackRightWheel.move(actual_turn);

        pros::lcd::set_text(1, std::to_string(angle_));
        pros::lcd::set_text(2, std::to_string(angle));
        pros::lcd::set_text(3, std::to_string(actual_turn));

        pros::delay(5);
    }

    stopHold();

    pros::lcd::set_text(4, "Goal reached");
}

void turnPID(int angle, double tolerance) {

    double upperAngleBound = angle + tolerance;
    double lowerAngleBound = angle - tolerance;

    long begin_time = pros::millis();

    double angle_ = (Inertial.get_heading());
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6

    int kU = 5;
    int tU = 2;
    // double Pu = 0.7;
    double kP = 0.2 * kU; // og 0.8
    double kI = 0;        // 1.2*kU/tU;//kU*2 / Pu;
    double kD = 1 * kU * tU;

<<<<<<< HEAD
        pros::lcd::set_text(1, std::to_string(angle_));
        pros::lcd::set_text(2, std::to_string(angle));
        pros::lcd::set_text(3, std::to_string(actual_turn));

        pros::delay(5);
    }

    stopHold();
>>>>>>> Stashed changes

    pros::lcd::set_text(4, "Goal reached");
}

<<<<<<< Updated upstream
        pros::lcd::set_text(1, std::to_string(angle_));
        pros::lcd::set_text(2, std::to_string(angle));
        pros::lcd::set_text(3, std::to_string(actual_turn));

        pros::delay(5);
    }

    stopHold();

    pros::lcd::set_text(4, "Goal reached");
}

/*
 * Turns the robot in place until it reaches the goal
 * @param goal - color of goal, 0 is red, 1 is blue, 2 is yellow
 * @param direction - if the goal is to the left or right of the robot
 * @return - double of the averaged motor displacement
 */
//
// void turnToGoal(int color) {
//     pros::vision_object_s_t rtn = Camera.get_by_sig(0, color);
//
//     int actual_turn = 0;
//     int offset = rtn.x_middle_coord - 158;
//     while ((rtn.x_middle_coord > 158+1 || rtn.x_middle_coord < 158-1) && actual_turn < 2) {
//
//       int offset = rtn.x_middle_coord - 158;
//       actual_turn = offset;
//       FrontLeftWheel.move(-actual_turn);
//       MiddleLeftWheel.move(-actual_turn);
//       BackLeftWheel.move(actual_turn);
//       FrontRightWheel.move(-actual_turn);
//       MiddleRightWheel.move(-actual_turn);
//       BackRightWheel.move(actual_turn);
//     }
// }

void turnPID(int angle, double tolerance) {

    double upperAngleBound = angle + tolerance;
    double lowerAngleBound = angle - tolerance;

    long begin_time = pros::millis();

    double angle_ = (Inertial.get_heading());

    //int kU = 5;
    //int tU = 2;
    // double Pu = 0.7;
    double kP = 1.9; // og 0.8
    double kI = 0.00004;        // 1.2*kU/tU;//kU*2 / Pu;
    double kD = 0;

    double turn_difference = 0;
    // auto time = 0;
    double prevError = 0;
    double integral = 0;

    // Special conditions (If the angle is at 0 for example)

    bool specialDown = false;
    bool specialUp = false;

    if (lowerAngleBound < 0) {
        lowerAngleBound = lowerAngleBound + 360;
        specialDown = true;
    }
    if (upperAngleBound > 360) {
        upperAngleBound = upperAngleBound - 360;
        specialUp = true;
    }

=======
/*
 * Turns the robot in place until it reaches the goal
 * @param goal - color of goal, 0 is red, 1 is blue, 2 is yellow
 * @param direction - if the goal is to the left or right of the robot
 * @return - double of the averaged motor displacement
 */
//
// void turnToGoal(int color) {
//     pros::vision_object_s_t rtn = Camera.get_by_sig(0, color);
//
//     int actual_turn = 0;
//     int offset = rtn.x_middle_coord - 158;
//     while ((rtn.x_middle_coord > 158+1 || rtn.x_middle_coord < 158-1) && actual_turn < 2) {
//
//       int offset = rtn.x_middle_coord - 158;
//       actual_turn = offset;
//       FrontLeftWheel.move(-actual_turn);
//       MiddleLeftWheel.move(-actual_turn);
//       BackLeftWheel.move(actual_turn);
//       FrontRightWheel.move(-actual_turn);
//       MiddleRightWheel.move(-actual_turn);
//       BackRightWheel.move(actual_turn);
//     }
// }

void turnPID(int angle, double tolerance) {

    double upperAngleBound = angle + tolerance;
    double lowerAngleBound = angle - tolerance;

    long begin_time = pros::millis();

    double angle_ = (Inertial.get_heading());

    //int kU = 5;
    //int tU = 2;
    // double Pu = 0.7;
    double kP = 1.9; // og 0.8
    double kI = 0.00004;        // 1.2*kU/tU;//kU*2 / Pu;
    double kD = 0;

    double turn_difference = 0;
    // auto time = 0;
    double prevError = 0;
    double integral = 0;

    // Special conditions (If the angle is at 0 for example)

    bool specialDown = false;
    bool specialUp = false;

    if (lowerAngleBound < 0) {
        lowerAngleBound = lowerAngleBound + 360;
        specialDown = true;
    }
    if (upperAngleBound > 360) {
        upperAngleBound = upperAngleBound - 360;
        specialUp = true;
    }

=======
    double turn_difference = 0;
    // auto time = 0;
    double prevError = 0;
    double integral = 0;

    // Special conditions (If the angle is at 0 for example)

    bool specialDown = false;
    bool specialUp = false;

    if (lowerAngleBound < 0) {
        lowerAngleBound = lowerAngleBound + 360;
        specialDown = true;
    }
    if (upperAngleBound > 360) {
        upperAngleBound = upperAngleBound - 360;
        specialUp = true;
    }

>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
    // if(lowerAngleBound < 0){
    // 	lowerAngleBound = lowerAngleBound + 360;
    // 	specialDown = true;}
    // if(upperAngleBound > 360){
    // 	upperAngleBound = upperAngleBound - 360;
    // 	specialUp = true;}
<<<<<<< Updated upstream
    float actual_turn = 127;
=======
<<<<<<< HEAD
    float actual_turn = 127;
=======
    struct timeval tp;
    long cycles = 0;
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
    while ((specialDown == true &&
            ((angle_ < lowerAngleBound && angle_ > angle + 180) ||
             (angle_ > upperAngleBound && angle_ < angle + 180))) ||
           (specialUp == true &&
            ((angle_ > upperAngleBound && angle_ < angle - 180) ||
             (angle_ < lowerAngleBound && angle_ > angle - 180))) ||
           ((specialUp == false && specialDown == false) &&
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
>>>>>>> Stashed changes
            (angle_ > upperAngleBound || angle_ < lowerAngleBound))
          || actual_turn > 2 || actual_turn < -2) {
        angle_ = (Inertial.get_heading());

        turn_difference = angle_ - angle;
        actual_turn = 0;
<<<<<<< Updated upstream
=======
=======
            (angle_ > upperAngleBound || angle_ < lowerAngleBound))) {
        angle_ = (Inertial.get_heading());

        turn_difference = angle_ - angle;
        float actual_turn = 0;
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
        if (turn_difference > 180)
            turn_difference = 360 - turn_difference;
        if (turn_difference < -180)
            turn_difference = 360 + turn_difference;
        if (turn_difference < 0 && turn_difference > -180)
            turn_difference = -turn_difference;

        // Spins in the directions which will allow bot to complete turn fastest
        if (turn_difference > 180)
            turn_difference = 360 - turn_difference;

        // Slows down if close to goal heading and stays fast if it is away
        // if(turn_difference < close_turn){
        actual_turn = kP * turn_difference + kI * integral +
                      kD * (turn_difference - prevError);
        // actual_turn =
        // (turn_speed*((turn_difference/(close_turn))+KPBASETURN));

        //}
        // else{
        // 	actual_turn = turn_speed;
        // }

        /*Special conditions if angle bounds are less than 0 or greater than 360
                Neccesary for proper turning and calculation*/
        if ((angle > angle_ + 180) ||
            (angle > angle_ - 180 && angle_ > 180 && angle < 180) ||
            (angle < angle_ && angle_ - angle < 180))
            actual_turn = -actual_turn;

        FrontLeftWheel.move(-actual_turn);
        MiddleLeftWheel.move(-actual_turn);
        BackLeftWheel.move(actual_turn);
        FrontRightWheel.move(-actual_turn);
        MiddleRightWheel.move(-actual_turn);
        BackRightWheel.move(actual_turn);

        pros::lcd::set_text(1, std::to_string(angle_));
        pros::lcd::set_text(2, std::to_string(angle));
        pros::lcd::set_text(3, std::to_string(actual_turn));
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
>>>>>>> Stashed changes
        //pros::lcd::set_text(3, std::to_string(actual_turn));

        pros::delay(5);
        prevError = turn_difference;
        integral += turn_difference;
        // auto time = std::chrono::system_clock::now();
    }
<<<<<<< Updated upstream

    stopHold();

=======

=======

        pros::delay(5);
        prevError = turn_difference;
        integral += turn_difference;
        if (Inertial.get_heading() > lowerAngleBound &&
            Inertial.get_heading() < upperAngleBound)
            cycles++;
        // auto time = std::chrono::system_clock::now();
    }

>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
    stopHold();

>>>>>>> Stashed changes
    pros::lcd::set_text(4, "Goal reached");
}

/*
 * @param x - the untransformed displacement vector
 * @param theta - current IMU reading for the bot IN RADIANS
 * @return - pair of doubles of the transformed displacements x, y
 */

static pair<double, double> Transform(double x, double theta) {
    double x2 = (x * cos(theta));
    double y2 = (x * sin(theta));
    return make_pair(x2, y2);
}

/*
 * updates the encoder values
 * @return - double of the averaged motor displacement
 */

static double Average() {
    double x = (BackRightWheel.get_position() - BR) +
               (BackLeftWheel.get_position() - BL) +
               (MiddleLeftWheel.get_position() - ML) +
               (MiddleRightWheel.get_position() - MR) +
               (FrontLeftWheel.get_position() - FL) +
               (FrontRightWheel.get_position() - FR);

    BR = BackRightWheel.get_position();
    BL = BackLeftWheel.get_position();
    ML = MiddleLeftWheel.get_position();
    MR = MiddleRightWheel.get_position();
    FR = FrontRightWheel.get_position();
    FL = FrontLeftWheel.get_position();
    return x / 6.0;
}

/*
 * Init the autonomous tracking
 * Run at thew beginning of any autonomous routine
 */

static void Setup() {

    FrontRightWheel.tare_position();
    FrontLeftWheel.tare_position();
    MiddleRightWheel.tare_position();
    MiddleLeftWheel.tare_position();
    BackRightWheel.tare_position();
    BackLeftWheel.tare_position();
    x = 0;
    y = 0;
    pros::lcd::set_text(5, "a;lksdjf");
}

void Track() {
    double displacement = Average();
    pair<double, double> disp =
        Transform(displacement, Inertial.get_heading() * M_PI / 180);
    x += disp.first;
    y += disp.second;
    pros::lcd::set_text(6, "X: " + to_string(x));
    pros::lcd::set_text(7, "Y:" + to_string(y));
}

void autonomous() {

    stopHold();
    // chang
    if (auton == -1) {
        move(2400, 360 - 7);
        FrontPiston.set_value(true);
        FrontPiston2.set_value(true);
        move(-2000, 0);
        pros::delay(500);
        turn(235, 3, 80);
        pros::delay(300);
        move(-1200);
        BackPiston.set_value(true);
        pros::delay(300);
        move(600);
        stopHold();
        RingIntake.move_relative(1500, 100);

        // turn(90,3,127);
    }

    // right
    if (auton == 0) {
        FrontPiston.set_value(!false);
        FrontPiston2.set_value(!false);
        move(2400, 4);
        FrontPiston.set_value(!true);
        FrontPiston2.set_value(!true);
        move(-1000, 1);
        turn(90, 3, 127);
        FrontPiston.set_value(!false);
        FrontPiston2.set_value(!false);

        move(-500, 135);
        turn(360 - 46, 3, 127);
        pros::delay(500);
<<<<<<< Updated upstream
        move(1300, 360 - 38);
=======
<<<<<<< HEAD
        move(1300, 360 - 38);
=======
        move(1500, 360 - 38);
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
        FrontPiston.set_value(!true);
        FrontPiston2.set_value(!true);
        move(-2300, 360 - 38);

        turn(180, 3, 100);
    }

    if (auton == 1) {

        FrontPiston.set_value(!false);
        FrontPiston2.set_value(!false);
        move(2700, 18);
        FrontPiston.set_value(!true);
        FrontPiston2.set_value(!true);
        // pros::delay(100);
        move(-900);
        pros::delay(100);
        turn(270, 13, 100);
        pros::delay(500);
        move(-2300, 270);
        pros::delay(100);
        move(300, 270);
        turn(225, 10, 200);
        pros::delay(200);
        move(-400);
        // move(2050,247);
        // BackPiston.set_value(true);
        move(1300, 256);
        move(2300, 180);
    }
    if (auton == 2) {
        // Inertial.tare();
        BackPiston.set_value(true);
        pros::delay(200);
<<<<<<< Updated upstream
        //RingIntake.move_relative(600, 127);
        //'pros::delay(500);
=======
<<<<<<< HEAD
        //RingIntake.move_relative(600, 127);
        //'pros::delay(500);
=======
        RingIntake.move_relative(500, 100);
        pros::delay(500);
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
        BackPiston.set_value(false);
        pros::delay(500);
        pros::delay(1000);
        move(500, 5);
        // turn(90,5,80);
        pros::delay(200);
        turn(90, 5, 100);
        pros::delay(50);
        move(500, 90);
        turn(0, 5, 100);
        pros::delay(200);
        move(-5600, 0);
        BackPiston.set_value(true);
        FrontPiston.set_value(!false);
        FrontPiston2.set_value(!false);
        pros::delay(100);
<<<<<<< Updated upstream
        RingIntake.move_relative(1200, 127);
=======
<<<<<<< HEAD
        RingIntake.move_relative(1200, 127);
=======
        RingIntake.move_relative(1200, 100);
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
        pros::delay(1000);
        move(600, 0);
        pros::delay(100);
        BackPiston.set_value(false);
        move(180, 0);
<<<<<<< Updated upstream
        move(1980, 56);
=======
<<<<<<< HEAD
        move(1980, 56);
=======
        move(1820, 56);
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
        FrontPiston.set_value(!true);
        FrontPiston2.set_value(!true);
        pros::delay(100);
        move(-2200);
    }
    if (auton == 3) {
    }

    // skills
    if (auton == 4) {

        // go  for small neutral left
        TopLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        BackPiston.set_value(true);
        FrontPiston.set_value(!false);
        FrontPiston2.set_value(!false);

        // elevate small neutral left
        pros::delay(300);
        move(500, 90);
        RingIntake.move(127);
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
>>>>>>> Stashed changes
        move(1800, 119);
        FrontPiston.set_value(!true);
        FrontPiston2.set_value(!true);
        TopLift.move_absolute(-4100, 127);
        pros::delay(700);
        move(2800, 113);

        TopLift.move_absolute(-2500, 128);
<<<<<<< Updated upstream
=======
=======
        move(1800, 118);
        FrontPiston.set_value(!true);
        FrontPiston2.set_value(!true);
        TopLift.move_absolute(-4000, 127);
        pros::delay(700);
        move(2800, 116);

        TopLift.move_absolute(-2500, 127);
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
        pros::delay(1000);

        FrontPiston.set_value(!false);
        FrontPiston2.set_value(!false);
        TopLift.move_absolute(-3500, 127);
        pros::delay(300);

        // align for large middge neutral
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
>>>>>>> Stashed changes
        move(-600, 117);

        TopLift.move_absolute(10, 127);
        pros::delay(500);
        turn(236, 3, 127);
        move(50, 237);
        move(1500, 218);
<<<<<<< Updated upstream
=======
=======
        move(-500, 116);

        TopLift.move_absolute(10, 127);
        pros::delay(500);
        turn(225, 3, 127);
        move(1500, 225);
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
        FrontPiston.set_value(!true);
        FrontPiston2.set_value(!true);
        //  TopLift.move_absolute(-1000,127);

<<<<<<< Updated upstream
=======
<<<<<<< HEAD
>>>>>>> Stashed changes
        move(1900, 226);

        pros::delay(100);
        turn(301, 3, 127);
        // elevate large neutral goal
        TopLift.move_absolute(-3500, 128);
<<<<<<< Updated upstream
=======
=======
        move(1900, 225);

        pros::delay(100);
        turn(300, 3, 127);
        // elevate large neutral goal
        TopLift.move_absolute(-3500, 127);
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
        pros::delay(1500);
        move(1150, 300);
        TopLift.move_absolute(-2500, 127);
        pros::delay(800);

        FrontPiston.set_value(!false);
        FrontPiston2.set_value(!false);
        movespeed(-150, 80);
        TopLift.move_absolute(-2500, 60);
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
>>>>>>> Stashed changes
        move(-500, 301);
        // turn(1,3,127);
        TopLift.move_absolute(10, 127);
        // go to right neutral goal
        move(-1400, 91);
        pros::delay(300);
        turn(87, 3, 127);
        pros::delay(300);
        move(500, 83);
        FrontPiston.set_value(!true);
        FrontPiston2.set_value(!true);
        pros::delay(300);
        move(1000, 61);
        pros::delay(300);
        turn(41, 14, 127);
        // elevate right small neutral
        TopLift.move_absolute(-3300, 127);
        pros::delay(1700);
        move(1900, 56);

        TopLift.move_absolute(-2500, 127);
        pros::delay(1000);
        //turn(36, 12, 127);
        //pros::delay(200);
        //turn(52, 3, 127);
<<<<<<< Updated upstream
=======
=======
        move(-500, 300);
        // turn(1,3,127);
        TopLift.move_absolute(10, 127);
        // go to right neutral goal
        move(-1400, 90);
        pros::delay(300);
        turn(87, 3, 127);
        pros::delay(300);
        move(500, 82);
        FrontPiston.set_value(!true);
        FrontPiston2.set_value(!true);
        pros::delay(300);
        move(1000, 60);
        pros::delay(300);
        turn(42, 14, 127);
        // elevate right small neutral
        TopLift.move_absolute(-3300, 127);
        pros::delay(1700);
        move(2150, 52);

        TopLift.move_absolute(-2500, 127);
        pros::delay(1000);
        turn(36, 12, 127);
        pros::delay(200);
        turn(52, 3, 127);
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
        FrontPiston.set_value(!false);
        FrontPiston2.set_value(!false);
        TopLift.move_absolute(-3500, 127);
        // pros::delay(300);

<<<<<<< Updated upstream
=======
<<<<<<< HEAD
>>>>>>> Stashed changes
        move(-400, 117);
        TopLift.move_absolute(10, 127);
        turn(161, 3, 127);
        pros::delay(300);
        move(1600, 161);
        turn(49,3,127);
        move(1600, 38);

        //turn(25, 3, 127);
        //move(1200, 25);
        FrontPiston.set_value(!true);
        FrontPiston2.set_value(!true);
        move(-4600, 88);
        turn(290, 3, 127);
        TopLift.move_absolute(-3500, 127);
        pros::delay(1200);

        move(1500, 296);
        //movespeed(150,60);
        FrontPiston.set_value(!false);
        FrontPiston2.set_value(!false);
        move(-800, 296);
        TopLift.move_absolute(10, 127);
        move(-3800,280);
        //pros::delay(300);
        //turn(185,3,127);
        //pros::delay(300);
        //move(800,180);
        //FrontPiston.set_value(!true);
        //FrontPiston2.set_value(!true);
        //pros::delay(100);
        //TopLift.move_absolute(-300, 127);
        //move(3500,90);
<<<<<<< Updated upstream
=======
=======
        move(-600, 116);
        TopLift.move_absolute(10, 127);
        turn(160, 3, 127);
        pros::delay(300);
        move(100, 180);
        move(1200, 90);

        turn(60, 3, 127);
        move(1400, 60);
        FrontPiston.set_value(!true);
        FrontPiston2.set_value(!true);
        move(-4000, 90);
        turn(315, 3, 127);
        TopLift.move_absolute(-3500, 127);
        pros::delay(1200);

        move(1300, 315);
        FrontPiston.set_value(!false);
        FrontPiston2.set_value(!false);
        move(-800, 315);
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
        BackPiston.set_value(false);

        // pros::delay(300);
        // turn(90,2,127);
        //  pros::delay(500);
        //  turnPID(270,1);
        //  pros::delay(500);
        //  turnPID(180,1);
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
>>>>>>> Stashed changes
    }
    if (auton == 5) {
      turnPID(90, 2);
      pros::delay(500);
      pros::lcd::set_text(1, std::to_string(Inertial.get_heading()));
      turnPID(270, 2);
      pros::delay(500);
      pros::lcd::set_text(1, std::to_string(Inertial.get_heading()));
      turnPID(45, 2);

<<<<<<< Updated upstream
=======
=======
>>>>>>> 31552a69bb3d86b0772a3187ba7a3a36a07a09e6
>>>>>>> Stashed changes
    }

    // test
    else {

        pros::lcd::set_text(1, "running...");
        Setup();
        pros::lcd::set_text(1, "Init over");

        while (true)
            Track();
    }
}

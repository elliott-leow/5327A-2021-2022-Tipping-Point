#include "main.h"
#include "math.h"
#include <chrono>
#include <cstdint>
#include <iostream>


#define close_turn 90
#define auton 5
#define M_PI 3.14159265
using namespace std;
//using namespace pros;

// GLOBAL POSITION VARIABLES
double x = 0;
double y = 0;
// CURRENT MOTOR ENCODER TICKS
double BL, BR, ML, MR, FL, FR;

//-1 == gilbert's left side autonomous
// 0 == elims
// 1 == small and large neutral
// 2 == winpoint auton
// 3 == do nothing
// 4 == prog skills
// 5 = left side neutral rush w/ pos tracking
// 6 == right side neutral rush
// double KPBASETURN = 0.2;
double KPBASETURN = 0.2;
//LV_IMG_DECLARE(gojo);
void initialize() {
//     lv_obj_t * img_src = lv_img_create(lv_scr_act(), NULL); /*Crate an image
//     // object*/ lv_img_set_src(img_src, &gojo);  /*Set the created file as image
//     // (a red fl  ower)*/ lv_obj_set_pos(img_src, 0, 0);      /*Set the
//     // positions*/ lv_obj_set_drag(img_src, true);
    // pros::delay(15000);

    pros::lcd::initialize();
    Inertial.reset();
    pros::delay(3000);
    //pros::lcd::set_text(1, "Init");
    pros::lcd::set_text(3, to_string(auton));

}

/*
 * @param x - the untransformed displacement vector
 * @param theta - current IMU reading for the bot IN RADIANS
 * @return - pair of doubles of the transformed displacements x, y
 */

static pair<double, double> Transform(double x, double theta) {
    double x2 = (x * cos(theta));
    double y2 = (x * sin(theta));
    // std::pair<double, double> coords;
    // coords.first = x2;
    // coords.second = y2;
    return make_pair(x2, y2);
}

/*
 * updates the encoder values
 * @return - double of the averaged motor displacement
 */

static double Average() {
    double x1 = (-(BackRightWheel.get_position() - BR) +
               (BackLeftWheel.get_position() - BL) -
               (MiddleLeftWheel.get_position() - ML) +
               (MiddleRightWheel.get_position() - MR) -
               (FrontLeftWheel.get_position() - FL) +
               (FrontRightWheel.get_position() - FR));


    BR = BackRightWheel.get_position();
    BL = BackLeftWheel.get_position();
    ML = MiddleLeftWheel.get_position();
    MR = MiddleRightWheel.get_position();
    FR = FrontRightWheel.get_position();
    FL = FrontLeftWheel.get_position();
    return x1 / 6.0;
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
    //pros::lcd::set_text(1, "eeeeeee");
    double displacement = Average();
    pair<double, double> disp =
        Transform(displacement, Inertial.get_heading() * M_PI / 180);
    x += disp.first;
    y += disp.second;
    pros::lcd::set_text(6, "X: " + to_string(x) + ", " + to_string(atan(y/x)));
    pros::lcd::set_text(7, "Y:" + to_string(y));
}

void competition_initialize() { initialize(); }

double saveHeading = 0;

void moveVoltage(int i, int angle, int speed) {
    // i = motor speed, angle = angle the robot should turn towards while moving

    FrontRightWheel.tare_position();
    FrontLeftWheel.tare_position();
    BackRightWheel.tare_position();
    BackLeftWheel.tare_position();
    int target = Inertial.get_heading();

    while (std::abs(FrontRightWheel.get_position()) < std::abs(i)) {

        int actual_turn = 0;
        //   int move = i < 0 ? -90 : 90;
        int move = i < 0 ? -127+speed : 127-speed;
        int tolerance = 3;
        int upperAngleBound = angle + tolerance;
        int lowerAngleBound = angle - tolerance;

        int angle_ = (Inertial.get_heading());
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
            int turn_speed = 150;
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
        Track();
        // FrontLeftWheel.move(-move - actual_turn);
        // MiddleLeftWheel.move(-move - actual_turn);
        // BackLeftWheel.move(+move + actual_turn);
        // FrontRightWheel.move(+move - actual_turn);
        // MiddleRightWheel.move(+move - actual_turn);
        // BackRightWheel.move(-move + actual_turn);
        //actual_turn = 0;
        // FrontLeftWheel.move_voltage((12000/127)*(-move - actual_turn));
        // MiddleLeftWheel.move_voltage((12000/127)*(-move - actual_turn));
        // BackLeftWheel.move_voltage((12000/127)*(+move + actual_turn));
        // FrontRightWheel.move_voltage((12000/127)*(+move - actual_turn));
        // MiddleRightWheel.move_voltage((12000/127)*(+move - actual_turn));
        // BackRightWheel.move_voltage((12000/127)*(-move + actual_turn));
        FrontLeftWheel.move_voltage(-12000);
        MiddleLeftWheel.move_voltage(-12000);
        BackLeftWheel.move_voltage(12000);
        FrontRightWheel.move_voltage(12000);
        MiddleRightWheel.move_voltage(12000);
        BackRightWheel.move_voltage(-12000);
        pros::delay(10);
    }

    // Moves the wheels at a certain "move" speed
    FrontRightWheel.move(0);
    FrontLeftWheel.move(0);
    BackRightWheel.move(0);
    BackLeftWheel.move(0);
    MiddleRightWheel.move(0);
    MiddleLeftWheel.move(0);
}


void move(int i, int angle, int speed) {
    // i = motor speed, angle = angle the robot should turn towards while moving

    FrontRightWheel.tare_position();
    FrontLeftWheel.tare_position();
    BackRightWheel.tare_position();
    BackLeftWheel.tare_position();
    int target = Inertial.get_heading();

    while (std::abs(FrontRightWheel.get_position()) < std::abs(i)) {

        int actual_turn = 0;
        //   int move = i < 0 ? -90 : 90;
        int move = i < 0 ? -127+speed : 127-speed;
        int tolerance = 3;
        int upperAngleBound = angle + tolerance;
        int lowerAngleBound = angle - tolerance;

        int angle_ = (Inertial.get_heading());
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
            int turn_speed = 150;
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
        Track();
        // FrontLeftWheel.move(-move - actual_turn);
        // MiddleLeftWheel.move(-move - actual_turn);
        // BackLeftWheel.move(+move + actual_turn);
        // FrontRightWheel.move(+move - actual_turn);
        // MiddleRightWheel.move(+move - actual_turn);
        // BackRightWheel.move(-move + actual_turn);
        FrontLeftWheel.move_voltage((12000/127)*(-move - actual_turn));
        MiddleLeftWheel.move_voltage((12000/127)*(-move - actual_turn));
        BackLeftWheel.move_voltage((12000/127)*(+move + actual_turn));
        FrontRightWheel.move_voltage((12000/127)*(+move - actual_turn));
        MiddleRightWheel.move_voltage((12000/127)*(+move - actual_turn));
        BackRightWheel.move_voltage((12000/127)*(-move + actual_turn));
        pros::delay(10);
    }

    // Moves the wheels at a certain "move" speed
    FrontRightWheel.move(0);
    FrontLeftWheel.move(0);
    BackRightWheel.move(0);
    BackLeftWheel.move(0);
    MiddleRightWheel.move(0);
    MiddleLeftWheel.move(0);
}

void movePID(int i, int angle, int min) {
    // i = motor speed, angle = angle the robot should turn towards while moving

    FrontRightWheel.tare_position();
    FrontLeftWheel.tare_position();
    BackRightWheel.tare_position();
    BackLeftWheel.tare_position();
    int target = Inertial.get_heading();

    while (std::abs(FrontRightWheel.get_position()) < std::abs(i)) {

        int actual_turn = 0;
        //   int move = i < 0 ? -90 : 90;
        int move = i < 0 ? -127 : 127;
        int tolerance = 3;
        int upperAngleBound = angle + tolerance;
        int lowerAngleBound = angle - tolerance;

        int angle_ = (Inertial.get_heading());
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
            int turn_speed = 150;
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
        Track();
        if (std::abs(FrontRightWheel.get_position()) - std::abs(i) < min) {
          move = 50*(std::abs(FrontRightWheel.get_position()) - std::abs(i));
        }
        FrontLeftWheel.move(-move - actual_turn);
        MiddleLeftWheel.move(-move - actual_turn);
        BackLeftWheel.move(+move + actual_turn);
        FrontRightWheel.move(+move - actual_turn);
        MiddleRightWheel.move(+move - actual_turn);
        BackRightWheel.move(-move + actual_turn);
        pros::delay(10);
    }

    // Moves the wheels at a certain "move" speed
    FrontRightWheel.move(0);
    FrontLeftWheel.move(0);
    BackRightWheel.move(0);
    BackLeftWheel.move(0);
    MiddleRightWheel.move(0);
    MiddleLeftWheel.move(0);
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
        //   int move = i < 0 ? -90 : 90;
        int move = i < 0 ? -127 : 127;
        int tolerance = 3;
        int upperAngleBound = angle + tolerance;
        int lowerAngleBound = angle - tolerance;

        int angle_ = (Inertial.get_heading());
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
            int turn_speed = 150;
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
        Track();
        // FrontLeftWheel.move(-move - actual_turn);
        // MiddleLeftWheel.move(-move - actual_turn);
        // BackLeftWheel.move(+move + actual_turn);
        // FrontRightWheel.move(+move - actual_turn);
        // MiddleRightWheel.move(+move - actual_turn);
        // BackRightWheel.move(-move + actual_turn);
        FrontLeftWheel.move_voltage((12000/127)*(-move - actual_turn));
        MiddleLeftWheel.move_voltage((12000/127)*(-move - actual_turn));
        BackLeftWheel.move_voltage((12000/127)*(+move + actual_turn));
        FrontRightWheel.move_voltage((12000/127)*(+move - actual_turn));
        MiddleRightWheel.move_voltage((12000/127)*(+move - actual_turn));
        BackRightWheel.move_voltage((12000/127)*(-move + actual_turn));
        pros::delay(10);
    }

    // Moves the wheels at a certain "move" speed
    FrontRightWheel.move(0);
    FrontLeftWheel.move(0);
    BackRightWheel.move(0);
    BackLeftWheel.move(0);
    MiddleRightWheel.move(0);
    MiddleLeftWheel.move(0);
    FrontLeftWheel.move_voltage(0);
    MiddleLeftWheel.move_voltage(0);
    BackLeftWheel.move_voltage(0);
    FrontRightWheel.move_voltage(0);
    MiddleRightWheel.move_voltage(0);
    BackRightWheel.move_voltage(0);
}

void stopHold() {

    FrontLeftWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    FrontRightWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    MiddleLeftWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    MiddleRightWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    BackRightWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackLeftWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    FrontLeftWheel.move(0);
    FrontRightWheel.move(0);

    MiddleRightWheel.move(0);
    MiddleLeftWheel.move(0);

    BackRightWheel.move(0);
    BackLeftWheel.move(0);
}

void turn(int angle, int tolerance, int turn_speed, int PIDRATIO) {

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
                (turn_speed * ((turn_difference / (close_turn)) ))*1.6* PIDRATIO + KPBASETURN;
        } else {
            actual_turn = turn_speed;
        }

        /*Special conditions if angle bounds are less than 0 or greater than 360
                Neccesary for proper turning and calculation*/
        if ((angle > angle_ + 180) ||
            (angle > angle_ - 180 && angle_ > 180 && angle < 180) ||
            (angle < angle_ && angle_ - angle < 180))
            actual_turn = -actual_turn;

            Track();
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
                (turn_speed * ((turn_difference / (close_turn)) ))*1.6 + KPBASETURN;
        } else {
            actual_turn = turn_speed;
        }

        /*Special conditions if angle bounds are less than 0 or greater than 360
                Neccesary for proper turning and calculation*/
        if ((angle > angle_ + 180) ||
            (angle > angle_ - 180 && angle_ > 180 && angle < 180) ||
            (angle < angle_ && angle_ - angle < 180))
            actual_turn = -actual_turn;

            Track();
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

/*
 * Turns the robot in place until it reaches the goal
 * @param goal - color of goal, 0 is red, 1 is blue, 2 is yellow
 * @param direction - if the goal is to the left or right of the robot
 * @return - double of the averaged motor displacement
 */
//

int completeGoal(int color) {
    pros::lcd::set_text(1, "complete goal");
    pros::vision_object_s_t rtn = Camera.get_by_sig(0, 2);
    //pros::lcd::set_text(2, "");
    int actual_turn = 0;
    int width = 316;
    int height = 212;
    int center = width/2;
    int object = rtn.x_middle_coord;
    pros::lcd::set_text(2, to_string(center - object));
    return object - center;

}
void turnToGoal(int color, int tolerance, int speed, int kP) {
    int error = completeGoal(color);
    while (true) {
        if (abs(error) < 3) break;
        error = completeGoal(color) * kP;
        int actual_turn = error;
        Track();
        FrontLeftWheel.move(-actual_turn);
        MiddleLeftWheel.move(-actual_turn);
        BackLeftWheel.move(actual_turn);
        FrontRightWheel.move(-actual_turn);
        MiddleRightWheel.move(-actual_turn);
        BackRightWheel.move(actual_turn);
    }
}



void turnPID(int angle, double tolerance) {

    double upperAngleBound = angle + tolerance;
    double lowerAngleBound = angle - tolerance;

    long begin_time = pros::millis();

    double angle_ = (Inertial.get_heading());

    //int kU = 5;
    //int tU = 2;
    // double Pu = 0.7;
    double kP = 3; // og 0.8
    double kI = 0.00002;        // 1.2*kU/tU;//kU*2 / Pu;
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

    // if(lowerAngleBound < 0){
    // 	lowerAngleBound = lowerAngleBound + 360;
    // 	specialDown = true;}
    // if(upperAngleBound > 360){
    // 	upperAngleBound = upperAngleBound - 360;
    // 	specialUp = true;}
    float actual_turn = 127;
    while ((specialDown == true &&
            ((angle_ < lowerAngleBound && angle_ > angle + 180) ||
             (angle_ > upperAngleBound && angle_ < angle + 180))) ||
           (specialUp == true &&
            ((angle_ > upperAngleBound && angle_ < angle - 180) ||
             (angle_ < lowerAngleBound && angle_ > angle - 180))) ||
           ((specialUp == false && specialDown == false) &&
            (angle_ > upperAngleBound || angle_ < lowerAngleBound))
          || actual_turn > 2 || actual_turn < -2) {
        angle_ = (Inertial.get_heading());

        turn_difference = angle_ - angle;
        actual_turn = 0;
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
        //pros::lcd::set_text(3, std::to_string(actual_turn));

        pros::delay(5);
        prevError = turn_difference;
        integral += turn_difference;
        // auto time = std::chrono::system_clock::now();
        Track();
    }

    stopHold();

    pros::lcd::set_text(4, "Goal reached");
}

void rDelay(int ms) {
  std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while(true)
    {
        Track();
        if(std::chrono::steady_clock::now() - start > std::chrono::milliseconds(ms))
            break;
    }
}

void moveCoords(int x1, int y1, int fowardSpeed, bool backwards) {
    int angle = 0;
    if (x1-x == 0) angle = 0;
    else angle = atan((y1-y)/(x1-x)) * 180/ M_PI;
    //1,10
    //

    //if (!simul) turnPID(angle, 3);
    int moveTolerance = 100;
    int dx = x1 - x;
    int dy = y1 - y;
    while (true) {
        if (abs(dx) < moveTolerance && abs(dy) < moveTolerance) break;
      dx = x1 - x;
      dy = y1 - y;
      double distance = sqrt(dx*dx + dy*dy);
      //if (abs(x-x1) < moveTolerance || abs(y-y1) < moveTolerance) break;
      float angle_ = Inertial.get_heading();
      if (x-x1 == 0) angle = 90;
      angle = atan((y1-y)/(x1-x)) * 180/ M_PI;
      //if (backwards) angle = 360 - angle + 180;

      angle +=360;
      angle %=360;
         if (dx < 0 &&  dy > 0) angle = 360-angle; //if 2nd quadrant
         if (dx < 0 && dy < 0)  angle = 360 - angle; // if 3rd quadrant
      //angle += 360;
      //if (backwards) angle += 180; // detect if robot moves backwards
      angle +=360;
      angle %=360;
      pros::lcd::set_text(1, "Target: " + to_string(angle));
      pros::lcd::set_text(2, "Current: " + to_string(angle_));

      //int turnDifference = angle_ - angle;

      int actualTurn = 0;
        bool specialDown = false;
        bool specialUp = false;
        int angleTolerance = 1;
        double upperAngleBound = angle + angleTolerance;
        double lowerAngleBound = angle - angleTolerance;
        if (lowerAngleBound < 0) {
            lowerAngleBound = lowerAngleBound + 360;
            specialDown = true;
        }
        if (upperAngleBound > 360) {
            upperAngleBound = upperAngleBound - 360;
            specialUp = true;
        }
        if ((specialDown == true &&
                ((angle_ < lowerAngleBound && angle_ > angle + 180) ||
                 (angle_ > upperAngleBound && angle_ < angle + 180))) ||
               (specialUp == true &&
                ((angle_ > upperAngleBound && angle_ < angle - 180) ||
                 (angle_ < lowerAngleBound && angle_ > angle - 180))) ||
               ((specialUp == false && specialDown == false) &&
                (angle_ > upperAngleBound || angle_ < lowerAngleBound))) {
                  int turn_difference = angle_ - angle;
                  //actual_turn = 0;
                  if (turn_difference > 180)
                      turn_difference = 360 - turn_difference;
                  if (turn_difference < -180)
                      turn_difference = 360 + turn_difference;
                  if (turn_difference < 0 && turn_difference > -180)
                      turn_difference = -turn_difference;

                  // Spins in the directions which will allow bot to complete turn fastest
                  if (turn_difference > 180)
                      turn_difference = 360 - turn_difference;

                      if (turn_difference > 180)
                          turn_difference = 360 - turn_difference;
                      int turn_speed = 90;
                      // Slows down if close to goal heading and stays fast if it is away
                      if (turn_difference < close_turn) {

                          actualTurn =
                              (turn_speed * ((turn_difference / (close_turn))*2.5 + KPBASETURN));
                      } else {
                          actualTurn = turn_speed;
                      }


              }



      //int angleDifference = (Inertial.get_heading() - angle) * 0.2;


      int move = backwards ? -fowardSpeed : fowardSpeed;
    //   if (PID && distance < 500) {
    //       move = (distance/500)*2+10;
    //   }

      // int closeTarget = 300;
      // if ((abs(x - x1) < closeTarget || abs(y-y1) < closeTarget) && fowardPID == true) {
      //   int closer = abs(x - x1) < abs(y-y1) ? abs(x - x1) : abs(y-y1);
      //   move = fowardSpeed * (closer / closeTarget);
      // }
      int difference = backwards ? 2*actualTurn : 2*actualTurn;

      Track();
      FrontLeftWheel.move(-move-difference);
      MiddleLeftWheel.move(-move-difference);
      BackLeftWheel.move(move+difference);
      FrontRightWheel.move(move-difference);
      MiddleRightWheel.move(move-difference);
      BackRightWheel.move(-move+difference);

     }
     stopHold();
}

void movespeed(int i, int a, int speed, bool e) {
    // i = motor speed
    int target = a;
    // FrontRightWheel.tare_position();
    // FrontLeftWheel.tare_position();
    // BackRightWheel.tare_position();
    // BackLeftWheel.tare_position();
    int initialPos = FrontRightWheel.get_position();

    if (i > 0) {
        while (FrontRightWheel.get_position()-initialPos < i) {
            int difference = (target - Inertial.get_heading()) *0.5;
            //int difference = 0;
            FrontLeftWheel.move(-127 - difference + speed);
            MiddleLeftWheel.move(-127 - difference + speed);
            BackLeftWheel.move(+127 + difference - speed);
            FrontRightWheel.move(+127 - difference - speed);
            MiddleRightWheel.move(+127 - difference - speed);
            BackRightWheel.move(-127 + difference + speed);
            Track();
            pros::lcd::set_text(4, std::to_string(difference));
        }
    }
    if (i < 0) {
        while (FrontRightWheel.get_position()-initialPos > i) {
            int difference = (target - Inertial.get_heading()) * 0.5;
            //int difference = 0;
            FrontLeftWheel.move(+127 + difference - speed);
            MiddleLeftWheel.move(+127 + difference - speed);
            BackLeftWheel.move(-127 - difference + speed);

            FrontRightWheel.move(-127 + difference + speed);
            MiddleRightWheel.move(-127 + difference + speed);
            BackRightWheel.move(+127 - difference - speed);
            Track();
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

void movespeed(int i, int angle, int speed) {
    // i = motor speed
    int target = angle;
    // FrontRightWheel.tare_position();
    // FrontLeftWheel.tare_position();
    // BackRightWheel.tare_position();
    // BackLeftWheel.tare_position();
    int initialPos = FrontRightWheel.get_position();

    if (i > 0) {
        while (FrontRightWheel.get_position()-initialPos < i) {
            //int difference = -(target - Inertial.get_heading()) *1.5;
            int difference = 0;
            FrontLeftWheel.move(-127 - difference + speed);
            MiddleLeftWheel.move(-127 - difference + speed);
            BackLeftWheel.move(+127 + difference - speed);
            FrontRightWheel.move(+127 - difference - speed);
            MiddleRightWheel.move(+127 - difference - speed);
            BackRightWheel.move(-127 + difference + speed);
            Track();
            pros::lcd::set_text(4, std::to_string(difference));
        }
    }
    if (i < 0) {
        while (FrontRightWheel.get_position()-initialPos > i) {
            //int difference = -(target - Inertial.get_heading()) * 1.5;
            int difference = 0;
            FrontLeftWheel.move(+127 + difference - speed);
            MiddleLeftWheel.move(+127 + difference - speed);
            BackLeftWheel.move(-127 - difference + speed);

            FrontRightWheel.move(-127 + difference + speed);
            MiddleRightWheel.move(-127 + difference + speed);
            BackRightWheel.move(+127 - difference - speed);
            Track();
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
bool toClamp = false;
bool val = false;

void backClamp(bool v) {
  val = v;
  toClamp = true;
}

void clamp(void * param) {

  while (true) {
    if (val && toClamp) {
      Tilter.set_value(val);

      pros::delay(400);
      BackPiston.set_value(val);
      toClamp = false;
    }
    else if (toClamp){



      BackPiston.set_value(val);
      pros::delay(200);
      Tilter.set_value(val);
      toClamp = false;

    }
    pros::delay(5);
  }
}

void autonomous() {

  pros::task_t  task = pros::c::task_create(clamp, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Task Name");
  pros::Task bClamp(task);

    TopLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    stopHold();
    // chang
    if (auton == -1) {
        move(2400, 360 - 7);
        FrontPiston.set_value(true);
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
        move(2400, 4);
        FrontPiston.set_value(!true);
        move(-1000, 1);
        turn(90, 3, 127);
        FrontPiston.set_value(!false);


        move(-500, 135);
        turn(360 - 46, 3, 127);
        pros::delay(500);
        move(1300, 360 - 38);
        FrontPiston.set_value(!true);

        move(-2300, 360 - 38);

        turn(180, 3, 100);
    }


    //left side -> small neutal -> alliance goal -> score rings
    if (auton == 1) {

        FrontPiston.set_value(!false);

        backClamp(true);
        move(2000,9);
        FrontPiston.set_value(!true);
        move(100,9);
        pros::delay(50);
        move(-2100,9);
        pros::delay(500);
        turn(312,3,100,2);
        movespeed(-500,313,60);

        backClamp(false);
        pros::delay(500);
        move(950,313);
        //movespeed(1200, 313,60);
        pros::delay(500);
        TopLift.move_absolute(-2000, 127);
        turn(45,3,100,2);
        RingIntake.move_voltage(-12000);
        move(1200,35,50);
        turn(90,3,100,2);

        move(250,80,70);
        move(250,100,70);
        move(250,80,70);
        move(250,100,70);
        move(250,80,70);
        move(250,100,70);
        move(250,80,70);
        move(250,100,70);
        move(250,80,70);
        move(250,100,70);
        move(250,80,70);
        move(250,100,70);
        move(250,80,70);
        move(250,100,70);
        backClamp(true);

    }
    if (auton == 2) {
        // Inertial.tare();
        //BackPiston.set_value(true);
        backClamp(true);
        pros::delay(500);
        move(-300,1,70);
        backClamp(false);
        pros::delay(1000);
        RingIntake.move_relative(-600, 127);
        pros::delay(700);
        backClamp(true);
        pros::delay(500);
        pros::delay(1000);
        move(500, 5);
        // turn(90,5,80);
        pros::delay(200);
        turn(90, 5, 100);
        pros::delay(50);
        move(600, 90);
        turn(0, 5, 100);
        pros::delay(200);
        move(-5600, 0);
        backClamp(false);
        FrontPiston.set_value(!false);

        pros::delay(700);
        RingIntake.move_relative(-3000, 127);
        pros::delay(1000);
        move(600, 0);
        pros::delay(100);
        backClamp(true);
        move(190, 0);
        move(2180, 51);
        FrontPiston.set_value(!true);

        pros::delay(100);
        move(-2700,56);
    }
    //right side -> small neutal -> alliance neutal -> rings
    if (auton == 3) {
      FrontPiston.set_value(!false);
      backClamp(true);
      //Setup();
      stopHold();
      //moveCoords(2300, 460, 127, false);
      //move(2100,1);
      moveVoltage(1900,1,0);
      FrontPiston.set_value(!true);
      move(100,1);
      move(-1200, 3);
      turn(260, 3, 127,2);
      move(-1050, 270,60);
      pros::delay(500);
      backClamp(false);
      pros::delay(500);
      RingIntake.move(-127);
      TopLift.move_absolute(-2000, 127);
      move(50,270);

      turn(1,3,127,2);
      move(2150,1,85);
      pros::delay(300);
      move(-2500,1,10);
      backClamp(true);
      //moveCoords(1000, 300, true, 90);
      stopHold();
    }

    // skills
    if (auton == 4) {

        // // go  for small neutral left
        // TopLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        // BackPiston.set_value(true);
        // FrontPiston.set_value(true);

        backClamp(true);
        FrontPiston.set_value(!false);
        pros::delay(500);
        move(-350,1,70);
        backClamp(false);
        pros::delay(1000);
        RingIntake.move_relative(-1400, 127);
        pros::delay(700);
        move(200,0);
        // elevate small neutral left
        pros::delay(300);
        move(500, 90);
        RingIntake.move(127);
        move(1800, 114);
        FrontPiston.set_value(false);
        TopLift.move_absolute(-3200,127);
        pros::delay(1300);
        move(2740, 123);



//drops small neutral
        TopLift.move_absolute(-2900, 127);
        pros::delay(700);
        FrontPiston.set_value(true);
        pros::delay(200);
        TopLift.move_absolute(-2900, 127);
        pros::delay(300);


        movespeed(-890, 117,90);
        TopLift.move_absolute(10,127);
        backClamp(true);
        pros::delay(800);
        movespeed(200,120,90);
        turn(315,3,60,3);
        pros::delay(300);
        move(900,310);

        //clamps the alliance mogo
        FrontPiston.set_value(false);
        pros::delay(100);
        TopLift.move_absolute(-3000,127);
        turn(110,3,127);
        pros::delay(600);
        move(1650,115);

        pros::delay(500);
        //TopLift.move_absolute(-2600,127);
        FrontPiston.set_value(true);
        pros::delay(500);
        TopLift.move_absolute(10,127);

        move(-950,115,10);
        TopLift.move_absolute(10,127);
        pros::delay(600);
        turn(218,3,127);

        move(1700,223);

        //clamps tall neutral mogo
        FrontPiston.set_value(false);
        move(-3800,225);
        move(-400,180);
        turn(180, 3,127,3);
        TopLift.move_absolute(-2200,127);
        pros::delay(1400);
        //pushing other mogos on platform
        move(1250,174, 70);
        pros::delay(700);

        FrontPiston.set_value(true);
        move(50, 174, 60);
        pros::delay(2000);
        TopLift.move_relative(250,127);
        //release tall  mogo
        pros::delay(300);
        move(-530, 174, 60);
        TopLift.move_absolute(10,127);
        pros::delay(1000);
        turn(295, 3,127);
        move(1000, 295);
        FrontPiston.set_value(false);
        move(-400,295);
        TopLift.move_absolute(-10,127);
        pros::delay(200);
        turn(225,3,127,3);

        move(5350,225);

        //elevate opposite alliance
        turn(292,3,127,3);
        TopLift.move_absolute(-2600,127);
        pros::delay(1000);


        move(1430,300);

        //TopLift.move_absolute(10,127);
        FrontPiston.set_value(true);

        //elevate right neutral
        pros::delay(500);
        move(-800,295); //prev 1500
        TopLift.move_absolute(10,127);
        pros::delay(1000);
        turn(125,3,121);
        move(1500, 119);
        FrontPiston.set_value(false);

        turn(295,3,127,3);
        TopLift.move_absolute(-2700,127);
        pros::delay(1000);


        move(2900,295);
        FrontPiston.set_value(true);
        move(-250,295,70);
        pros::delay(800);
        TopLift.move_absolute(10,127);

        // 2nd home alliance alignment
        turn(180,3,127);
        pros::delay(100);
        move(1850,182);
        FrontPiston.set_value(false);
        move(100,182);
        pros::delay(400);
        move(-900,180);

        pros::delay(100);
        turn(90,3,127,3);
        pros::delay(100);
        move(2700,90);
        pros::delay(100);
        turn(60,3,127,4);
        //pros::delay(300);
        TopLift.move_absolute(-2700,127);
        pros::delay(750);
        move(1150,70,60);

        //drop home alliance mogo
        FrontPiston.set_value(true);
        move(-450,60,80);
        TopLift.move_absolute(10,127);
        pros::delay(100);
        turn(0,3,127,2);
        move(-1250,0,60);


        turn(45,3,127);
        move(1000,45,80);
        FrontPiston.set_value(false);
        move(-3000,90);
        turn(302,3,127,2);
        TopLift.move_absolute(-2300,127);
        pros::delay(2000);
        move(2500,315);
        FrontPiston.set_value(true);
        move(-2000,302);






        //movespeed(-200,120,90);

        //moveCoords(800,-8000,127,false);

        pros::delay(30000);

        //END OF SKILLS

        // align for large middge neutral
        move(-600, 117);

        TopLift.move_absolute(10, 127);
        pros::delay(500);
        turn(236, 3, 127);
        move(50, 237);
        move(1500, 218);
        FrontPiston.set_value(!true);

        //  TopLift.move_absolute(-1000,127);

        move(1900, 226);

        pros::delay(100);
        turn(301, 3, 127);
        // elevate large neutral goal
        TopLift.move_absolute(-3500, 128);
        pros::delay(1500);
        move(1150, 300);
        TopLift.move_absolute(-2500, 127);
        pros::delay(800);

        FrontPiston.set_value(!false);

        move(-150);
        TopLift.move_absolute(-2500, 60);
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
        FrontPiston.set_value(!false);



        TopLift.move_absolute(-3500, 127);
        // pros::delay(300);

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

        move(-4600, 88);
        turn(290, 3, 127);
        TopLift.move_absolute(-3500, 127);
        pros::delay(1200);

        move(1500, 296);
        //movespeed(150,60);
        FrontPiston.set_value(!false);

        move(-800, 296);
        TopLift.move_absolute(10, 127);
        move(-3800,280);
        //pros::delay(300);
        //turn(185,3,127);
        //pros::delay(300);
        //move(800,180);
        //FrontPiston.set_value(!true);
        //
        //pros::delay(100);
        //TopLift.move_absolute(-300, 127);
        //move(3500,90);
        BackPiston.set_value(false);

        // pros::delay(300);
        // turn(90,2,127);
        //  pros::delay(500);
        //  turnPID(270,1);
        //  pros::delay(500);
        //  turnPID(180,1);
    }

    //rightneutral juke -> middle neutal -> alliance goal -> rings
    if (auton == 5) {
      FrontPiston.set_value(!false);
      backClamp(true);
      Setup();
      stopHold();
      move(350,1);
      move(2850,315);
      FrontPiston.set_value(!true);
      move(-1970,315);
      turn(270,3,100,2);


      move(-950, 270,60);
      pros::delay(500);
      backClamp(false);
      pros::delay(500);
      RingIntake.move(-127);
      TopLift.move_absolute(-2000, 127);
      move(130,270);

      turn(1,3,127,2);
      move(2150,1,85);
      pros::delay(300);
      move(-2400,1,10);
      backClamp(true);
      //moveCoords(1000, 300, true, 90);
      stopHold();

      //moveCoords(2300, 460, 127, false);
      // move(2600,10);
      // FrontPiston.set_value(!true);
      // move(-1300, 10);
      // FrontPiston.set_value(!false);
      // rDelay(500);
      // move(-800,10);
      // turn(295, 3, 127);
      // move(-550, 285);
      // pros::delay(500);
      // BackPiston.set_value(true);
      // pros::delay(500);
      // RingIntake.move(127);
      // //moveCoords(1000, 300, true, 90);
      // stopHold();
    }
    //right neutral rush -> large neutral -> alliance -> rings

    if (auton == 6) {
      int offset = 45-13;
      FrontPiston.set_value(!false);
      backClamp(true);
        move(1000,1);
        move(1700,360-4);
        FrontPiston.set_value(!true);
        move(200,360-4);
        move(-1500,360-6); // old 1700

        turn(270+offset,3,100,2);


        move(-1600, 270+offset,60);
        pros::delay(500);
        backClamp(false);
        pros::delay(500);
        RingIntake.move(-127);
        TopLift.move_absolute(-2000, 127);
        move(155,270+offset);

        turn(1+offset,3,127,2);
        move(2150,1+offset,70);

        pros::delay(300);

        move(-2400,1+offset,10);
        backClamp(true);
        //moveCoords(1000, 300, true, 90);
        stopHold();



        // Setup();
        // stopHold();
        // FrontPiston.set_value(!false);
        // moveCoords(2350, 0, 127, false);
        // FrontPiston.set_value(!true);
        //
        // move(-1200, 0);
        // TopLift.move_absolute(-100, 127);
        //
        // //FrontPiston.set_value(!false);
        // move(-200,0);
        // turn(270,3,100,3);
        // pros::delay(500);
        // move(-1200, 270);
        // //moveCoords(300,700, 100, false);
        // BackPiston.set_value(true);
        // pros::delay(400);
        // move (200, 245);
        //
        // turn(357, 3, 127, 3);
        // TopLift.move_absolute(-1000, 127);
        // RingIntake.move(127);
        // pros::delay(500);
        // movespeed(2500, 0, 90);
        // pros::delay(500);
        // movespeed(-3000,0, 40);
        // //movespeed(+800, 90);
        // //movespeed(-800, 90);
        // // moveCoords(x+300, y, 60, true);
        // // moveCoords(x-900, y, 60, true);
        // // moveCoords(x+900, y, 60, true);

    }
    //left juke
    if (auton == 7) {
      FrontPiston.set_value(!false);
      backClamp(true);
      move(1400,0);
      turn(90,3,127);
      move(2500,90,30);
      pros::delay(500);
      move(-530,90);
      turn(45,3,127);
      move(800,45,50);
      FrontPiston.set_value(!true);
      move(-2700,45);
      turn(310,3,127,3);
      move(-700,310,60);
      backClamp(false);

      //turn

      //TopLift.move_absolute(-2400, 127);


    }

    // test
    else {

        pros::lcd::set_text(3, "running...");
        Setup();
        pros::lcd::set_text(4, "Init over");

        while (true) Track();
    }
}

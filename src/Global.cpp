#include "main.h"

pros::Motor FrontRightWheel(11, pros::E_MOTOR_GEARSET_06 , false,pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FrontLeftWheel(12, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BackRightWheel(13, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BackLeftWheel(1, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor Lift(15, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor RingIntake(10, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

pros::Controller CONTROLLER(pros::E_CONTROLLER_MASTER);

pros::Imu Inertial(20);

#include "main.h"

pros::Motor FrontRightWheel(8, pros::E_MOTOR_GEARSET_06 , true,pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FrontLeftWheel(5, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor MiddleRightWheel(7, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS); //
pros::Motor MiddleLeftWheel(4, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BackRightWheel(6, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BackLeftWheel(3, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor RingIntake(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor TopLift(9, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::ADIDigitalOut FrontPiston(2);
pros::ADIDigitalOut FrontPiston2(4);
pros::ADIDigitalOut BackPiston(3);

pros::Controller CONTROLLER(pros::E_CONTROLLER_MASTER);

pros::Imu Inertial(15);

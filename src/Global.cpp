#include "main.h"

//gilbert's ports
// pros::Motor FrontRightWheel(18, pros::E_MOTOR_GEARSET_06 , false,pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor FrontLeftWheel(11, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor MiddleRightWheel(19, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS); //
// pros::Motor MiddleLeftWheel(12, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor BackRightWheel(20, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor BackLeftWheel(13, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
//
// pros::Motor RingIntake(6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor TopLift(5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
//
// pros::ADIDigitalOut FrontPiston(1);
// pros::ADIDigitalOut BackPiston(2);
//
// pros::Controller CONTROLLER(pros::E_CONTROLLER_MASTER);
//
// pros::Imu Inertial(16);


//urmil
// pros::Motor FrontRightWheel(8, pros::E_MOTOR_GEARSET_06 , true,pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor FrontLeftWheel(5, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor MiddleRightWheel(7, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS); //
// pros::Motor MiddleLeftWheel(16, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor BackRightWheel(6, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor BackLeftWheel(3, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
//
// pros::Motor RingIntake(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor TopLift(9, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
//
// pros::ADIDigitalOut FrontPiston(2);
// pros::ADIDigitalOut FrontPiston2(4);
// pros::ADIDigitalOut BackPiston(3);
//
// pros::Vision Camera(21);
//
// pros::Controller CONTROLLER(pros::E_CONTROLLER_MASTER);
//
// pros::Imu Inertial(15);
pros::Motor FrontRightWheel(8, pros::E_MOTOR_GEARSET_06 , false,pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FrontLeftWheel(18, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor MiddleRightWheel(6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS); //
pros::Motor MiddleLeftWheel(17, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BackRightWheel(7, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BackLeftWheel(15, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor RingIntake(5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor TopLift(9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

//pros::ADIDigitalOut FrontPiston(1);s
pros::ADIDigitalOut FrontPiston(4);
pros::ADIDigitalOut BackPiston(2);

pros::Vision Camera(21);

pros::Controller CONTROLLER(pros::E_CONTROLLER_MASTER);

pros::Controller CONTROLLER2(pros::E_CONTROLLER_PARTNER);

pros::Imu Inertial(16);

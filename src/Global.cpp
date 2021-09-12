#include "main.h"

pros::Motor FRONTRIGHTWHEEL(11, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FRONTLEFTWHEEL(10, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BACKRIGHTWHEEL(12, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BACKLEFTWHEEL(1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor CLAWMOTOR(1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

pros::Controller CONTROLLER(pros::E_CONTROLLER_MASTER);

pros::Imu INERTIAL(13);
pros::ADIEncoder  RIGHTENCODER(1,2,true);
pros::ADIEncoder  MIDDLEENCODER(3,4,false);
pros::ADIEncoder  LEFTENCODER(5,6,false);

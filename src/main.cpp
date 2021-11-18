#include "main.h"
#include "math.h"
//#include "pros/apix.h"

void opcontrol() {

    //LIFT.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    int liftLimit = -1250;
    Lift.tare_position();

    //pros::lcd::initialize();


    while (true) {
        //float initialclaw = CLAWMOTOR.get_position();
        pros::lcd::set_text(1, "Front left: " + std::to_string(FrontLeftWheel.get_position()));
        pros::lcd::set_text(2, "Back left: " + std::to_string(BackLeftWheel.get_position()));
        pros::lcd::set_text(3, "Front right: " + std::to_string(FrontRightWheel.get_position()));
        pros::lcd::set_text(4, "Back right: " + std::to_string(BackRightWheel.get_position()));
        double TURN = CONTROLLER.get_analog(ANALOG_LEFT_X);
        double STRAIGHT = CONTROLLER.get_analog(ANALOG_RIGHT_Y);
        double leftWheels = CONTROLLER.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

        bool ringIntakeUp = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
        bool ringIntakeDown = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
        bool liftUp = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
        bool liftDown = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);


        if (liftUp && Lift.get_position() <= 0) {
            Lift.move(127);
        }
        else if (liftDown && Lift.get_position() >= liftLimit) {
            Lift.move(-127);
        } else if (!liftUp || !liftDown) {
            Lift.move(0);
        }
        if (ringIntakeUp) {
            //LIFT.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            RingIntake.move(127);
        }
        else if (ringIntakeDown) {
            //LIFT.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            RingIntake.move(-127);
        } else if (!ringIntakeUp || !ringIntakeDown){
            RingIntake.move(0);
        }
        FrontLeftWheel.move(STRAIGHT + TURN);
        BackLeftWheel.move(STRAIGHT + TURN);
        FrontRightWheel.move(STRAIGHT - TURN);
        BackRightWheel.move(STRAIGHT - TURN);
        // } else {
        //     LIFT.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        // }


        //
        // //Getting current angle
        // float angle = INERTIAL.get_heading();
        // if(angle < 0) angle = 360 + angle;
        //
        // //Calculating left joystick angle
        // float joystick_angle = atan(left_right/up_down) * 180 / M_PI;
        // if(up_down < 0) joystick_angle = 180 + joystick_angle;
        // if(joystick_angle < 0) joystick_angle = 360 + joystick_angle;
        //
        // //Calcualating difference in angles
        // float difference = angle - joystick_angle;
        // if(difference < 0) difference = 360 + difference;
        // difference = 360 - difference;
        //
        // //Magnitude calculations
        // float magnitude = sqrt(pow(up_down, 2.0) + pow(left_right, 2.0));
        // if(magnitude > 127) magnitude = 127;
        //
        // //Calculating right joystick angle
        // float turn_angle = atan(turnX/turnY) * 180 / M_PI;
        // if(turnY < 0) turn_angle = 180 + turn_angle;
        // if(turn_angle < 0) turn_angle = 360 + turn_angle;
        //
        // //Calculating turn difference in angles
        // float turn_difference = turn_angle - angle;
        // if(turn_difference < 0) turn_difference = 360 + turn_difference;
        // turn_difference = 360 - turn_difference;
        //
        // //Turn magnitude calculations
        // float turn_magnitude = (sqrt(pow(turnY, 2.0) + pow(turnX, 2.0)))*((turn_difference/360)+0.5);
        // if(turn_magnitude > 127) turn_magnitude = 127;
        //
        // //Calculating actual turn value based on joystick position
        // if(turn_difference < 180){
        //     turn_magnitude = -turn_magnitude;}
        // if(turn_difference > 180) turn_difference = 360 - turn_difference;
        // float proportion = sqrt(turn_difference/60);
        // turn_magnitude = turn_magnitude*proportion;
        // if(isinf(turn_magnitude)) turn_magnitude = 0;
        // if(turn_difference < 1 || turn_difference > 359) turn_magnitude = 0;
        //
        // //Actual calculated values for motors
        // int actual_up_down = cos(difference * M_PI / 180.0) * magnitude;
        // int actual_left_right = -sin(difference * M_PI / 180.0) * magnitude;
        // int actual_turn = turn_magnitude;

        //Applying final values to motors for motion
        // FRONTLEFTWHEEL.move(actual_up_down - actual_left_right + actual_turn);
        // BACKLEFTWHEEL.move(actual_up_down + actual_left_right + actual_turn);
        // FRONTRIGHTWHEEL.move(-actual_up_down - actual_left_right + actual_turn);
        // BACKRIGHTWHEEL.move(-actual_up_down + actual_left_right + actual_turn);

    }
}

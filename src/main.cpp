#include "main.h"
#include "math.h"


void opcontrol() {



    TopLift.tare_position();





    while (true) {

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

        bool topLiftUp = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_X);
        bool topLiftDown = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_B);
        bool flipOut1 = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
        bool flipOut = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);

        bool pistonTop = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

        bool pistonBottom = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

        
        if (topLiftUp) {
            TopLift.move(127);
        }
        else if (topLiftDown) {
            TopLift.move(-127);
        } else if (!topLiftUp || !topLiftDown) {
            TopLift.move(0);
        }

        if (ringIntakeUp) {

            RingIntake.move(127);
        }
        else if (ringIntakeDown) {

            RingIntake.move(-127);
        } else if (!ringIntakeUp || !ringIntakeDown){
            RingIntake.move(0);
        }
        FrontLeftWheel.move(STRAIGHT + TURN);
        MiddleLeftWheel.move(STRAIGHT + TURN);
        BackLeftWheel.move(STRAIGHT + TURN);
        FrontRightWheel.move(STRAIGHT - TURN);
        MiddleLeftWheel.move(STRAIGHT - TURN);
        BackRightWheel.move(STRAIGHT - TURN);




    }
}

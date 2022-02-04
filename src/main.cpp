#include "main.h"
#include "math.h"

bool isFrontClamp = true;
bool isBackClamp = true;
bool isConveyerUp = false;
bool isConveyerDown = false;

bool buttonR2Prev=false;
bool buttonL2Prev=false;
bool buttonR1Prev=false;
bool buttonL1Prev=false;

bool buttonR2Pressed = false;
bool buttonL2True = false;
bool buttonR1True=false;
bool buttonL1True=false;








void opcontrol() {



    TopLift.tare_position();

    TopLift.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);



    while (true) {

        pros::lcd::set_text(1, "Front left: " + std::to_string(FrontLeftWheel.get_position()));
        pros::lcd::set_text(2, "Back left: " + std::to_string(BackLeftWheel.get_position()));
        pros::lcd::set_text(3, "Front right: " + std::to_string(FrontRightWheel.get_position()));
        pros::lcd::set_text(4, "Back right: " + std::to_string(BackRightWheel.get_position()));
        pros::lcd::set_text(5, "IMU: " + std::to_string(Inertial.get_heading()));
        // double TURN = CONTROLLER.get_analog(ANALOG_RIGHT_X);
        // double STRAIGHT = CONTROLLER.get_analog(ANALOG_LEFT_Y);
        double TURN = CONTROLLER.get_analog(ANALOG_LEFT_X);
        double STRAIGHT = CONTROLLER.get_analog(ANALOG_RIGHT_Y);
        double leftWheels = CONTROLLER.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

        bool ringIntakeUp = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
        bool ringIntakeDown = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
        bool liftUp = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
        bool liftDown = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);

        bool topLiftUp = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
        bool topLiftDown = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);

        bool pistonFront = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

        bool pistonBack = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_L2);



        if (topLiftUp) {
            TopLift.move(-127);
        }
        else if (topLiftDown) {
            TopLift.move(127);
        } else if (!topLiftUp || !topLiftDown) {

            TopLift.move(0);
        }

        // if (ringIntakeUp) {
        //
        //     RingIntake.move(127);
        // }
        // else if (ringIntakeDown) {
        //
        //     RingIntake.move(-127);
        // } else if (!ringIntakeUp || !ringIntakeDown){
        //     RingIntake.move(0);
        // }


        if (pistonFront&& !buttonR2Prev) {
          FrontPiston.set_value(isFrontClamp);
          FrontPiston2.set_value(isFrontClamp);
          isFrontClamp = !isFrontClamp;
        }


        if (pistonBack && !buttonL2Prev) {
          BackPiston.set_value(!isBackClamp);
          isBackClamp = !isBackClamp;
        }

        if (ringIntakeUp && !buttonR1Prev) {
          isConveyerUp ? (RingIntake.move(100)) : RingIntake.move(0);
          isConveyerUp = !isConveyerUp;
        }
        if (ringIntakeDown && !buttonL1Prev) {
          isConveyerDown ? RingIntake.move(-100) : RingIntake.move(0);
          isConveyerDown = !isConveyerDown;
        }

        FrontLeftWheel.move(-STRAIGHT - TURN);
        MiddleLeftWheel.move(-STRAIGHT - TURN);
        BackLeftWheel.move(STRAIGHT + TURN);
        FrontRightWheel.move(STRAIGHT - TURN);
        MiddleRightWheel.move(STRAIGHT - TURN);
        BackRightWheel.move(-STRAIGHT + TURN);


        buttonR2Prev = pistonFront;
        buttonL2Prev = pistonBack;
        buttonR1Prev = ringIntakeUp;
        buttonL1Prev = ringIntakeDown;


    }
}

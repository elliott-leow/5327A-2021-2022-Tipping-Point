#include "main.h"
#include "math.h"




void opcontrol() {

	//float initialclaw = CLAWMOTOR.get_position();

	    float up_down = CONTROLLER.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	  	float left_right = CONTROLLER.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
			float turnX = CONTROLLER.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
			float turnY = CONTROLLER.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

			float clawup = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
			float clawdown = CONTROLLER.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);

			while (clawup == 1) {
				CLAWMOTOR.move(127);
				//initialclaw = CLAWMOTOR.get_position();
			}

			while (clawup == 0 && clawdown==0) {
				//float claw = CLAWMOTOR.get_position();
				//if (initialclaw - claw > 0) {
					CLAWMOTOR.move_velocity(0);
				//}
			}

			while (clawdown == 1) {
				CLAWMOTOR.move(-127);
				//initialclaw = CLAWMOTOR.get_position();
			}



			//Getting current angle
			float angle = INERTIAL.get_heading();
			if(angle < 0) angle = 360 + angle;

			//Calculating left joystick angle
			float joystick_angle = atan(left_right/up_down) * 180 / M_PI;
			if(up_down < 0) joystick_angle = 180 + joystick_angle;
			if(joystick_angle < 0) joystick_angle = 360 + joystick_angle;

			//Calcualating difference in angles
			float difference = angle - joystick_angle;
			if(difference < 0) difference = 360 + difference;
			difference = 360 - difference;

			//Magnitude calculations
			float magnitude = sqrt(pow(up_down, 2.0) + pow(left_right, 2.0));
			if(magnitude > 127) magnitude = 127;

			//Calculating right joystick angle
			float turn_angle = atan(turnX/turnY) * 180 / M_PI;
			if(turnY < 0) turn_angle = 180 + turn_angle;
			if(turn_angle < 0) turn_angle = 360 + turn_angle;

			//Calculating turn difference in angles
			float turn_difference = turn_angle - angle;
			if(turn_difference < 0) turn_difference = 360 + turn_difference;
			turn_difference = 360 - turn_difference;

			//Turn magnitude calculations
			float turn_magnitude = (sqrt(pow(turnY, 2.0) + pow(turnX, 2.0)))*((turn_difference/360)+0.5);
			if(turn_magnitude > 127) turn_magnitude = 127;

			//Calculating actual turn value based on joystick position
			if(turn_difference < 180){
				turn_magnitude = -turn_magnitude;}
			if(turn_difference > 180) turn_difference = 360 - turn_difference;
			float proportion = sqrt(turn_difference/60);
			turn_magnitude = turn_magnitude*proportion;
			if(isinf(turn_magnitude)) turn_magnitude = 0;
			if(turn_difference < 1 || turn_difference > 359) turn_magnitude = 0;

			//Actual calculated values for motors
			int actual_up_down = cos(difference * M_PI / 180.0) * magnitude;
			int actual_left_right = -sin(difference * M_PI / 180.0) * magnitude;
			int actual_turn = turn_magnitude;

			//Applying final values to motors for motion
	    FRONTLEFTWHEEL.move(actual_up_down - actual_left_right + actual_turn);
			BACKLEFTWHEEL.move(actual_up_down + actual_left_right + actual_turn);
	    FRONTRIGHTWHEEL.move(-actual_up_down - actual_left_right + actual_turn);
			BACKRIGHTWHEEL.move(-actual_up_down + actual_left_right + actual_turn);
}

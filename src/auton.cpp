#include "main.h"
#include "math.h"

#define close_turn 90

int auton = 0;
//0 == small neutral and large neutral on right side
//1 == small neutral on left side
//2 == do nothing
double KPBASETURN = 0.2;
LV_IMG_DECLARE(gojo);
void initialize(){
  lv_obj_t * img_src = lv_img_create(lv_scr_act(), NULL); /*Crate an image object*/
  lv_img_set_src(img_src, &gojo);  /*Set the created file as image (a red fl  ower)*/
  lv_obj_set_pos(img_src, 0, 0);      /*Set the positions*/
  lv_obj_set_drag(img_src, true);
  pros::delay(15000);
  pros::lcd::set_text(6, "Stop setup");
  Inertial.reset();
  pros::delay(2000);
}

void competition_initialize(){
  initialize();
}

double saveHeading = 0;
void move(int i) {
  //i = motor speed
  FrontRightWheel.tare_position();
  FrontLeftWheel.tare_position();
  BackRightWheel.tare_position();
  BackLeftWheel.tare_position();
    if (i > 0){
    while (FrontRightWheel.get_position() < i) {
      FrontRightWheel.move(117);
      FrontLeftWheel.move(127);
      BackRightWheel.move(117);
      BackLeftWheel.move(127);
    }
  }
  if (i < 0){
  while (FrontRightWheel.get_position() > i) {
    FrontRightWheel.move(-117);
    FrontLeftWheel.move(-127);
    BackRightWheel.move(-117);
    BackLeftWheel.move(-127);
  }
}
FrontRightWheel.move(0);
FrontLeftWheel.move(0);
BackRightWheel.move(0);
BackLeftWheel.move(0);
}
void move(int i, int angle) {
// i = motor speed, i = angle the robot should turn towards while moving
  FrontRightWheel.tare_position();
  FrontLeftWheel.tare_position();
  BackRightWheel.tare_position();
  BackLeftWheel.tare_position();
  int target = Inertial.get_heading();

    while (std::abs(FrontRightWheel.get_position()) < std::abs(i)) {

      int actual_turn = 0;
      int move = i<0?-90:90;
        int tolerance = 3;
        int upperAngleBound = angle + tolerance;
      	int lowerAngleBound = angle - tolerance;



        int angle_ = (Inertial.get_heading());
        bool specialDown = false;
      	bool specialUp = false;
      	if(lowerAngleBound < 0){
      		lowerAngleBound = lowerAngleBound + 360;
      		specialDown = true;}
      	if(upperAngleBound > 360){
      		upperAngleBound = upperAngleBound - 360;
      		specialUp = true;
        }
        //if the robot is not at the heading
        if ((specialDown == true && ((angle_ <  lowerAngleBound && angle_ > angle+180) || (angle_ > upperAngleBound && angle_ < angle+180))) ||
      		(specialUp == true && ((angle_ > upperAngleBound && angle_ < angle-180) || (angle_ < lowerAngleBound && angle_ > angle-180))) ||
      		((specialUp == false && specialDown == false) && (angle_ > upperAngleBound || angle_ < lowerAngleBound))) {
            angle_ = (Inertial.get_heading());

            float turn_difference = angle_-angle;

            if(turn_difference > 180) turn_difference = 360-turn_difference;
        		if(turn_difference < -180) turn_difference = 360+turn_difference;
        		if(turn_difference < 0 && turn_difference > -180) turn_difference = -turn_difference;

      			//Spins in the directions which will allow bot to complete turn fastest
      			if(turn_difference > 180) turn_difference = 360-turn_difference;

      			//Slows down if close to goal heading and stays fast if it is away
            int turn_speed = 90;
      			if(turn_difference < close_turn){
      				actual_turn = (turn_speed*((turn_difference/(close_turn))+KPBASETURN));
      			}
      			else{
      				actual_turn = turn_speed;
      			}

      			/*Special conditions if angle bounds are less than 0 or greater than 360
      				Neccesary for proper turning and calculation*/
      			if((angle > angle_+180) || (angle > angle_-180 && angle_ > 180 && angle < 180) ||
      				(angle < angle_ && angle_-angle < 180)) actual_turn = -actual_turn;


          }
          int c = 5;
          if (i < 0) {

            c = -c;
          }
          //move robot foward and turn at same time
          FrontRightWheel.move(move-actual_turn+c);
          FrontLeftWheel.move(move+actual_turn-c);
          BackRightWheel.move(move-actual_turn+c);
          BackLeftWheel.move(move+actual_turn-c);

      }




      //Moves the wheels at a certain "move" speed
      FrontRightWheel.move(0);
      FrontLeftWheel.move(0);
      BackRightWheel.move(0);
      BackLeftWheel.move(0);

    }






// void turn(int i) {
//   Inertial.tare();
//   while(i < Inertial.get_heading()) {
//     int error = (Inertial.get_heading()-i)*1.4;
//     int move = error > 75 ? 75 : -75;
//     FrontRightWheel.move(-move);
//             FrontLeftWheel.move(move);
//             BackRightWheel.move(-move);
//             BackLeftWheel.move(move);
//   }
// }

void stopHold(){

	FrontLeftWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	FrontRightWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	BackRightWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	BackLeftWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  FrontLeftWheel.move(0);
  FrontRightWheel.move(0);
  BackRightWheel.move(0);
  BackLeftWheel.move(0);
}

void turn(int angle, int tolerance, int turn_speed){
  int upperAngleBound = angle + tolerance;
	int lowerAngleBound = angle - tolerance;

	long begin_time = pros::millis();

  int angle_ = (Inertial.get_heading());

	//Special conditions (If the angle is at 0 for example)

	bool specialDown = false;
	bool specialUp = false;

	if(lowerAngleBound < 0){
		lowerAngleBound = lowerAngleBound + 360;
		specialDown = true;}
	if(upperAngleBound > 360){
		upperAngleBound = upperAngleBound - 360;
		specialUp = true;}

  while((specialDown == true && ((angle_ <  lowerAngleBound && angle_ > angle+180) || (angle_ > upperAngleBound && angle_ < angle+180))) ||
		(specialUp == true && ((angle_ > upperAngleBound && angle_ < angle-180) || (angle_ < lowerAngleBound && angle_ > angle-180))) ||
		((specialUp == false && specialDown == false) && (angle_ > upperAngleBound || angle_ < lowerAngleBound))) {

      angle_ = (Inertial.get_heading());

      float turn_difference = angle_-angle;
      float actual_turn = 0;
  		if(turn_difference > 180) turn_difference = 360-turn_difference;
  		if(turn_difference < -180) turn_difference = 360+turn_difference;
  		if(turn_difference < 0 && turn_difference > -180) turn_difference = -turn_difference;

			//Spins in the directions which will allow bot to complete turn fastest
			if(turn_difference > 180) turn_difference = 360-turn_difference;

			//Slows down if close to goal heading and stays fast if it is away
			if(turn_difference < close_turn){
				actual_turn = (turn_speed*((turn_difference/(close_turn))+KPBASETURN));
			}
			else{
				actual_turn = turn_speed;
			}

			/*Special conditions if angle bounds are less than 0 or greater than 360
				Neccesary for proper turning and calculation*/
			if((angle > angle_+180) || (angle > angle_-180 && angle_ > 180 && angle < 180) ||
				(angle < angle_ && angle_-angle < 180)) actual_turn = -actual_turn;

        FrontRightWheel.move(-actual_turn);
        FrontLeftWheel.move(actual_turn);
        BackRightWheel.move(-actual_turn);
        BackLeftWheel.move(actual_turn);

      pros::lcd::set_text(1, std::to_string(angle_));
      pros::lcd::set_text(2, std::to_string(angle));
      pros::lcd::set_text(3, std::to_string(actual_turn));

    pros::delay(5);
  }

  stopHold();

  pros::lcd::set_text(4, "Goal reached");
}


void autonomous(){



stopHold();
    if (auton == 0) {
      TopLift.move_relative(-1300,127);
      //flip out clamp
      //piston.set_value(false);
      //BottomLift.move_relative(-2100,127);
      //move mogo lift down to prepare to intake it
      move(3300,20);
      //move towards small neutral mogo

      //BottomLift.move_relative(2150,127);
      //pick up small neutral mogo
      pros::delay(1500);
      move(-500);
      turn(270,10,137);
      //moves back and turns toward middle neutral mogo
      pros::delay(500);
      move(-1900,254);
      //move towards middle neutral mogo
      //piston.set_value(true);
      pros::delay(300);
      //clamp neutral mogo
      move(3700,220);
      //return to home zone

    }

    if (auton == 1){
      TopLift.move_relative(-1300,127);
      //flip out clamp
      //piston.set_value(false);
      move(-2800,1);
      //move towards small neutral
      //piston.set_value(true);
      //clamp small neutral
      move(2800,1);
      //return to home zone



    }
    if (auton == 2) {

    }


}

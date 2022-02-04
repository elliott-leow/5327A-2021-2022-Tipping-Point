#include "main.h"
#include "math.h"

#define close_turn 90

int auton = 2;
//-1 == gilbert's left side autonomous
//0 == skills
//1 == small and large neutral
//2 == winpoint auton
//3 == do nothing
//double KPBASETURN = 0.2;
double KPBASETURN = 0.3;
// LV_IMG_DECLARE(gojo);
void initialize(){
   // lv_obj_t * img_src = lv_img_create(lv_scr_act(), NULL); /*Crate an image object*/
   // lv_img_set_src(img_src, &gojo);  /*Set the created file as image (a red fl  ower)*/
   // lv_obj_set_pos(img_src, 0, 0);      /*Set the positions*/
   // lv_obj_set_drag(img_src, true);
  //pros::delay(15000);
  pros::lcd::initialize();
  pros::lcd::set_text(6, "Stop setup");
  Inertial.reset();
  pros::delay(3000);
}

void competition_initialize(){
  initialize();
}

double saveHeading = 0;

void movespeed(int i, int angle,int speed) {
// i = motor speed, angle = angle the robot should turn towards while moving
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


          FrontLeftWheel.move(-move-actual_turn+speed);
          MiddleLeftWheel.move(-move-actual_turn+speed);
          BackLeftWheel.move(+move+actual_turn-speed);
          FrontRightWheel.move(+move-actual_turn-speed);
          MiddleRightWheel.move(+move-actual_turn-speed);
          BackRightWheel.move(-move+actual_turn+speed);

          //move robot foward and turn at same time
          // FrontRightWheel.move(move-actual_turn+c);
          // FrontLeftWheel.move(move+actual_turn-c);
          // BackRightWheel.move(move-actual_turn+c);
          // BackLeftWheel.move(move+actual_turn-c);



      }




      //Moves the wheels at a certain "move" speed
      FrontRightWheel.move(0);
      FrontLeftWheel.move(0);
      BackRightWheel.move(0);
      BackLeftWheel.move(0);

    }

void move(int i) {
  //i = motor speed
  int target = Inertial.get_heading();
  FrontRightWheel.tare_position();
  FrontLeftWheel.tare_position();
  BackRightWheel.tare_position();
  BackLeftWheel.tare_position();
    if (i > 0){
    while (FrontRightWheel.get_position() < i) {
      int difference = (Inertial.get_heading()-target)*KPBASETURN;

      FrontLeftWheel.move(-127-difference);
      MiddleLeftWheel.move(-127-difference);
      BackLeftWheel.move(+127+difference);
      FrontRightWheel.move(+127-difference);
      MiddleRightWheel.move(+127-difference);
      BackRightWheel.move(-127+difference);

      pros::lcd::set_text(4, std::to_string(difference));
    }
  }
  if (i < 0){
  while (FrontRightWheel.get_position() > i) {
    int difference = (Inertial.get_heading()-target)*KPBASETURN;

    FrontLeftWheel.move(+127+difference);
    MiddleLeftWheel.move(+127+difference);
    BackLeftWheel.move(-127-difference);

    FrontRightWheel.move(-127+difference);
    MiddleRightWheel.move(-127+difference);
    BackRightWheel.move(+127-difference);

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
void move(int i, int angle) {
// i = motor speed, angle = angle the robot should turn towards while moving
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


          FrontLeftWheel.move(-move-actual_turn);
          MiddleLeftWheel.move(-move-actual_turn);
          BackLeftWheel.move(+move+actual_turn);
          FrontRightWheel.move(+move-actual_turn);
          MiddleRightWheel.move(+move-actual_turn);
          BackRightWheel.move(-move+actual_turn);

          //move robot foward and turn at same time
          // FrontRightWheel.move(move-actual_turn+c);
          // FrontLeftWheel.move(move+actual_turn-c);
          // BackRightWheel.move(move-actual_turn+c);
          // BackLeftWheel.move(move+actual_turn-c);



      }




      //Moves the wheels at a certain "move" speed
      FrontRightWheel.move(0);
      FrontLeftWheel.move(0);
      BackRightWheel.move(0);
      BackLeftWheel.move(0);

    }








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


void autonomous(){



stopHold();
//chang
if(auton == -1) {
  move(2400,360-7);
  FrontPiston.set_value(true);
  FrontPiston2.set_value(true);
  move(-2000,0);
  pros::delay(500);
  turn(235,3,80);
  pros::delay(300);
  move(-1200);
  BackPiston.set_value(true);
  pros::delay(300);
  move(600);
  stopHold();
  RingIntake.move_relative(1500, 100);

  //turn(90,3,127);

}

//skills
    if (auton == 0) {
      FrontPiston.set_value(false);
      FrontPiston2.set_value(false);
      move(250);
      //turn()
    }

    if (auton == 1){
      FrontPiston.set_value(false);
      FrontPiston2.set_value(false);
      move(2700,18);
      FrontPiston.set_value(true);
      FrontPiston2.set_value(true);
      //pros::delay(100);
      move(-600);
      pros::delay(100);
      turn(270,10,148);
      pros::delay(100);
      move(-2000,270);
      pros::delay(100);
      move(300,270);
      turn(230,10,200);
      pros::delay(100);
      move(-470);
      //move(2050,247);
      BackPiston.set_value(true);
      move(1300,256);
      move(2300,180);



    }
    if (auton == 2) {
      //Inertial.tare();
      RingIntake.move_relative(500, 100);
      pros::delay(1000);
      move(500,5);
      //turn(90,5,80);
      pros::delay(200);
      turn(90,5,100);
      pros::delay(50);
      move(500,90);
      turn(0,5,100);
      pros::delay(200);
      move(-5600,0);
      BackPiston.set_value(true);
      FrontPiston.set_value(false);
      FrontPiston2.set_value(false);
      pros::delay(100);
      RingIntake.move_relative(1200, 100);
      pros::delay(1000);
      move(600,0);
      pros::delay(100);
      BackPiston.set_value(false);
      move(180,0);
      move(1820,56);
      FrontPiston.set_value(true);
      FrontPiston2.set_value(true);
      pros::delay(100);
      move(-2200);



    }
    if (auton == 3) {


    }


}

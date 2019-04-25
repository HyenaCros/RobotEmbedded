/*
 * MotorControls.h
 *
 * Created: 4/16/2019 3:09:44 PM
 *  Author: colea
 */ 
void setSpeed(int speed);
void wheelSetup();
void goForwards();
void goBackwards();
void stop();
void onlyLeftForwards();
void onlyRightForwards();
void onlyLeftBackwards();
void onlyRightBackwards();
void differentSpeeds(int right, int left);
void leftForwardsRightBack();
void rightForwardsLeftBack();
int findSpeed(int speed);
void TurnDegrees(int degree, int left);
void RadiusTurn(double cm, double degrees, int left);
void test1();
void test2();
void test3();
void test4();
void test5();
void driveStraight(int millis, int forwards);
void goStraightDistance(int cm, int forwards);
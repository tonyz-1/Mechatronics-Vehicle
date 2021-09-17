#define LEncoderPin 3    
#define REncoderPin 2

#include <AFMotor.h>

#define echoPin A3 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin A4 //attach pin D3 Arduino to pin Trig of HC-SR04

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


AF_DCMotor left_motor(1, MOTOR34_1KHZ);  // left motor to M1 on motor control board
AF_DCMotor right_motor(3, MOTOR12_1KHZ); // right motor to M3 on motor control board
int LeftEncoderCount = 0;
int RightEncoderCount = 0;
boolean detected=false;
boolean ifstop=false;
boolean balanced=false;
double balancefactor=0;
int color=0;
double speeds=100;
boolean sonic_sensor_check=false;
boolean right_infrared_sensor_check=false;
boolean left_infrared_sensor_check=false;
boolean IR_sensor_check=false;
boolean right_encoder_sensor_check=false;
boolean left_encoder_sensor_check=false;
boolean infraredsensorcheck=false;
boolean irsensorcheck=false;
boolean state_check=false;
int preleftsensor=0;
int prerightsensor=0;
int precolor=0;
int rightsensor=0;
int leftsensor=0;
int left_x_shift=0;
int right_x_shift=0;
boolean right_turn_processing=false;
boolean left_turn_processing=false;
boolean pre_motion=false;
double angle_1_y=0;
double angle_1_x=0;
double angle_2_y=0;
double angle_2_x=0;
int comback_distance=0;
double angle1=0;
double angle2=0;
int block1x=0;
int block2x=0;
int count=0;
int precount;


void setup() {

attachInterrupt(1, countLEncoder, RISING); //calls on any CHANGE on pin 3 (interrupt #1, soldered to Pin3)
attachInterrupt(0, countREncoder, RISING); //calls on any CHANGE on pin 2 (interrupt #0, connected to header on Pin2)
interrupts();
pinMode(A0, INPUT);
pinMode(A1, INPUT);
pinMode(A2,INPUT);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
Serial.begin (115200);    // set up Serial library at 115200 bps



 
}

void loop() {
 rightsensor=digitalRead(A0);
 leftsensor=digitalRead(A1);
if(infraredsensorcheck=false){
prerightsensor=rightsensor;
preleftsensor=leftsensor;
 
}
color=analogRead(A2);
if(irsensorcheck=false){
precolor=color;
 
}
sonic_scan();

while(state_check==false){
  sonic_scan();
start_check();
}

Serial.println("Hi");
if(color>150){
 
  left_motor.run(FORWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
 
 
 

  obstacle_avoid_system();
  if(count==0){
    angle_1_x=right_x_shift;
    block1x=right_x_shift;
    }
else if(count==1){
  angle_2_x=right_x_shift;
  block1x=right_x_shift;
}
else{
 
}
if(pre_motion==false){
  right_trun_back_check();
 
}else{
  left_trun_back_check();
 
}





 
}

 
else{

   left_motor.run(FORWARD);
  right_motor.run(FORWARD);

  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(500);
  angle_2_y=RightEncoderCount-precount;
  turnaround();

  if(count=1){
    angle_2_x=angle_1_x;
  }
  goback();
  exit(0);


 
 

 
}










}


void right_turn(){
  left_motor.run(FORWARD);
  right_motor.run(BACKWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
  delay(380);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(1000);


  left_motor.run(FORWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
   int precount=LeftEncoderCount;
  delay(750);
  right_x_shift=right_x_shift+(RightEncoderCount-precount);
  Serial.print("pre right_x_shift: ");
  Serial.print(right_x_shift);
  Serial.println(" cm");
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(1000);


 
  left_motor.run(BACKWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
  delay(380);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(1000);

 
}

void left_turn(){
left_motor.run(BACKWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
  delay(380);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(1000);

left_motor.run(FORWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
  int precount=LeftEncoderCount;
  delay(750);
  left_x_shift=left_x_shift+(LeftEncoderCount-precount);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(1000);


 
  left_motor.run(FORWARD);
  right_motor.run(BACKWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
  delay(380);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(1000);

 
}

void sonic_scan(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void start_check(){
  if(distance!=0&&sonic_sensor_check==false){
    sonic_sensor_check=true;
    Serial.println(" sonic sensor checked ");
  }
  if(LeftEncoderCount!=0&&left_encoder_sensor_check==false){
    left_encoder_sensor_check=true;
    Serial.println(" left encoder checked ");
  }

  if(RightEncoderCount!=0&&right_encoder_sensor_check==false){
    right_encoder_sensor_check=true;
    Serial.println(" right encoder checked ");
  }

  if(rightsensor!=prerightsensor&&right_infrared_sensor_check==false){
    right_infrared_sensor_check=true;
    Serial.println(" right infrared sensor checked ");
   

  }

 
  if(leftsensor!=preleftsensor&&left_infrared_sensor_check==false){
    left_infrared_sensor_check=true;
    Serial.println(" left infrared checked ");

  }

  if(color!=precolor&&IR_sensor_check==false){
    IR_sensor_check=true;
    Serial.println(" color sensor checked ");
  }

  if(IR_sensor_check==true&&left_infrared_sensor_check==true&&right_infrared_sensor_check==true&& right_encoder_sensor_check==true&&left_encoder_sensor_check==true&&sonic_sensor_check==true){
    state_check=true;
    delay(1000);

   






   
  }



 
}

void obstacle_avoid_system(){


if(rightsensor==LOW&&leftsensor==LOW||leftsensor==LOW){

angle_1_y=RightEncoderCount;

  left_motor.run(BACKWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(400);



 
   right_turn_processing=true;
   right_turn();
   delay(100);
   pre_motion=false;
  }

else if(rightsensor==LOW){
   left_motor.run(BACKWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(400);
  left_turn_processing=true;
  left_turn();
  delay(100);
  pre_motion=true;
}
else{
left_turn_processing=false;
right_turn_processing=false;

 
}


 
}

void right_trun_back_check(){
if(right_turn_processing==false&&left_turn_processing==false&&right_x_shift!=0){
  if(right_x_shift!=0){
    left_motor.run(FORWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
    delay(500);
  }
turnleft();
sonic_scan();

rightsensor=digitalRead(A0);
 leftsensor=digitalRead(A1);

if(rightsensor==HIGH&&leftsensor==HIGH&&distance>50){
   int prerightcount=RightEncoderCount;
   Serial.print("right_x_shift ");
  Serial.print(right_x_shift);
  Serial.println(" cm");
  while(RightEncoderCount<prerightcount+right_x_shift){
  left_motor.run(FORWARD);
   right_motor.run(FORWARD);
 
    left_motor.setSpeed(speeds);
    right_motor.setSpeed(speeds+50);
    Serial.print("right Encoder count ");
  Serial.print(RightEncoderCount);
  Serial.println(" cm");
  Serial.print("prerightcount+right_x_shift");
  Serial.print(prerightcount+right_x_shift);
  Serial.println(" cm");

  }
  Serial.print("shit ");
 
left_motor.run(FORWARD);
   right_motor.run(FORWARD);
 
    left_motor.setSpeed(0);
    right_motor.setSpeed(0);
    delay(500);


turnright();
  right_x_shift=0;
  count=count+1;

precount=RightEncoderCount;
}


else{
    turnright();
  }

 
}

 
}


void left_trun_back_check(){
if(right_turn_processing==false&&left_turn_processing==false&&left_x_shift!=0){
  if(left_x_shift!=0){
    left_motor.run(FORWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
    delay(700);
  }
right_turn();
if(rightsensor==HIGH&&leftsensor==HIGH){
   int prerightcount=RightEncoderCount;
  while(RightEncoderCount<prerightcount+left_x_shift){
  left_motor.run(FORWARD);
   right_motor.run(FORWARD);
 
    left_motor.setSpeed(speeds);
    right_motor.setSpeed(speeds+50);

  }
  left_x_shift=0;
}else{
    left_turn();
  }

 
}

 
}

void turnleft(){

left_motor.run(BACKWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
  delay(350);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(1000);
 
}

void turnright(){

left_motor.run(FORWARD);
  right_motor.run(BACKWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
  delay(350);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(1000);
 
}









void balance(){
   left_motor.run(FORWARD);
   right_motor.run(FORWARD);
 
    left_motor.setSpeed(80);
    right_motor.setSpeed(80);
    delay(200);
    balancefactor=LeftEncoderCount/RightEncoderCount;
   
    Serial.print(balancefactor);
    delay(500);
   
 }
 void turnaround(){

  turnright();
  turnright();
 }

 void goback(){
  angle1=atan(angle_1_x/angle_1_y);
  angle2=atan(angle_2_x/angle_2_y);


 
  if(block2x>block1x){
    gobackfromleft();
  }
  else if(block2x<block1x){
    gobackfromright();
  }
  else{
    gobackfromleft();
  }

 
 }


 void gobackfromleft(){





 
  int currentcountleft=LeftEncoderCount;
  int currentcountright=RightEncoderCount;
 
  int anglelength2=angle_2_y/sin(angle2);
  int anglelength1=angle_1_y/sin(angle1);
  angle2*=4.5*(180/3.14);
  int angle =(int)angle2;

  angle1*=4.5*(180/3.14);
  int aangle =(int)angle1;



for(int i=0; i<200; i++){
  Serial.print("this is angle!!!!!!!:");
  Serial.println(angle);


}
  left_motor.run(BACKWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(100);
  right_motor.setSpeed(150);
  delay(angle);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
/*
 *
 * problem starts here, angle is not a int
 */






 
 
 
while(LeftEncoderCount<currentcountleft+anglelength2){
  left_motor.run(FORWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
}
 left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(100);
  left_motor.run(FORWARD);
  right_motor.run(BACKWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
  delay(angle);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(1000);
currentcountleft=LeftEncoderCount;
currentcountright=RightEncoderCount;
while(LeftEncoderCount<currentcountleft+comback_distance){
  left_motor.run(FORWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
}
left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(100);


 
left_motor.run(FORWARD);
  right_motor.run(BACKWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
  delay(aangle);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(1000);
 
while(LeftEncoderCount<currentcountleft+anglelength1){
  left_motor.run(FORWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
}
 left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  ifstop=true;



 
 }
 void gobackfromright(){





 
  int currentcountleft=LeftEncoderCount;
  int currentcountright=RightEncoderCount;
 
  int anglelength2=angle_2_y/sin(angle2);
  int anglelength1=angle_1_y/sin(angle1);
  angle2*=4.5*(180/3.14);
  int angle =(int)angle2;

  angle1*=4.5*(180/3.14);
  int aangle =(int)angle1;


  left_motor.run(FORWARD);
  right_motor.run(BACKWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
  delay(angle);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(1000);
 
while(LeftEncoderCount<currentcountleft+anglelength2){
  left_motor.run(FORWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
}
 left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(100);
  left_motor.run(BACKWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
  delay(angle);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(1000);
currentcountleft=LeftEncoderCount;
currentcountright=RightEncoderCount;
while(LeftEncoderCount<currentcountleft+comback_distance){
  left_motor.run(FORWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
}
left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(100);


 
left_motor.run(BACKWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
  delay(aangle);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(1000);
 
while(LeftEncoderCount<currentcountleft+anglelength1){
  left_motor.run(FORWARD);
  right_motor.run(FORWARD);
  left_motor.setSpeed(speeds);
  right_motor.setSpeed(speeds+50);
}
 left_motor.setSpeed(0);
  right_motor.setSpeed(0);
 

ifstop=true;



 
 }

void countLEncoder(){ // interrupt function for left encoder
    LeftEncoderCount++;
     delay(5);
}

void countREncoder(){ // interrupt function for right encoder
      RightEncoderCount++;
      delay(5);
}

#include <SoftwareSerial.h>

#define TX_pin 8
#define RX_pin 7  //make sure these pins are not used for any other purpose

SoftwareSerial mySerial(RX_pin,TX_pin);
char direction;

int R_PWM = 10;
int L_PWM = 9;

//  Motor Direction Pins
int R_direction = 5;
int L_direction = 6;

#define Forward 1
#define Reverse 0


// Left Speed
int CCW_R = 180;        // Forward (max 0 - min 255)
int CCW_L = 40;         // Reverse (max 255 - min 0)
// right Speed
int CW_R = 40;          // Forward (max 0 - min 255)
int CW_L = 180;         // Reverse (max 255 - min 0)
//wheel speeds (Forward/Reverse)
int right_speed = 40;
int left_speed  = 40;


void FForward() 
{
        analogWrite(R_PWM, right_speed);
        digitalWrite(R_direction, Forward);
        
        analogWrite(L_PWM, left_speed);
        digitalWrite(L_direction, Forward);     
}

void RReverse() 
{
        analogWrite(R_PWM, 210);
        digitalWrite(R_direction, Reverse);
        
        analogWrite(L_PWM, 210);
        digitalWrite(L_direction, Reverse);     
}

void stop_SIMBOT() 
{
        analogWrite(R_PWM, 0);
        digitalWrite(R_direction, Reverse);
        
        analogWrite(L_PWM, 0);
        digitalWrite(L_direction, Reverse);     
}

void turn_right() 
{
        analogWrite(R_PWM, right_speed);
        digitalWrite(R_direction, Reverse);
        
        analogWrite(L_PWM, left_speed);
        digitalWrite(L_direction, Forward); 
}

void turn_left() 
{   
        analogWrite(R_PWM, right_speed);
        digitalWrite(R_direction, Forward);
        
        analogWrite(L_PWM, left_speed);
        digitalWrite(L_direction, Reverse);
}


void setup() {

  Serial.begin(115200);
  mySerial.begin(4800);

}

void loop() {

//To receive data
  //Serial.print("Data received:");

  while (mySerial.available()==0) {}    //Wait until data is received

 // if(mySerial.available()) {
  direction = char(mySerial.read());
  Serial.print("direction = ");
  Serial.println(direction);
  //} 


  switch (direction) {
    
  case 'forward':  FForward();
  Serial.println("The car is commanded to go forward"); //no need for curly brackets after case
  break;
  
  case 'B': RReverse();
  Serial.println("The car is commanded to reverse");
  break;
  
  case 'L': turn_left();
  Serial.println("The car is commanded to go left");
  break;
  
  case 'R': turn_right();
  Serial.println("The car is commanded to go right");
  break;

  case 'S': stop_SIMBOT(); 
  Serial.println("The car is commanded to stop");
  break;

  //default: stop_SIMBOT();
   //Serial.println("The car is stopped");
  }

  //direction='S';
 delay(250);

}

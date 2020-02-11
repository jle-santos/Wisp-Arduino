/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *MOTOR_B = AFMS.getMotor(2);
Adafruit_DCMotor *MOTOR_C = AFMS.getMotor(3);
Adafruit_DCMotor *MOTOR_D = AFMS.getMotor(4);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

#define A_PIN 2
#define B_PIN 3
#define EN_PIN 4
#define LED_PIN 13

#define BIT0 5
#define BIT1 6
#define BIT2 7

int PIN_A = 0;
int PIN_B = 0;
int PIN_EN = 0;

int BIT0VAL = 0;
int BIT1VAL = 0;
int BIT2VAL = 0;

void setup() {
  pinMode(A_PIN, INPUT);
  pinMode(B_PIN, INPUT);
  pinMode(EN_PIN, INPUT);
  
  pinMode(LED_PIN, OUTPUT);
  
  pinMode(BIT0, INPUT);
  pinMode(BIT1, INPUT);
  pinMode(BIT2, INPUT);

  
  digitalWrite(LED_PIN, LOW);
  
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(255);
  MOTOR_B->setSpeed(255);
  MOTOR_C->setSpeed(255);
  MOTOR_D->setSpeed(255);
  /*
  myMotor->run(FORWARD);
  MOTOR_B->run(FORWARD);
  MOTOR_C->run(FORWARD);
  MOTOR_D->run(FORWARD);
  */
  // turn on motor
  myMotor->run(RELEASE);
  MOTOR_B->run(RELEASE);
  MOTOR_C->run(RELEASE);
  MOTOR_D->run(RELEASE);
}

void loop() {
  //uint8_t i;
  PIN_A = digitalRead(A_PIN);
  PIN_B = digitalRead(B_PIN);
  PIN_EN = digitalRead(EN_PIN);

  BIT0VAL = digitalRead(BIT0);
  BIT1VAL = digitalRead(BIT1);
  BIT2VAL = digitalRead(BIT2);

  byte i = (getSpeed(BIT0VAL, BIT1VAL, BIT2VAL))*32;
  myMotor->setSpeed(i);
  MOTOR_B->setSpeed(i);
  MOTOR_C->setSpeed(i);
  MOTOR_D->setSpeed(i); 
  //Serial.print(speedMotor);
  //Serial.print("\n");
  
  checkDir(PIN_A, PIN_B, PIN_EN);
  /*
  Serial.print("tick");
  myMotor->run(FORWARD);
  MOTOR_B->run(FORWARD);
  MOTOR_C->run(FORWARD);
  MOTOR_D->run(FORWARD);
  i = 255;
  myMotor->setSpeed(i);
  MOTOR_B->setSpeed(i);
  MOTOR_C->setSpeed(i);
  MOTOR_D->setSpeed(i);  
  delay(2000);
  myMotor->run(RELEASE);
  MOTOR_B->run(RELEASE);
  MOTOR_C->run(RELEASE);
  MOTOR_D->run(RELEASE);

  //go backwards
  myMotor->run(BACKWARD);
  MOTOR_B->run(BACKWARD);
  MOTOR_C->run(BACKWARD);
  MOTOR_D->run(BACKWARD);

    delay(2000);
  myMotor->run(RELEASE);
  MOTOR_B->run(RELEASE);
  MOTOR_C->run(RELEASE);
  MOTOR_D->run(RELEASE);
   */ 
  /*
  myMotor->run(FORWARD);
  MOTOR_B->run(FORWARD);
  MOTOR_C->run(FORWARD);
  MOTOR_D->run(FORWARD);
  
  for (i=0; i<255; i++) {
    myMotor->setSpeed(i);
    MOTOR_B->setSpeed(i);
    MOTOR_C->setSpeed(i);
    MOTOR_D->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor->setSpeed(i);
    MOTOR_B->setSpeed(i);
    MOTOR_C->setSpeed(i);
    MOTOR_D->setSpeed(i);    
    delay(10);
  }
  
  Serial.print("tock");

  myMotor->run(BACKWARD);
  MOTOR_B->run(BACKWARD);
  MOTOR_C->run(BACKWARD);
  MOTOR_D->run(BACKWARD);
  for (i=0; i<255; i++) {
    myMotor->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor->setSpeed(i);  
    delay(10);
  }

  Serial.print("tech");
  myMotor->run(RELEASE);
  MOTOR_B->run(RELEASE);
  MOTOR_C->run(RELEASE);
  MOTOR_D->run(RELEASE);
  */
  //delay(1000);
}

byte getSpeed(int A, int B, int C) {
  byte speedControl = 0x00;

  bitWrite(speedControl, 0, A);
  bitWrite(speedControl, 1, B); 
  bitWrite(speedControl, 2, C);  
  
  return speedControl;
}

void checkDir(int A, int B, int EN) {
  if(EN == HIGH){
    digitalWrite(LED_PIN, HIGH);
    
    if(A == HIGH && B == HIGH){
      myMotor->run(BACKWARD);
      MOTOR_B->run(BACKWARD);
      MOTOR_C->run(BACKWARD);
      MOTOR_D->run(BACKWARD);
    }
    else if(A == LOW && B == LOW) {
      myMotor->run(FORWARD);
      MOTOR_B->run(FORWARD);
      MOTOR_C->run(FORWARD);
      MOTOR_D->run(FORWARD);
    }
    else if(A == LOW && B == HIGH) {
      myMotor->run(FORWARD);
      MOTOR_B->run(BACKWARD);
      MOTOR_C->run(FORWARD);
      MOTOR_D->run(BACKWARD);
    }
    else if(A == HIGH && B == LOW) { 
      myMotor->run(BACKWARD);
      MOTOR_B->run(FORWARD);
      MOTOR_C->run(BACKWARD);
      MOTOR_D->run(FORWARD);
    }
  }
  else {
      myMotor->run(RELEASE);
      MOTOR_B->run(RELEASE);
      MOTOR_C->run(RELEASE);
      MOTOR_D->run(RELEASE);

  digitalWrite(LED_PIN, LOW);
  }
}

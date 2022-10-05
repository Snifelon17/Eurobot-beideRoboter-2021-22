#include <AccelStepper.h>
#include <Servo.h>
#include <math.h>

#define enableL 8
#define enableR 8

#define stepL 25
#define stepR 34

#define dirL 33
#define dirR 29




int t = 100; //ms Pause
int accelerationPhase = 100;          // die 100 ersten Steps
int accelerationNummer = 0.0025;      //multiplikator
int stepsDone = 0;
int i = 0;                              //test

int front = 5;
int back = 6;
int left = 3;
int right = 4;


int frontAn = 15;
int backAn = 16;
int leftAn = 13;
int rightAn = 14;

Servo servoArm;
Servo servoWuerfel;// Define our Servo

void setup() //Hier beginnt das Setup.
{
  Serial.begin(9600);
  pinMode(8, OUTPUT);  
  pinMode(25, OUTPUT);
  pinMode(34, OUTPUT);  
  pinMode(33, OUTPUT);
  pinMode(29, OUTPUT);



  digitalWrite(enableR,HIGH); //oder low, habs vergessen
  digitalWrite(enableL,HIGH); //oder low, habs vergessen

  servoWuerfel.attach(11); // servo on digital pin 10
  servoArm.attach(10); // servo on digital pin 10
}

void loop() 
{
  /*servoArm.write(180); // Turn Servo Left to 0 degrees
  delay(500);
  driveForward(1000);
  delay(500);
  servoArm.write(180); // Turn Servo Left to 0 degrees
  delay(500);
  servoArm.write(90); // Turn Servo Left to 0 degrees
  delay(500);
  driveForward(2000);

*/
delay(3000);
//Serial.println("Fahre los");
delay(3000);
driveForward(1000);
delay(3000);
//turnLeft(200);
//delay(3000);
//turnRight(200);
//delay(3000);
driveBackwards(1000);
}


   ////////////////////////////////////////////////////////////////////
  //                           Funktionen                           //
 ///////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////// AUS /////////////////////////////////////////////
void frontAus()
{
  Serial.write(front);
  //delay(1000);
  Serial.println("Der Vordere ist aus!");
}

void backAus()
{
  Serial.write(back);
  //delay(1000);
  Serial.println("Der Hintere ist aus!");
}

void leftAus()
{
  Serial.write(left);
}

void rightAus()
{
  Serial.write(right);
} 


////////////////////////////////////////////////////AN //////////////////////////////////////////////////////////

void frontAnmachen()
{
  Serial.write(frontAn);
  //delay(1000);
  //Serial.println("Der Vordere ist an!");
}

void backAnmachen()
{
  Serial.write(backAn);
  //delay(1000);
  //Serial.println("Der Hintere ist an!");
}

void leftAnmachen()
{
  Serial.write(leftAn);
}

void rightAnmachen()
{
  Serial.write(rightAn);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



 void driveForward(int steps)
 {
    int speed = 0;
    int a = 0; 
    float MotorAn;
    float MotorAus;
    
    digitalWrite(enableR,LOW); //oder low, habs vergessen
    digitalWrite(enableL,LOW); //oder low, habs vergessen

    digitalWrite(dirL,LOW);  //oder andersrum
    digitalWrite(dirR,LOW);  //oder andersrum

    //Ativiert die wichtigen Ultraschalsensoren
    frontAnmachen();
    delay(100);
    backAus();
    delay(100);
    leftAus();
    delay(100);
    rightAus();
    delay(5000);

    
    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )
    {    
        if (digitalRead(5) == LOW)
        {

// gain Speed
          if (speed == 0){
            MotorAn = stepsDone * 0.5;
            if (MotorAn > t)
            { 
                MotorAn = t;
                speed = 1;
            }
            MotorAus = (1.2*t) - MotorAn;
          }

          Serial.println("STEP");
          digitalWrite(stepL,HIGH);
          digitalWrite(stepR,HIGH);
          delayMicroseconds(MotorAn);
          digitalWrite(stepL,LOW);
          digitalWrite(stepR,LOW);
          delayMicroseconds(MotorAus);
        }

        // wird ausgeführt wenn ein Hindernis erkannt wird
        else {
          speed = 0;
          stepsDone = stepsDone - 1;
          delayMicroseconds(100);
          }
              
    }
 }



 
 void driveBackwards(int steps)
 {
    int speed = 0;
    int a = 0; 
    float MotorAn;
    float MotorAus;
    
    digitalWrite(enableR,LOW); //oder low, habs vergessen
    digitalWrite(enableL,LOW); //oder low, habs vergessen

    digitalWrite(dirL,HIGH);  //oder andersrum
    digitalWrite(dirR,HIGH);  //oder andersrum

    //Ativiert die wichtigen Ultraschalsensoren
    delay(1000);
    backAnmachen();
    delay(1000);
    frontAus();
    delay(1000);
    leftAus();
    delay(1000);
    rightAus();
    delay(1000);
    
    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )
    {    
        if (digitalRead(5) == LOW)
        {

// gain Speed
          if (speed == 0){
            MotorAn = stepsDone * 0.5;
            if (MotorAn > t)
            { 
                MotorAn = t;
                speed = 1;
            }
            MotorAus = (1.2*t) - MotorAn;
          }

          Serial.println("STEP");
          digitalWrite(stepL,HIGH);
          digitalWrite(stepR,HIGH);
          delayMicroseconds(MotorAn);
          digitalWrite(stepL,LOW);
          digitalWrite(stepR,LOW);
          delayMicroseconds(MotorAus);
        }

        // wird ausgeführt wenn ein Hindernis erkannt wird
        else {
          speed = 0;
          stepsDone = stepsDone - 1;
          delayMicroseconds(100);
          }
              
    }
 }
 


 
 void turnLeft(int steps)
 {
    int speed = 0;
    int a = 0; 
    float MotorAn;
    float MotorAus;
    
    digitalWrite(enableR,LOW); //oder low, habs vergessen
    digitalWrite(enableL,LOW); //oder low, habs vergessen

    digitalWrite(dirL,HIGH);  //oder andersrum
    digitalWrite(dirR,LOW);  //oder andersrum

    //Ativiert die wichtigen Ultraschalsensoren
    frontAnmachen();
    rightAnmachen();
    backAus();
    leftAus();


    
    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )
    {    
        if (digitalRead(5) == LOW)
        {
          digitalWrite(stepL,HIGH);
          digitalWrite(stepR,HIGH);
          delayMicroseconds(100);
          digitalWrite(stepL,LOW);
          digitalWrite(stepR,LOW);
          delayMicroseconds(100);
        }

        // wird ausgeführt wenn ein Hindernis erkannt wird
        else {
          speed = 0;
          stepsDone = stepsDone - 1;
          delayMicroseconds(100);
          }
              
    }
 }



 
 void turnRight(int steps)
 {
    int speed = 0;
    int a = 0; 
    float MotorAn;
    float MotorAus;
    
    digitalWrite(enableR,LOW); //oder low, habs vergessen
    digitalWrite(enableL,LOW); //oder low, habs vergessen

    digitalWrite(dirL,LOW);  //oder andersrum
    digitalWrite(dirR,HIGH);  //oder andersrum

    //Ativiert die wichtigen Ultraschalsensoren
    frontAnmachen();
    leftAnmachen();
    backAus();
    rightAus();


    
    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )
    {    
        if (digitalRead(5) == LOW)
        {
          digitalWrite(stepL,HIGH);
          digitalWrite(stepR,HIGH);
          delayMicroseconds(100);
          digitalWrite(stepL,LOW);
          digitalWrite(stepR,LOW);
          delayMicroseconds(100);
        }

        // wird ausgeführt wenn ein Hindernis erkannt wird
        else {
          speed = 0;
          stepsDone = stepsDone - 1;
          delayMicroseconds(100);
          }
              
    }
 }

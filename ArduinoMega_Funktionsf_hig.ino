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
  servoArm.write(180); // Turn Servo Left to 0 degrees
  delay(500);
  driveForward(1000);
  delay(500);
  servoArm.write(180); // Turn Servo Left to 0 degrees
  delay(500);
  servoArm.write(90); // Turn Servo Left to 0 degrees
  delay(500);
  driveForward(2000);
}


   ////////////////////////////////////////////////////////////////////
  //                           Funktionen                           //
 ///////////////////////////////////////////////////////////////////





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


    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )
    {    
        if (digitalRead(5) == LOW)
        {
/*          if(stepsDone < accelerationPhase && stepsDone <= steps/2) // Acceleration
          {
            a = 100 * 0.0025 *(100 - stepsDone);
            //Serial.println("+");
            //Serial.println(stepsDone);
            //Serial.println(a);
            
          }
  
          if (steps - stepsDone < accelerationPhase && stepsDone > steps / 2) // Decceleration
          {
            a = 100 * 0.0025 * (100 - (steps - stepsDone));
            //Serial.println("-");
            //Serial.println(stepsDone);
            //Serial.println(a);
          }
*/  

          if (speed == 0){
            MotorAn = stepsDone * 0.5;
            if (MotorAn > t)
            { 
                MotorAn = t;
                speed = 1;
            }
            MotorAus = (1.2*t) - MotorAn;
          }


          digitalWrite(stepL,HIGH);
          digitalWrite(stepR,HIGH); 
          delayMicroseconds(MotorAn);
          digitalWrite(stepL,LOW);
          digitalWrite(stepR,LOW);
          delayMicroseconds(MotorAus);
//          delayMicroseconds(t + a);
          Serial.println(t+a);
        }
        else {
          speed = 0;
          stepsDone = stepsDone - 1;
          delayMicroseconds(100);
          }
              
    }
 }

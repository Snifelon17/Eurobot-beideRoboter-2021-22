#include <AccelStepper.h>
#include <Servo.h>
#include <math.h>

#define enableL 8
#define enableR 8

#define stepL 25
#define stepR 34

#define dirL 33
#define dirR 29


#define comF 7
#define comB 6
#define comL 5
#define comR 4

int t = 100; //ms Pause
int accelerationPhase = 100;          // die 100 ersten Steps
int accelerationNummer = 0.0025;      //multiplikator
int stepsDone = 0;
int i = 0;                              //test

bool Falarm = false;
bool Balarm = false;
bool Lalarm = false;
bool Ralarm = false;

bool enabledF = true;
bool enabledB = true;
bool enabledL = true;
bool enabledR = true;



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

  servoWuerfel.attach(11); // servo on digital pin 11
  servoArm.attach(10); // servo on digital pin 10
}

void loop() 
{

  driveForward(2000);
  delay(3000);
  
}


   ////////////////////////////////////////////////////////////////////
  //                           Funktionen                           //
 ///////////////////////////////////////////////////////////////////


// Wenn der pin HIIGH is, ist der dazugehörige Ultraschallsensor aktiviert...
////////////////////////////////////////////////////// AN /////////////////////////////////////////////


void updateAlarm()
{
    if(digitalRead(comF) == HIGH)  
    {
           Falarm = true; 
      
    }
    else if(digitalRead(comF) == LOW)
    {
          Falarm = false;
          
    }    

    //Back    

    else if(digitalRead(comB) == HIGH)  
    {
           Balarm = true; 
      
    }
    else if(digitalRead(comB) == LOW)
    {
          Balarm = false;

    }    

    //Left

    else if(digitalRead(comL) == HIGH)  
    {
           Lalarm = true; 
      
    }
    else if(digitalRead(comL) == LOW)
    {
          Lalarm = false;

    }      


    // Right

    else if(digitalRead(comR) == HIGH)  
    {
           Ralarm = true; 
      
    }
    else if(digitalRead(comR) == LOW)
    {
          Ralarm = false;

    }      

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

    
    

    
    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )
    {    
        if (digitalRead(comF) == LOW)   //Wenn vorne kein Alarm ist
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

    
   
    
    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )
    {    
        if (digitalRead(comB) == LOW)
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

    
    


    
    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )
    {    
        if (digitalRead(7) == LOW)
        {
          Serial.println("STEP");
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

    
    


    
    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )
    {    
        if (digitalRead(7) == LOW)
        {
          Serial.println("STEP");
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

#include <AccelStepper.h>
#include <Servo.h>
#include <math.h>

#define enableL 8
#define enableR 8

#define stepL 25
#define stepR 34

#define dirL 33
#define dirR 29


#define comF 6
#define comB 5
#define comL 4
#define comR 4

int t = 80; //ms Pause  
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
  // driveBackwards(2000);
  // delay(3000);
  // turnLeft(5000);
  // delay(3000);
  
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
    
    int accelerationPhase = 200;          // die 100 ersten Steps
    int a = 0; 
    
    digitalWrite(enableR,LOW); //oder low, habs vergessen
    digitalWrite(enableL,LOW); //oder low, habs vergessen

    digitalWrite(dirL,LOW);  //oder andersrum
    digitalWrite(dirR,LOW);  //oder andersrum

    
    Serial.println(digitalRead(comF));

    
    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )
    {    
        if (digitalRead(comF) == LOW)   //Wenn vorne kein Alarm ist
        {

          Serial.println("STEP");
          digitalWrite(stepL,HIGH);
          digitalWrite(stepR,HIGH);
          delayMicroseconds(t+accelerationPhase);
          if (accelerationPhase > 0) 
          {
              accelerationPhase--;              
          }
          digitalWrite(stepL,LOW);
          digitalWrite(stepR,LOW);
          delayMicroseconds(t+accelerationPhase);
        }

        // wird ausgeführt wenn ein Hindernis erkannt wird
        else {
          accelerationPhase = 200; 
          stepsDone = stepsDone - 1;
          delay(10);
          }
              
    }
 }



 
 void driveBackwards(int steps)
 {
    
    
    int accelerationPhase = 200; 
    int a = 0; 
    
    digitalWrite(enableR,LOW); //oder low, habs vergessen
    digitalWrite(enableL,LOW); //oder low, habs vergessen

    digitalWrite(dirL,HIGH);  //oder andersrum
    digitalWrite(dirR,HIGH);  //oder andersrum

    
   
    
    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )
    {    
        if (digitalRead(comB) == LOW)
        {

          Serial.println("STEP");
          digitalWrite(stepL,HIGH);
          digitalWrite(stepR,HIGH);
          delayMicroseconds(t+accelerationPhase);
          if (accelerationPhase > 0) 
          {
              accelerationPhase--;              
          }
          digitalWrite(stepL,LOW);
          digitalWrite(stepR,LOW);
          delayMicroseconds(t+accelerationPhase);
        }

        // wird ausgeführt wenn ein Hindernis erkannt wird
        else {
          stepsDone = stepsDone - 1;
          delay(10);
          int accelerationPhase = 200; 
          }
              
    }
 }
 


 
 void turnLeft(int steps)
 {

        
    int accelerationPhase = 200; 
    int a = 0; 
    
    digitalWrite(enableR,LOW); //oder low, habs vergessen
    digitalWrite(enableL,LOW); //oder low, habs vergessen

    digitalWrite(dirL,HIGH);  //oder andersrum
    digitalWrite(dirR,LOW);  //oder andersrum

    
    


    
    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )
    {    
        if (digitalRead(comF) == LOW && digitalRead(comL) == LOW)
        {
          Serial.println("STEP");
          digitalWrite(stepL,HIGH);
          digitalWrite(stepR,HIGH);
          delayMicroseconds(t+accelerationPhase);
          if (accelerationPhase > 0) 
          {
              accelerationPhase--;              
          }
          digitalWrite(stepL,LOW);
          digitalWrite(stepR,LOW);
          delayMicroseconds(t+accelerationPhase);
        }

        // wird ausgeführt wenn ein Hindernis erkannt wird
        else {
          int accelerationPhase = 200; 
          stepsDone = stepsDone - 1;
          delay(10);
          }
              
    }
 }



 
 void turnRight(int steps)
 {
  
  
    int accelerationPhase = 200; 
    int a = 0; 
    
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
          delayMicroseconds(t+accelerationPhase);
          if (accelerationPhase > 0) 
          {
              accelerationPhase--;              
          }
          digitalWrite(stepL,LOW);
          digitalWrite(stepR,LOW);
          delayMicroseconds(t+accelerationPhase);
        }

        // wird ausgeführt wenn ein Hindernis erkannt wird
        else {
          int accelerationPhase = 200; 
          stepsDone = stepsDone - 1;
          delay(100);
          }
              
    }
 }

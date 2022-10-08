#include <AccelStepper.h>
#include <Servo.h>
#include <math.h>
#include <TimerOne.h>

#define enableL 8         // Enable Pins, beide Motoren haben den selben Enable Pin
#define enableR 8

#define stepL 25          //Beide Step Pins, pro Intervall ein Schritt
#define stepR 34

#define dirL 33       //Direction Pin des linken Motors
#define dirR 29


#define comF 6        // Kommunikation-Pins, wenn einer der Pins high ist,
#define comB 5        // meldet der dazugehörig Sensor Alarm
#define comL 4
#define comR 4

#define startPin 7

int t = 50; //ms Pause         // Zeit, die zwischen 2 Steps des Stepper Motors vergeht
int stepsDone = 0;             // gemachte Schritte einer Funktion driveX
int timeElapsed;

bool enabledF = true;           //Wenn man einzelne Ultraschall- Sensoren auschalten will, müssen diese Werte auf false gesetzt werden
bool enabledB = true;
bool enabledL = true;
bool enabledR = true;

bool zeitZuEnde = false;


Servo servoArm;                 //Defininert die beiden Servomotoren
Servo servoWuerfel;


   ///////////////////////////////////////////////////////////////////
  //                           SETUP                               //
 ///////////////////////////////////////////////////////////////////


void setup() //Hier beginnt das Setup.
{
  Serial.begin(9600);       //Serielle Geschwindigkeit festlegen
  pinMode(8, OUTPUT);  
  pinMode(25, OUTPUT);
  pinMode(34, OUTPUT);  
  pinMode(33, OUTPUT);
  pinMode(29, OUTPUT);

  pinMode(startPin, INPUT_PULLUP);    

  digitalWrite(enableR,HIGH);           //beide Enable Pins auf high, sodass keine falschen Bewegungen passieren können
  digitalWrite(enableL,HIGH); 

  servoWuerfel.attach(11); // servo auf digital pin 11
  servoArm.attach(10); // servo auf digital pin 10
  servoArm.write(180);  
  servoWuerfel.write(75);

  while(!digitalRead(startPin)) 
  {
    delay(100);
  }
  Timer1.initialize(1000000);
  Timer1.start();
  Timer1.attachInterrupt(startCountdown);
}
void startCountdown()
{
  timeElapsed++;
  if (timeElapsed > 95)
  { 
    digitalWrite(enableR,HIGH);           //beide Enable Pins auf high, sodass keine falschen Bewegungen passieren können
    digitalWrite(enableL,HIGH); 
    zeitZuEnde = true;
  }
}

   ////////////////////////////////////////////////////////////////////
  //                           Loop                                //
 ///////////////////////////////////////////////////////////////////


void loop() 
{
  
    driveForward(100);
    delay(100);
    driveBackwards(100);
    delay(1000);
    turnLeft(2000);
     
  
  
  //teamLila();
//  teamGelb();
}


   ////////////////////////////////////////////////////////////////////
  //                           Funktionen                           //
 ///////////////////////////////////////////////////////////////////

void teamLila() {
  driveForward(500);
  servoArmDrehen(90);
  driveForward(50);
  turnLeft(80);
  driveForward(50);
  turnLeft(80);
  driveForward(200); 
  enabledF = false;  
  driveForward(30);
  delay(1000);  
    
}

void teamGelb(){
  
}

void ArmTest()
{
  servoArmDrehen(180);    //startposition von Schieber
  delay(1000);
  servoWuerfelDrehen(75);   //Startposition vom Würfelarm
  delay(1000);
  servoArmDrehen(90);    //Ausgefahrener Schieber
  delay(1000);
  servoWuerfelDrehen(180);      //Ausgefahrener Würfelarm 
  delay(1000);
  servoWuerfelDrehen(75);
  delay(1000);
}

void servoArmDrehen(int winkel)
{
  if (zeitZuEnde == false) {
    servoArm.write(winkel);
  }
}

void servoWuerfelDrehen(int winkel)
{
  if (zeitZuEnde == false) {
    servoWuerfel.write(winkel);
  }
}

 void driveForward(int strecke)
 {
    //1000 steps sind 26 cm       3846 steps sind 80 cm

    int steps = strecke/80 *3846;
    int accelerationPhase = 200;          // die 100 ersten Steps
    int a = 0; 
    
    digitalWrite(enableR,LOW);          //beide Enable pins auf low, sodass sie sich bewegen können
    digitalWrite(enableL,LOW); 

    digitalWrite(dirL,LOW);             //Hier wird die Richtung des Motors festgelegt
    digitalWrite(dirR,LOW);  

    
    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )       // Für jeden Schritt
    {    
        if (digitalRead(comF) == LOW || enabledF == false)   //Wenn vorne kein Alarm ist
        {

          Serial.println("STEP");                           //Schritt
          digitalWrite(stepL,HIGH);
          digitalWrite(stepR,HIGH);
          delayMicroseconds(t+accelerationPhase);
          if (accelerationPhase > 0)                      //Wenn die Beschleunigung noch nicht vorbei ist, mache die Geschwindikeit höher
          {
              accelerationPhase--;              
          }
          digitalWrite(stepL,LOW);
          digitalWrite(stepR,LOW);
          delayMicroseconds(t+accelerationPhase);
        }   
        else {                                           // wird ausgeführt wenn ein Hindernis erkannt wird 
          accelerationPhase = 200; 
          stepsDone = stepsDone - 1;
          delay(10);
          }
              
    }
 }



 
 void driveBackwards(int strecke)
 {
    
    int steps = strecke/26 *1000;
    int accelerationPhase = 200; 
    int a = 0; 
    
    digitalWrite(enableR,LOW); //oder low, habs vergessen
    digitalWrite(enableL,LOW); //oder low, habs vergessen

    digitalWrite(dirL,HIGH);  //oder andersrum
    digitalWrite(dirR,HIGH);  //oder andersrum

    
   
    
    for( stepsDone = 0; stepsDone < steps ; stepsDone++ )
    {    
        if (digitalRead(comB) == LOW || enabledB == false)
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
        if (digitalRead(comF) == LOW && digitalRead(comR) == LOW   ||
            enabledF == false && enabledR == false                 ||
            digitalRead(comF) == LOW && enabledR == false          ||
            digitalRead(comR) == LOW && enabledF == false
          )
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
        if (digitalRead(comF) == LOW && digitalRead(comL) == LOW   ||
            enabledF == false && enabledL == false                 ||
            digitalRead(comF) == LOW && enabledL == false          ||
            digitalRead(comL) == LOW && enabledF == false
          )
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

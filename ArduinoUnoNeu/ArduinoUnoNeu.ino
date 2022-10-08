
/*
F = front
B= back
L = left
R = right

*/

#include <math.h>


#define triggerF 6 //Change
#define echoF 4    //Change

#define triggerB 10 //Change
#define echoB 8    //Change

#define triggerR 5 //Change
#define echoR 12    //Change

#define triggerL 9 //Change
#define echoL 7    //Change

//#define datetransfer 11 // 11, aber zu deaktivierung auf 15 geändert

#define comF 11
#define comB 3
#define comL 2
#define comR 2


// Init Supersonice front


long dauerF = 0;
long entfernungF = 0;


// Init Supersonice back


long dauerB = 0;
long entfernungB = 0;


// Init Supersonice left

long dauerL = 0;
long entfernungL = 0;


// Init Supersonice right

long dauerR = 0;
long entfernungR = 0;



 

void setup() 
{

  Serial.begin (9600);
  Serial.begin (9600);
  
  pinMode(triggerF, OUTPUT);
  pinMode(echoF, INPUT);

  pinMode(triggerB, OUTPUT);
  pinMode(echoB, INPUT);

  pinMode(triggerL, OUTPUT);
  pinMode(echoL, INPUT);

  pinMode(triggerR, OUTPUT);
  pinMode(echoR, INPUT);
  
}

void loop() {
  checkBack();
  checkFront();
  checkLeft();
  checkRight();
  delay(100);
}  
///////////////////////////////////////////////////////////////////////////////







void checkFront()
{
  digitalWrite(triggerF, LOW);
  delay(5);
  digitalWrite(triggerF, HIGH);
  delay(10);
  digitalWrite(triggerF, LOW);
  dauerF = pulseIn (echoF, HIGH);
  entfernungF = dauerF/2*0.03432;
  Serial.println (entfernungF);

  if (entfernungF < 25)
  {
    digitalWrite(comF, HIGH);
    delay(10);
    Serial.println("Alarm")  ;
    
    
  }
  else
  {
        digitalWrite(comF, LOW);
  }
    
}

///////////////////////////////////////////////////////////////////////////////////////

void checkBack()
{
  digitalWrite(triggerB, LOW);
  delay(5);
  digitalWrite(triggerB, HIGH);
  delay(10);
  digitalWrite(triggerB, LOW);
  dauerB = pulseIn (echoB, HIGH);
  entfernungB = dauerB/2*0.03432;
  Serial.println (entfernungB);

  if (entfernungB < 20)  // && enabledB == true
  {
    digitalWrite(comB, HIGH);
    delay(10);
    Serial.println("Alarm")  ;
    
     
  }
  else
  {
      digitalWrite(comB, LOW);
      Serial.println("Entwarnung");
      
  }
    
}

///////////////////////////////////////////////////////////////////////////////////

void checkLeft()
{
  digitalWrite(triggerL, LOW);
  delay(5);
  digitalWrite(triggerL, HIGH);
  delay(10);
  digitalWrite(triggerL, LOW);
  dauerL = pulseIn (echoL, HIGH);
  entfernungL = dauerL/2*0.03432;
  Serial.println (entfernungL);

  if (entfernungL < 20 )
  {
    digitalWrite(comL, HIGH);
    delay(10);
    Serial.println("Alarm")  ; 
  
    
  }
  else
  {
      digitalWrite(comL, LOW);
  }
    
}

////////////////////////////////////////////////////////////////////////////////

void checkRight()
{
  digitalWrite(triggerR, LOW);
  delay(5);
  digitalWrite(triggerR, HIGH);
  delay(10);
  digitalWrite(triggerR, LOW);
  dauerR = pulseIn (echoR, HIGH);
  entfernungR = dauerR/2*0.03432;
  Serial.println (entfernungR);

  if (entfernungR < 20 )
  {
    digitalWrite(comR, HIGH);
    delay(10);
    Serial.println("Alarm")  ; 
  
    
  }
  else
  {
      digitalWrite(comR, LOW);
  }
    
}

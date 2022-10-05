
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
#define echoR 100    //Change

#define triggerL 9 //Change
#define echoL 7    //Change

#define datetransfer 11

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




int enabledF = true;
int enabledB = true;
int enabledR = true;
int enabledL = true;
 

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
  checkFront();
  checkBack();
  checkLeft();
  //checkRight();
  //checkStatus();
  //Serial.println("Check") ; 
  delay(500);
  //Serial.println(enabledB);

}


////////////////////////////////////////////////////////////////////////////////

void checkStatus()
{
    if (Serial.available() > 0)
    {
      int empfangen = Serial.read();
      //Serial.println(empfangen);
      if(empfangen == 1)
      {
          enabledF = false;  
      }
      else if(empfangen == 2)
      {
          enabledB = false;  
      }
      else if(empfangen == 3)
      {
          enabledL = false;  
      }
      else if(empfangen == 4)
      {
          enabledR = false;  
      }


      else if(empfangen == 11)
      {
          enabledF = true;  
      }
      else if(empfangen == 12)
      {
          enabledB = true;  
      }
      else if(empfangen == 13)
      {
          enabledL = true;  
      }
      else if(empfangen == 14)
      {
          enabledR = true;  
      }
       
    }
}








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

  if (entfernungF < 30 && enabledF == true)
  {
    digitalWrite(datetransfer, HIGH);
    delay(10);
    Serial.println("Alarm")  ;
    checkStatus();
    checkFront();
    
  }
  else
  {
      digitalWrite(datetransfer, LOW);
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

  if (entfernungB < 30 && enabledB == true)
  {
    digitalWrite(datetransfer, HIGH);
    delay(10);
    Serial.println("Alarm")  ;
    checkStatus();
    checkBack();
     
  }
  else
  {
      digitalWrite(datetransfer, LOW);
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

  if (entfernungL < 30 && enabledL == true)
  {
    digitalWrite(datetransfer, HIGH);
    delay(10);
    Serial.println("Alarm")  ; 
    checkStatus();
    checkLeft();
    
  }
  else
  {
      digitalWrite(datetransfer, LOW);
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

  if (entfernungR < 30 && enabledR == true)
  {
    digitalWrite(datetransfer, HIGH);
    delay(10);
    Serial.println("Alarm")  ; 
    checkStatus();
    checkRight();
    
  }
  else
  {
      digitalWrite(datetransfer, LOW);
  }
    
}

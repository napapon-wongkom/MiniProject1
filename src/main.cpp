#include <Arduino.h>

#define STEP_PIN_1 19
#define STEP_PIN_2 18
#define STEP_PIN_3 17
#define STEP_PIN_4 16
//////////////////////////////////////////////////////////////////////////////
//Variable Zone//
String Key = "";  
int mem=0;
/////////////////////////////////////////////////////////////////////////////
void Step_Drive(){
    digitalWrite(STEP_PIN_1,HIGH);
    digitalWrite(STEP_PIN_2,LOW);
    digitalWrite(STEP_PIN_3,LOW);
    digitalWrite(STEP_PIN_4,LOW);
    delay(3);
    digitalWrite(STEP_PIN_1,LOW);
    digitalWrite(STEP_PIN_2,HIGH);
    digitalWrite(STEP_PIN_3,LOW);
    digitalWrite(STEP_PIN_4,LOW);
    delay(3);
    digitalWrite(STEP_PIN_1,LOW);
    digitalWrite(STEP_PIN_2,LOW);
    digitalWrite(STEP_PIN_3,HIGH);
    digitalWrite(STEP_PIN_4,LOW);
    delay(3);
    digitalWrite(STEP_PIN_1,LOW);
    digitalWrite(STEP_PIN_2,LOW);
    digitalWrite(STEP_PIN_3,LOW);
    digitalWrite(STEP_PIN_4,HIGH);
    delay(3);
}

void Step_Drive_Reverse(){
    digitalWrite(STEP_PIN_4,HIGH);
    digitalWrite(STEP_PIN_3,LOW);
    digitalWrite(STEP_PIN_2,LOW);
    digitalWrite(STEP_PIN_1,LOW);
    delay(3);
    digitalWrite(STEP_PIN_4,LOW);
    digitalWrite(STEP_PIN_3,HIGH);
    digitalWrite(STEP_PIN_2,LOW);
    digitalWrite(STEP_PIN_1,LOW);
    delay(3);
    digitalWrite(STEP_PIN_4,LOW);
    digitalWrite(STEP_PIN_3,LOW);
    digitalWrite(STEP_PIN_2,HIGH);
    digitalWrite(STEP_PIN_1,LOW);
    delay(3);
    digitalWrite(STEP_PIN_4,LOW);
    digitalWrite(STEP_PIN_3,LOW);
    digitalWrite(STEP_PIN_2,LOW);
    digitalWrite(STEP_PIN_1,HIGH);
    delay(3);
}

int set_zero(int mem){
  if(mem == 4){
    for (int i = 0; i < 128; i++)
      {
        Step_Drive_Reverse();
      }
      return 0;
  }else if(mem == 3){
    for (int i = 0; i < 85; i++)
      {
        Step_Drive_Reverse();
      }
      return 0;
  }else if(mem == 2){
    for (int i = 0; i < 64; i++)
      {
        Step_Drive_Reverse();
      }
      return 0;
  }else if(mem == 1){
    for (int i = 0; i < 43; i++)
      {
        Step_Drive_Reverse();
      }
      return 0;
  }else if(mem == 0){
      return 0;
  }
  //Serial.println("Reverse");
}
//////////////////////////////////////////////////////////////////////////////
void setup(){
    
}
//////////////////////////////////////////////////////////////////////////////
void loop(){  
    pinMode(STEP_PIN_1,OUTPUT);
    pinMode(STEP_PIN_2,OUTPUT);
    pinMode(STEP_PIN_3,OUTPUT);
    pinMode(STEP_PIN_4,OUTPUT);
  
    Serial.begin(9600);
    Serial.println("Enter Key:");  
    while (Serial.available() == 0)   { }  
    Key = Serial.readString(); //Reading the Input string from Serial port.  
    
    Serial.println("-------------------------"); //Showing the details 
    ////////////////////////////////////////////////////////////////////////
    if(Key == "4"){
      set_zero(mem);
      Serial.println("90 Degree");
      for (int i = 0; i < 128; i++)
      {
        Step_Drive();
      }
      mem = 4;
      
    }else if (Key == "3")
    {
      Serial.println("60 Degree");
      set_zero(mem);
      for (int i = 0; i < 85; i++)
      {
        Step_Drive();
      }
      mem = 3;
    }else if(Key == "2"){
      Serial.println("45 Degree");
      set_zero(mem);
      for (int i = 0; i < 64; i++)
       {
         Step_Drive();
       }
      mem = 2;
    }else if(Key == "1"){
      Serial.println("30 Degree");
      set_zero(mem);
      for (int i = 0; i < 43; i++)
      {
        Step_Drive();
      }
      mem = 1;
    }else if(Key == "0"){
      Serial.println("0 Degree");
      set_zero(mem);
      mem = 0;
    }else if(Key == "00"){
      Serial.println("Terminate");
      set_zero(mem);
      while (true){

      }
      mem = 0;
      
    }else{
      Serial.println("Wrong Key!");
    }
    /////////////////////////////////////////////////////////////////////////
    while (Serial.available() == 0) {}    
}  
  



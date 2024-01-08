#include <Arduino.h>
#include <WiFi.h>
#include <MQTT.h>
#include <string.h>
#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2);
//////////////////////////////////////////////////////////////////////////////
#define STEP_PIN_1 19
#define STEP_PIN_2 18
#define STEP_PIN_3 17
#define STEP_PIN_4 16
//////////////////////////////////////////////////////////////////////////////
//Variable Zone//
//String Key = "";   -----------------Doesn't use!
int mem=0;
/// MQTT SETUP VAR////////////////////////////////////////////////////////////
const char ssid[] = "Imyourjay";
const char pass[] = "aleecha0909";

const char mqtt_broker[]="test.mosquitto.org";
const char mqtt_topic[]="group1.43/control";
const char mqtt_publish[]="group1.43/recieve";
const char mqtt_client_id[]="arduino_group_1.43"; // must change this string to a unique value
int MQTT_PORT=1883;

WiFiClient net;
MQTTClient client;
/////////////////////////////////////////////////////////////////////////////
void connect() {
  lcd.clear();
  lcd.println("checking wifi...");
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  lcd.clear();
  Serial.print("\nconnecting...");
  lcd.print("connecting...");
  while (!client.connect(mqtt_client_id)) {  
    Serial.print(".");
    delay(1000);
  }

  lcd.clear();
  Serial.println("\nconnected!");
  lcd.print("connected!");
  client.subscribe(mqtt_topic);
  // client.unsubscribe("/hello");
}

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

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: "+ payload);
  lcd.clear();
  delay(500);
  lcd.print("incoming: "+ payload);
  delay(1000);
  ////////////////////////////////////////////Subscribe here!//////////////////////////////////////////////
  if(String(payload) == "4"){
      set_zero(mem);
      lcd.clear();
      Serial.println("90 Degree");
      lcd.print("90 Degree");
      client.publish(mqtt_publish,"90 Degree");
      for (int i = 0; i < 128; i++)
      {
        Step_Drive();
      }
      mem = 4;
      
    }else if (String(payload) == "3")
    {
      lcd.clear();
      Serial.println("60 Degree");
      lcd.print("60 Degree");
      set_zero(mem);
      client.publish(mqtt_publish,"60 Degree");
      for (int i = 0; i < 85; i++)
      {
        Step_Drive();
      }
      mem = 3;
    }else if(String(payload) == "2"){
      lcd.clear();
      Serial.println("45 Degree");
      lcd.print("45 Degree");
      client.publish(mqtt_publish,"45 Degree");
      set_zero(mem);
      for (int i = 0; i < 64; i++)
       {
         Step_Drive();
       }
      mem = 2;
    }else if(String(payload) == "1"){
      lcd.clear();
      Serial.println("30 Degree");
      lcd.print("30 Degree");
      client.publish(mqtt_publish,"30 Degree");
      set_zero(mem);
      for (int i = 0; i < 43; i++)
      {
        Step_Drive();
      }
      mem = 1;
    }else if(String(payload) == "0"){
      lcd.clear();
      Serial.println("0 Degree");
      lcd.print("0 Degree");
      client.publish(mqtt_publish,"0 Degree");
      set_zero(mem);
      mem = 0;
    }else if(String(payload) == "00"){
      lcd.clear();
      Serial.println("Terminate");
      lcd.print("Terminate!");
      client.publish(mqtt_publish,"Terminated!");
      set_zero(mem);
      while (true){

      }
      mem = 0;
    }
}
//////////////////////////////////////////////////////////////////////////////
void setup(){
    pinMode(STEP_PIN_1,OUTPUT);
    pinMode(STEP_PIN_2,OUTPUT);
    pinMode(STEP_PIN_3,OUTPUT);
    pinMode(STEP_PIN_4,OUTPUT);
    Serial.begin(9600);
    WiFi.begin(ssid, pass);
    client.begin(mqtt_broker, MQTT_PORT, net);
    client.onMessage(messageReceived);
{
    lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                 // this stop the library(LCD_I2C) from calling Wire.begin()
    lcd.backlight();
}

    connect();
}
//////////////////////////////////////////////////////////////////////////////
void loop(){  
    client.loop();
    delay(10);  // <- fixes some issues with WiFi stability
    
    if (!client.connected()) {
      connect();
    }
}  
  



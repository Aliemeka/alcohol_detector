/*
 * Alcohol Sensor Project
 * using MQ3 alcohol sensor and an Lcd display
 * 
 * 
 */

#include<LiquidCrystal.h>

LiquidCrystal lcd(5,6,7,8,9,10);

const int sensorInput = A0; //alcohol sensor analog input
float alcoholinput; //analog value of the sensor input
float alcoholvolt;  //voltage value of the sensor input
float alcohollevel;  //calculated alcohol level
int alcoholguage=50;
const int alcoholdetect=2; //
const int buzzer=3;

void setup() {

  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Alcohol Level");

  pinMode(buzzer,OUTPUT);
  pinMode(alcoholdetect,INPUT);
  //digitalWrite(buzzer,LOW);

}

void loop() {

  float RS;
  float RO;
  float Ps;
 
  for(int i=0;i<100;i++){
    alcoholinput=alcoholinput+analogRead(sensorInput);
  }
  alcoholinput=alcoholinput/100;
  alcoholvolt= (alcoholinput/1024)*5.0;
  
  RS = (5.0-alcoholvolt)/alcoholvolt;//alcoholvolt;
  RO=0.15;
  float J = RS/RO;
  //Ps= (25.0*RS)/((RS+36)*(RS+36))*100;
  if(J>0.7&&J<=1){
    alcohollevel=1.4-(0.25*J);
    Serial.print(" Alcohol level: ");
    Serial.print(alcohollevel);
  }
  
 
  
  Serial.print(alcoholinput);
  Serial.print(" Output voltage:");
  Serial.print(alcoholvolt);
  Serial.print(" RS/RO: ");
  Serial.print(RS/RO);
  Serial.print(" RS: ");
  Serial.println(RS);
  //Serial.print(" PS: ");
  //Serial.println(Ps);
  
  lcd.setCursor(0,1);
  lcd.print(RS/RO);

  int alcohol=digitalRead(alcoholdetect);
  delay(100);
  
  if(alcohol==0){
      digitalWrite(buzzer,HIGH);
      Serial.println("HIGH");
      delay(1000);
      digitalWrite(buzzer,LOW);
      lcd.setCursor(6,1);
      lcd.print("AL. HIGH");  
  }
  else{
    delay(500);
    digitalWrite(buzzer,LOW);
    lcd.setCursor(6,1);
    lcd.print("        ");
  }
  delay(500);

}

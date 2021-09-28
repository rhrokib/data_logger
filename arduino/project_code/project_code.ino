#include <LiquidCrystal.h>
#include <stdio.h>
#include <String.h>
#include <dht.h>


// pins and setup
int sonar_echo = 9;
int sonar_trig = 10;
int ldr = A5;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
dht DHT;

void setup() {
  Serial.begin(9600);
  pinMode(sonar_echo, INPUT);
  pinMode(sonar_trig, OUTPUT);
}

long getDistance(){
  digitalWrite(sonar_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(sonar_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonar_trig, LOW);
  long duration = pulseIn(sonar_echo, HIGH);
  long distance = (duration*0.034)/2;
  return distance;
}

int getTemperature(){
  return DHT.temperature;
}

int getHumidity(){
  return DHT.humidity;
}

float getLightIntensity(){
  return analogRead(ldr);  
}

void sendToCloud(){
  String data = String(getDistance()) + "," + String(DHT.temperature) + "," + String(DHT.humidity) + "," + String(getLightIntensity());
  Serial.print(data);
}


void display(){
  long distance = getDistance();
  float intensity = getLightIntensity();
  lcd.begin(16,4);
  lcd.setCursor(0,0);
  lcd.print("Distance : " + String(distance) + "CM");

  lcd.setCursor(0,1);
  DHT.read22(8);
  lcd.print("Temp     : " + String(DHT.temperature) + "C");

  lcd.setCursor(0,2);
  lcd.print("Humidity : " + String(DHT.humidity) +  "%");

  lcd.setCursor(0,3);
  lcd.print("LUX      : " + String(intensity) + " lx");

}
void loop() {
  display();
  sendToCloud();
  delay(2000);
}

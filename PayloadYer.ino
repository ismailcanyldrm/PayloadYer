#include "LoRa_E32.h"
#include <SoftwareSerial.h>

SoftwareSerial lora(11,10);
LoRa_E32 E32(&lora);
 
struct Signal {

    byte gaz1[4];
    byte gaz2[4];
    byte t[4];
    byte p[4];
    byte h[4];
    byte gpsE[4];
    byte gpsB[4];
    byte gpsH[4];
    byte gpsS[4];
    
} data;
void setup() {
  Serial.begin(9600);
  E32.begin(); 
  pinMode(13,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  
}
void loop() {
    while (E32.available() > 1) {
    ResponseStructContainer rsc = E32.receiveMessage(sizeof(Signal));
    struct Signal data = *(Signal*) rsc.data;
    rsc.close();


    Serial.print(*(int*)(data.gaz1));  Serial.print("* ");
    Serial.print(*(int*)(data.gaz2));  Serial.print("* ");
    Serial.print(*(float*)(data.t),2);      Serial.print("* "); 
    Serial.print(*(float*)(data.p),2);      Serial.print("* ");
    Serial.print(*(float*)(data.h),2);      Serial.print("* "); 
    Serial.print(*(float*)(data.gpsE),6);   Serial.print("* ");
    Serial.print(*(float*)(data.gpsB),6);   Serial.print("* ");
    Serial.print(*(float*)(data.gpsH),2);   Serial.print("* ");
    Serial.print(*(float*)(data.gpsS),2);   Serial.println("* ");
    }   
}

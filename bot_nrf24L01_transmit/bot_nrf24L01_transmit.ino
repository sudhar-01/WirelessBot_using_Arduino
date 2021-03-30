#include "RF24.h"
#include<nRF24L01.h>
#include<SPI.h>
RF24 radio(7,8);
const byte addr[6] = "00001"; 
int s1;
int s2;
void setup() {
//Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addr);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  }
void loop(){
  String in;
  char txt[10];
  int x = analogRead(0);
  int y = analogRead(1);
  String xaxis = String(x);
  String yaxis = String(y);
  in = xaxis + "," + yaxis;
  in.toCharArray(txt,10);
  radio.write(&txt,sizeof(txt));
//Serial.println(txt);
  delay(100);
}

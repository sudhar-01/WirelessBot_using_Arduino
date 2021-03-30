#include "RF24.h"
#include<nRF24L01.h>
#include<SPI.h>
RF24 radio(7,8);
const byte addr[6] = "00001";   
int s1;
int s2;
void setup() {
 Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,addr);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
}
void loop(){
  char txt[10];
  if(radio.available()){
    radio.read(&txt,sizeof(txt));
    Serial.println(txt);
    int n=0;
    String s = String(txt);
    
    for(int i=0;i<10;i++){
      if(txt[i] == ','){
        n=i;
        break;
  }
 }
  int x = s.substring(0,n).toInt();
  int y = s.substring(n+1,10).toInt();
  
  if(x<504){
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(2,LOW);
    s1 = map(x,503,0,0,255);
    if(y<489){
      s2 = map(y,488,0,0,255);
      analogWrite(5,s1);
      analogWrite(6,s2);
     }
    else if(y>=510){
      s2 = map(y,510,1023,0,255);
      analogWrite(5,s2);
      analogWrite(6,s1);
    }
    else{
      analogWrite(5,s1);
      analogWrite(6,s1);
    }
  }
 else if(x>524) {
  delay(10);
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(2,HIGH);
    s1 = map(x,525,1023,0,255);
    if(y<489){
      s2 = map(y,488,0,0,255);
      analogWrite(5,s1);
      analogWrite(6,s2);
    }
    else if(y>=510){
      s2 = map(y,510,1023,0,255);
      analogWrite(5,s2);
      analogWrite(6,s1);
    }
    
    else{
      analogWrite(5,s1);
      analogWrite(6,s1);
    }
  }
  else {
    analogWrite(5,0);
    analogWrite(6,0);
  }
}
else Serial.println(".");
 delay(100);
}

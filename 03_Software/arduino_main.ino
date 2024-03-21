#include <stdio.h>
#include <NewPing.h>

#define NVIDIA 6
#define SIGNAL 5

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

int NVIDIA_RS;
int ultrasonic_o;
int ultrasonic_rs;
const int dirPin = 4;
const int enPin = 8;
const int stepPin = 3;
const int bir_turdaki_adim = 400;



void setup() {

  Serial.begin(115200);
  pinMode(NVIDIA,INPUT);
  pinMode(SIGNAL,OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  digitalWrite(SIGNAL,LOW);

  NVIDIA_RS = digitalRead(NVIDIA) ;


  while(NVIDIA_RS == 1){

    NVIDIA_RS = digitalRead(NVIDIA);
  
  }

}

void loop() {

  NVIDIA_RS = digitalRead(NVIDIA); 
   
  if(NVIDIA_RS == 1){

    ultrasonic_o = 0;
    
    while(ultrasonic_o != 1){

      digitalWrite(dirPin, HIGH);

      // 1 turdaki adım sayısı kadar adım attırıp 360 derece döndürüyoruz
      for(int x = 0; x < bir_turdaki_adim; x++){
        
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(500);
      }

      ultrasonic_rs = sonar.ping_cm();

      //Serial.println(ultrasonic_rs);

      if(ultrasonic_rs<=14){

        ultrasonic_o = 1;

      }else {

        ultrasonic_o = 0;

      }
    }


    for(int x = 0; x < 1200; x++){
        
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
      
    }
    delay(100);

    digitalWrite(SIGNAL,HIGH);
    delay(100);
    digitalWrite(SIGNAL,LOW);

    NVIDIA_RS = digitalRead(NVIDIA);

    while(NVIDIA_RS == 0){

      NVIDIA_RS = digitalRead(NVIDIA);

    }

    ultrasonic_o = 0;

    while(ultrasonic_o != 1){

      Serial.println("Second loop");

      Serial.println(ultrasonic_rs);

      for(int x = 0; x < 2400; x++){  
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(500);
      }

      ultrasonic_rs = sonar.ping_cm();

      if(ultrasonic_rs<=14){

        ultrasonic_o = 0;

      }else {

        ultrasonic_o = 1;

      }
      
    }

    digitalWrite(SIGNAL,HIGH);
    delay(100);
    digitalWrite(SIGNAL,LOW);

    Serial.println("durdum");
    
       
  }else {

  }
}

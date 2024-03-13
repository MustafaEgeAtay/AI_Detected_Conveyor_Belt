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
const int dirPin = 3;
const int stepPin = 4;
const int bir_turdaki_adim = 1080;



void setup() {

  Serial.begin(115200);
  pinMode(NVIDIA,INPUT);
  pinMode(SIGNAL,OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  NVIDIA_RS = 0;

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
        delayMicroseconds(300);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(300);
      }

      ultrasonic_rs = sonar.ping_cm();

      if(ultrasonic_rs<4){

        ultrasonic_o = 1;

      }else {

        ultrasonic_o = 0;

      }
    }


    for(int x = 0; x < 180; x++){
        
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(300);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(300);
      
    }

    digitalWrite(SIGNAL,HIGH);
    delay(1000);
    digitalWrite(SIGNAL,LOW);

    NVIDIA_RS = digitalRead(NVIDIA);

    while(NVIDIA_RS==0){

      NVIDIA_RS = digitalRead(NVIDIA);

    }

    for(int x = 0; x < 360; x++){
        
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(300);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(300);
      
    }   
  }else {}
}

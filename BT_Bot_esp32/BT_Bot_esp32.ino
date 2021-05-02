// SWARM BOTS STAND ALONE bt CONTROL 
// Modifyed for esp32 by ThaBoom
// ARDUINO BLUETOOTH RC CAR APP FOR ANDROID 
 
//Pin numbers definition  esp32 d1r32 board

const int motorEnableLeft = 13;
const int motorForwardLeft = 14;
const int motorBackLeft = 12;
const int motorEnableRight = 23;
const int motorForwardRight = 15;
const int motorBackRight = 5;
const int trigPinFront = 4;
const int echoPinFront = 26;
const int trigPinLeft = 25;
const int echoPinLeft = 17;
const int trigPinRight = 16;
const int echoPinRight = 27;
const int irPin = 2;
const int NEOIO = 38;

//RGB LED pins
const int LEDred = 18;
const int LEDgreen = 36;
const int LEDblue = 34;

  
//Variables for the Motors
const int leftMotorSpeed = 200;
const int rightMotorSpeed = 200;
const int delayTime = 150;

//Bluetooth esp32
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

// Use it to make a delay... without delay() function!
long previousMillis = -1000*10;// -1000*10=-10sec. to read the first value. If you use 0 then you will take the first value after 10sec.  
long interval = 1000*10;       // interval at which to read battery voltage, change it if you want! (10*1000=10sec)
unsigned long currentMillis;   //unsigned long currentMillis;
  
//Useful Variables
int i=0;
int j=0;
int state;
  
 void BOT_Stop() {
  digitalWrite(motorForwardLeft, LOW);
  digitalWrite(motorBackLeft, LOW);
  digitalWrite(motorForwardRight, LOW);
  digitalWrite(motorBackRight, LOW);
  ledcWrite(motorEnableLeft, 0);
  ledcWrite(motorEnableRight, 0);
}

void BOT_ForwardFull () {
  digitalWrite(motorForwardLeft, HIGH);
  digitalWrite(motorBackLeft, LOW);
  digitalWrite(motorForwardRight, HIGH);
  digitalWrite(motorBackRight, LOW);
  ledcWrite(motorEnableLeft, leftMotorSpeed);
  ledcWrite(motorEnableRight, rightMotorSpeed);
}

void BOT_Left () {
  digitalWrite(motorForwardLeft, LOW);
  digitalWrite(motorBackLeft, LOW);
  digitalWrite(motorForwardRight, HIGH);
  digitalWrite(motorBackRight, LOW);
  ledcWrite(motorEnableLeft, 0);
  ledcWrite(motorEnableRight, rightMotorSpeed);
}

void BOT_Right () {
  digitalWrite(motorForwardLeft, HIGH);
  digitalWrite(motorBackLeft, LOW);
  digitalWrite(motorForwardRight, LOW);
  digitalWrite(motorBackRight, LOW);
  ledcWrite(motorEnableLeft, leftMotorSpeed);
  ledcWrite(motorEnableRight, 0);
}

void BOT_Back () {
  digitalWrite(motorForwardLeft, LOW);
  digitalWrite(motorBackLeft, HIGH);
  digitalWrite(motorForwardRight, LOW);
  digitalWrite(motorBackRight, HIGH);
  ledcWrite(motorEnableLeft, leftMotorSpeed);
  ledcWrite(motorEnableRight, rightMotorSpeed);
}
void setup() {
    // Set pins as outputs:

    pinMode(motorForwardLeft, OUTPUT);
    pinMode(motorBackLeft, OUTPUT);
    pinMode(motorForwardRight, OUTPUT);
    pinMode(motorBackRight, OUTPUT);
    pinMode(motorEnableLeft, OUTPUT);   
    pinMode(motorEnableRight, OUTPUT);   
    ledcSetup(0, 30000, 8);
    Serial.begin(115200);
        ledcAttachPin(motorEnableLeft, 0);  
    ledcAttachPin(motorEnableRight, 0);
    SerialBT.begin("SwarmBot"); //Bluetooth device name
}
 
void loop() {


  //Save income data to variable 'state'
    if(SerialBT.available()){     
      state = SerialBT.read();
      Serial.write(state);   
    }

     
  /***********************Forward****************************/
  //If state is equal with letter 'F', car will go forward!
    if (state == 'F') {Serial.write("state");
      BOT_ForwardFull();
    }
   /***********************Backward****************************/
  //If state is equal with letter 'B', car will go backward
    else if (state == 'B') {
      BOT_Back();
    }
   /***************************Left*****************************/
  //If state is equal with letter 'L', wheels will turn left
    else if (state == 'L') {
      BOT_Left();
    }
  /***************************Right*****************************/
  //If state is equal with letter 'R', wheels will turn right
    else if (state == 'R') {
      BOT_Right();
    }
  /************************Stop*****************************/
  //If state is equal with letter 'S', stop the car
    else if (state == 'S'){
      BOT_Stop();
}
}

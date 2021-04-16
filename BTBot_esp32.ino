// SWARM BOTS STAND ALONE bt CONTROL 
// Modifyed for esp32 by ThaBoom
// ARDUINO BLUETOOTH RC CAR APP FOR ANDROID 
 
//L293 Connection   
const int motorEnableLeft = 9;     // Pin 1 of L293
const int motorForwardLeft  = 7;     // Pin  2 of L293
const int motorBackLeft  = 8;        // Pin  7 of L293 
const int motorEnableRight = 11;   // Pin 9 of L293      
const int motorForwardRight  = 12;   // Pin 10 of L293
const int motorBackRight  = 10;      // Pin 14 of L293
  
//Variables for the Motors
const int leftMotorSpeed = 255;
const int rightMotorSpeed = 255;
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
    ledcAttachPin(motorEnableLeft, 0);  
    ledcAttachPin(motorEnableRight, 0);
    pinMode(motorForwardLeft, OUTPUT);
    pinMode(motorBackLeft, OUTPUT);
    pinMode(motorForwardRight, OUTPUT);
    pinMode(motorBackRight, OUTPUT);   
    ledcSetup(0, 4000, 8);
    // Initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    SerialBT.begin("SwarmBot"); //Bluetooth device name
}
 
void loop() {


  //Save income data to variable 'state'
    if(SerialBT.available() > 0){     
      state = SerialBT.read();   
    }
  

     
  /***********************Forward****************************/
  //If state is equal with letter 'F', car will go forward!
    if (state == 'F') {
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


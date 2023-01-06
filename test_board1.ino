#include <Servo.h>
const int switch1 = 2;
const int switch2 = 4;
const int pressuresensor = A0;
const int voltagepin = A1;
const int enablepin = 12;
const int solenoid1F = 7;
const int solenoid1R = 8;
const int solenoid2F = 9;
const int solenoid2R = 10;
int switch1state = 0;
int switch2state = 0;
float analogpressurevalue = 0;
int analogvoltagevalue = 0;
float voltagepressure = 0;
int pressure = 0;
float voltage = 0;
int enablestate = 0;
int pressurestate = 1;
Servo compressor;
int supplypin = 13;

void setup()
{
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
  pinMode(voltagepin, INPUT);
  pinMode(pressuresensor, INPUT); 
  pinMode(solenoid1F, OUTPUT);
  pinMode(solenoid1R, OUTPUT);
  pinMode(solenoid2F, OUTPUT);
  pinMode(solenoid2R, OUTPUT);
  pinMode(enablepin, INPUT_PULLUP);
  pinMode(supplypin, OUTPUT);
  Serial.begin(9600);
  compressor.attach(6);
}

void loop()
{
  //read switches
  if(digitalRead(switch1) == 1){
    switch1state = 0;
  }
  else{
    switch1state = 1;
  }

  if(digitalRead(switch2) == 1){
    switch2state = 0;
  }
  else{
    switch2state = 1;
  }


  // read and calculate pressure
  analogpressurevalue = analogRead(pressuresensor);
  voltagepressure = analogpressurevalue / 204.6;
  pressure = (250 * (voltagepressure / 4.949) - 18); 
  //set pressure switch state
  if(pressure > 90){
    pressurestate = 0;
  }
  if(pressure < 75){
    pressurestate = 1;
  }

  Serial.println(pressure);

  //set enable state
  if(digitalRead(enablepin) == 0){
    enablestate = 1;
  }
  else{
    enablestate = 0;
  }


  //set compressor 
  if( pressurestate == 1 && enablestate == 1){
    compressor.writeMicroseconds(1950);
  }
  else{
    compressor.writeMicroseconds(1500);
  }

  //enable 5v pin

  digitalWrite(supplypin, HIGH);
  //set solenoid 1
  if( switch1state == 1 && enablestate == 1 ){
    digitalWrite(solenoid1F, HIGH);
    digitalWrite(solenoid1R, LOW);
  }
  else{
    digitalWrite(solenoid1F, LOW);
    digitalWrite(solenoid1R, HIGH);
    
  //set solenoid 2
  if( switch2state == 1 && enablestate == 1 ){
    digitalWrite(solenoid2F, HIGH);
    digitalWrite(solenoid2R, LOW);
  }
  else{
    digitalWrite(solenoid2F, LOW);
    digitalWrite(solenoid2R, HIGH);
  }
  }

}


const int switch1 = 5;
const int switch2 = 4;
const int pressuresensor = A0;
const int compressor = 6;
const int voltagepin = A1;
const int enablepin = 11;
const int solenoid1F = 7;
const int solenoid1R = 8;
const int solenoid2F = 9;
const int solenoid2R = 10;
int switch1state = 0;
int switch2state = 0;
int analogpressurevalue = 0;
int analogvoltagevalue = 0;
int pressure = 0;
int voltage = 0;
int enablestate = 0;

void setup()
{
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(voltagepin, INPUT);
  pinMode(pressuresensor, INPUT);
  pinMode(compressor, OUTPUT);
  pinMode(solenoid1F, OUTPUT);
  pinMode(solenoid1R, OUTPUT);
  pinMode(solenoid2F, OUTPUT);
  pinMode(solenoid2R, OUTPUT);
  pinMode(enablepin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  //read switches
  switch1state = digitalRead(switch1);
  switch2state = digitalRead(switch2);
    
  
  // read and calculate pressure
  analogpressurevalue = analogRead(pressuresensor);
  pressure = analogpressurevalue * .1953125;
  
  //read and calculate voltage
  analogvoltagevalue = analogRead(voltagepin);
  voltage = analogvoltagevalue * .025;
  
  //set enable state
  if(digitalRead(enablepin) == 1 && voltage > 8){
    enablestate = 1;
  }
  else{
    enablestate = 0;
  }
  
  //set compressor state
  if( pressure < 115 && enablestate == 1){
    digitalWrite(compressor, HIGH);
  }
  else{
    digitalWrite(compressor, LOW);
  }  
  
  //set solenoid 1
  if( switch1state == 1 && enablestate == 1){
    digitalWrite(solenoid1F, HIGH);
    digitalWrite(solenoid1R, LOW);
  }
  else{
    digitalWrite(solenoid1F, LOW);
    digitalWrite(solenoid1R, HIGH);
  }
  
  //set solenoid 2
  if( switch2state == 1 && enablestate == 1){
    digitalWrite(solenoid2F, HIGH);
    digitalWrite(solenoid2R, LOW);
  }
  else{
    digitalWrite(solenoid2F, LOW);
    digitalWrite(solenoid2R, HIGH);
  }
}
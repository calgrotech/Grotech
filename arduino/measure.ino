////Fan Pins
//const int tachometer = 2; //Pin D2
//const int fanPMW = 3; //Pin D3
//const int fanRelay = 4; //Pin D4
//
////LED Pins
//const int ledRelay = 5; //Pin D5
//
////Light Sensor Pins
//const int lightSensor = 14; //Pin A0

//Temp Sensor Pins
const int tempSensorOne = 15; //Pin A1
const int tempSensorTwo = 16; //Pin A2
const int tempSensorThree = 17; //Pin A3

//Global Variables
//bool fanOn = false; //Fan is OFF
//bool lightOn = false; //Light is OFF
//
//int lightCal;
//int lightVal;

int tempOne;
int tempTwo;
int tempThree;
//int aveTemp;
//int tempAct = 90; //"Activation Temp"
//int tempActHighOffset = 30;

//int timeOn = 6; //Start Hour of LED
//int timeOff = 20; //End Hour of LED
//int startTime = 0; //Starting Time of LED
//int currentTime;

void setup()
{
//  //Fan Setup
//  pinMode(fanPMW,OUTPUT);
//  pinMode(fanRelay, OUTPUT);
//  analogWrite(fanPMW, 0); //Fan Speed LOW
//  digitalWrite(fanRelay, HIGH);
//  digitalWrite(fanRelay, HIGH);
//
//  //LED Setup
//  timeOn = timeOn * 60; //hours => mins
//  timeOff = timeOff * 60; //hours => mins
//  currentTime = startTime;
//  
//  //Sensors Setup

  //Communications Setup
  Serial.begin(115200);
}

void loop(){
  //Measure Temp of Each Temp Sensor and send it to RaspberryPi
  //if (Serial.available() > 0){
  tempOne = analogRead(tempSensorOne);
  tempTwo = analogRead(tempSensorTwo);
  tempThree = analogRead(tempSensorThree);
  //  aveTemp = (tempOne + tempTwo + tempThree) / 3;
  Serial.print("[");
  Serial.print(tempOne);
  Serial.print(",");
  Serial.print(tempTwo);
  Serial.print(",");
  Serial.print(tempThree);
  Serial.println("]");
  Serial.flush();
  //}
//  // send data only when you receive data:
//  if (Serial.available() > 0) {
//  
//    // read the incoming byte:
//  
//    // say what you got:
//    Serial.print((char)Serial.read());
//  }
//  Serial.print("Average Temperature: ");
//  Serial.println(aveTemp); //Print average temp

//  //Turn up Fan Speed at Activation Temp
//  if (aveTemp > tempAct){ 
//    //analogWrite(fanPMW, 255); //Fan Speed HIGH
//    digitalWrite(fanRelay, LOW); //Fan ON
//    fanOn = true;
//    Serial.println("FAN IS ON!");
//  }
//  if (aveTemp < tempAct){
//    //analogWrite(fanPMW, 0); //Fan Speed Low
//    digitalWrite(fanRelay, HIGH); //Fan OFF
//    fanOn = false;
//    Serial.println("FAN IS OFF!");
//  }
//
//  //Turn Light On/Off at timeOn/Off
//  if (currentTime == timeOn){
//    lightOn = true;
//    digitalWrite(ledRelay, LOW);
//    Serial.println("LIGHT IS ON!");
//  }
//  if (currentTime == timeOff){
//    lightOn = false;
//    digitalWrite(ledRelay, HIGH);
//    Serial.println("LIGHT IS OFF!");
//  }
//
//  //Clock Reset: if timer reaches 24-hour mark (1440-min mark), then set time to 0
//  if (currentTime > 1440){
//    currentTime = 0;
//  }
//  
//  currentTime += 1;
//  Serial.print("Time: ");
//  Serial.println(currentTime);
//  
}

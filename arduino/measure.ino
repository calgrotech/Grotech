//Temp Sensor Pins
const int tempSensorOne = 15; //Pin A1
const int tempSensorTwo = 16; //Pin A2
const int tempSensorThree = 17; //Pin A3

//Global Variables
int tempOne;
int tempTwo;
int tempThree;

void setup(){
  //Communications Setup
  Serial.begin(115200);
}

void loop(){
  //Measure Temp of Each Temp Sensor and send it to RaspberryPi
  tempOne = analogRead(tempSensorOne);
  tempTwo = analogRead(tempSensorTwo);
  tempThree = analogRead(tempSensorThree);
  
  Serial.print("[");
  Serial.print(tempOne);
  Serial.print(",");
  Serial.print(tempTwo);
  Serial.print(",");
  Serial.print(tempThree);
  Serial.println("]");
  Serial.flush();
}

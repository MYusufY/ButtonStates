#include <Arduino.h>

#include <ButtonStates.h>
ButtonSwitch buttonOne(2);
ButtonSwitch buttonTwo(3);

void setup(){
  Serial.begin(9600);
}

void loop(){
  int userActionOne = buttonOne.triggerLong();
  int userActionTwo = buttonTwo.triggerDouble();

  switch(userActionOne){
    case 1:
      Serial.println("Button 1: Single click");
      break;
    case 2:
      Serial.println("Button 1: Double click");
      break;
    case 3:
      Serial.println("Button 1: Long click");
      break;
  }

  switch(userActionTwo){
    case 1:
      Serial.println("Button 2: Single click");
      break;
    case 2:
      Serial.println("Button 2: Double click");
      break;
    case 3:
      Serial.println("Button 2: Long click");
      break;
  }

  delay(10);
}
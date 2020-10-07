#include <Arduino.h>
#include <ButtonStates.h>

// Instantiate buttons
ButtonSwitch buttonOne(2);
ButtonSwitch buttonTwo(3);

#define LED 4

void setup(){
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop(){
  // Read button values
  int userActionOne = buttonOne.triggerLong();
  int userActionTwo = buttonTwo.triggerDouble();

  // Do something depending on the value...
  switch(userActionOne){
    case 1:
      Serial.println("Button 1: Single click");
      Serial.print("Single clicks since start: ");
      Serial.println(buttonOne.singleClicks);
      Serial.print("Switch is ");
      Serial.println(buttonOne.flipflop);

      // Flipflop variable can be used to set an output HIGH or LOW
      digitalWrite(LED, buttonOne.flipflop);
      break;
    case 2:
      Serial.println("Button 1: Double click");
      Serial.print("Double clicks since start: ");
      Serial.println(buttonOne.doubleClicks);
      break;
    case 3:
      Serial.println("Button 1: Long click");
      Serial.print("Long clicks since start: ");
      Serial.println(buttonOne.longClicks);
      break;
  }

  switch(userActionTwo){
    case 1:
      Serial.println("Button 2: Single click");
      Serial.print("Single clicks since start: ");
      Serial.println(buttonTwo.singleClicks);
      Serial.print("Switch is ");
      Serial.println(buttonTwo.flipflop);

      // Flipflop variable of another button can be set by another function
      buttonOne.fliptheflop();
      digitalWrite(LED, buttonOne.flipflop);
      break;
    case 2:
      Serial.println("Button 2: Double click");
      Serial.print("Double clicks since start: ");
      Serial.println(buttonTwo.doubleClicks);
      break;
  }

  delay(10);
}

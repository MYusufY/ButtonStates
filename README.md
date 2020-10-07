# buttonstates by master_mugen
An Arduino library for handling button actions and debouncing.

Instantiate a button:
```cpp
ButtonSwitch button(2);
```

Read that button's actions depending on what you need:
```cpp
int userAction = button.triggerSingle(); // detects single clicks
int userAction = button.triggerDouble(); // detects single and double clicks
int userAction = button.triggerLong();   // detects single, double and long clicks
```

Get the number of clicks:
```cpp
int nbSingleClicks = button.singleClicks;
int nbDoubleClicks = button.doubleClicks;
int nbLongClicks = button.longClicks;
```

Get the flipflop value of a switch:
```cpp
digitalWrite(LED, button.flipflop);
```

Flip the flipflop value manually (to make a n-way flipflop switch):
```cpp
button.fliptheflop();
```

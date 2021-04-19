# ButtonStates by master_mugen
An Arduino library for handling button actions and debouncing. 

Instantiate a button:
```cpp
ButtonStates button(2); // 2 being the pin number
```

Read that button's actions depending on what you need:
```cpp
int userAction = button.triggerSingle(); // detects single clicks (returns 1)
int userAction = button.triggerDouble(); // detects single and double clicks (returns 2)
int userAction = button.triggerLong();   // detects single, double and long clicks (returns 3)
```

Get the number of clicks:
```cpp
int nbSingleClicks = button.singleClicks;
int nbDoubleClicks = button.doubleClicks;
int nbLongClicks   = button.longClicks;
```

The initial state of a button is 0 and when the library registers a click, the state becomes 1. The variable flipflop helps you track the state of the button (if required). To get the flipflop value of a switch and use it to toggle a LED for example:
```cpp
digitalWrite(LED, button.flipflop);
```

You can also flip the flipflop value manually (to make a n-way flipflop switch):
```cpp
button.fliptheflop();
```

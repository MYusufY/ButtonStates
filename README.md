# ButtonStates by master_mugen
An Arduino library for handling button actions and debouncing. 
The button needs to be wired to ground. The library declares the pin with an INPUT_PULLUP.

Instantiate a button:
```cpp
ButtonStates button(2); // 2 being the pin number
```

Read that button's actions depending on what you need. These functions need to be called in the main loop to be effective.
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

The initial value of this variable is 0. When the library registers a click, the value becomes 1. When the button is triggered again, the value reverts to 0. Just like a flipflop. This variable can help you track the state of the button for example. You could also use it to toggle a LED:
```cpp
int state = button.flipflop; // returns 1 or 0
digitalWrite(LED, state);
```

You can also flip the flipflop value manually (to make a n-way flipflop switch):
```cpp
button.fliptheflop();
```

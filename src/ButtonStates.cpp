#include <Arduino.h>
#include <ButtonStates.h>

ButtonSwitch::ButtonSwitch(int pin) {
    _pin = pin;

    // setup the button as pulled high
    pinMode(pin, INPUT_PULLUP);

    // reset all internal variables
    _history = 255;
    _clicks = 0;
    _timeRelease = 0;
    _timePress = 0;

    // reset counters
    singleClicks = 0;
    doubleClicks = 0;
    longClicks = 0;

    // reset single click flip flop
    flipflop = 0b0;
}

void ButtonSwitch::fliptheflop(){
    flipflop ^= 1;
}

// Function detecting and debouncing just one click.
// Debouncing is done by storing the pin's change over time,
// and then checking the history against a mask, thus ignoring the bounces

uint8_t ButtonSwitch::triggerSingle(){
    _history = _history << 1;
    _history |= digitalRead(_pin); 

    if ((_history & 0b11110100) == 0b11110000){ 
        _history = 0b00000000;

        singleClicks++;
        flipflop ^= 1;
        return SINGLECLICK;
    }

    return NOCLICK;
}

// Function detecting and debouncing single and double clicks.
// Double clicks are detected by comparing times between clicks.
// The time between 2 clicks needs to be less than 300ms.

uint8_t ButtonSwitch::triggerDouble(){
    _timeNow = millis();

    _history = _history << 1; 
    _history |= digitalRead(_pin);
    
    if ((_history & 0b11110100) == 0b11110000){
        _history = 0b00000000;

        _clicks++;
        _timePress = millis();
    }

    if ((_clicks == 1) && ((_timeNow-_timePress) > 300)){ 
      _clicks = 0;
      _timePress = 0;

      singleClicks++;
      flipflop ^= 1;
      return SINGLECLICK;
    }
    
    if ((_clicks == 2) && ((_timeNow-_timePress) < 300)){ 
      _clicks = 0;
      _timePress = 0;

      doubleClicks++;
      return DOUBLECLICK;
    }
    
    return NOCLICK;
}

// Function detecting and debouncing, single, double and long clicks.
// Long clicks are identified by comparing press and release times.
// This time we have to use history and mask to detect press and release.

uint8_t ButtonSwitch::triggerLong(){
    _timeNow = millis();

    _history = _history << 1;
    _history |= digitalRead(_pin);
    
    if ((_history & 0b11110100) == 0b11110000){ 
        _history = 0b00000000;

        _timePress = millis();
    }

    if ((_history & 0b00101111) == 0b00001111){ 
        _history = 0b11111111;

        _timeRelease = millis();
        _clicks++;
    }

    if ((_clicks == 1) && (_timeRelease > _timePress) && ((_timeRelease-_timePress) > 300)){
        _clicks = 0;
        _timePress = 0;
        _timeRelease = 0;

        longClicks++;
        return LONGCLICK;
    }

    if ((_clicks == 1) && ((_timeNow-_timePress) > 300)){
      _clicks = 0;
      _timePress = 0;

      singleClicks++;
      flipflop ^= 1;
      return SINGLECLICK;
    }
    
    if ((_clicks == 2) && ((_timeNow-_timePress) < 300)){ 
      _clicks = 0;
      _timePress = 0;

      doubleClicks++;
      return DOUBLECLICK;
    }
    
    return NOCLICK;
}

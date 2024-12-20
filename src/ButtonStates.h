#ifndef BUTTON_STATES_H
#define BUTTON_STATES_H

#include <Arduino.h>

// Click types
#define NOCLICK       0
#define SINGLECLICK   1
#define DOUBLECLICK   2
#define LONGCLICK     3

class ButtonStates {
    public:
        // Constructor: accepts the pin number to which the button is connected
        ButtonStates(int pin);

        // Configure the thresholds for detecting double-clicks and long-clicks
        void setThresholds(uint16_t doubleClick, uint16_t longClick);

        // Functions to detect various click patterns
        uint8_t triggerSingle();  // Detect single clicks
        uint8_t triggerDouble();  // Detect single and double clicks
        uint8_t triggerLong();    // Detect single, double, and long clicks

        // Toggle the internal flipflop variable
        void fliptheflop();

        // Counters for how many times each click type has occurred
        uint8_t singleClicks;
        uint8_t doubleClicks;
        uint8_t longClicks;

        // State of the flipflop (HIGH or LOW)
        uint8_t flipflop;

    private:
        // Pin to which the button is connected
        int _pin;

        // Internal state variables
        volatile uint8_t _history;
        volatile uint8_t _clicks;

        volatile unsigned long _timePress;
        volatile unsigned long _timeRelease;

        // Thresholds (in milliseconds) for double and long clicks
        uint16_t _doubleClickThreshold;
        uint16_t _longClickThreshold;

        // Current time tracking
        unsigned long _timeNow;

        // Internal helper methods
        void updateHistory();
        bool isStablePress();
        bool isStableRelease();
        void resetClickState();
};

#endif // BUTTON_STATES_H

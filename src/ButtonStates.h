#include <Arduino.h>

#define NOCLICK 0
#define SINGLECLICK 1
#define DOUBLECLICK 2
#define LONGCLICK 3

class ButtonStates {
    public:
        ButtonStates(int pin);

        // Function returning debounced single clicks
        uint8_t triggerSingle();

        // Function returning debounced single and double clicks
        uint8_t triggerDouble();

        // Function returning debounced single, double and long clicks
        uint8_t triggerLong();

        // Function that flips the flipflop variable
        void fliptheflop();

        // Simple click counters
        uint8_t singleClicks;
        uint8_t doubleClicks;
        uint8_t longClicks;

        // State of the flip flop (HIGH or LOW)
        uint8_t flipflop;

    private:
        int _pin;
        
        volatile uint8_t _history;
        volatile uint8_t _clicks;

        volatile unsigned long _timePress;
        volatile unsigned long _timeRelease;
        unsigned long _timeNow;
};

#include <Arduino.h>

#define NOCLICK 0
#define SINGLECLICK 1
#define DOUBLECLICK 2
#define LONGCLICK 3

class ButtonSwitch {
    public:
        ButtonSwitch(int pin);

        uint8_t triggerSingle();
        uint8_t triggerDouble();
        uint8_t triggerLong();

    private:
        int _pin;
        
        volatile uint8_t _history;
        volatile uint8_t _clicks;

        volatile unsigned long _timePress;
        volatile unsigned long _timeRelease;
        unsigned long _timeNow;
};
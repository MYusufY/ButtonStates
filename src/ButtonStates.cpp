#include <Arduino.h>
#include <ButtonStates.h>

// ==================
// Constants & Macros
// ==================

// Debounce patterns: Adjust these masks and values to match your button release/press patterns.
const uint8_t DEBOUNCE_PATTERN_MASK_PRESS   = 0b11110100;
const uint8_t DEBOUNCE_PATTERN_STABLE_PRESS = 0b11110000;

const uint8_t DEBOUNCE_PATTERN_MASK_RELEASE = 0b00101111;
const uint8_t DEBOUNCE_PATTERN_STABLE_REL   = 0b00001111;

const uint8_t NOCLICK       = 0;
const uint8_t SINGLECLICK   = 1;
const uint8_t DOUBLECLICK   = 2;
const uint8_t LONGCLICK     = 3;


// ==================
// Constructor
// ==================
ButtonStates::ButtonStates(int pin) {
    _pin = pin;
    
    // Setup the button with internal pull-up resistor.
    pinMode(_pin, INPUT_PULLUP);

    // Initialize internal variables
    _history              = 0xFF;  // Start with all '1's: button is not pressed initially
    _clicks               = 0;
    _timeRelease          = 0;
    _timePress            = 0;

    // Counters
    singleClicks          = 0;
    doubleClicks          = 0;
    longClicks            = 0;

    // Flip-flop
    flipflop              = 0b0;

    // Default thresholds (in milliseconds)
    _doubleClickThreshold = 300;
    _longClickThreshold   = 300;
}

// ==================
// Public Methods
// ==================

void ButtonStates::fliptheflop() {
    flipflop ^= 1;
}

// Allows adjusting thresholds at runtime
void ButtonStates::setThresholds(uint16_t doubleClick, uint16_t longClick) {
    _doubleClickThreshold = doubleClick;
    _longClickThreshold   = longClick;
}

// -------------------
// triggerSingle()
// Detects single clicks using debouncing.
// -------------------
uint8_t ButtonStates::triggerSingle() {
    updateHistory();
    if (isStablePress()) {
        // Reset history so we're ready for next cycle
        _history = 0b00000000;

        singleClicks++;
        fliptheflop();
        return SINGLECLICK;
    }
    return NOCLICK;
}

// -------------------
// triggerDouble()
// Detects single and double clicks using timing checks.
// -------------------
uint8_t ButtonStates::triggerDouble() {
    uint32_t currentTime = millis();
    updateHistory();

    if (isStablePress()) {
        _history = 0b00000000;
        _clicks++;
        _timePress = currentTime;
    }

    // If one click detected and no second click within threshold => single click
    if ((_clicks == 1) && ((currentTime - _timePress) > _doubleClickThreshold)) {
        resetClickState();

        singleClicks++;
        fliptheflop();
        return SINGLECLICK;
    }

    // If two clicks detected within threshold => double click
    if ((_clicks == 2) && ((currentTime - _timePress) < _doubleClickThreshold)) {
        resetClickState();

        doubleClicks++;
        return DOUBLECLICK;
    }

    return NOCLICK;
}

// -------------------
// triggerLong()
// Detects single, double, and long clicks.
// -------------------
uint8_t ButtonStates::triggerLong() {
    uint32_t currentTime = millis();
    updateHistory();

    // Check for press event
    if (isStablePress()) {
        _history = 0b00000000;
        _timePress = currentTime;
    }

    // Check for release event
    if (isStableRelease()) {
        _history = 0xFF; // Reset history to "all released"
        _timeRelease = currentTime;
        _clicks++;
    }

    // Long click: If release detected and duration > long click threshold
    if ((_clicks == 1) && (_timeRelease > _timePress) && ((_timeRelease - _timePress) > _longClickThreshold)) {
        resetClickState();
        longClicks++;
        return LONGCLICK;
    }

    // Single click: If only one press and no second click within long click threshold
    if ((_clicks == 1) && ((currentTime - _timePress) > _longClickThreshold)) {
        resetClickState();
        singleClicks++;
        fliptheflop();
        return SINGLECLICK;
    }

    // Double click: If two presses occurred within double click threshold
    if ((_clicks == 2) && ((currentTime - _timePress) < _doubleClickThreshold)) {
        resetClickState();
        doubleClicks++;
        return DOUBLECLICK;
    }

    return NOCLICK;
}

// ==================
// Private Methods
// ==================

// Update the history register with the current button state.
void ButtonStates::updateHistory() {
    _history <<= 1;
    _history |= digitalRead(_pin);
}

// Check if a stable button press is detected after debouncing.
bool ButtonStates::isStablePress() {
    return ((_history & DEBOUNCE_PATTERN_MASK_PRESS) == DEBOUNCE_PATTERN_STABLE_PRESS);
}

// Check if a stable button release is detected after debouncing.
bool ButtonStates::isStableRelease() {
    return ((_history & DEBOUNCE_PATTERN_MASK_RELEASE) == DEBOUNCE_PATTERN_STABLE_REL);
}

// Reset internal click tracking variables
void ButtonStates::resetClickState() {
    _clicks = 0;
    _timePress = 0;
    _timeRelease = 0;
}

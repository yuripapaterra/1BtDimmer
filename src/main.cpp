#include "mbed.h"
#include <iostream>
#include <string>

DigitalOut redLed(p5); // Orange Led
DigitalOut blueLed(p6);
InterruptIn button(p7);
PwmOut intensity(p8);
Timeout pressingTimeout, ledTimeout;

enum States { 
    UP, 
    DOWN, 
    RISE, 
    FALL, 
    MAX,
    MIN, 
};

States state = UP;
bool pressFlag = false;
float ledIntensity;
float blinkPeriod;

void setInitialValues();
void startButtonPress();
void finishButtonPress();
void handleStates();
void blink();
string handleStateName();

int main() {
    setInitialValues();
    button.rise(&startButtonPress);
    button.fall(&finishButtonPress);
    
    while(1) {
        intensity = ledIntensity;
        std::cout << "State: " << handleStateName() << "\n";
        printf("Intensity: %.2f\n", ledIntensity);
        wait_ms(100);
    }
}

void setInitialValues() {
    blueLed = 1;
    redLed = 0;
    ledIntensity = 0.5;
}

void startButtonPress() {
    pressFlag = true;
    pressingTimeout.attach(&handleStates, 1.0);
}

void finishButtonPress() {
    pressFlag = false;
    switch (state) {
        case DOWN:
        case RISE:
        case MIN:
            if (ledIntensity < 1) {
                blueLed = 1;
                redLed = 0;
                state = UP;
            }
            break;
        case UP:
        case FALL:
        case MAX:
            if (ledIntensity > 0) {
                blueLed = 0;
                redLed = 1;
                state = DOWN;
            }
            break;
    }
}

void handleStates(){
    pressingTimeout.attach(&handleStates, 1.0);
    ledTimeout.attach(&blink, 0.2);

        if (pressFlag) {
            switch (state) {
                case RISE:
                    if (ledIntensity == 1) state = MAX;
                    else ledIntensity += 0.05;
                    break;
                case FALL:
                    if (ledIntensity == 0) state = MIN;
                    else ledIntensity -= 0.05;
                    break;
                case UP:
                    state = RISE;
                    ledIntensity += 0.05;
                    break;
                case DOWN:
                    state = FALL;
                    ledIntensity -= 0.05;
                    break;
                default:
                    break;
            }

            if (ledIntensity >= 1) {
                state = MAX;
                ledIntensity = 1;
            } else if (ledIntensity <= 0) {
                state = MIN;
                ledIntensity = 0;
            }
    }
}

void blink(){
    switch(state) {
        case MIN:
        case FALL:
            redLed = !redLed;
            break;
        case MAX:
        case RISE:
            blueLed = !blueLed;
            break;
        default:
            break;
    }

    switch(state) {
        case MAX:
        case MIN:
            blinkPeriod = 0.1;
            break;
        case RISE:
            blinkPeriod = 0.2 * (1 + ledIntensity / 0.05);
            break;
        case FALL:
            blinkPeriod = (0.2 * (ledIntensity / 0.05 - 1));
            break;
        default:
            break;
    }
    ledTimeout.attach(&blink, blinkPeriod);
}

string handleStateName() {
    string stateName;
    switch(state) {
        case UP: stateName = "UP"; break;
        case DOWN: stateName = "DOWN"; break;
        case RISE: stateName = "RISING"; break;
        case FALL: stateName = "FALLING"; break;
        case MAX: stateName = "MAX"; break;
        case MIN: stateName = "MIN"; break;
    }
    return stateName;
}
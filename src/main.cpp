#include "mbed.h"
#include <iostream>
#include <string>

DigitalOut redLed(p5);
DigitalOut blueLed(p6);
InterruptIn button(p7);
PwmOut intensity(p8);
Timeout pressingTimeout, ledTimeout;

enum States 
{ 
    UP, DOWN,  RISE,  FALL,  MAX, MIN, 
};

States state = UP;
bool Flag = false;
float ledOsc;
float blinkPeriod;
void valorInicial();
void start();
void stop();
void estado();
void piscar();
string desc();


int main()
{
    valorInicial();
    button.rise(&start);
    button.fall(&stop);
    while(1) {
        intensity = ledOsc;
        std::cout << "State: " << desc() << "\n";
        printf("Intensity: %.2f\n", ledOsc);
        wait_ms(100);
 }}

void valorInicial() 
{
    blueLed = 1;
    redLed = 0;
    ledOsc = 0.5;
}

void start() {
    Flag = true;
    pressingTimeout.attach(&estado, 1.0);
}

void stop()
 {
    Flag = false;
    switch (state)
 {
        case DOWN:
        case RISE:
        case MIN:
            if (ledOsc < 1)
            {
                blueLed = 1;
                redLed = 0;
                state = UP;
            }
            break;
        case UP:
        case FALL:
        case MAX:
            if (ledOsc > 0)
           {
                blueLed = 0;
                redLed = 1;
                state = DOWN;
            }
            break;
    }
}
void estado()
{
    pressingTimeout.attach(&estado, 1.0);
    ledTimeout.attach(&piscar, 0.2);

        if (pressFlag)
        {
            switch (state) 
            {
                case RISE:
                    if (ledOsc == 1) state = MAX;
                    else ledOsc += 0.05;
                    break;
                case FALL:
                    if (ledOsc == 0) state = MIN;
                    else ledOsc -= 0.05;
                    break;
                case UP:
                    state = RISE;
                    ledOsc += 0.05;
                    break;
                case DOWN:
                    state = FALL;
                    ledOsc -= 0.05;
                    break;
                default:
                    break;
            }
            if (ledOsc >= 1) 
            {
                state = MAX;
                ledOsc = 1;
            } else if (ledOsc <= 0) 
              {
                state = MIN;
                ledOsc = 0;
              }
    }
}
void blink()
{
    switch(state)
    {
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

    switch(state) 
    {
        case MAX:
        case MIN:
            blinkPeriod = 0.1;
            break;
        case RISE:
            blinkPeriod = 0.2 * (1 + ledOsc / 0.05);
            break;
        case FALL:
            blinkPeriod = (0.2 * (ledOsc / 0.05 - 1));
            break;
        default:
            break;
    }
    ledTimeout.attach(&blink, blinkPeriod);
}

string desc() 
{
    string final;
    switch(state) 
    {
        case UP: 
        state = "UP"; break;
        case DOWN: 
        state = "DOWN"; break;
        case RISE: 
        state = "RISING"; break;
        case FALL: 
        state = "FALLING"; break;
        case MAX:
        state = "MAX"; break;
        case MIN:
        state = "MIN"; break;
    }
    return final;
}

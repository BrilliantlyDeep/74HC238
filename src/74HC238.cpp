/*
* 74HC238.cpp
*
* Class for the control of a digital 3-to-8 line decoder/demultiplex
* https://assets.nexperia.com/documents/data-sheet/74HC_HCT238.pdf
* 
* Date: 2017-12-04
* Author: Mattia Iurich
* Rev: 1.0
*
*/

#include "Arduino.h"
#include "74HC238.h"

#define DEBUG true

CD74HC238 :: CD74HC238 (int* select, int enablePin, ENType enableType)
{
    A[0] = select[0];
    A[1] = select[1];
    A[2] = select[2];

    enPin = enablePin;
    typeEN = enableType;

    Y = 0;

    pinMode(A[0], OUTPUT);
    pinMode(A[1], OUTPUT);
    pinMode(A[2], OUTPUT);
    pinMode(enablePin, OUTPUT);
}

void CD74HC238 :: Enable()
{
    #if DEBUG
        Serial.println("I'm enabled.");
        Serial.print("Enable type = ");
        Serial.println(typeEN);
        Serial.println("");
        Serial.println(A[0]);
        Serial.println(A[1]);
        Serial.println(A[2]);
        Serial.println(enPin);
        Serial.println("##################");
    #endif

    digitalWrite(A[0], LOW);
    digitalWrite(A[1], LOW);
    digitalWrite(A[2], LOW);

    if (typeEN == EN_ACTIVE_L)
        digitalWrite(enPin, LOW);
    else if (typeEN == EN_ACTIVE_H)
        digitalWrite(enPin, HIGH);
}

void CD74HC238 :: Disable()
{
    if (typeEN == EN_ACTIVE_L)
        digitalWrite(enPin, HIGH);
    else if (typeEN == EN_ACTIVE_H)
        digitalWrite(enPin, LOW);
}

void CD74HC238 :: SetOutput(int enableOutY)
{
    Y = enableOutY;

    switch (Y)
    {
        case 0:
            digitalWrite(A[0], LOW);
            digitalWrite(A[1], LOW);
            digitalWrite(A[2], LOW);
            break;
        case 1:
            digitalWrite(A[0], HIGH);
            digitalWrite(A[1], LOW);
            digitalWrite(A[2], LOW);
            break;
        case 2:
            digitalWrite(A[0], LOW);
            digitalWrite(A[1], HIGH);
            digitalWrite(A[2], LOW);
            break;
        case 3:
            digitalWrite(A[0], HIGH);
            digitalWrite(A[1], HIGH);
            digitalWrite(A[2], LOW);
            break;
        case 4:
            digitalWrite(A[0], LOW);
            digitalWrite(A[1], LOW);
            digitalWrite(A[2], HIGH);
            break;
        case 5:
            digitalWrite(A[0], HIGH);
            digitalWrite(A[1], LOW);
            digitalWrite(A[2], HIGH);
            break;
        case 6:
            digitalWrite(A[0], LOW);
            digitalWrite(A[1], HIGH);
            digitalWrite(A[2], HIGH);
            break;
        case 7:
            digitalWrite(A[0], HIGH);
            digitalWrite(A[1], HIGH);
            digitalWrite(A[2], HIGH);
            break;
    }
}

void CD74HC238 :: NextOutput()
{
    Y++;
    if (Y > 7)
        Y = 0;
        
    SetOutput(Y);
}

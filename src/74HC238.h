/*
* 74HC238.h
*
* Class for the control of a digital 3-to-8 line decoder/demultiplex
* https://assets.nexperia.com/documents/data-sheet/74HC_HCT238.pdf
* 
* Date: 2017-12-04
* Author: Mattia Iurich
* Rev: 1.0
*
*/

#ifndef __74HC238__
#define __74HC238__

#include "Arduino.h"

enum ENType {EN_ACTIVE_L, EN_ACTIVE_H};

class CD74HC238
{
public:
    CD74HC238(int[], int, ENType);    // 3 select pins, enable pin, enable type

    void Enable();
    void Disable();
    void SetOutput(int);
    void NextOutput();
private:
    int A[3];
    int enPin, Y;
    ENType typeEN;
};

#endif // __74HC238__
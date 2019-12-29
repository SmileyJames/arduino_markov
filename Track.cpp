#include <Arduino.h>
#include "Track.h"

#define L_TRK 10
#define M_TRK 4
#define R_TRK 2

using namespace Track;

void Track::setup() {
    pinMode(L_TRK, INPUT);
    pinMode(M_TRK, INPUT);
    pinMode(R_TRK, INPUT);
}

Input Track::track() {
    return (
        ((7 * !digitalRead(L_TRK)) & 4) |
        ((7 * !digitalRead(M_TRK)) & 2) |
        ((7 * !digitalRead(R_TRK)) & 1)
    );
}

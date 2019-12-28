#include <Arduino.h>
#include "Track.h"

#define L_TRK 10
#define M_TRK 4
#define R_TRK 2

using namespace Track;

void Track::setupTrack() {
    pinMode(L_TRK, INPUT);
    pinMode(M_TRK, INPUT);
    pinMode(R_TRK, INPUT);
}

Input Track::track() {
    return (
        (!digitalRead(L_TRK) & 4) |
        (!digitalRead(M_TRK) & 2) |
        (!digitalRead(R_TRK) & 1));
}

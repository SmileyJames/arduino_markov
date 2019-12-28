#include <Arduino.h>
#include "Move.h"

#define L_WHL_SPD 5
#define R_WHL_SPD 6
#define L_WHL_FWD 7
#define L_WHL_BWD 8
#define R_WHL_BWD 9
#define R_WHL_FWD 11

#define STEADY 100
#define FAST 250
#define SLOW 30

using namespace Move;


namespace {
    void forward() {
        analogWrite(L_WHL_SPD, STEADY);
        analogWrite(R_WHL_SPD, STEADY);
        digitalWrite(L_WHL_FWD, HIGH);
        digitalWrite(L_WHL_BWD, LOW);
        digitalWrite(R_WHL_FWD, HIGH);
        digitalWrite(R_WHL_BWD, LOW);
    }

    void forwardPlus() {
        analogWrite(L_WHL_SPD, FAST);
        analogWrite(R_WHL_SPD, FAST);
        digitalWrite(L_WHL_FWD, HIGH);
        digitalWrite(L_WHL_BWD, LOW);
        digitalWrite(R_WHL_FWD, HIGH);
        digitalWrite(R_WHL_BWD, LOW);
    }

    void backward() {
        analogWrite(L_WHL_SPD, STEADY);
        analogWrite(R_WHL_SPD, STEADY);
        digitalWrite(L_WHL_FWD, LOW);
        digitalWrite(L_WHL_BWD, HIGH);
        digitalWrite(R_WHL_FWD, LOW);
        digitalWrite(R_WHL_BWD, HIGH);
    }

    void leftTurn() {
        analogWrite(L_WHL_SPD, SLOW);
        analogWrite(R_WHL_SPD, STEADY);
        digitalWrite(L_WHL_FWD, HIGH);
        digitalWrite(L_WHL_BWD, LOW);
        digitalWrite(R_WHL_FWD, HIGH);
        digitalWrite(R_WHL_BWD, LOW);
    }

    void leftPivot() {
        analogWrite(L_WHL_SPD, STEADY);
        analogWrite(R_WHL_SPD, STEADY);
        digitalWrite(L_WHL_FWD, LOW);
        digitalWrite(L_WHL_BWD, HIGH);
        digitalWrite(R_WHL_FWD, HIGH);
        digitalWrite(R_WHL_BWD, LOW);
    }

    void rightTurn() {
        analogWrite(L_WHL_SPD, STEADY);
        analogWrite(R_WHL_SPD, SLOW);
        digitalWrite(L_WHL_FWD, HIGH);
        digitalWrite(L_WHL_BWD, LOW);
        digitalWrite(R_WHL_FWD, HIGH);
        digitalWrite(R_WHL_BWD, LOW);
    }

    void rightPivot() {
        analogWrite(L_WHL_SPD, STEADY);
        analogWrite(R_WHL_SPD, STEADY);
        digitalWrite(L_WHL_FWD, HIGH);
        digitalWrite(L_WHL_BWD, LOW);
        digitalWrite(R_WHL_FWD, LOW);
        digitalWrite(R_WHL_BWD, HIGH);
    }

    void stop() {
        digitalWrite(L_WHL_SPD, LOW);
        digitalWrite(R_WHL_SPD, LOW);
    }
}

void Move::setupMove() {
    pinMode(L_WHL_FWD, OUTPUT);
    pinMode(L_WHL_BWD, OUTPUT);
    pinMode(R_WHL_BWD, OUTPUT);
    pinMode(R_WHL_FWD, OUTPUT);
    pinMode(L_WHL_SPD, OUTPUT);
    pinMode(R_WHL_SPD, OUTPUT);
    stop();
}

void Move::move(Command m) {
    switch (m) {
        case Forward:
            forward();
        case ForwardPlus:
            forwardPlus();
        case Backward:
            backward();
        case LeftTurn:
            leftTurn();
        case LeftPivot:
            leftPivot();
        case RightTurn:
            rightTurn();
        case RightPivot:
            rightPivot();
        case Stop:
            stop();
        default:
            stop();
    }
}

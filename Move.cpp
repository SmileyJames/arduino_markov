#include <Arduino.h>
#include "Move.h"

#define L_WHL_SPD 5
#define R_WHL_SPD 6
#define L_WHL_FWD 7
#define L_WHL_BWD 8
#define R_WHL_BWD 9
#define R_WHL_FWD 11

#define SLOW 100
#define FAST 140

using namespace Move;


namespace {
    void forward() {
        analogWrite(L_WHL_SPD, SLOW);
        analogWrite(R_WHL_SPD, SLOW);
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
        analogWrite(L_WHL_SPD, SLOW);
        analogWrite(R_WHL_SPD, SLOW);
        digitalWrite(L_WHL_FWD, LOW);
        digitalWrite(L_WHL_BWD, HIGH);
        digitalWrite(R_WHL_FWD, LOW);
        digitalWrite(R_WHL_BWD, HIGH);
    }

    void left() {
        analogWrite(L_WHL_SPD, SLOW);
        analogWrite(R_WHL_SPD, SLOW);
        digitalWrite(L_WHL_FWD, LOW);
        digitalWrite(L_WHL_BWD, HIGH);
        digitalWrite(R_WHL_FWD, HIGH);
        digitalWrite(R_WHL_BWD, LOW);
    }

    void leftPlus() {
        analogWrite(L_WHL_SPD, FAST);
        analogWrite(R_WHL_SPD, FAST);
        digitalWrite(L_WHL_FWD, LOW);
        digitalWrite(L_WHL_BWD, HIGH);
        digitalWrite(R_WHL_FWD, HIGH);
        digitalWrite(R_WHL_BWD, LOW);
    }

    void right() {
        analogWrite(L_WHL_SPD, FAST);
        analogWrite(R_WHL_SPD, FAST);
        digitalWrite(L_WHL_FWD, HIGH);
        digitalWrite(L_WHL_BWD, LOW);
        digitalWrite(R_WHL_FWD, LOW);
        digitalWrite(R_WHL_BWD, HIGH);
    }

    void rightPlus() {
        analogWrite(L_WHL_SPD, SLOW);
        analogWrite(R_WHL_SPD, SLOW);
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

void Move::setup() {
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
            Serial.println("Forward");
            forward();
        break;
        case ForwardPlus:
            Serial.println("Forward Plus");
            forwardPlus();
        break;
        case Backward:
            Serial.println("Backward");
            backward();
        break;
        case Left:
            Serial.println("Left");
            left();
        break;
        case LeftPlus:
            Serial.println("Left Plus");
            leftPlus();
        break;
        case Right:
            Serial.println("Right");
            right();
        break;
        case RightPlus:
            Serial.println("Right Plus");
            rightPlus();
        break;
        case Stop:
            Serial.println("Stop");
            stop();
        break;
        default:
            stop();
        break;
    }
}

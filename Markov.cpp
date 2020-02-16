#include <EEPROM.h>
#include <Arduino.h>

#include "Markov.h"

#define RATE 100
#define MAX_VAL 65536

using namespace Markov;

Move::Command Process::get(State state) {
    const Int s = getIndex(state);
    Int choice = random(0, MAX_VAL);
    for (int m=0; m < MOVE_SIZE; m++) {
        Int val = chain[s][m].value;
        if (choice < val) {
            return m;
        }
        choice -= val;
    }
    return MOVE_SIZE - 1;
}


void Process::loss(State state, Move::Command move, int adjustment) {
    const Int s = getIndex(state);
    
    const int balance = RATE / adjustment;
    int change = 0;

    for (int m=0; m < MOVE_SIZE; m++) {
        if (m != move) {

            int b = balance;
            if (b > 0 && chain[s][m].value < b) {
                b = chain[s][m].value;
            } else if (b < 0 && chain[s][m].value > MAX_VAL + b) {
                b = chain[s][m].value - MAX_VAL;
            }

            chain[s][m].value -= b;
            change += b;
        }
    }

    chain[s][move].value += change;
}

void Process::save() {
    Int address = 0;
    for (Int s=0; s < STATE_SIZE; s++) {
        for (Int m=0; m < MOVE_SIZE; m++) {
            EEPROM.write(address, chain[s][m].split[0]);
            EEPROM.write(address + 1, chain[s][m].split[1]);
            address += 2;
        }
    }
}

void Process::load() {
    Int address = 0;
    for (Int s=0; s < STATE_SIZE; s++) {
        for (Int m=0; m < MOVE_SIZE; m++) {
            chain[s][m].split[0] = EEPROM.read(address);
            chain[s][m].split[1] = EEPROM.read(address + 1);
            address += 2;
        }
    }
}

void Process::clear() {
    const Int init = MAX_VAL / MOVE_SIZE;
    for (Int s=0; s < STATE_SIZE; s++) {
        for (Int m=0; m < MOVE_SIZE; m++) {
            chain[s][m].value = init;
        }
    }
}

void Process::print() {
    for (Int s=0; s < STATE_SIZE; s++) {
        for (Int m=0; m < MOVE_SIZE; m++) {
            Serial.print(chain[s][m].value);
            Serial.print(", ");
        }
        Serial.println();
    }
    Serial.println();
}

Int Process::getIndex(State s) {
    return s.track0 | (s.track1 << 3);
}

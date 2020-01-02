#include <EEPROM.h>
#include <Arduino.h>

#include "Markov.h"

#define RATE 700
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


void Process::sub(int s, int m, Int val) {
    if (chain[s][m].value > val) {
        chain[s][m].value -= val;
    } else {
        chain[s][m].value = 0;
    }
}


void Process::add(int s, int m, Int val) {
    if (chain[s][m].value < MAX_VAL - val) {
        chain[s][m].value += val;
    } else {
        chain[s][m].value = MAX_VAL;
    }
}


void Process::reward(State state, Move::Command move, int index) {
    const Int s = getIndex(state);

    const int rate = RATE / index;
    const Int loss = rate / (MOVE_SIZE - 1);

    for (int m=0; m < MOVE_SIZE; m++) {
        if (m == move) {
            add(s, m, rate);
        } else {
            sub(s, m, loss);
        }
    }
}

void Process::punish(State state, Move::Command move, int index) {
    const Int s = getIndex(state);

    const int rate = RATE / index;
    const Int loss = rate / (MOVE_SIZE - 1);

    for (int m=0; m < MOVE_SIZE; m++) {
        if (m == move) {
            sub(s, m, rate);
        } else {
            add(s, m, loss);
        }
    }
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

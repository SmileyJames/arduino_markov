#include <EEPROM.h>
#include <Arduino.h>

#include "Markov.h"

#define RATE 400
#define MAX_VAL 65536

using namespace Markov;

Process::Process() {
    const Int init = MAX_VAL / MOVE_SIZE;
    for (Int s=0; s < STATE_SIZE; s++) {
        for (Int m=0; m < MOVE_SIZE; m++) {
            chain[s][m].value = init;
        }
    }
}

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
}


void Process::reward(State state, Move::Command move) {
    const Int s = getIndex(state);
    const Int loss = RATE / (MOVE_SIZE - 1);
    for (int m=0; m < MOVE_SIZE; m++) {
        if (m == move) {
            chain[s][m].value += RATE;
        } else {
            chain[s][m].value -= loss;
        }
    }
}

void Process::punish(State state, Move::Command move) {
    const Int s = getIndex(state);
    const Int loss = RATE / (MOVE_SIZE - 1);
    for (int m=0; m < MOVE_SIZE; m++) {
        if (m == move) {
            chain[s][m].value -= RATE;
        } else {
            chain[s][m].value += loss;
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

Int Process::getIndex(State s) {
    return s.track0 | (s.track1 << 3);
}

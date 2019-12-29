#include <IRremote.h>
#include "Move.h"
#include "Track.h"
#include "Markov.h"

#define ACTION_DURATION 200
#define ACTIONS_SIZE 25

#define IR_RECV 12

#define KEY_OK   16712445
#define KEY_UP   16736925
#define KEY_DOWN 16754775
#define KEY_STAR 16728765
#define KEY_HASH 16732845

struct Action {
    Markov::State state;
    Move::Command move; 
};

IRrecv irRecv(IR_RECV);
decode_results irInput;
unsigned long irValue;
unsigned long time;
bool paused = true;

Markov::Process m;

Track::Input prevTrack;
Action actions[ACTIONS_SIZE];
int actionsIndex = 0;
int actionsLength = 0;


void setup() {
    Serial.begin(9600);
    irRecv.enableIRIn();
    m.load();
    Track::setup();
    Move::setup();
    randomSeed(analogRead(0));
}


void loop() {
    if (irRecv.decode(&irInput)) {
        irValue = irInput.value;
        irRecv.resume();

        switch (irValue) {
            case KEY_OK:
                paused = !paused;
                if (paused) {
                    Move::stop();
                } else {
                    nextAction();
                }
            break;
            case KEY_STAR:
                m.save();
            break;
            case KEY_HASH:
                m.clear();
            break;
            case KEY_UP:
                rewardActions();
            break;
            case KEY_DOWN:
                punishActions();
            break;
        }
    }

    if (!paused && (millis() - time > ACTION_DURATION)) {
        nextAction();
    }
}

void nextAction() {
    time = millis();
    Action a;

    if (actionsLength == 0) {
        a.state.track0 = a.state.track1 = prevTrack = Track::track();
    } else {
        a.state.track1 = prevTrack;
        a.state.track0 = prevTrack = Track::track();
    }

    a.move = m.get(a.state);
    Move::move(a.move);

    actions[actionsIndex] = a;
    actionsIndex = (actionsIndex + 1) % ACTIONS_SIZE;
    actionsLength = min(actionsLength + 1, ACTIONS_SIZE);
}

void rewardActions() {
    for (int i = 0; i < actionsLength; i++) {
        Action action = actions[i];
        m.reward(action.state, action.move);
    }
    actionsIndex = 0;
    actionsLength = 0;
}

void punishActions() {
    for (int i = 0; i < actionsLength; i++) {
        Action action = actions[i];
        m.punish(action.state, action.move);
    }
    actionsIndex = 0;
    actionsLength = 0;
}

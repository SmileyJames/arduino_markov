#include <IRremote.h>
#include "Move.h"
#include "Track.h"
#include "Markov.h"

#define ACTION_DURATION 4000
#define ACTIONS_SIZE 5

#define IR_RECV 12

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

Markov::Process m;

Track::Input prevTrack;
Action actions[ACTIONS_SIZE];
int actionsIndex = 0;
int actionsLength = 0;


void setup() {
    Serial.begin(9600);
    irRecv.enableIRIn();
    Track::setup();
    Move::setup();
}


void loop() {
    if (irRecv.decode(&irInput)){
        time = millis();
        irValue = irInput.value;
        irRecv.resume();

        switch (irValue) {
            case KEY_STAR:
                m.load();
            break;
            case KEY_HASH:
                m.save();
            break;
            case KEY_UP:
                rewardActions();
            break;
            case KEY_DOWN:
                punishActions();
            break;
        }
    } else {
        if (millis() - time > ACTION_DURATION) {
            time = millis();
            nextAction();
        }
    }
}

void nextAction() {
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
    for (int i = actionsLength; i < actionsLength; i++) {
        Action action = actions[i];
        m.reward(action.state, action.move);
    }
    actionsIndex = 0;
    actionsLength = 0;
}

void punishActions() {
    for (int i = actionsLength; i < actionsLength; i++) {
        Action action = actions[i];
        m.punish(action.state, action.move);
    }
    actionsIndex = 0;
    actionsLength = 0;
}

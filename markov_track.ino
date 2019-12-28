#include <IRremote.h>
#include "Move.h"
#include "Track.h"
#include "Markov.h"

#define ACTION_DURATION 400
#define ACTIONS_SIZE 60

#define IR_RECV 13

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
    irRecv.enableIRIn();
    Track::setupTrack();
    Move::setupMove();
    // m = Markov::Process();
}


void loop() {
    if (irRecv.decode(&irInput)){ 
        time = millis();
        irValue = irInput.value;
        irRecv.resume();

        switch (irValue) {
            case KEY_STAR:
                m.load();
            case KEY_HASH:
                m.save();
            case KEY_UP:
                rewardActions();
            case KEY_DOWN:
                punishActions();
        }
    } else {
        if (millis() - time > ACTION_DURATION) {
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
}

void punishActions() {
    for (int i = actionsLength; i < actionsLength; i++) {
        Action action = actions[i];
        m.punish(action.state, action.move);
    }
}

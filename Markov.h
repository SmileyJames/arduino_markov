#ifndef MARKOV_H 
#define MARKOV_H 

#include "Track.h"
#include "Move.h"

#define STATE_SIZE 64

namespace Markov {
    using Int = unsigned short int;
    using Byte = unsigned char;

    struct State {
        Track::Input track0;
        Track::Input track1;
    };

    union Value {
        Int value;
        Byte split[2]; 
    };

    class Process {
        public:
            Move::Command get(State);
            void reward(State, Move::Command, int);
            void punish(State, Move::Command, int);
            void save();
            void load();
            void clear();
            void print();
        private:
            void sub(int s, int m, Int val);
            void add(int s, int m, Int val);
            Value chain[STATE_SIZE][MOVE_SIZE];
            Int getIndex(State);
    };
}

#endif

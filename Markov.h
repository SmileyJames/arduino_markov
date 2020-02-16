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
            void loss(State, Move::Command, int);
            void save();
            void load();
            void clear();
            void print();
        private:
            Value chain[STATE_SIZE][MOVE_SIZE];
            Int getIndex(State);
    };
}

#endif

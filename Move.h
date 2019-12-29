#ifndef MOVE_H 
#define MOVE_H 

#define MOVE_SIZE 8

namespace Move {
    enum Command {
        Forward,
        ForwardPlus,
        Backward,
        Left,
        LeftPlus,
        Right,
        RightPlus,
        Stop,
    };

    void setup();
    void move(Command);
    void stop();
}

#endif

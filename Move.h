#ifndef MOVE_H 
#define MOVE_H 

#define MOVE_SIZE 8

namespace Move {
    enum Command {
        Forward,
        ForwardPlus,
        Backward,
        LeftTurn,
        LeftPivot,
        RightTurn,
        RightPivot,
        Stop,
    };

    void setupMove();
    void move(Command);
}

#endif

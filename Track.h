#ifndef TRACK_H
#define TRACK_H 

namespace Track {
    enum Input {
        None,
        Right,
        Middle,
        MiddleRight,
        Left,
        LeftRight,
        LeftMiddle,
        LeftMiddleRight,
    };

    void setupTrack();
    Input track();
}

#endif

#ifndef YARAOSUD_TIMER_H
#define YARAOSUD_TIMER_H

#include "Include.h"
class Timer {
private:
    clock_t start_time;
public:
    void start() {
        start_time = clock();
    }

    double elapsedMili() {
        return static_cast<double>(clock() - start_time);
    }
    int elapsedSec() {
        return static_cast<int>(clock() - start_time)/CLOCKS_PER_SEC;
    }
};


#endif //YARAOSUD_TIMER_H

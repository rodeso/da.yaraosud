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

    double elapsed() {
        return static_cast<double>(clock() - start_time);
    }
};


#endif //YARAOSUD_TIMER_H

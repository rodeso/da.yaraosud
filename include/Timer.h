#ifndef YARAOSUD_TIMER_H
#define YARAOSUD_TIMER_H

#include "Include.h"
/**
 * @class Timer
 * @brief A class for measuring time intervals.
 */
class Timer {
private:
    clock_t start_time; /**< The start time of the timer. */

public:
    /**
     * @brief Starts the timer.
     */
    void start() {
        start_time = clock();
    }

    /**
     * @brief Calculates the elapsed time in milliseconds.
     * @return The elapsed time in milliseconds.
     */
    double elapsedMili() {
        return static_cast<double>(clock() - start_time);
    }

    /**
     * @brief Calculates the elapsed time in seconds.
     * @return The elapsed time in seconds.
     */
    int elapsedSec() {
        return static_cast<int>(clock() - start_time) / CLOCKS_PER_SEC;
    }
};


#endif //YARAOSUD_TIMER_H

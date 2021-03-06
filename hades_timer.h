#ifndef HADES_TIMER_H
#define HADES_TIMER_H

#include <stddef.h>
#include <stdbool.h>

/** defined in "hades_timer.h"
 * Hades_Timer
 *  Timer tool
 *
 * Fields
 *  size_t start_ticks      ticks since first started
 *        paused_ticks      ticks since last paused
 *
 *  bool        paused      true if paused
 *             started      true if started
 */
typedef struct Hades_Timer {
    size_t start_ticks, paused_ticks;
    bool paused, started;
} Hades_Timer;

/** defined in "hades_timer.h"
 * Hades_Timer* Hades_CreateTimer();
 *  Create a new timer
 */
Hades_Timer* Hades_CreateTimer();

/** defined in "hades_timer.h"
 * void Hades_StartTimer(Hades_Timer* timer);
 *  Start the timer
 */
void Hades_StartTimer(Hades_Timer*);

/** defined in "hades_timer.h"
 * void Hades_StopTimer(Hades_Timer* timer);
 *  Stop the timer
 */
void Hades_StopTimer(Hades_Timer*);

/** defined in "hades_timer.h"
 * void Hades_PauseTimer(Hades_Timer* timer);
 *  Pause the timer
 */
void Hades_PauseTimer(Hades_Timer*);

/** defined in "hades_timer.h"
 * void Hades_UnpauseTimer(Hades_Timer* timer);
 *  Unpause the timer
 */
void Hades_UnpauseTimer(Hades_Timer*);

/** defined in "hades_timer.h"
 * size_t Hades_GetTimerTicks(Hades_Timer* timer);
 *  Get the ticks since the timer started
 */
size_t Hades_GetTimerTicks(Hades_Timer*);

/** defined in "hades_timer.h"
 * bool Hades_TimerIsStarted(Hades_Timer* timer);
 *  Returns true if timer has been started
 */
bool Hades_TimerIsStarted(Hades_Timer*);

/** defined in "hades_timer.h"
 * bool Hades_TimerIsPaused(Hades_Timer* timer);
 *  Returns true if timer has been paused
 */
bool Hades_TimerIsPaused(Hades_Timer*);

#endif

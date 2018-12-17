#include "hades_timer.h"
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

Hades_Timer* Hades_CreateTimer()
{
    Hades_Timer* timer = (Hades_Timer*) malloc(sizeof(Hades_Timer));
    timer->start_ticks = 0;
    timer->paused_ticks = 0;
    timer->paused = false;
    timer->started = false;
    return timer;
}

void Hades_DestroyTimer(Hades_Timer* timer)
{
    free(timer);
}

void Hades_StartTimer(Hades_Timer* timer)
{
    timer->started = true;
    timer->paused = false;
    timer->start_ticks = SDL_GetTicks();
    timer->paused_ticks = 0;
}

void Hades_StopTimer(Hades_Timer* timer)
{
    timer->started = false;
    timer->paused = false;
    timer->start_ticks = 0;
    timer->paused_ticks = 0;
}

void Hades_PauseTimer(Hades_Timer* timer)
{
    if (!timer->started || timer->paused) {
        return;
    }
    timer->paused = true;
    timer->paused_ticks = SDL_GetTicks() - timer->start_ticks;
    timer->start_ticks = 0;
}

void Hades_UnpauseTimer(Hades_Timer* timer)
{
    if (!timer->started || !timer->paused) {
        return;
    }
    timer->paused = false;
    timer->start_ticks = SDL_GetTicks() - timer->paused_ticks;
    timer->paused_ticks = 0;
}

size_t Hades_GetTimerTicks(Hades_Timer* timer)
{
    if (!timer->started) {
        return 0;
    } else if (timer->paused) {
        return timer->paused_ticks;
    }
    return SDL_GetTicks() - timer->start_ticks;
}

bool Hades_TimerIsStarted(Hades_Timer* timer)
{
    return timer->started;
}

bool Hades_TimerIsPaused(Hades_Timer* timer)
{
    return timer->paused;
}

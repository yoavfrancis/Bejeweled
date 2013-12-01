#include "Timer.h"
#include <SDL.h>

namespace bejeweled {

Timer::Timer() : m_startTicks(0), m_pausedTicks(0), m_paused(false), m_started(false) {  
}

void Timer::start() {
    m_started = true;
    m_paused = false;
    m_startTicks = SDL_GetTicks();
}

void Timer::stop() {
    m_started = false;
    m_paused = false;
}

void Timer::pause() {
    if(m_started && !m_paused) {
        m_paused = true;
        m_pausedTicks = SDL_GetTicks() - m_startTicks;
    }
}

void Timer::unpause() {
    if(m_paused) {
        m_paused = false;
        m_startTicks = SDL_GetTicks() - m_pausedTicks;
        m_pausedTicks = 0;
    } 
}

int Timer::getTicks() const {
    if(m_started) {
        if(m_paused) {
            return m_pausedTicks;
        } 
        return SDL_GetTicks() - m_startTicks;
    }
    return 0;
}

bool Timer::isStarted() const {
    return m_started;
}

bool Timer::isPaused() const {
    return m_paused;
}

} //namespace bejeweled
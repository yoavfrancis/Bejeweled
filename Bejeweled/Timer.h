#ifndef __Bejeweled_Timer_h__
#define __Bejeweled_Timer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

namespace bejeweled {

/**
 * Describes a game timer. Inspired by Lazyfoo.net
 */
class Timer
{
public:
    /// Constructor
    Timer();

    /// game timer operations
    void start();
    void stop();
    void pause();
    void unpause();

    /// Gets the timer's time
    int getTicks() const;

    /// Checks the status of the timer
    bool isStarted() const;
    bool isPaused() const;   

private:
    /// The clock time when the timer started
    int m_startTicks;

    /// The ticks stored when the timer was paused
    int m_pausedTicks;

    /// The timer status
    bool m_paused;
    bool m_started;
}; // class Timer

} // namespace bejeweled

#endif // __Bejeweled_Timer_h__

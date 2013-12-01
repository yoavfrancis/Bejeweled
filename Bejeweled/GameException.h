#ifndef __Bejeweled_GameException_h__
#define __Bejeweled_GameException_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <stdexcept>
#include <string>

namespace bejeweled {

using std::runtime_error;
using std::string;

/**
 * Represents an exception in the game. Displays the last SDL error as a text when thrown.
 */
class GameException : public runtime_error
{
public:
    /// Empty ctor uses SDL_GetError as the message.
    GameException();

    /// ctor from string that contains the msg.
    GameException(const string&);
    
    /// ctor from char* that contains the msg.
    GameException(const char*);
    
    /// virtual dtor
    virtual ~GameException() throw();
};

} // namespace bejeweled

#endif // __Bejeweled_GameException_h__
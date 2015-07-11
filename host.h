#ifndef HOSTS_HOST_H_INCLUDED
#define HOSTS_HOST_H_INCLUDED

#define HOST_VERSION_MAJOR 0
#define HOST_VERSION_MINOR 3
#define HOST_VERSION_MINI 0

#define HOST_UP 0
#define HOST_DOWN 1
#define HOST_LEFT 2
#define HOST_RIGHT 3
#define HOST_ACTION 4
#define HOST_BUTTON1 5
#define HOST_BUTTON2 6
#define HOST_BUTTON3 7
#define HOST_BUTTON4 8
#define HOST_BUTTON5 9
#define HOST_BUTTON6 10

#define HOST_BUTTONCOUNT 11

#define HOST_RETURNCODE_USEFIXEDFUNCTION 0
#define HOST_RETURNCODE_USEINPUTMETHODS 1
#define HOST_RETURNCODE_USECALLBACK 2

/**
 * @brief Initiates the host. 
 *
 * This can be implemented if the host needs 
 * initialization.
 */
extern "C"
{
    int init(int playerCount);
}
/**
 * @brief Gets the state of the specified button. 
 *
 * States are integers between 0 and 100000, while 0 means 
 * completely off and 100000 means completely on.
 *
 * This function gets called every frame of the input loop, so there must 
 * not be any delays. The best way to accomodate this is to use an internal
 * caching mechanism.
 */
extern "C"
{
    int getButtonState(int playerID, int button);
}

namespace piga
{
    class GameInput;
}
extern "C"
{
    void setGameInput(piga::GameInput *gameInput);
}


/**
 * @brief Sets a callback function to be called when an input happens.
 *
 * This function will only be called when @ref HOST_RETURNCODE_USECALLBACK
 * is set.
 */
extern "C"
{
    void setCallbackFunc(void (*inputHappened)(int, int, int));
}

/**
 * @brief Gets called before the host will be destroyed. 
 *
 * This can be implemented if the host needs a destruction handling.
 */
extern "C"
{
    int destroy();
}

extern "C"
{
    int getPigaMajorVersion()
    {
        return HOST_VERSION_MAJOR;
    }
    int getPigaMinorVersion()
    {
        return HOST_VERSION_MINOR;
    }
    int getPigaMiniVersion()
    {
        return HOST_VERSION_MINI;
    }
    /**
     * Returns the name of the host. (Set by the host programmer.)
     */
    const char* getName();
    /**
     * Returns the description of the host. (Set by the host programmer.)
     */
    const char* getDescription();
    /**
     * @brief Returns the author of the host. (Set by the host programmer.)
     */
    const char* getAuthor();
}

#endif

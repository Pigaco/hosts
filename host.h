#ifndef HOSTS_HOST_H_INCLUDED
#define HOSTS_HOST_H_INCLUDED

#include "host_defines.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Initiates the host. 
 *
 * This can be implemented if the host needs 
 * initialization.
 */
int init(int playerCount);
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
int getButtonState(int playerID, int button);

#ifdef __cplusplus
namespace piga {
    class GameInput;
}
void setGameInput(piga::GameInput *gameInput);
#endif

/**
 * @brief A shortcut to leave out the implementation of the output functions. 
 *
 * @return HOST_RETURNCODE_FALSE if the host doesn't implement outputs, HOST_RETURNCODE_TRUE if it does. 
 */
int implementsOutputs();
/**
 * @brief Returns the number of outputs (all types and positions) this host is capable of. 
 *
 * @return The number of outputs. Numbers can be used to iterate over the possible outputs in the getOutputType() and getOutputPos() functions.
 */
int getOutputCount();
/**
 * @brief Returns the type of the specified output.
 *
 * @param outputID The ID of the output.
 *
 * @return The HOST_OUTPUT_TYPE of the output. 
 */
int getOutputType(int outputID);
/**
 * @brief Returns the position of the specified output.
 *
 * @param outputID The ID of the output.
 *
 * @return The HOST_OUTPUT_POS of the specified output. 
 */
int getOutputPos(int outputID);
/**
 * @brief Returns the name of the specified output. 
 *
 * @param outputID The ID of the output to get the name from. 
 *
 * @return The name of the output. 
 */
const char* getOutputName(int outputID);
/**
 * @brief Returns the description of the specified output. 
 *
 * @param outputID The ID of the output to get the description from. 
 *
 * @return The description of the output. 
 */
const char* getOutputDescription(int outputID);

int getIntOutputRangeMin(int outputID);
int getIntOutputRangeMax(int outputID);
float getFloatOutputRangeMin(int outputID);
float getFloatOutputRangeMax(int outputID);
double getDoubleOutputRangeMin(int outputID);
double getDoubleOutputRangeMax(int outputID);

/**
 * @brief Sets a color output. 
 *
 * @param outputID The ID of the output. 
 * @param r Red
 * @param g Green
 * @param b Blue
 * @param a Alpha (if used)
 *
 * @return HOST_RETURNCODE_SUCCESS if successful, HOST_RETURNCODE_FAIL or HOST_RETURNCODE_FAIL_INVALID_TYPE otherwise. 
 */
int setColorOutput(int outputID, float r, float g, float b, float a);
/**
 * @brief Sets a true/false output. 
 *
 * @param outputID The ID of the output. 
 * @param value 1 means true, 0 means false. 
 *
 * @return HOST_RETURNCODE_SUCCESS if successful, HOST_RETURNCODE_FAIL or HOST_RETURNCODE_FAIL_INVALID_TYPE otherwise. 
 */
int setBoolOutput(int outputID, int value);
/**
 * @brief Sets a string output. 
 *
 * @param outputID The ID of the output. 
 * @param outString The string to be sent to the output. 
 *
 * @return HOST_RETURNCODE_SUCCESS if successful, HOST_RETURNCODE_FAIL or HOST_RETURNCODE_FAIL_INVALID_TYPE otherwise. 
 */
int setStringOutput(int outputID, const char* outString);
/**
 * @brief Sets an integer output. 
 *
 * @param outputID The ID of the output. 
 * @param value The value to be sent to the output. 
 *
 * @return HOST_RETURNCODE_SUCCESS if successful, HOST_RETURNCODE_FAIL or HOST_RETURNCODE_FAIL_INVALID_TYPE otherwise. 
 */
int setIntOutput(int outputID, int value);
/**
 * @brief Sets a float output. 
 *
 * @param outputID The ID of the output. 
 * @param value The value to be sent to the output. 
 *
 * @return HOST_RETURNCODE_SUCCESS if successful, HOST_RETURNCODE_FAIL or HOST_RETURNCODE_FAIL_INVALID_TYPE otherwise. 
 */
int setFloatOutput(int outputID, float value);
/**
 * @brief Sets a double output. 
 *
 * @param outputID The ID of the output. 
 * @param value The value to be set to the output. 
 *
 * @return HOST_RETURNCODE_SUCCESS if successful, HOST_RETURNCODE_FAIL or HOST_RETURNCODE_FAIL_INVALID_TYPE otherwise. 
 */
int setDoubleOutput(int outputID, double value);

/**
 * @brief Sets a callback function to be called when an input happens.
 *
 * This function will only be called when @ref HOST_RETURNCODE_USECALLBACK
 * is set.
 *
 * Parameters for the input callback function: ControlCode/ButtonID, PlayerID, state
 */
void setCallbackFunc(host_input_callback_func callback);

/**
 * @brief Gets called before the host will be destroyed. 
 *
 * This can be implemented if the host needs a destruction handling.
 */
int destroy();

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

#ifdef __cplusplus
}
#endif

#endif

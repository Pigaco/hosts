#include <outputs.hpp>
#include "../../host_defines.h"

namespace Outputs
{
    int implementsOutputs()
    {
        //Yes, this host implements outputs. 
        return HOST_RETURNCODE_TRUE;
    }

    int getOutputCount()
    {
        //We have 12 outputs in this host:
        //6 for player 1 
        //6 for palyer 2
        return 12;
    }
    int getOutputType(int outputID)
    {
        if(outputID >= 0 && outputID < 12)
        {
            //The LEDs have strengths represented in a ranged integer type. 
            //Because of the limitations of the arduino system, the range is [0;255]
            return HOST_OUTPUT_TYPE_RANGED_INTEGER;
        }

        return HOST_OUTPUT_TYPE_BOOL;
    }
    int getOutputPos(int outputID)
    {
        int pos = 0;
        if(outputID >= 0 && outputID < 6)
        {
            //Player 1 buttons
            pos = HOST_OUTPUT_POS_CONTROLS_PLAYER_1;
        }
        else if(outputID >= 6 && outputID < 12) 
        {
            //Player 2 buttons
            pos = HOST_OUTPUT_POS_CONTROLS_PLAYER_2;
        }

        //Define the positions of the inputs individually.
        switch(outputID % 6) 
        {
            case 0: 
                pos = pos | HOST_OUTPUT_POS_1;
                break;
            case 1: 
                pos = pos | HOST_OUTPUT_POS_2;
                break;
            case 2: 
                pos = pos | HOST_OUTPUT_POS_3;
                break;
            case 3: 
                pos = pos | HOST_OUTPUT_POS_4;
                break;
            case 4: 
                pos = pos | HOST_OUTPUT_POS_5;
                break;
            case 5: 
                pos = pos | HOST_OUTPUT_POS_6;
                break;
        }

        return pos;
    }

#define SWITCH_OUTPUT_NAME_CASE(CASENUM, PLAYER, ID) case CASENUM: return "Player " PLAYER " - Button " ID " LED"; 
    const char* getOutputName(int outputID)
    {
        switch(outputID)
        {
            SWITCH_OUTPUT_NAME_CASE(0, "1", "1")
            SWITCH_OUTPUT_NAME_CASE(1, "1", "2")
            SWITCH_OUTPUT_NAME_CASE(2, "1", "3")
            SWITCH_OUTPUT_NAME_CASE(3, "1", "4")
            SWITCH_OUTPUT_NAME_CASE(4, "1", "5")
            SWITCH_OUTPUT_NAME_CASE(5, "1", "6")

            SWITCH_OUTPUT_NAME_CASE(6, "2", "1")
            SWITCH_OUTPUT_NAME_CASE(7, "2", "2")
            SWITCH_OUTPUT_NAME_CASE(8, "2", "3")
            SWITCH_OUTPUT_NAME_CASE(9, "2", "4")
            SWITCH_OUTPUT_NAME_CASE(10, "2", "5")
            SWITCH_OUTPUT_NAME_CASE(11, "2", "6")
        }
        return "Unnamed";
    }
#define SWITCH_OUTPUT_DESC_CASE(CASENUM, PLAYER, ID) case CASENUM: return "LED output (0-255) of player " PLAYER " on button " ID "."; 
    const char* getOutputDescription(int outputID)
    {
        switch(outputID)
        {
            SWITCH_OUTPUT_DESC_CASE(0, "1", "1")
            SWITCH_OUTPUT_DESC_CASE(1, "1", "2")
            SWITCH_OUTPUT_DESC_CASE(2, "1", "3")
            SWITCH_OUTPUT_DESC_CASE(3, "1", "4")
            SWITCH_OUTPUT_DESC_CASE(4, "1", "5")
            SWITCH_OUTPUT_DESC_CASE(5, "1", "6")

            SWITCH_OUTPUT_DESC_CASE(6, "2", "1")
            SWITCH_OUTPUT_DESC_CASE(7, "2", "2")
            SWITCH_OUTPUT_DESC_CASE(8, "2", "3")
            SWITCH_OUTPUT_DESC_CASE(9, "2", "4")
            SWITCH_OUTPUT_DESC_CASE(10, "2", "5")
            SWITCH_OUTPUT_DESC_CASE(11, "2", "6")
        }
        return "No Description.";
    }

    int getIntOutputRangeMin(int outputID)
    {
        if(outputID >= 0 && outputID < 12)
        {
            return 0;
        }
        return 0;
    }
    int getIntOutputRangeMax(int outputID)
    {
        if(outputID >= 0 && outputID < 12)
        {
            return 255;
        }
        return 0;
    }

    int setIntOutput(int outputID, int value)
    {
        if(outputID >= 0 && outputID < 12 && value >= 0 && value <= 255)
        {
            //This is a valid output!
            
            return HOST_RETURNCODE_SUCCESS;
        }
        else
        {
            return HOST_RETURNCODE_FAIL;
        }
    }
}

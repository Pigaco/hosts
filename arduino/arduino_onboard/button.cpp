#include "Arduino.h"
#include "button.h"
#include "serial_connector.h"

SerialConnector* Button::serialConnector = 0;
int Button::m_cacheVal = 0;

Button::Button(const uint8_t pin, const uint8_t button)
    : m_pin(pin), m_button(button)
{

}
Button::~Button()
{

}

void Button::loop()
{
    updateCache();

    if(m_currentState == false
            && m_cacheVal == 1)
    {
        //Button went from LOW to HIGH
        m_currentState = true;
        serialConnector->sendInput(m_button, true);
    }
    else if(m_currentState == true 
            && m_cacheVal == 0)
    {
        //Button went from HIGH to LOW
        m_currentState = false;
        serialConnector->sendInput(m_button, false);
    }

    //No other states are neccessary. 
}

void Button::updateCache()
{
    m_cacheVal = digitalRead(m_pin);
}

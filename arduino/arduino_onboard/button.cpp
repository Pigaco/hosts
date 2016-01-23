#include "Arduino.h"
#include "button.h"
#include "serial_connector.h"

SerialConnector* Button::serialConnector = 0;

Button::Button(const uint8_t pin, const uint8_t button)
    : m_button(button)
{
    pinMode(pin, INPUT);
    digitalWrite(pin, HIGH);

    m_pinBouncer.attach(pin);
    m_pinBouncer.interval(BUTTON_BOUNCE_INTERVAL);
}
Button::~Button()
{

}

void Button::loop()
{
    if(m_pinBouncer.update()) 
    {
        //Only update if the button has a new state. 
        if(m_pinBouncer.read())
        {
            //Button went from LOW to HIGH
            serialConnector->sendInput(m_button, true);
        } 
        else 
        {
            //Button went from HIGH to LOW
            serialConnector->sendInput(m_button, false);
        }
    }
}

#include "Arduino.h"
#include "button.h"
#include "serial_connector.h"

#define BOUNCE_LOCK_OUT
#include "bounce2/Bounce2.h"

SerialConnector* Button::serialConnector = 0;
int Button::m_cacheVal = 0;

Button::Button(const uint8_t pin, const uint8_t button)
    : m_pin(pin), m_button(button), m_pinBouncer()
{
    pinMode(pin, INPUT);
    digitalWrite(pin, HIGH);

    m_pinBouncer.attach(pin);
    m_pinBouncer(BUTTON_BOUNCE_INTERVAL);
}
Button::~Button()
{

}

void Button::loop()
{
    if(m_pinBouncer.update() != 0) 
    {
        if(m_pinBouncer.read() == 1)
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

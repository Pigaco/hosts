#include "Arduino.h"
#include "led.h"

LED::LED(const uint8_t pin)
    : m_pin(pin), m_pwr(0), m_counter(0), m_state(0)
{

}
LED::~LED()
{

}

void LED::loop()
{
    m_counter -= 1;
    if(m_counter == 0)
    {
        //When 0 is reached, the counter will be set up to 255. 
        //0 means off, so the LED must not be switched. 
        m_counter = 255;
    }
    if(m_pwr >= m_counter) 
    {
        digitalWrite(m_pin, m_state);
        if(m_state == 1)
            m_state = 0;
        else
            m_state = 1;
    }
}

void LED::setPwr(uint8_t pwr)
{
    m_pwr = pwr;
}
uint8_t LED::getPwr()
{
    return m_pwr;
}
void LED::setCounter(uint8_t counter)
{
    m_counter = counter;
}
uint8_t LED::getCounter()
{
    return m_counter;
}


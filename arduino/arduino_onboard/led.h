#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

class LED
{
    public:
        LED(const uint8_t pin);
        ~LED();

        void loop();
        
        void setPwr(uint8_t pwr);
        uint8_t getPwr();

        void setCounter(uint8_t counter);
        uint8_t getCounter();
    private:
        const uint8_t m_pin;
        uint8_t m_pwr;
        uint8_t m_counter;
        uint8_t m_state;
};

#endif

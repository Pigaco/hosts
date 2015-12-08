#ifndef SERIAL_CONNECTOR_H_INCLUDED
#define SERIAL_CONNECTOR_H_INCLUDED

class LED;

class SerialConnector
{
    public:
        SerialConnector(const int baudRate);
        ~SerialConnector();

        void setup();
        void loop();

        void sendInput(uint8_t button, bool state);
        LED** leds;
    private:
        void handleLongPacket();
        void handleShortPacket();

        const int m_baudRate;
        uint8_t m_serialInput[2];

};

#endif

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
        void flush();

        void sendInput(uint8_t button, bool state);
        LED** leds;

        void sendHello();
        void handleHello(byte packet);
    private:
        void handleLongPacket();
        void handleShortPacket();

        const int m_baudRate;
        char m_serialInput[3];

};

#endif

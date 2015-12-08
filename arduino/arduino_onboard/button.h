#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

//Taken from the host api
#define BUTTON_UP 0
#define BUTTON_DOWN 1
#define BUTTON_LEFT 2
#define BUTTON_RIGHT 3
#define BUTTON_ACTION 4
#define BUTTON_BUTTON1 5
#define BUTTON_BUTTON2 6
#define BUTTON_BUTTON3 7
#define BUTTON_BUTTON4 8
#define BUTTON_BUTTON5 9
#define BUTTON_BUTTON6 10

class SerialConnector;

class Button
{
    public:
        Button(const uint8_t pin, const uint8_t button);
        ~Button();

        void loop();

        void updateCache();

        static SerialConnector* serialConnector;
    private:
        const uint8_t m_pin;
        /**
         * Button-IDs:
         *
         * The buttons are kept as bytes, because enums would 
         * be a source of problems in this context. 
         *
         * See host.h for a detailed explanation. Here is a short list:
         *   - 0: UP
         *   - 1: DOWN
         *   - 2: LEFT
         *   - 3: RIGHT
         *   - 4: ACTION
         *   - 5: BUTTON 1
         *   - 6: BUTTON 2
         *   - 7: BUTTON 3
         *   - 8: BUTTON 4
         *   - 9: BUTTON 5
         *   - 10: BUTTON 6
         */
        const uint8_t m_button;

        bool m_currentState = false;

        //Cache value for getting the current button state. Static to save memory.
        static int m_cacheVal;
};

#endif

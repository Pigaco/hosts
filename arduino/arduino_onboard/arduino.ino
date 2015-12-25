#include "serial_connector.h"
#include "button.h"
#include "led.h"

//If you change the baud rate here, you also have 
//to change it in the makefile.
SerialConnector serialConnector(115200);

//Workaround for an arduino compiler bug
void* __dso_handle;
void* __cxa_atexit;

//LEDs
LED *leds[6];

//Buttons
Button *buttons[11];

void setup(void)
{
    //Status-LED
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    serialConnector.setup();

    //Send the hello signal, so the host knows the arduino is up. 
    serialConnector.sendHello();
    serialConnector.flush();

    Button::serialConnector = &serialConnector;

    //Create LEDs and buttons.
    //Be cautious with the IDs and pins!
    //
    //!!!!!!!!!!!
    //CHANGE THIS
    //!!!!!!!!!!!
    
    //LEDs use the analog pins.
    leds[0] = new LED(A0);
    leds[1] = new LED(A1);
    leds[2] = new LED(A2);
    leds[3] = new LED(A3);
    leds[4] = new LED(A4);
    leds[5] = new LED(A5);

    //Buttons use the digital pins.
    buttons[0] = new Button(2, BUTTON_UP);
    buttons[1] = new Button(3, BUTTON_DOWN);
    buttons[2] = new Button(4, BUTTON_LEFT);
    buttons[3] = new Button(5, BUTTON_RIGHT);
    buttons[4] = new Button(6, BUTTON_ACTION);
    buttons[5] = new Button(7, BUTTON_BUTTON1);
    buttons[6] = new Button(8, BUTTON_BUTTON2);
    buttons[7] = new Button(9, BUTTON_BUTTON3);
    buttons[8] = new Button(10, BUTTON_BUTTON4);
    buttons[9] = new Button(11, BUTTON_BUTTON5);
    buttons[10] = new Button(12, BUTTON_BUTTON6);

    serialConnector.leds = leds;
}

void loop(void)
{
    int i;

    serialConnector.loop();

    for(i = 0; i < 6; ++i)
    {
        leds[i]->loop();
    }

    for(i = 0; i < 11; ++i)
    {
        buttons[i]->loop();
    }
}

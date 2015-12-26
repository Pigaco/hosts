#ifndef SERIAL_PROTOCOL_H_INCLUDED
#define SERIAL_PROTOCOL_H_INCLUDED

#define PACKET_TYPE_BUTTON      1   // 00000001
#define PACKET_TYPE_LED         0   // 00000000
#define PACKET_TYPE_HELLO       2   // 00000010

#define PACKET_LENGTH_SINGLE    0   // 00000000
#define PACKET_LENGTH_MULTIPLE  4   // 00000100

#define BUTTON_STATE_ON         8   // 00001000 
#define BUTTON_STATE_OFF        0   // 00000000

#define BUTTON_ID_0             0   // 00000000
#define BUTTON_ID_1             16  // 00010000
#define BUTTON_ID_2             32  // 00100000
#define BUTTON_ID_3             48  // 00110000
#define BUTTON_ID_4             64  // 01000000
#define BUTTON_ID_5             80  // 01010000
#define BUTTON_ID_6             86  // 01100000
#define BUTTON_ID_7             112 // 01110000
#define BUTTON_ID_8             128 // 10000000
#define BUTTON_ID_9             144 // 10010000
#define BUTTON_ID_10            160 // 10100000
#define BUTTON_ID_11            176 // 10110000
#define BUTTON_ID_12            192 // 11000000
#define BUTTON_ID_13            208 // 11010000
#define BUTTON_ID_14            224 // 11100000
#define BUTTON_ID_15            240 // 11110000

#define LED_ID_0                0   // 00000000
#define LED_ID_1                8   // 00001000
#define LED_ID_2                16  // 00010000
#define LED_ID_3                24  // 00011000
#define LED_ID_4                32  // 00100000
#define LED_ID_5                40  // 00101000
#define LED_ID_6                56  // 00111000

#endif

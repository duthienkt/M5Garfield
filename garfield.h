
#ifndef ESP32
#define ESP32
#endif

#ifndef GARFIELD_H
#define GARFIELD_H
#include <M5Stack.h>

#define G_KEYBOARD_I2C_ADDR 0X08
#define G_KEYBOARD_INT 5

#define G_KEY_UP 1
#define G_KEY_DOWN 2
#define G_KEY_LEFT 4
#define G_KEY_RIGHT 8
#define G_KEY_A 16
#define G_KEY_B 32
#define G_KEY_SELECT 64
#define G_KEY_START 128







typedef void (*g_keyboard_callback)(uint8_t code);
typedef void (*g_update_callback)(float deltaTime);
typedef void (*g_draw_callback)();

g_keyboard_callback gKeyboardCallback = NULL;
g_update_callback gUpdateCallback = NULL;
g_draw_callback gDrawCallback = NULL;

long gFrameCount = 0;
long long gLastUpdateTime = 0;
long long gNowTime = 0;
long long gDelayTime = 0;

void gInit()
{
    M5.begin();
    Wire.begin();
    pinMode(G_KEYBOARD_INT, INPUT_PULLUP);
    gNowTime = millis();
}

void gLoop()
{
    //for key event
    if (digitalRead(G_KEYBOARD_INT) == LOW)
    {
        Wire.requestFrom(G_KEYBOARD_I2C_ADDR, 1); // request 1 byte from keyboard
        while (Wire.available())
        {
            uint8_t key_val = Wire.read(); // receive a byte as character
            if (key_val != 0 && gKeyboardCallback != NULL)
            {
                gKeyboardCallback(key_val);
            }
        }
    }
    gLastUpdateTime = gNowTime;
    gNowTime = millis();
    if (gNowTime < gLastUpdateTime) gLastUpdateTime = 0;
    if (gUpdateCallback != NULL)
        gUpdateCallback((gNowTime - gLastUpdateTime)/1000.0);
    if (gDrawCallback != NULL)
        gDrawCallback();
    ++gFrameCount;
    gDelayTime = gNowTime+33 - millis();
    if (gDelayTime < 0) gDelayTime = 0;
    delay(gDelayTime);
}

void gKeyboardFunc(g_keyboard_callback cb)
{
    gKeyboardCallback = cb;
}

void gUpdateFunc(g_update_callback cb)
{
    gUpdateCallback = cb;
}

void gDrawFunc(g_draw_callback cb){
  gDrawCallback = cb;
}

/* code */
#endif ///*define*/


#include "garfield.h"
#include "math.h"
#include "tetris.h"

float w = 320;
float h = 240;

int  blockType = 0;
int blockState = 0;

void onKey(uint8_t _key)
{
  if (!(_key & G_KEY_UP)){
    blockType = (blockType +1)%7;
    blockState = 0;
  }
  if (!(_key & G_KEY_DOWN))
  {
    blockType = (blockType + 6) % 7;
    blockState = 0;
  }

  if (!(_key & G_KEY_A))
  {
    blockState = (blockState + 1) % 4;
  }

  if (!(_key & G_KEY_B))
  {
    blockState = (blockState + 3) % 4;
  }
}


void setup()
{
  gInit();
  tetris::init();
}

void loop()
{
  gLoop();
}

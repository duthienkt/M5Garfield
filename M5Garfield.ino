
#include "garfield.h"
#include "math.h"
#include "tetris.h"

void setup()
{
  gInit();
  tetris::init();
}

void loop()
{
  gLoop();
}

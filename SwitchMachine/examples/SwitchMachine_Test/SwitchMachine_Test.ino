#include <Pulser.h>

#include "SwitchMachine.h"

const int P1 = 5;
const int P2 = 4;
const int EN = 3;
const int LED = 13;

SwitchMachine* sm;
Pulser ctrl(1000, 2000);

void setup()
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  sm = new SwitchMachine(eLH, P2, P1, EN);
  sm->setRoute(eMain);
  delay(2000);
}

void loop()
{
  sm->update();
  ctrl.update();
  if (ctrl.read()) {
    sm->setRoute(eDiverging);
  } else {
    sm->setRoute(eMain);
  }
}

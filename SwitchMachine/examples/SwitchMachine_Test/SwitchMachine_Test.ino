#include <Pulser.h>
#include <SwitchMachine.h>

const int P_RED = 5;  // pin driving red wire
const int P_BLK = 4;  // pin driving black wire
const int P_ENA = 3;  // pin driving enable

// NOTE: Pointers to SwitchMachine objects should
// be used so they can be created in sequence,
// to prevent them from trying to initialize (move)
// at the same time.

SwitchMachine* sm;        // pointer to object
Pulser ctrl(1000, 2000);  // on 1 sec, off 2 sec, repeat

void setup()
{
  // Create new SwitchMachine object.  Switch machine
  // will set itself to default position (main for LH
  // and RH, left for Y, parallel for DX).
  sm = new SwitchMachine(P_RED, P_BLK, P_ENA);
  delay(1000);
}

void loop()
{
  // Update SwitchMachine's state machine.
  sm->update();
  // Update Pulser.
  ctrl.update();
  // If Pulser is ON...
  if (ctrl.read()) {
    // ... throw points to other position
    // (LH RH diverging, Y right, DX crossover).
    sm->throwPoints(SwitchMachine::eRedToBlk);
  } else {
    // ... otherwise throw points to default
    // position.
    sm->throwPoints(SwitchMachine::eBlkToRed);
  }
  // NOTE: SwitchMachine will activate driver and
  // move points only if commanded and current
  // positions of points aren't the same.
}

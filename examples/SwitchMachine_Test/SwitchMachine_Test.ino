#include <Pulser.h>
#include <SwitchMachine.h>

// Pin numbers are chosen to allow a standard servo
// cable (white/red/black) to be used.
const Triad swm1(4, 5, 6);
const Triad swm2(7, 8, 9);

// NOTE: Pointers to SwitchMachine objects should
// be used so they can be created in sequence,
// to prevent them from trying to initialize (move)
// at the same time.

SwitchMachine** sms;      // array of pointers to objects
Pulser ctrl(1000, 2000);  // on 1 sec, off 2 sec, repeat

void setup()
{
  // Create new SwitchMachine objects.  Switch machines
  // will set themselves to default position (main for LH
  // and RH, left for Y, parallel for DX).
  sms = new SwitchMachine*[2];
  sms[0] = new SwitchMachine(swm1);
  delay(100);
  sms[1] = new SwitchMachine(swm2);
  delay(100);
}

void loop()
{
  // Update SwitchMachine state machines.
  StateMachine::updateAll(sms, 2);
  // Update Pulser.
  ctrl.update();
  // If Pulser is ON...
  if (ctrl.read()) {
    // ... throw points to other position
    // (LH RH diverging, Y right, DX crossover).
    sms[0]->throwPoints(SwitchMachine::eDiverging);
  } else {
    // ... otherwise throw points to default
    // position.
    sms[0]->throwPoints(SwitchMachine::eMain);
  }
  // NOTE: SwitchMachine will activate driver and
  // move points only if commanded and current
  // positions of points aren't the same.
}

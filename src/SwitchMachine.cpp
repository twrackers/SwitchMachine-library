#include "SwitchMachine.h"

// KATO switch machines require a minimum 20 msec pulse to throw reliably.
// This should NOT be increased past, say, 500, or there will be a risk of
// burning out the switch machine's solenoid coil.
const byte pulse = 20;  // msec

// Constructor
SwitchMachine::SwitchMachine(
  const byte enable,
  const byte red,
  const byte black 
) : StateMachine(5, true),  // will update on 5 msec intervals
  m_switchTime(0L),         // time when pulse is scheduled to end
  m_current(eDiverging),    // set current state to Diverging...
  m_command(eMain),         // ... and commanded state to Main, to force init
  m_state(false),           // no pulse
  m_pinEna(enable),         // enable pin
  m_pinRed(red),            // red pin
  m_pinBlk(black)           // black pin
{
  // Set pins to output, initialize logic levels.
  pinMode(m_pinRed, OUTPUT);
  digitalWrite(m_pinRed, HIGH);
  pinMode(m_pinBlk, OUTPUT);
  digitalWrite(m_pinBlk, HIGH);
  pinMode(m_pinEna, OUTPUT);
  digitalWrite(m_pinEna, LOW);
}

// Convenience constructor
SwitchMachine::SwitchMachine(const Triad& triad) :
  SwitchMachine(triad.enable, triad.red, triad.black)
{
}

// Set red and black pins to throw turnout to diverging route.
// Turnout won't be thrown until enable pin is pulsed.
void SwitchMachine::setDiverging()
{
  digitalWrite(m_pinBlk, LOW);
  digitalWrite(m_pinRed, HIGH);
}

// Set red and black pins to throw turnout to main route.
// Turnout won't be thrown until enable pin is pulsed.
void SwitchMachine::setMain()
{
  digitalWrite(m_pinRed, LOW);
  digitalWrite(m_pinBlk, HIGH);
}

// Update state when scheduled.
// Returns true when update occurred.
bool SwitchMachine::update()
{
  // If it's not time to update, return false now.
  if (!StateMachine::update()) return false;
  
  // Are we in the middle of a pulse?
  if (m_state) {
    // If so, and the pulse timeout has occurred...
    if ((long) (millis() - m_switchTime) >= 0) {
      // ... turn off the enable pulse, and change state.
      digitalWrite(m_pinEna, LOW);
      m_state = false;
    }
  } else {
    // If not in pulse state, is commanded setting different from current
    // setting of turnout?
    if (m_current != m_command) {
      // If so, act upon command.
      if (m_command == eDiverging) {
        // Set red/black pins for diverging route.
        setDiverging();
      } else if (m_command == eMain) {
        // Set red/black pins for main route.
        setMain();
      } else /* m_command == eRefresh */ {
        // Otherwise, command must be REFRESH, so set commanded setting
        // to where it's supposed to be anyway, then we will pulse the enable.
        if (m_current == eDiverging) {
          m_command = eDiverging;
          setDiverging();
        } else /* m_current == eMain */ {
          m_command = eMain;
          setMain();
        }
      }
      // Save the commanded setting.
      m_current = m_command;
      // Turn on enable pin (starting pulse), then set time when it should
      // turn off again.
      digitalWrite(m_pinEna, HIGH);
      m_switchTime = millis() + pulse;
      // Set pulse-on state.
      m_state = true;
    }
  }
  // Return true because state has been updated.
  return true;
}

// Set commanded switch motion (main, diverging, or refresh).
void SwitchMachine::throwPoints(
  const SwitchMachine::E_DIR which
)
{
  m_command = which;
}

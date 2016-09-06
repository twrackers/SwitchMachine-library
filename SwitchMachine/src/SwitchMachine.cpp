#include "SwitchMachine.h"

const byte pulse = 20;  // msec

SwitchMachine::SwitchMachine(
  const byte enable,
  const byte red,
  const byte black 
) : StateMachine(1, true),
  m_switchTime(0L),
  m_current(eDiverging),
  m_command(eMain),
  m_state(false),
  m_pinEna(enable),
  m_pinRed(red),
  m_pinBlk(black)
{
  pinMode(m_pinRed, OUTPUT);
  digitalWrite(m_pinRed, HIGH);
  pinMode(m_pinBlk, OUTPUT);
  digitalWrite(m_pinBlk, HIGH);
  pinMode(m_pinEna, OUTPUT);
  digitalWrite(m_pinEna, LOW);
}

SwitchMachine::SwitchMachine(const Triad<byte>& triad) :
  SwitchMachine(triad.first, triad.second, triad.third)
{
}

void SwitchMachine::setDiverging()
{
  digitalWrite(m_pinRed, HIGH);
  digitalWrite(m_pinBlk, LOW);
}

void SwitchMachine::setMain()
{
  digitalWrite(m_pinRed, LOW);
  digitalWrite(m_pinBlk, HIGH);
}

bool SwitchMachine::update()
{
  if (!StateMachine::update()) return false;
  if (m_state) {
    if (millis() >= m_switchTime) {
      digitalWrite(m_pinEna, LOW);
      m_state = false;
    }
  } else {
    if (m_current != m_command) {
      if (m_command == eDiverging) {
        setDiverging();
      } else if (m_command == eMain) {
        setMain();
      } else /* m_command == eRefresh */ {
        if (m_current == eDiverging) {
          m_command = eDiverging;
          setDiverging();
        } else /* m_current == eMain */ {
          m_command = eMain;
          setMain();
        }
      }
      m_current = m_command;
      digitalWrite(m_pinEna, HIGH);
      m_switchTime = millis() + pulse;
      m_state = true;
    }
  }
  return true;
}

void SwitchMachine::throwPoints(
  const SwitchMachine::E_DIR which
)
{
  m_command = which;
}

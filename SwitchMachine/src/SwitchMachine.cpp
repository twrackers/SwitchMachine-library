#include "SwitchMachine.h"

const byte pulse = 20;  // msec

SwitchMachine::SwitchMachine(
  const byte red, 
  const byte black, 
  const byte enable
) : StateMachine(1, true),
  m_switchTime(0L),
  m_current(eRedToBlk),
  m_command(eBlkToRed),
  m_state(false),
  m_pinRed(red),
  m_pinBlk(black),
  m_pinEna(enable)
{
  pinMode(m_pinRed, OUTPUT);
  digitalWrite(m_pinRed, HIGH);
  pinMode(m_pinBlk, OUTPUT);
  digitalWrite(m_pinBlk, HIGH);
  pinMode(m_pinEna, OUTPUT);
  digitalWrite(m_pinEna, LOW);
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
      if (m_command == eRedToBlk) {
        digitalWrite(m_pinRed, HIGH);
        digitalWrite(m_pinBlk, LOW);
      } else {
        digitalWrite(m_pinRed, LOW);
        digitalWrite(m_pinBlk, HIGH);
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
  const E_POLARITY which
)
{
  m_command = which;
}


#include "SwitchMachine.h"

const byte pulse = 20;  // msec

SwitchMachine::SwitchMachine(
  E_TYPE type,
  const byte red, 
  const byte black, 
  const byte enable
) : StateMachine(1, true),
  m_switchTime(0L),
  m_routeCur(eUnk),
  m_routeCmd(eUnk),
  m_state(false),
  m_type(type),
  m_wireRed(red),
  m_wireBlack(black),
  m_enable(enable)
{
  pinMode(m_wireRed, OUTPUT);
  digitalWrite(m_wireRed, HIGH);
  pinMode(m_wireBlack, OUTPUT);
  digitalWrite(m_wireBlack, HIGH);
  pinMode(m_enable, OUTPUT);
  digitalWrite(m_enable, LOW);
}

bool SwitchMachine::update()
{
  if (!StateMachine::update()) return false;
  if (m_state) {
    if (millis() >= m_switchTime) {
      digitalWrite(m_enable, LOW);
      digitalWrite(13, LOW);
      m_state = false;
    }
  } else {
    if (m_routeCur != m_routeCmd) {
      if (m_routeCmd == eL) {
        digitalWrite(m_wireRed, HIGH);
        digitalWrite(m_wireBlack, LOW);
      } else {
        digitalWrite(m_wireRed, LOW);
        digitalWrite(m_wireBlack, HIGH);
      }
      digitalWrite(m_enable, HIGH);
      m_routeCur = m_routeCmd;
      m_switchTime = millis() + pulse;
      digitalWrite(13, HIGH);
      m_state = true;
    }
  }
  return true;
}

bool SwitchMachine::setRoute(const E_ROUTE route)
{
  bool success = false;
  
  if (route == eLeft) {
    m_routeCmd = eL;
    success = true;
  } else if (route == eRight) {
    m_routeCmd = eR;
    success = true;
  } else if (route == eMain) {
    if (m_type == eLH) {
      m_routeCmd = eR;
      success = true;
    } else if (m_type == eRH) {
      m_routeCmd = eL;
      success = true;
    }
  } else if (route == eDiverging) {
    if (m_type == eLH) {
      m_routeCmd = eL;
      success = true;
    } else if (m_type == eRH) {
      m_routeCmd = eR;
      success = true;
    }
  }
  
  return success;
}


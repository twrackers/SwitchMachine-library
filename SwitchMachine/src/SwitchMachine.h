#ifndef _SWITCH_MACHINE__H_
#define _SWITCH_MACHINE__H_

#include <StateMachine.h>

enum E_TYPE {
  eWye,
  eLH,
  eRH
};
enum E_ROUTE {
  eLeft,
  eRight,
  eMain,
  eDiverging
};

class SwitchMachine : public StateMachine
{
  private:
    enum E_ROUTE_IMPL {
      eUnk,
      eL,
      eR
    };
    unsigned long m_switchTime;
    E_ROUTE_IMPL  m_routeCur;
    E_ROUTE_IMPL  m_routeCmd;
    bool          m_state;
    const E_TYPE  m_type;
    const byte    m_wireRed;
    const byte    m_wireBlack;
    const byte    m_enable;
    
  public:
    SwitchMachine(
      E_TYPE type,
      const byte red, 
      const byte black, 
      const byte enable
    );

    virtual bool update();

    bool setRoute(const E_ROUTE route);
};

#endif


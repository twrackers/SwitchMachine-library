#ifndef _SWITCH_MACHINE__H_
#define _SWITCH_MACHINE__H_

#include <StateMachine.h>
#include <Triad.h>

/*
 * NOTE: The KATO switch machines are used on four types of turnouts:
 *	LH - left-hand
 *	RH - right-hand
 *	Y  - wye
 *	DX - double crossover
 *
 * Direction of current flow determines selected route.
 *
 *      Black=>Red    Red=>Black
 * LH   main (right)  diverging (left)
 * RH   main (left)   diverging (right)
 * Y    left          right
 * DX   thru          crossover
 */

class SwitchMachine : public StateMachine
{
  public:
    enum E_DIR {
      eRefresh,
      eMain,
      eDiverging
    };
    
  private:
    unsigned long m_switchTime;
    E_DIR         m_current;
    E_DIR         m_command;
    bool          m_state;
    const byte    m_pinEna;
    const byte    m_pinRed;
    const byte    m_pinBlk;
    
    void setMain();
    void setDiverging();
    
  public:
    SwitchMachine(
      const byte enable,
      const byte red, 
      const byte black
    );
    SwitchMachine(
      const Triad<byte>& triad
    );

    virtual bool update();

    void throwPoints(const E_DIR which);
};

#endif


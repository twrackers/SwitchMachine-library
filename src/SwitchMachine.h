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
    // Allowed commands to a SwitchMachine object.
    enum E_DIR {
      eRefresh,     // set to already stored position
      eMain,        // set to main route (Black=>Red current flow)
      eDiverging    // set to diverging route (Red=>Black current flow)
    };
    
  private:
    unsigned long m_switchTime;   // time when pulse should terminate
    E_DIR         m_current;      // most recently completed command
    E_DIR         m_command;      // most recently received command
    bool          m_state;        // true during pulse period
    const byte    m_pinEna;       // enable I/O pin
    const byte    m_pinRed;       // red I/O pin
    const byte    m_pinBlk;       // black I/O pin
    
    // Set red and black I/O for throw to main.
    void setMain();
    
    // Set red and black I/O for throw to diverging.
    void setDiverging();
    
  public:
    // Constructor, assigns I/O pins
    SwitchMachine(
      const byte enable,
      const byte red, 
      const byte black
    );
    
    // Constructor, assigns I/O pins in Triad struct
    SwitchMachine(
      const Triad<byte>& triad
    );

    // Overrides StateMachine update method, returns true only when
    // an update to this object's state occurs.
    virtual bool update();

    // Queues up a command to throw this object's attached turnout.
    void throwPoints(const E_DIR which);
};

#endif


#ifndef _SWITCH_MACHINE__H_
#define _SWITCH_MACHINE__H_

#include <StateMachine.h>

/*
 * NOTE: The KATO switch machines are mounted in four types of turnouts:
 *	- left-hand (#6 718mm, #4 481mm, compact 150mm)
 *	- right-hand (same sizes as left-hand)
 *	- wye (481mm)
 *	- double crossover (approx #5 end-to-end)
 * The solenoids in the switch machines are wired such that applying the
 * current to throw the points will work consistently across the various
 * types of turnouts depending on the direction of the current flow.
 *
 * Current flow black-to-red wires:
 *	- LH, RH throw to Main route
 *	- Y throws to Left route
 *	- DX throws to Parallel routes
 * Current flow red-to-black wires:
 *	- LH, RH throw to Diverging route
 *	- Y throws to Right route
 *	- DX throws to Crossover routes
 */

class SwitchMachine : public StateMachine
{
  public:
	enum E_POLARITY {
		eBlkToRed,
		eRedToBlk
	};

  private:
    unsigned long m_switchTime;
    E_POLARITY    m_current;
    E_POLARITY    m_command;
    bool          m_state;
    const byte    m_pinRed;
    const byte    m_pinBlk;
    const byte    m_pinEna;
    
  public:
    SwitchMachine(
      const byte red, 
      const byte black, 
      const byte enable
    );

    virtual bool update();

    void throwPoints(const E_POLARITY which);
};

#endif


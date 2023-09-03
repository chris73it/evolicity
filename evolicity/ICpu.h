#pragma once
#include "IPeripheral.h"
class ICpu : public IPeripheral
{
public:
	// External event functions. In hardware these represent pins that are asserted
	// to produce a change in state.
	virtual void reset() =0;	// Reset Interrupt - Forces CPU into known state
	virtual void irq() =0;		// Interrupt Request - Executes an instruction at a specific location
	virtual void nmi() =0;		// Non-Maskable Interrupt Request - As above, but cannot be disabled
	virtual void clock() =0;	// Perform one clock cycle's worth of update
};
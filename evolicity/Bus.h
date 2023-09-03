#pragma once
#include <cstdint>
#include "Mos6502.h"
#include "Ram32KB.h"
#include "Screen40x25.h"
#include "Keyboard_US.h"
class Bus
{
public:
	Bus();
	~Bus() = default;
	
	// The CPU reads and writes the other peripherals
	// (including RAM, even though on a different architecture
	// it may be necessary to use the two more specialized APIs below.)
	uint8_t cpuRead(size_t address, bool readonly) const;
	void cpuWrite(size_t address, uint8_t data);

	// Even though RAM is a peripheral, these two functions
	// provide a way to access it (useful in case RAM's address
	// range is so large that it would overlap with the address
	// of the  other 
	const uint8_t ramRead(size_t address) const;
	void ramWrite(size_t address, uint8_t byte);

	Mos6502& getCpu();
	//const Mos6502& getCpu() const;
	Ram32KB& getRam();
	//const Ram32KB& getRam() const;
	Screen40x25& getScreen();
	//const Screen40x25& getScreen() const;
	Keyboard_US& getKeyboard();
	//const Keyboard_US& getKeyboard() const;

	void dump() const;

private:
	Mos6502 cpu;
	Ram32KB ram;
	Screen40x25 screen;
	Keyboard_US keyboard;
};


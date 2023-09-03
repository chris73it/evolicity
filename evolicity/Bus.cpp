#include <iostream>
#include <cassert>
#include "Bus.h"

Bus::Bus()
{
	// Connect the CPU to this bus
	cpu.bus = this;
}

uint8_t Bus::cpuRead(size_t address, bool readonly) const
{
	uint8_t data = 0x00;
	if (address >= cpu.fromAddress && address < cpu.toAddress)
	{
		if (address >= screen.fromAddress && address < screen.toAddress)
		{
			data = screen.read(address);
		}
		else if (address >= keyboard.fromAddress && address < keyboard.toAddress)
		{
			data = keyboard.read(address);
		}
		else if (address >= ram.fromAddress && address < ram.toAddress)
		{
			data = ram.read(address);
		}
	}
	return data;
}

void Bus::cpuWrite(size_t address, uint8_t data)
{
	if (address >= cpu.fromAddress && address < cpu.toAddress)
	{
		if (address >= screen.fromAddress && address < screen.toAddress)
		{
			screen.write(address, data);
		}
		/*else if (address >= keyboard.fromAddress && address < keyboard.toAddress)
		{
			keyboard.write(address, data);
		}*/
		else if (address >= ram.fromAddress && address < ram.toAddress)
		{
			ram.write(address, data);
		}
	}
}

const uint8_t Bus::ramRead(size_t address) const
{
	assert(address >= ram.fromAddress && address < ram.toAddress);
	return ram.read(address);
}

void Bus::ramWrite(size_t address, uint8_t byte)
{
	assert(address >= ram.fromAddress && address < ram.toAddress);
	ram.write(address, byte);
}

Mos6502& Bus::getCpu()
{
	//std::cout << "Bus::getCpu     const" << std::endl;
	return cpu;
}

//const Mos6502& Bus::getCpu() const
//{
//	//std::cout << "Bus::getCpu     const" << std::endl;
//	return cpu;
//}

Ram32KB& Bus::getRam()
{
	//std::cout << "Bus::getRam non const" << std::endl;
	return ram;
}

//const Ram32KB& Bus::getRam() const
//{
//	//std::cout << "Bus::getRam     const" << std::endl;
//	return ram;
//}

Screen40x25& Bus::getScreen()
{
	//std::cout << "Bus::getScreen     const" << std::endl;
	return screen;
}

//const Screen40x25& Bus::getScreen() const
//{
//	//std::cout << "Bus::getScreen     const" << std::endl;
//	return screen;
//}

Keyboard_US& Bus::getKeyboard()
{
	//std::cout << "Bus::getKeyboard     const" << std::endl;
	return keyboard;
}

//const Keyboard_US& Bus::getKeyboard() const
//{
//	//std::cout << "Bus::getKeyboard     const" << std::endl;
//	return keyboard;
//}

void Bus::dump() const
{
	cpu.dump();
	ram.dump();
	screen.dump();
	keyboard.dump();
}
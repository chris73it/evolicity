#include <iostream>
#include <cassert>
#include "Keyboard_US.h"

uint8_t Keyboard_US::read(size_t address) const
{
	assert(address >= fromAddress && address < toAddress);
	std::cerr << "[IKeyboard] Keyboard_US::read" << std::endl;
	return bytes[address - fromAddress];
}

void Keyboard_US::write(size_t address, uint8_t byte)
{
	assert(address >= fromAddress && address < toAddress);
	std::cerr << "[IKeyboard] Keyboard_US::write" << std::endl;
	bytes[address - fromAddress] = byte;
}

//std::array<uint8_t, Keyboard_US::amount>& Keyboard_US::getBytes()
//{
//	std::cout << "Keyboard_US::getBytes non const" << std::endl;
//	return bytes;
//}

const std::array<uint8_t, Keyboard_US::amount>& Keyboard_US::getBytes() const
{
	//std::cout << "Keyboard_US::getBytes     const" << std::endl;
	return bytes;
}

void Keyboard_US::dump() const
{
	std::cout << "Keyboard_US::dump" << std::endl;
	uint8_t value;
	for (size_t index = fromAddress; index < toAddress; ++index)
	{
		value = read(index);
		std::cout << "[" << index << "] = " << unsigned(value) << std::endl;
	}
}
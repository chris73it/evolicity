#include <iostream>
#include <cassert>
#include "Ram32KB.h"

Ram32KB::Ram32KB()
	: bytes{ 0 }
{
}

uint8_t Ram32KB::read(size_t address) const
{
	assert(address >= fromAddress && address < toAddress);
	//std::cerr << "[IMemory] Ram32KB::read" << std::endl;
	return bytes[address - fromAddress];
}

void Ram32KB::write(size_t address, uint8_t byte)
{
	assert(address >= fromAddress && address < toAddress);
	//std::cerr << "[IMemory] Ram32KB::write" << std::endl;
	bytes[address - fromAddress] = byte;
}

//std::array<uint8_t, Ram32KB::amount>& Ram32KB::getBytes()
//{
//	std::cout << "Ram32KB::getBytes non const" << std::endl;
//	return bytes;
//}

const std::array<uint8_t, Ram32KB::amount>& Ram32KB::getBytes() const
{
	//std::cout << "Ram32KB::getBytes     const" << std::endl;
	return bytes;
}

void Ram32KB::dump() const
{
	std::cout << "Ram32KB::dump" << std::endl;
	uint8_t value;
	for (size_t index = fromAddress; index < toAddress; ++index)
	{
		value = read(index);
		std::cout << "[" << index << "] = " << unsigned(value) << std::endl;
	}
}
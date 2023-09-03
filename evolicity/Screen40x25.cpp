#include <iostream>
#include <cassert>
#include "Screen40x25.h"

Screen40x25::Screen40x25()
	: bytes{ 0 }
{
}

uint8_t Screen40x25::read(size_t address) const
{
	assert(address >= fromAddress && address < toAddress);
	//std::cerr << "[IScreen] Screen40x25::read " << address << std::endl;
	return bytes[address - fromAddress];
}

void Screen40x25::write(size_t address, uint8_t byte)
{
	assert(address >= fromAddress && address < toAddress);
	//std::cerr << "[IScreen] Screen40x25::write " << address << std::endl;
	bytes[address - fromAddress] = byte;
}

//std::array<uint8_t, Screen40x25::amount>& Screen40x25::getBytes()
//{
//	std::cout << "Screen40x25::getBytes non const" << std::endl;
//	return bytes;
//}

const std::array<uint8_t, Screen40x25::amount>& Screen40x25::getBytes() const
{
	//std::cout << "Screen40x25::getBytes     const" << std::endl;
	return bytes;
}

void Screen40x25::dump() const
{
	std::cout << "Screen40x25::dump" << std::endl;
	uint8_t value;
	for (size_t index = fromAddress; index < toAddress; ++index)
	{
		value = read(index);
		std::cout << "[" << index << "] = " << unsigned(value) << std::endl;
	}
}
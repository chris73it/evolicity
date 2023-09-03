#pragma once
#include <cstdint>
class IPeripheral
{
public:
	virtual uint8_t read(size_t address) const = 0;
	virtual void write(size_t address, uint8_t value) = 0;
};

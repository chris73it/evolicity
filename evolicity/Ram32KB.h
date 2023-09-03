#pragma once
#include <array>
#include "IMemory.h"
class Ram32KB : public IMemory
{
public:
	static const size_t fromAddress = 0x08000; //32768
	static const size_t toAddress   = 0x10000; //65536
	static const size_t amount      = toAddress - fromAddress; //32768

	Ram32KB();
	~Ram32KB() = default;

	// IPeripheral
	uint8_t read(size_t address) const override;
	void write(size_t address, uint8_t byte) override;
	
	//std::array<uint8_t, Ram32KB::amount>& getBytes();
	const std::array<uint8_t, Ram32KB::amount>& getBytes() const;
	
	void dump() const;

private:
	std::array<uint8_t, Ram32KB::amount> bytes;
};
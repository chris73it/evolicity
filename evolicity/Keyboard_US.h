#pragma once
#include <array>
#include "IKeyboard.h"
class Keyboard_US : public IKeyboard
{
public:
	static const size_t fromAddress = 0x00600; //1536
	static const size_t toAddress   = 0x00602; //1538
	static const size_t amount = toAddress - fromAddress; //2

	Keyboard_US() = default;
	~Keyboard_US() = default;

	// IPeripheral
	uint8_t read(size_t address) const override;
	void write(size_t address, uint8_t byte) override;

	//std::array<uint8_t, Keyboard_US::amount>& getBytes();
	const std::array<uint8_t, Keyboard_US::amount>& getBytes() const;

	void dump() const;

private:
	std::array<uint8_t, Keyboard_US::amount> bytes;
};
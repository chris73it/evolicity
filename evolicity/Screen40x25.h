#pragma once
#include <array>
#include "IScreen.h"
class Screen40x25 : public IScreen
{
public:
	static const size_t fromAddress = 0x0200; //512
	static const size_t toAddress   = 0x4080; //16512
	static const size_t amount = toAddress - fromAddress; //1024

	Screen40x25();
	~Screen40x25() = default;

	// IPeripheral
	uint8_t read(size_t address) const override;
	void write(size_t address, uint8_t byte) override;

	//std::array<uint8_t, Screen40x25::amount>& getBytes();
	const std::array<uint8_t, Screen40x25::amount>& getBytes() const;

	void dump() const;

private:
	std::array<uint8_t, Screen40x25::amount> bytes;
};
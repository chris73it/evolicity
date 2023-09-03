#include <iostream>
#include <string>
#include <memory>
#include <Windows.h>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "Bus.h"

class Demo : public olc::PixelGameEngine
{
public:
	static const int nScreenWidth = 80;  // Console Screen Size X (columns)
	static const int nScreenHeight = 50; // Console Screen Size Y (rows)
	static const int nPixelWidth = 4;     // Pixel Width
	static const int nPixelHeight = 4;    // Pixel Height

	Demo() :
		bus{ std::make_unique<Bus>() },
		cpu{ bus->getCpu() },
		ram{ bus->getRam() },
		screen{ bus->getScreen() },
		keyboard{ bus->getKeyboard() },
		alpha{ 255 }
	{
		sAppName = "evolicity";
	}

protected:
	virtual bool OnUserCreate() override
	{
		// Load the program in memory
		char c = '?';
		uint16_t address;
		uint8_t  addr_lo;
		uint8_t  addr_hi;
		auto pc = cpu.pc = ram.fromAddress; // 0x8000
		for (size_t y = 0; y < nScreenHeight; ++y)
		{
			for (size_t x = 0; x < nScreenWidth; ++x)
			{
				// LDA
				ram.write(pc++, 0xA9);               // LDA $..
				ram.write(pc++, uint8_t(c + x + y)); // LDA $41 +x +y
				// STA
				address = uint16_t(screen.fromAddress + x + y * nScreenWidth);
				addr_lo = address & 0x00FF;
				addr_hi = (address & 0xFF00) >> 8;
				ram.write(pc++, 0x8D);    // STA $....
				ram.write(pc++, addr_lo); // STA $..00
				ram.write(pc++, addr_hi); // STA $0200 (top left corner of the display)
			}
		}
		ram.write(pc++, 0x00); // JMP $....
		ram.write(pc++, 0x00); // JMP $..00
		ram.write(pc++, 0x80); // JMP $8000 (go back to the start of this short program)
		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime) override
	{
		// Run the program to fill up the video memory
		for (int y = 0; y < nScreenHeight; y++)
		{
			for (int x = 0; x < nScreenWidth; x++)
			{
				// Exec LDA (2 cycles)
				cpu.clock();
				cpu.clock();
				// Exec STA (4 cycles)
				cpu.clock();
				cpu.clock();
				cpu.clock();
				cpu.clock();

				// Compose Frame
				Draw(x, y, olc::Pixel{ screen.read(screen.fromAddress + x + y * nScreenWidth), alpha });
			}
		}
		readAZ();
		readDigits();
		readFxKeys();
		return true;
	}

	void readAZ()
	{
		for (olc::Key key = olc::Key::A; key <= olc::Key::Z; ++key)
		{
			if (GetKey(key).bHeld)
			{
				DrawString(0, 0, std::string(1, 'A' + key - 1), olc::WHITE, 1);
			}
		}
	}

	void readDigits()
	{
		for (olc::Key key = olc::Key::K0; key <= olc::Key::K9; ++key)
		{
			if (GetKey(key).bHeld)
			{
				DrawString(0, 0, std::string(1, '0' + key - 27), olc::WHITE, 1);
			}
		}
	}

	void readFxKeys()
	{
		for (olc::Key key = olc::Key::F1; key <= olc::Key::F9; ++key)
		{
			if (GetKey(key).bHeld)
			{
				DrawString(0, 0, std::string(1, 'F'), olc::WHITE, 1);
				DrawString(8, 0, std::string(1, '0' + key - 36), olc::WHITE, 1);
			}
		}
		for (olc::Key key = olc::Key::F10; key <= olc::Key::F12; ++key)
		{
			if (GetKey(key).bHeld)
			{
				DrawString(0, 0, std::string(1, 'F'), olc::WHITE, 1);
				DrawString(8, 0, std::string(1, '1'), olc::WHITE, 1);
				DrawString(16, 0, std::string(1, '0' + key - 46), olc::WHITE, 1);
			}
		}
	}

	void SetAlpha()
	{
		static const uint8_t APLHA_QUANTUM = 1;
		auto button = GetKey(olc::Key::UP);
		if (button.bHeld)
		{
			if (alpha > 255 - APLHA_QUANTUM)
			{
				alpha = 255;
			}
			else
			{
				alpha += APLHA_QUANTUM;
			}
		}
		button = GetKey(olc::Key::DOWN);
		if (button.bHeld)
		{
			if (alpha < APLHA_QUANTUM)
			{
				alpha = 0;
			}
			else
			{
				alpha -= APLHA_QUANTUM;
			}
		}
	}

private:
	std::unique_ptr<Bus> bus;
	Mos6502& cpu;
	Ram32KB& ram;
	Screen40x25& screen;
	Keyboard_US& keyboard;
	uint8_t alpha;
};

int main()
{
	Demo demo{};
	if (demo.Construct(Demo::nScreenWidth, Demo::nScreenHeight, Demo::nPixelWidth, Demo::nPixelHeight))
	{
		demo.Start();
	}

	return 0;
}

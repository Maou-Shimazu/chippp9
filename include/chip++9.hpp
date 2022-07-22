#pragma once

#include <cstdint>
#ifndef CHIP_9_HPP
#define CHIP_9_HPP

#include "tigr.h"
#include <array>
#include <cstdio>
#include <iostream>
#include <vector>
#ifdef __WIN32__
#include <windows.h>
#endif

class chip9 {
	uint16_t opcode;
	uint16_t I;
	uint16_t pc;
	uint16_t sp;

	std::array<uint16_t, 4096> memory{};
	std::array<uint8_t, 16> V{};
	std::array<uint16_t, 64 * 32> gfx{};
	std::array<uint16_t, 16> stack{};
	std::array<uint8_t, 16> key{};

	char16_t sound_timer = 0x00;
	char16_t delay_timer = 0x00;

	const std::array<char16_t, 96> font{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80, // F
	};

	const std::vector<char16_t> data_registers{

	};

public:
	//--- FUNCTIONS ---//
	// chip9() = default;
	explicit chip9() {
		this->pc	 = 0x200; // program counter starts at 200
		this->opcode = 0x00; // Reset current op code
		this->I		 = 0x00; // reset index register
		this->sp	 = 0x00; // reset stack pointer

		for (auto& i : this->font)
			this->memory[i] = this->font[i]; // add font to memory
	};
	// void initialize(){};
	void loadGame(const char* filename){};
	void emulateCycle() {
		this->opcode = memory[pc] << static_cast<uint16_t>(0x08) |
					   static_cast<uint16_t>(memory[pc + 2]);

		switch (opcode & 0xF000) {
			case 0xA000: { // ANNN: Sets I to the address NNN
				this->I = this->opcode & 0x0FFF;
				this->pc += 2;
			} break;

			case 0xB000: {
				this->pc = this->V[0] + 0x000;
				this->pc += 2;
			} break;

			case 0x2000: {
				this->stack[this->sp] = this->pc;
				++this->sp;
				this->pc = this->opcode & 0x0FFF;
			}

			default: {
				std::cout << "Unknown opcode: " << opcode << std::endl;
			}
		}

		// Update timers
		if (this->delay_timer > 0)
			--this->delay_timer;

		if (this->sound_timer > 0) {
			if (this->sound_timer == 1)
				std::cout << "\a" << std::flush;
			--this->sound_timer;
		}
	};
	void setKeys(){};
	void draw(uint8_t x, uint8_t y) {
		if (x >= 64 or y >= 32) {
		}
	}
};

#endif

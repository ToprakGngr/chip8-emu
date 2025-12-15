#include "chip8.h"
#include <fstream>
#include <ios>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

const unsigned int FONTSET_SIZE = 80;

const uint8_t fontset[FONTSET_SIZE] =
{
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
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void Chip8::LoadFont(){
    for(unsigned i = 0; i < FONTSET_SIZE; i++){
        memory[i] = fontset[i];
    }
}

Chip8::Chip8(){
    pc = 0x200;
    I = 0;
    sp = 0;
    opcode = 0;
    LoadFont();

    srand(static_cast<unsigned int>(time(nullptr)));

    memset(memory, 0, sizeof(memory));
    memset(V, 0, sizeof(V));
    memset(stack, 0, sizeof(stack));
    memset(display, 0, sizeof(display));
    memset(keypad, 0, sizeof(keypad));

   for (unsigned int i = 0; i < 16; ++i) {
        chip8Table[i] = &Chip8::OP_NULL;
        chip8Table0[i] = &Chip8::OP_NULL;
        chip8Table8[i] = &Chip8::OP_NULL;
        chip8TableE[i] = &Chip8::OP_NULL;
    }
    for (unsigned int i = 0; i < 256; ++i) {
        chip8TableF[i] = &Chip8::OP_NULL;
    }

    // --- Main Table (0-F) ---
    chip8Table[0x0] = &Chip8::Table0; // 0 series director
    chip8Table[0x1] = &Chip8::OP_1NNN;
    chip8Table[0x2] = &Chip8::OP_2NNN;
    chip8Table[0x3] = &Chip8::OP_3XNN;
    chip8Table[0x4] = &Chip8::OP_4XNN;
    chip8Table[0x5] = &Chip8::OP_5XY0;
    chip8Table[0x6] = &Chip8::OP_6XNN;
    chip8Table[0x7] = &Chip8::OP_7XNN;
    chip8Table[0x8] = &Chip8::Table8; // 8 series director
    chip8Table[0x9] = &Chip8::OP_9XY0;
    chip8Table[0xA] = &Chip8::OP_ANNN;
    chip8Table[0xB] = &Chip8::OP_BNNN;
    chip8Table[0xC] = &Chip8::OP_CXNN;
    chip8Table[0xD] = &Chip8::OP_DXYN;
    chip8Table[0xE] = &Chip8::TableE; // E series director
    chip8Table[0xF] = &Chip8::TableF; // F series director

    // --- Table 0 (00E0 ve 00EE) ---
    // last digit: 0 and E
    chip8Table0[0x0] = &Chip8::OP_00E0; // CLS
    chip8Table0[0xE] = &Chip8::OP_00EE; // RET

    // --- Table 8 (Math. ops) ---
    // last digit: 0-7 and E
    chip8Table8[0x0] = &Chip8::OP_8XY0;
    chip8Table8[0x1] = &Chip8::OP_8XY1;
    chip8Table8[0x2] = &Chip8::OP_8XY2;
    chip8Table8[0x3] = &Chip8::OP_8XY3;
    chip8Table8[0x4] = &Chip8::OP_8XY4;
    chip8Table8[0x5] = &Chip8::OP_8XY5;
    chip8Table8[0x6] = &Chip8::OP_8XY6;
    chip8Table8[0x7] = &Chip8::OP_8XY7;
    chip8Table8[0xE] = &Chip8::OP_8XYE;

    // --- Table E (Keypad COntrollers) ---
    // Ex9E ve ExA1
    chip8TableE[0xE] = &Chip8::OP_EX9E;
    chip8TableE[0x1] = &Chip8::OP_EXA1;

    // --- Table F (Memory and Timer) ---
    chip8TableF[0x07] = &Chip8::OP_FX07;
    chip8TableF[0x0A] = &Chip8::OP_FX0A;
    chip8TableF[0x15] = &Chip8::OP_FX15;
    chip8TableF[0x18] = &Chip8::OP_FX18;
    chip8TableF[0x1E] = &Chip8::OP_FX1E;
    chip8TableF[0x29] = &Chip8::OP_FX29;
    chip8TableF[0x33] = &Chip8::OP_FX33;
    chip8TableF[0x55] = &Chip8::OP_FX55;
    chip8TableF[0x65] = &Chip8::OP_FX65;
}

// --- Table Directors ---

void Chip8::Table0(){
    // take the last digit
    (this->*chip8Table0[opcode & 0x000F])();
}

void Chip8::Table8(){
    // take last digit
    (this->*chip8Table8[opcode & 0x000F])();
}

void Chip8::TableE() {
    // take the last digit
    (this->*chip8TableE[opcode & 0x000F])();
}

void Chip8::TableF() {
    // take the last two digits
    (this->*chip8TableF[opcode & 0x00FF])();
}

void Chip8::OP_NULL() {
    // undefined opcode - do nothing
}

const unsigned int START_POS = 0x200;
const unsigned int MEM_SIZE = 4096;

void Chip8::LoadRom(const char* filename) {
    std::ifstream file(filename, std::ios_base::binary | std::ios_base::ate);

    if(file.is_open()){
        std::streampos size = file.tellg();

        const long max_size = MEM_SIZE - START_POS;

        if(size > max_size){
            std::cerr << "Warning: ROM has grown too big, the overflowed data will be discarded.\n";
            size = max_size;
        }

            char* buffer = new char[size];

            file.seekg(0, std::ios_base::beg);
            file.read(buffer, size);
            file.close();

            for(long i = 0; i < size; i++){
                memory[START_POS + i] = static_cast<uint8_t>(buffer[i]);
            }

        delete[] buffer;
    }
}

void Chip8::EventCycle(){
    //Fetch
    opcode = (memory[pc] << 8) | (memory[pc+1]);
    pc += 2;
 
    // Decode - Execute
    (this->*chip8Table[(opcode & 0xF000) >> 12])();
    
    //if(delay_timer > 0) --delay_timer;
    //if(sound_timer > 0) --sound_timer;
}

void Chip8::UpdateTimers() {
    if(delay_timer > 0) --delay_timer;
    if(sound_timer > 0) --sound_timer;
}


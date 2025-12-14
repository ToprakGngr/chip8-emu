#include "chip8.h"
#include <fstream>
#include <ios>
#include <iostream>:
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
    pc = 0;
    I = 0;
    sp = 0;
    LoadFont();
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
            file.read(buffer, length);
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

    



}

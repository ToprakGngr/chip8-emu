#include "chip8.h"

// 8xy0 - LD Vx, Vy
void Chip8::OP_8XY0(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;
    V[Vx] = V[Vy];
}

// 8xy1 - OR Vx, Vy
void Chip8::OP_8XY1(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;
    V[Vx] = V[Vx] | V[Vy];
}

// 8xy2 - AND Vx, Vy
void Chip8::OP_8XY2(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;
    V[Vx] = V[Vx] & V[Vy];
}

// 8xy3 - XOR Vx, Vy
void Chip8::OP_8XY3(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;
    V[Vx] = V[Vx] ^ V[Vy];
}

// 8xy4 - ADD Vx, Vy (Set VF = Carry)
void Chip8::OP_8XY4(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;
    
    uint16_t sum = V[Vx] + V[Vy];
    V[0xF] = sum >> 8;
    V[Vx] = sum & 0xFF;
}

// 8xy5 - SUB Vx, Vy (Set VF = NOT Borrow)
void Chip8::OP_8XY5(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;
    
    uint16_t sub = V[Vx] - V[Vy];
    
    V[0xF] = 0;
    if(V[Vx] >= V[Vy]) V[0xF] = 1;

    V[Vx] = sub;
}

// 8xy6 - SHR Vx (Vy is ignored in modern interpreters)
void Chip8::OP_8XY6(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    V[0xF] = V[Vx] & 0x1;
    V[Vx] = V[Vx] >> 1;
}
    
// 8xy7 - SUBN Vx, Vy (Set VF = NOT Borrow)
void Chip8::OP_8XY7(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;
    uint16_t subn = V[Vy] - V[Vx];

    V[0xF] = 0;
    if(V[Vy] >= V[Vx]) V[0xF] = 1;
    V[Vx] = subn;
}

// 8xyE - SHL Vx (Vy is ignored)
void Chip8::OP_8XYE(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    V[0xF] = (V[Vx] & 0x80) >> 7;
    V[Vx] = V[Vx] << 1;
}

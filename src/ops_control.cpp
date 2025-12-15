#include "chip8.h"


void Chip8::OP_00E0(){
    memset(display, 0, sizeof(display);
}


void CHip08::OP_00EE(){
    pc = stack[sp];
    sp--;
}


void Chip08::OP_1NNN(){
    uint16_t address = (opcode & 0x0FFF);
    PC = address;
}


void Chip08::OP_2NNN(){
    uint16_t address = (opcode & 0x0FFF);
    stack[sp] = pc;
    sp++;
    pc = address;
}


void Chip08::OP_3XNN(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t kk = (opcode & 0x00FF);

    if(V[Vx] == kk) pc += 2;
}


void Chip08::OP_4XNN(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t kk = (opcode & 0x00FF);

    if(V[Vx] != kk) pc += 2;
}


void Chip08::OP_5XY0(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;

    if(V[Vx] == V[Vy]) pc += 2;
}


void Chip08::OP_9XY0(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;

    if(V[Vx] != V[Vy]) pc += 2;
}

void Chip8::OP_BNNN(){
    uint16_t address = (opcode & 0x0FFF);
    pc = address + V[0x0];
}

void Chip8::OP_EX9E(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    
    if(keypad[V[Vx]]) pc += 2;
}

void Chip08::OP_EXA1(){
    uint8_t Vx = (opcode & 0x0F00) >> 8; 

    if(keypad[V[Vx]] == 0) pc += 2;
}




















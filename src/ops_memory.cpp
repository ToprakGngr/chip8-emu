#include "chip8.h"

// Set Vx = delay timer value
void Chip8::OP_FX07(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    V[Vx] = delay_timer;
}

// Wait for a key press, store the value of the key in Vx
void Chip8::OP_FX0A(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    const uint8_t size = 16;
    for(long i = 0; i < size; i++){
        if(keypad[i]){
            V[Vx] = i;
            return;
        }
    }
    // it was incremented already, so we revert it back
    pc -= 2;
}

// Set delay timer = Vx
void Chip8::OP_FX15(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    delay_timer = V[Vx];
}

// Set sound timer = Vx
void Chip8::OP_FX18(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    sound_timer = V[Vx];
}

// Set I = I + Vx
void Chip8::OP_FX1E(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    I = I + V[Vx];
}

// Set I = location of sprite for digit Vx
void Chip8::OP_FX29(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t digit = V[Vx];
    I = digit*5;
}

// Store BCD representation of Vx in memory locations I, I+1, and I+2
void Chip8::OP_FX33(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t value = V[Vx];

    // ones at I+2
    // 16 bit index may exceed 4kb, so we mask it
    memory[(I+2) & 0xFFF] = value % 10;
    value = value/10;

    // tens at I+1
    memory[(I+1) & 0xFFF] = value % 10;
    value = value/10;       
    
    // hundreds at I
    memory[I & 0xFFF] = value % 10;
    value = value/10;
}

// Store registers V0 through Vx in memory starting at location I
void Chip8::OP_FX55(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    
    for(long i = 0; i <= Vx; i++){
        uint8_t value = V[i];
        memory[(I + i) & 0xFFF] = value;
    }
}

// Read registers V0 through Vx from memory starting at location I
void Chip8::OP_FX65(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    
    for(long i = 0; i <= Vx; i++){
        V[i] = memory[I + i];
    }
}

void Chip8::OP_ANNN(){
    uint16_t value = (opcode & 0x0FFF);
    I = value;
}



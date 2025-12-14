#include "chip8.h"

void Chip8::OP_FX07(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    V[Vx] = delay_timer;
}

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
void OP_FX15(); // LD DT, Vx
void OP_FX18(); // LD ST, Vx
void OP_FX1E(); // ADD I, Vx
void OP_FX29(); // LD F, Vx (Font)
void OP_FX33(); // LD B, Vx (BCD)
void OP_FX55(); // LD [I], Vx (Reg Dump)
void OP_FX65(); // LD Vx, [I] (Reg Load)


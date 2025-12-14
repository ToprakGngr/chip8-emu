#include <cstdint>

class Chip8{
public:
    uint8_t V[16] {};
    uint8_t memory[4096] {};
    uint16_t I {};
    uint16_t pc {};
    uint16_t stack[16] {};
    uint8_t sp {};
    uint8_t delay_timer {};
    uint8_t sound_timer {};
    uint8_t keypad[16] {};
    uint8_t display[64*32] {};
    uint16_t opcode {};

    Chip8();

    void LoadRom(const char* filename);
    void LoadFont();
    void EventCycle(); 
    
    typedef void (Chip8::*Chip8Func)();

    // main table, 0-F 
    Chip8Func chip8Table[16];

    // tables with multiple entries
    Chip8Func chip8Table0[16];
    Chip8Func chip8Table8[16];
    Chip8Func chip8TableE[16];
    Chip8Func chip8TableF[256];

    void Table0();
    void Table8();
    void TableE();
    void TableF();

    // empty-wrong functions
    void OP_NULL();

    // 0 Series
    void OP_0NNN(); // SYS addr (ignored by modern interpreters)
    void OP_00E0(); // CLS (Clear Display)
    void OP_00EE(); // RET (Return from Subroutine)

    // 1 - 7 Series (Standard Commands)
    void OP_1NNN(); // JP addr
    void OP_2NNN(); // CALL addr
    void OP_3XNN(); // SE Vx, byte (kk = NN)
    void OP_4XNN(); // SNE Vx, byte
    void OP_5XY0(); // SE Vx, Vy
    void OP_6XNN(); // LD Vx, byte
    void OP_7XNN(); // ADD Vx, byte

    // 8 Series (Mathematical and Bitwise operations)
    void OP_8XY0(); // LD Vx, Vy
    void OP_8XY1(); // OR Vx, Vy
    void OP_8XY2(); // AND Vx, Vy
    void OP_8XY3(); // XOR Vx, Vy
    void OP_8XY4(); // ADD Vx, Vy
    void OP_8XY5(); // SUB Vx, Vy
    void OP_8XY6(); // SHR Vx
    void OP_8XY7(); // SUBN Vx, Vy
    void OP_8XYE(); // SHL Vx

    // 9 - D Series
    void OP_9XY0(); // SNE Vx, Vy
    void OP_ANNN(); // LD I, addr
    void OP_BNNN(); // JP V0, addr
    void OP_CXNN(); // RND Vx, byte
    void OP_DXYN(); // DRW Vx, Vy, nibble

    // E Series (Keypad)
    void OP_EX9E(); // SKP Vx
    void OP_EXA1(); // SKNP Vx

    // F Series (Timer, Memory and BCD operations)
    void OP_FX07(); // LD Vx, DT
    void OP_FX0A(); // LD Vx, K (Wait for key)
    void OP_FX15(); // LD DT, Vx
    void OP_FX18(); // LD ST, Vx
    void OP_FX1E(); // ADD I, Vx
    void OP_FX29(); // LD F, Vx (Font)
    void OP_FX33(); // LD B, Vx (BCD)
    void OP_FX55(); // LD [I], Vx (Reg Dump)
    void OP_FX65(); // LD Vx, [I] (Reg Load)

};



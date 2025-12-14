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
    void Initialize();
    void EventCycle(); 

};



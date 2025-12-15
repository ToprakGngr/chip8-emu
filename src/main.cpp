#include "chip8.h"
#include "platform.h"
#include <iostream>
#include <chrono>
#include <cstring>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
        // delay is for instuction per frame
        std::cerr << "Instructions Per Frame is recommended 10\n";
        return EXIT_FAILURE;
    }

    int videoScale = std::stoi(argv[1]);
    int instructionsPerFrame = std::stoi(argv[2]); // cpu, process size per cycle
    char const* romFilename = argv[3];

    Platform platform("Chip-8 Emulator", 
                      Chip8::DISPLAY_WIDTH * videoScale, 
                      Chip8::DISPLAY_HEIGHT * videoScale, 
                      Chip8::DISPLAY_WIDTH, 
                      Chip8::DISPLAY_HEIGHT);

    Chip8 chip8;
    chip8.LoadRom(romFilename);

    int pitch = sizeof(uint32_t) * Chip8::DISPLAY_WIDTH;
    uint32_t videoBuffer[Chip8::DISPLAY_WIDTH * Chip8::DISPLAY_HEIGHT];

    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    bool quit = false;

    while (!quit) {
        quit = platform.ProcessInput(chip8.keypad);

        auto currentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        // 60Hz ~= 16.67ms)
        if (dt > 16.67f) {
            lastCycleTime = currentTime;

            // Batch Processing
            // X command per frame
            for (int i = 0; i < instructionsPerFrame; i++) {
                chip8.EventCycle();
            }

            chip8.UpdateTimers();

            // prepare the display and draw
            for (int i = 0; i < Chip8::DISPLAY_WIDTH * Chip8::DISPLAY_HEIGHT; ++i) {
                uint8_t pixel = chip8.display[i];
                videoBuffer[i] = (pixel == 1) ? 0xFFFFFFFF : 0x00000000;
            }

            platform.Update(videoBuffer, pitch);
        }
    }

    return 0;
}

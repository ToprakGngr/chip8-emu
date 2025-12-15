#include "chip8.h"

void Chip8::OP_DXYN(){
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;
    uint8_t bytes = (opcode & 0x000F);

    uint8_t xPos = V[Vx] % DISPLAY_WIDTH;
    uint8_t yPos = V[Vy] % DISPLAY_HEIGHT;

    V[0xF] = 0;

    for(unsigned int row = 0; row < bytes; row++){
        uint8_t spriteByte = memory[I + row];
        
        for(unsigned int col = 0; col < 8; col++){
            uint8_t spritePixel = spriteByte & (0x80 >> col) // loop through all bytes of col
            uint8_t* screenPixel = &display[(yPos + row) * DISPLAY_WIDTH + (xPos + col)];

            if(spritePixel){
                
                // on collision
                if(*screenPixel == 1){
                    V[0xF] = 1;
                }

                *screenPixel ^= 1;
            }
        }
    }

}

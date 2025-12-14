#include "chip8.h"
#include <fstream>
#include <ios>

const unsigned int START_POS = 0x200;
const unsigned int MEM_SIZE = 4096;

void Chip8::LoadRom(const char* filename) {
    std::ifstream file(filename, std::ios_base::binary | std::ios_base::ate);

    if(file.is_open()){
        std::streampos size = file.tellg();

        const long max_size = MEM_SIZE - START_POS;

        if(size > max_Size){
            std::cerr << "Warning: ROM has grown too big, the overflowed data will be discarded.\n";
            size = max_size;
        }

            char* buffer = new char[length];

            file.seekg(0, std::ios_base::beg);
            file.read(buffer, length);
            file.close();

            for(long i = 0; i < length(); i++){
                memory[START_POS + i] = static_cast<uint8_t>(buffer[i]);
            }

        delete[] buffer;
    }
}


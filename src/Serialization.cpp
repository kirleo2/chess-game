//
//  Serialization.cpp
//  chess
//
//  Created by Kirill on 22.05.2022.
//

#include "Serialization.hpp"

void Serializer::putBit(bool bit) {
    if (bit_position == 0) {
        file_bytes.push_back(0);
    }
    if (bit) {
    file_bytes[byte_position] |= (mask >> bit_position);
    }
    bit_position++;
    if (bit_position == 8) {
        bit_position = 0;
        byte_position++;
    }
}

void Serializer::put3BitNumber(uint8_t num) {
    for (int i = 2; i >= 0; i--) {
        putBit(num & (1 << i));
    }
}

bool Serializer::makeOutputFile(const string & filename) {
   ofstream outStream;
    outStream.open(filename);
    if(!outStream.is_open()) return false;
    for (uint8_t byte : file_bytes) {
        if(!outStream.put((char) byte)) return false;
    }
    outStream.close();
    return true;
}

Deserializer::Deserializer ( const string & filename ) {
    ifstream file;
    file.open(filename, ios::binary);
    file_is_open = file.is_open();
    char byte;
    while (file.get(byte)) {
        uint8_t b = (int) (unsigned char) byte;
        file_bytes.push_back(b);
    }
    file.close();
}

bool Deserializer::getNextBit () {
   
    bool bit = ((file_bytes[current_byte_pos]) & ( mask >> (current_bit_pos++)));
    if (current_bit_pos == 8) {
        current_bit_pos = 0;
        current_byte_pos++;
    }
    return bit;
}

uint8_t Deserializer::getNext3Bit() {
    uint8_t num = 0;
    for (int i = 2; i >= 0; i--) {
        num += (getNextBit() * (1 << i));
    }
    return num;
}

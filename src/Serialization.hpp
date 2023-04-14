//
//  Serialization.h
//  chess
//
//  Created by Kirill on 19.05.2022.
//

#ifndef Serialization_h
#define Serialization_h

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/**
 * \brief   Class that is necessary to encode all movesinto a binary file
 *
 * \details It has mask, bit and byte positions to write bits into a vector of bytes
 *
 */
class Serializer {
public:
    Serializer():
    bit_position(0),
    byte_position(0)
    {}
    /**
     * \brief   Function to write a bit into a binary file
     *
     * \details This method writes bit on corrent position in current byte array using mask.
                We can imagine an infinite array of bytes 0x0 (0b00000000), that method fills it up
                with "1" on correct positions by moving "1" towards the right in mask.
     *
     */
    void putBit(bool bit);
    /**
     * \brief   Function to write a 3 bit number into a binary file
     *
     * \details This method is necessary to write board coordinates - because they are encoded with 3 bits (0-7)
     *
     */
    void put3BitNumber(uint8_t num);
    /**
     * \brief   Method to write all encoded bytes into the result compressed file.
     *
     */
    bool makeOutputFile(const string & filename);
    
    vector<char> getLast2Bytes();

private:
    vector<uint8_t> file_bytes;
    int bit_position;
    int byte_position;
    uint8_t mask = 0b10000000;
    
};

/**
 * \brief   Class that is necessary to decode all moves from a binary file
 *
 * \details It has mask, bit and byte positions to write bits into a vector of bytes
 *
 */
class Deserializer {
    
public:
    /*
     reading input file bytes, those we will keep in vector of unsigned 8-bit integers
     (the same thing as an unsigned char)
     */
    Deserializer ( const string & filename );
    
    bool isFileEmpty() {
        return !file_bytes.size();
    }
    /**
     * \brief    Functiont for examination, if we can proceed with getting of next bytes and bits in our input file
     *           (if we didnt reach the end of the file)
     *
     */
    bool isBytesLeft() const {
        return (current_byte_pos < (int) file_bytes.size());
    }
    
    bool isFileOpen () const {
        return file_is_open;
    }
    
    /**
     * \brief   Function to read a bit from a binary file
     *
     * \details It reads bits using the mask 0b10000000
     *          we move the "1" towards the right and get current bit in current byte using & operator
     *
     */
    bool getNextBit ();
    /**
     * \brief   Function to read 3 bits based on getNextBit
     *
     */
    uint8_t getNext3Bit();
    
private:
    int current_bit_pos = 0;
    int current_byte_pos = 0;
    bool file_is_open = false;
    const uint8_t mask = 0b10000000;
    vector <uint8_t> file_bytes;
};

#endif /* Serialization_h */

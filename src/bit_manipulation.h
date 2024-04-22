#ifndef __BIT_MANIPULATION_H
#define __BIT_MANIPULATION_H

//set bit on byte as 1
#define setBit(byte, nbit) ((byte) |= (1 << (nbit))) 
//set bit on byte as 0
#define clearBit(byte ,nbit) ((byte) &= ~(1 << (nbit)))
//check if bit on byte is 1 
#define checkBit(byte, nbit) ((byte) & (1 << (nbit))) 
//flip all bits (so all 1 set as 0, all 0 set as 1)
#define flipBit(byte, nbit) ((byte) ^= (1 << (nbit))) 

#endif
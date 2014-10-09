#ifndef IO_H
#define IO_H
/* This file will be used to implement the core i/o related functions. */ 
#include <stdint.h>
void init_video() ;  
void move_csr() ; 
void scroll() ; 
void putch(unsigned char c) ;  
uint8_t inportb (uint16_t _port) ;  // used for inputting. 
void outportb (uint16_t _port, uint8_t _data) ;  // used for outputting a value to a register
void print(int32_t) ; 
void print(uint32_t) ; 
void print(long) ; 
void print(float) ; 
void print(double) ; 
void print(const char*) ;
#endif 

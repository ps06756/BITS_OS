#ifndef STRING_H
#define STRING_H 
#include <stdint.h> 
/* It will contain the string related functions. */
void* memcpy(void *dest, const void *src, size_t count) ; 
void* memset(void *dest, char val, size_t count) ; 
unsigned short* memsetw(unsigned short *dest, unsigned short val, size_t count) ; 
size_t strlen(const char *str); 
#endif  

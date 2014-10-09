#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <stdint.h>  
/* This file will contain the parameters related to the processor.*/ 
/* These parameters will be set when the processor restarts. */ 
struct breg 
{
  int32_t eax ; 
  int32_t ecx ; 
  int32_t edx ; 
  int32_t ebx ; 
  int32_t esp ; 
  int32_t ebp ; 
  int32_t esi ; 
  int32_t edi ; 
} ; 
typedef struct breg breg ;
extern breg reg_val ; 
// always call this function before using the above variable.  
extern "C" void get_breg_a(breg) ;
extern "C" void get_ax_a(short) ;
extern "C" void get_eax_a(int) ;
extern "C" void get_cs_a(unsigned int, short) ; 
extern "C" void get_ip_a(int) ;  
extern "C" void enable_interrupts() ; 
extern "C" void disable_interrupts() ;
extern "C" void enable_protected_mode() ;      
#endif 

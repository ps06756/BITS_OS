#ifndef EXCEPTION_H
#define EXCEPTION_H 
#include <processor.h>
extern "C" void isr0() ; 
extern "C" void isr8() ;  
/* This header file will define some common functions used to handle the exceptiosn. */ 
extern "C" void divide_by_zero(breg val) ; // to be called from assembly code. (is0)
extern "C" void double_fault(breg val) ;  // to be called from assembly code. (isr8) 
#endif  

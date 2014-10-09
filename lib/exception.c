#include <exception.h> 
#include <processor.h>
#include <io.h>
short exception_nested = 0 ;  
void divide_by_zero(breg val)
{
  exception_nested++ ;
  disable_interrupts() ; 
  print("Divide by zero exception raised..\nip = ")  ;
  if(exception_nested > 5)
    {
      for(;;) ; 
    }
  //enable_interrupts() ; 
}
void double_fault(breg val)
{
  //disable_interrupts() ;
  exception_nested++ ; 
  print("Double fault occurred..\n") ;
  print(val.esp) ; 
  print("\n") ;
  if(exception_nested > 5)
    {
      for(;;) ;
    }
  //enable_interrupts() ; 
}

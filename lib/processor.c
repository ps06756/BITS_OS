#include <processor.h> 
#include <stdint.h>
#include <io.h> 
breg reg_val ;   
extern "C" void get_breg_a(breg val)
{
  reg_val.eax = val.eax ; 
  reg_val.ecx = val.ecx ; 
  reg_val.edx = val.edx ; 
  reg_val.ebx = val.ebx ; 
  reg_val.ebp = val.ebp ; 
  reg_val.esp = val.esp ; 
  reg_val.esi = val.esi ; 
  reg_val.edi = val.edi ;
}
extern "C" void get_ax_a(short val)
{
  print(val) ; 
}
extern "C" void get_eax_a(int val)
{
  print(val) ;
}
extern "C" void get_cs_a(unsigned int fip, short val) // forward instruction pointer. now we have to subtract the address value. 
{
  print(val) ;
  print("\n") ; 
  print(fip) ; 
  
}
extern "C" void get_ip_a(int val)
{
  print(val) ; 
}
  

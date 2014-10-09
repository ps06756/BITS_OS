#include <processor.h>
#include <io.h>
#include <idt.h> 
#include <exception.h> 
extern "C" void get_breg() ;
extern "C" void get_ax() ;
extern "C" void get_eax() ;
extern "C" void get_cs() ;  
extern "C" void enable_protected_mode() ;      
extern "C" int check_if_protected_mode() ; 
extern "C" void kernel_main()
{
  init_video() ; 
  print("\t\t\tBITS OS\t\t\t\n") ; 
  print("Welcome to our OS.\n") ;  
  idt_install() ;   
  disable_interrupts() ;
  enable_interrupts() ;  // giving the exception 
  print("IDT installed succesfully\n") ;
  print("\n") ;
  if(check_if_protected_mode() == 1)
  {
    print("In the protected mode...\n") ; 
  }
  else 
  {
    print("Not in protected mode...\n") ; 
  }
  enable_protected_mode() ; 
  if(check_if_protected_mode() == 1)
  {
    print("In the protected mode...\n") ; 
  }
  else 
  {
    print("Not in protected mode...\n") ; 
  }

  // int num1 = 5;
  // int num2 = 0;
  // int num3 = num1/num2 ;
  // print("num3 = ") ;
  // print(num3) ;
  // for(;;)  ;
} 

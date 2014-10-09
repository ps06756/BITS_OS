#ifndef IDT_H
#define IDT_H 
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        /* Our kernel segment goes here! */
    unsigned char always0;     /* This will ALWAYS be set to 0! */
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

typedef struct idt_entry idt_entry ; 
typedef struct idt_ptr idt_ptr ; 

extern "C"  void idt_load();
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) ; 
void idt_install() ; 
#endif 

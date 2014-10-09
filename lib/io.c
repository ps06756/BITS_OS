#include <io.h>
#include <stdint.h>
#include <string.h>  
unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

void move_csr(void)
{
    unsigned temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = csr_y * 80 + csr_x;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

/* Clears the screen */
void cls()
{
    unsigned blank;
    int i;

    /* Again, we need the 'short' that will be used to
    *  represent a space with color */
    blank = 0x20 | (attrib << 8);

    /* Sets the entire screen to spaces in our current
    *  color */
    for(i = 0; i < 25; i++)
        memsetw (textmemptr + i * 80, blank, 80);

    /* Update out virtual cursor, and then move the
    *  hardware cursor */
    csr_x = 0;
    csr_y = 0;
    move_csr();
}

void scroll(void)
{
    unsigned blank, temp;

    /* A blank is defined as a space... we need to give it
    *  backcolor too */
    blank = 0x20 | (attrib << 8);

    /* Row 25 is the end, this means we need to scroll up */
    if(csr_y >= 25)
    {
        /* Move the current text chunk that makes up the screen
        *  back in the buffer by a line */
        temp = csr_y - 25 + 1;
        memcpy (textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);

        /* Finally, we set the chunk of memory that occupies
        *  the last line of text to our 'blank' character */
        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
    }
}

unsigned char inportb (uint16_t _port) // used for inputting a value. 
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (uint16_t _port, uint8_t _data) // used for outputting a value to a register. 
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void putch(unsigned char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;

    /* Handle a backspace, by moving the cursor back one space */
    if(c == 0x08)
    {
        if(csr_x != 0)
        {
            csr_x --;
            putch(' ');
            csr_x--;
        }

        else
        {
            if(csr_y == 0);
            else
            {
                csr_x = 79;
                csr_y--;
                putch(' ');
                csr_x = 79;
                csr_y--;
            }
        }
    }
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    /* Handles a 'Carriage Return', which simply brings the
    *  cursor back to the margin */
    else if(c == '\r')
    {
        csr_x = 0;
    }
    /* We handle our newlines the way DOS and the BIOS do: we
    *  treat it as if a 'CR' was also there, so we bring the
    *  cursor to the margin and we increment the 'y' value */
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    else if(c >= ' ')
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;	/* Character AND attributes: color */
        csr_x++;
    }

    /* If the cursor has reached the edge of the screen's width, we
    *  insert a new line in there */
    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    /* Scroll the screen if needed, and finally move the cursor */
    scroll();
    move_csr();
}
void init_video(void)
{
    textmemptr = (unsigned short *)0xB8000;
    cls();
}

void print(int num)
{
    if(num < 0)
    {
        putch('-');
        num = -num;
    }
    if(num/10)
    {
        print(num/10);
    }
    putch(num%10 + '0');
}

/* Takes an unsigned integer and prints it on the console. */
void print(unsigned int num)
{
    if(num < 0)
    {
        putch('-');
        num = -num;
    }
    if(num/10)
    {
        print(num/10);
    }
    putch(num%10 + '0');
}

/* Takes a long and prints it on the console. */
void print(long num)
{
    if(num < 0)
    {
        putch('-');
        num = -num;
    }
    if(num/10)
    {
        print(num/10);
    }
    putch(num%10 + '0');
}

/* Takes a float and prints it on the console. Prints 6 digits after decimal point.*/
void print(float num)
{
    int i = (int) num;
    print(i);
    putch('.');
    num -= i;
    num *= 1000000;
    print((int) num);
}

/* Takes a double and prints it on the console. Prints 6 digits after decimal point. */
void print(double num)
{
    int ipart = (int) num;
    print(ipart);
    putch('.');
    num -= ipart;
    for(int i = 0; i < 6; i++)
    {
        num *= 10;
        ipart = (int)num; 
        putch(ipart + '0');
        num -= ipart;
    }
}

/* Outputs the parameter string. */
void print(const char *text)
{
  uint32_t i ; 

    for (i = 0; i < strlen(text); i++)
    {
        putch(text[i]);
    }
}

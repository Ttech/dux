#include <dux/drivers/core/ports.h>
#include <dux/drivers/core/console.h>

#include <isr.h>

unsigned char buf[0x1000];
unsigned char *buffer;
unsigned char *origbuffer;

unsigned char kbdus[128] =
{
  0, 27, '1', '2', '3', '4', '5', '6', '7', '8',    /* 9 */
  '9', '0', '-', '=', '\x08',  /* Backspace */
  '\t',        /* Tab */
  'q', 'w', 'e', 'r',    /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',    /* Enter key */
  0,              /* 29 - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',  /* 39 */
  '\'', '`', 0,            /* Left shift */
  '\\', 'z', 'x', 'c', 'v', 'b', 'n',      /* 49 */
  'm', ',', '.', '/', 0,        /* Right shift */
  '*',
  0,  /* Alt */
  ' ',  /* Space bar */
  0,  /* Caps lock */
  0,  /* 59 - F1 key ... > */
  0, 0, 0, 0, 0, 0, 0, 0,
  0,  /* < ... F10 */
  0,  /* 69 - Num lock*/
  0,  /* Scroll Lock */
  0,  /* Home key */
  0,  /* Up Arrow */
  0,  /* Page Up */
  '-',
 
  0,  /* Left Arrow */
  0,
  0,  /* Right Arrow */
  '+',
  0,  /* 79 - End key*/
  0,  /* Down Arrow */
  0,  /* Page Down */
  0,  /* Insert Key */
  0,  /* Delete Key */
  0, 0, 0,
  0,  /* F11 Key */
  0,  /* F12 Key */
  0,  /* All other keys are undefined */
};

static void kb_irq_handler()
{
	unsigned int scancode = inb(0x60);

	*++buffer = kbdus[scancode];
}

char kb_read()
{
	char tmp;
start:
	if (buffer > origbuffer) {
		tmp = *buffer--;
		return tmp;
	} else {
		// Goto is usually frowned upon, but it is truly the most
		// understandable method here. We could also use a while loop.
		goto start;
	}
}

void kb_init()
{
	irq_install_handler(1, kb_irq_handler);
	// The compiler is convinced that unsigned char[0x1000] is not an
	// lvalue, so all these hacks are needed to compile.
	buffer = buf;
	origbuffer = buffer;
}

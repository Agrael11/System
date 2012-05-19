#include "inc/IO.h"


namespace IO {
	void oB(unsigned short port, unsigned char data) {
		asm("outb %1, %0" : : "dN" (port), "a" (data));
	}

	unsigned char iB(unsigned short port) {
		unsigned char r;
		asm("inb %1, %0" : "=a" (r) : "dN" (port));
		return r;
	}
}
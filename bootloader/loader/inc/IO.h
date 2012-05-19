#ifndef __IO_H__
#define __IO_H__

namespace IO {
	void oB(unsigned short port, unsigned char data);

	unsigned char iB(unsigned short port);
}

#endif
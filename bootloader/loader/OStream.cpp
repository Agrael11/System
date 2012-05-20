#include "inc/OStream.h"

#define COLOR ((backgroundColor << 4 | textColor) << 8)

OStream::OStream() {
	char cardType = (*(unsigned short*) 0x410 & 0x30);
	
	if(cardType == 0x30) {
		video = (unsigned short*) 0xb0000;
		crtcMem = 0x3b4;
	} else {
		video = (unsigned short*) 0xb8000;
		crtcMem = 0x3d4;
	}

	height = 25;
	width = 80;
	x = 0;
	y = 0;

	backgroundColor = 0;
	textColor = 0x7;
	Clear();
}


void OStream::Clear() {
	for(unsigned int i=0;i<(width * height);i++) {
		video[i] = (unsigned char) ' ' | COLOR;
	}
}


void OStream::write(char *text) {
	while(*text) put(*(text++));
}


void OStream::put(char c) {
	int pos;
	switch(c) {
		case '\r':
			x=0;
			break;
		case '\n':
			x=0;
			y++;
			break;
		case 8:
			pos = x + y * width;
			if(pos) pos--;

			if(x > 0) {
				x--;
			} else {
				y--;
				x = width-1;
			}

			*(video + pos) = ' ' | COLOR;
			break;
		default:
			*(video + x + y * width) = c | COLOR;
			for(int k=0;k<100;k++);
			x++;
			if(x == width) {
				x=0;
				y++;
			}
			break;
	}

	if(y == height) {
		scrollUp();
		y--;
	}

	SetCursor(x, y);
}


void OStream::scrollUp() {
	unsigned int i=width*10;
	for(;i<width*(height-1);i++) {
		*(video + i) = *(video + i + width);
	}

	for(;i<width * height;i++) {
		*(video + i) = ' ' | COLOR;
	}
}


void OStream::SetCursor(unsigned int x, unsigned int y) {
	unsigned short offset;
	offset = x + y * width;
	
	IO::oB(crtcMem, 14);
	IO::oB(crtcMem + 1, offset >> 8);

	IO::oB(crtcMem, 15);
	IO::oB(crtcMem + 1, offset);
}


void OStream::SetTextColor(Colors color) {
	textColor = (unsigned char)color;
}


void OStream::SetBackgroundColor(Colors color) {
	backgroundColor = (unsigned char)color;
}


OStream& OStream::operator <<(const char *str) {
	write((char *)str);
	return *this;
}


OStream& OStream::operator <<(char *str) {
	write(str);
	return *this;
}


OStream& OStream::operator <<(char str) {
	put(str);
	return *this;
}


OStream& OStream::operator <<(unsigned char str) {
	put((char)str);
	return *this;
}

#undef COLOR
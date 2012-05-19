#include "IO.h"

#ifndef __OSTREAM_H__
#define __OSTREAM_H__

class OStream {
public:
	OStream();
	OStream& operator <<(const char *str);
	OStream& operator <<(char *str);
	OStream& operator <<(char str);
	OStream& operator <<(unsigned char str);

	enum Colors {
		Black,
		Blue,
		Green,
		Cyan,
		Red,
		Magenta,
		Brown,
		LightGrey,
		DarkGrey,
		LightBlue,
		LightGreen,
		LightCyan,
		LightRed,
		LightMagenta,
		LightBrown,
		White
	};

	void Clear();
	void SetBackgroundColor(Colors color);
	void SetTextColor(Colors color);
	void SetCursor(unsigned int x, unsigned int y);

private:
	unsigned short *video,
					crtcMem;

	unsigned int height,
				 width;

	unsigned char backgroundColor,
				  textColor;

	unsigned int x,
				 y;

	void write(char *);
	void put(char);
	void scrollUp();
};

#endif
#include "inc/Keyboard.h"

namespace Keyboard {

	unsigned short read() {
		return IO::iB(0x64);
	}
}
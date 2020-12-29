#include <Windows.h>
#include <io.h>

#define  GTEST_OS_WINDOWS 1

enum GTestColor {
	COLOR_DEFAULT,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_YELLOW
};

WORD GetColorAttribute(GTestColor color);

#if GTEST_OS_WINDOWS && !GTEST_OS_WINDOWS_MOBILE

// Returns the character attribute for the given color.
WORD GetColorAttribute(GTestColor color) {
	switch (color) {
	case COLOR_RED:    return FOREGROUND_RED;
	case COLOR_GREEN:  return FOREGROUND_GREEN;
	case COLOR_YELLOW: return FOREGROUND_RED | FOREGROUND_GREEN;
	default:           return 0;
	}
}

#else

// Returns the ANSI color code for the given color.  COLOR_DEFAULT is
// an invalid input.
const char* GetAnsiColorCode(GTestColor color) {
	switch (color) {
	case COLOR_RED:     return "1";
	case COLOR_GREEN:   return "2";
	case COLOR_YELLOW:  return "3";
	default:            return NULL;
	};
}

#endif 

void ColoredPrintf(GTestColor color, const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	const HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	GetConsoleScreenBufferInfo(stdout_handle, &buffer_info);

	const WORD old_color_attrs = buffer_info.wAttributes;
	fflush(stdout);

	SetConsoleTextAttribute(stdout_handle,
		GetColorAttribute(color) | FOREGROUND_INTENSITY);
	vprintf(fmt, args);
	fflush(stdout);
	// Restores the text color.
	SetConsoleTextAttribute(stdout_handle, old_color_attrs);
	va_end(args);
}

int main()
{
	ColoredPrintf(COLOR_YELLOW, "\nMy test output color fonts.");
	ColoredPrintf(COLOR_RED, " test again.");
	return 0;
}
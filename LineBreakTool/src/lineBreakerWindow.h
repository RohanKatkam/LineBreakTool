#pragma once

#include "imgui.h"
#include <string>

// Textbox height in number of lines as unit
#define TEXT_BOX_HEIGHT 8

// Maximum number of bytes a string holds
#define MAX_STD_STRING_LENGTH 2048

// Maximum number of bytes output text must hold
#define MAX_OUTPUT_TEXT_LEN 2048

namespace window
{
	// Removes the line break
	static void removeLineBreak(std::string entryText, char* outputText);

	// Clears and resets the output text
	static void resetOutputText(char* outputText);

	// Creates a window instance
	void generateWindow(void);
}

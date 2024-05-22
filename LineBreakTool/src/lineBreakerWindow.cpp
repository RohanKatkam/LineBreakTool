// Source file for the window

#include "lineBreakerWindow.h"
#include "misc/cpp/imgui_stdlib.h"
#include <string>

namespace window
{
    // Initialize tool parameters
    bool isConvertButtonClicked = false;
    char defaultOutputText[MAX_STD_STRING_LENGTH] = "Output text is here";
    static std::string entryText;
    static char outputText[MAX_OUTPUT_TEXT_LEN] = "Default Output has'dsf'";

    static bool isIgnoredMultipleLineBreak = false;
    static void removeLineBreak(std::string entryText, char* filteredText)
    {
        // Read every character
        unsigned int outputIdx = 0;
        for (int i = 0; i < entryText.length(); i++)
        {
            // Line breaking logic
            if (entryText[i] != '\n')
            {
                filteredText[outputIdx++] = entryText[i];
            }
            else
            {
                if (i - 1 < 0) continue;
                if ((i + 1) >= entryText.length()) break;
                char previousChar = entryText[i - 1];
                char nextChar = entryText[i + 1];

                if (!isIgnoredMultipleLineBreak)
                {
                    if (nextChar == '\n')
                    {
                        filteredText[outputIdx++] = '\n';
                        continue;
                    }
                }
                
                if (! (previousChar == '-' || previousChar == ' ' || nextChar == ' ' || previousChar == '\n'))
                {
                    filteredText[outputIdx++] = ' ';
                }

                // Multiline ignore feature
                
            }
        }
        filteredText[outputIdx] = '\0';
    }

    static void resetOutputText(char* outputText)
    {
        for (int i = 0; i < MAX_OUTPUT_TEXT_LEN; i++)
            outputText[i] = defaultOutputText[i];
    }

    void generateWindow(void)
    {
        // Your own code that is, your appplication window begins 
        ImGui::Begin("Line Breaking Tool");

        // Input Textbox 
        ImGui::Text("Welcome to the tool application, where unncessary line breaks are broken at ease, please add your input text to the textbox below");
        ImGui::SeparatorText("Input");

        ImGui::Checkbox("Ignore multiple line Breaks?", &isIgnoredMultipleLineBreak);
        //ImGui::InputText("Input Text", &entryText);

        ImGui::InputTextMultiline("Input 'Text", &entryText, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * TEXT_BOX_HEIGHT));

        // Convert Button
        if (ImGui::Button("Convert Text"))
            isConvertButtonClicked = true;
        else
            isConvertButtonClicked = false;

        // Output Textbox
        ImGui::SeparatorText("Output");
        if (isConvertButtonClicked && (entryText.length() < MAX_OUTPUT_TEXT_LEN))
        {
            removeLineBreak(entryText, outputText);
        }

        // Print output
        ImGui::TextWrapped(outputText);

        // Copy Button
        static bool isCopyButtonClicked = false;

        if (ImGui::Button("Copy Output"))
            isCopyButtonClicked = true;

        // Copy logic?!
        if (isCopyButtonClicked)
        {
            ImGui::LogToClipboard();
            ImGui::LogText(outputText);
            ImGui::LogFinish();

            ImGui::SameLine();
            ImGui::Text("Output Successfully Copied!");
        }

        // Clear I/O Text
        bool isIOButtonClicked = ImGui::Button("Clear I/O Text");

        if (isIOButtonClicked)
        {
            // Reset input to blank
            entryText = "";

            // Reset output text to default text
            resetOutputText(outputText);

            isCopyButtonClicked = false;
        }

        // End window
        ImGui::End();
    }

}
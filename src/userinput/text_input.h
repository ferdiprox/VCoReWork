#pragma once

#include <vector>
#include <SDL2/SDL.h>

namespace text_input
{
    enum SPECIAL_INPUT_CHAR
    {
      SIC_ENTER,
      SIC_BACKSPACE,

      SIC__MAX,
    };

    extern std::vector<char> frameInputChars;

    // sdlEvent: SDL_TextInputEvent or SDL_KeydownEvent
    void inputFromSDL(const SDL_Event& sdlEvent);
    void endFrame();

    void xtInputHandler(SDL_Event* sdlEventPointer);

    void init();

    inline bool isSpecialInput(char inputChar)
    {
        return inputChar < SIC__MAX;
    }
}

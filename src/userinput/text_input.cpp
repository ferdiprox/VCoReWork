#include "text_input.h"

#include <iostream>

namespace text_input
{
    std::vector<char> frameInputChars;

    void inputFromSDL(const SDL_Event& sdlEvent)
    {

        switch(sdlEvent.type)
        {
        case SDL_TEXTINPUT:
            frameInputChars.push_back(*sdlEvent.text.text);
            break;
        case SDL_KEYDOWN:
            switch(sdlEvent.key.keysym.scancode)
            {
            case SDL_SCANCODE_BACKSPACE:
                frameInputChars.push_back(SIC_BACKSPACE);
                break;
            case SDL_SCANCODE_RETURN:
                frameInputChars.push_back(SIC_ENTER);
                break;
            }
            break;
        }
    }

    void endFrame()
    {
        frameInputChars.clear();
    }

    // Changed to input from KeyCenter.
    //void xtInputHandler(SDL_Event* sdlEventPointer)
    //{
    //    inputFromSDL(*sdlEventPointer);
    //}

    void init()
    {
        //text_input_handler = &xtInputHandler;
    }
}

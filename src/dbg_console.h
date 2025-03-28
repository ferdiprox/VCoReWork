#pragma once

#include <string>

class DebugConsole
{
public:

    void init();
    void update();

    bool isOpen = false;

private:

    std::string currentInputText;

    struct Message
    {
        enum MESSAGE_TYPE
        {
            MT_LOG,
            MT_ERROR,
        };

        unsigned char type = MT_LOG;
        std::string text = "";

        Message& operator=(const Message& copyFrom)
        {
            text = copyFrom.text;
            type = copyFrom.type;

            return *this;
        }
    };

    struct MessageStack
    {
        Message* buffer = 0;
        int bufferOffset = 0;
        int bufferSize = 0;

        inline void create(int size)
        {
            buffer = new Message[bufferSize = size];
        }

        // Move all messages forward, to reserve place for one message at the begin
        inline void shiftBuffer()
        {
            for(int i = bufferOffset; i > 0; i--)
            {
                buffer[i] = buffer[i-1];
            }
        }

        inline Message& pushAndGet()
        {
            shiftBuffer();

            if(bufferOffset != bufferSize-1) bufferOffset++;

            return buffer[0];
        }
    };

    MessageStack messageHistory;

    void updateWindow();
    void updateBody();

    void checkInput();

    void drawMessages();
    void pushMessage(std::string text, unsigned char type);

    void analyseCommand();
};

extern DebugConsole dbgConsole;

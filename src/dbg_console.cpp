#include "dbg_console.h"

#include <sstream>

#include "xgraph.h"
#include "sqfont.h"
#include "userinput/text_input.h"

#include "units/mechos.h"

DebugConsole dbgConsole;

extern bool aciKeyboardLocked;

static constexpr int DBGCON_X = 40;
static constexpr int DBGCON_Y = 30;

static constexpr int DBGCON_WIDTH = 600;
static constexpr int DBGCON_MSGBODY_HEIGHT = 500;
static constexpr int DBGCON_INPUTLINE_HEIGHT = 16 + 1; // 16 is font height, 1 is space mid text.

static constexpr int DBGCON_BODY_COLOR = 224; // BLACK from palette
static constexpr int DBGCON_INPUTLINE_COLOR = 228; // GRAY from palette
static constexpr int DBGCON_MAX_MESSAGES = DBGCON_MSGBODY_HEIGHT / DBGCON_INPUTLINE_HEIGHT;

void DebugConsole::init()
{
    messageHistory.create(DBGCON_MAX_MESSAGES);

    pushMessage("Print 'help' to get console info, 'close' to close console. Recommended fullscreen mode.", Message::MT_LOG);
}

void DebugConsole::update()
{
    // Note: Debug console is toggles externally from KeyCenter(road.cpp).
    if(!this->isOpen)
    {
        return;
    }

    this->updateWindow();
}

void DebugConsole::updateWindow()
{
    updateBody();

    drawMessages();

    checkInput();

    // Draw entered text
    sysfont.draw(DBGCON_X, DBGCON_Y + DBGCON_MSGBODY_HEIGHT, currentInputText);
}

void DebugConsole::updateBody()
{
    // Message body
    XGR_Rectangle(DBGCON_X, DBGCON_Y, DBGCON_WIDTH, DBGCON_MSGBODY_HEIGHT, DBGCON_BODY_COLOR, DBGCON_BODY_COLOR, XGR_FILLED);

    // Input line body
    XGR_Rectangle(DBGCON_X, DBGCON_Y + DBGCON_MSGBODY_HEIGHT, DBGCON_WIDTH, DBGCON_INPUTLINE_HEIGHT, DBGCON_INPUTLINE_COLOR, DBGCON_BODY_COLOR, XGR_FILLED);
}

void DebugConsole::checkInput()
{
    bool isSpecialKey;

    for(char inputKey : text_input::frameInputChars)
    {
        switch(inputKey)
        {
        default:
            currentInputText += inputKey;
            break;
        case text_input::SIC_BACKSPACE:
            if(currentInputText.empty())
                break;

            currentInputText.erase(currentInputText.size()-1, 1);
            break;
        case text_input::SIC_ENTER:
            analyseCommand();
            currentInputText.clear();
            break;
        }
    }
}

void DebugConsole::drawMessages()
{
    int yPosition = DBGCON_MSGBODY_HEIGHT - DBGCON_INPUTLINE_HEIGHT + DBGCON_Y;

    for(int i = 0; i < messageHistory.bufferOffset; i++)
    {
        Message& message = messageHistory.buffer[i];
        sysfont.draw(DBGCON_X, yPosition, message.text, message.type == Message::MT_ERROR ? SQ_SYSCOLOR : SYSCOLOR);
        yPosition -= DBGCON_INPUTLINE_HEIGHT;
    }
}

void DebugConsole::pushMessage(std::string text, unsigned char type)
{
    std::vector<std::string> sendQueue;

    int msgX = 0;
    for(int i = 0; i < text.size(); i++)
    {
        msgX += sysfont.sx;

        if(msgX > DBGCON_WIDTH || text[i] == '\n')
        {
            msgX = 0;

            std::string& subMessage = sendQueue.emplace_back();
            subMessage = text.substr(0, i);

            // Erase '\n' too.
            if(text[i] == '\n')
            {
                i++;
            }

            text.erase(0, i);
            i = -1;
        }
    }

    if(text.size())
    {
        sendQueue.push_back(text);
    }

    for(const std::string& newMsgText : sendQueue)
    {
        Message& newMessage = messageHistory.pushAndGet();

        newMessage.text = newMsgText;
        newMessage.type = type;
    }
}

#define ASSERT_GET_TOKEN(varName) if(!(parseStream >> varName)) { pushMessage("Expected one more '"#varName"' token.", Message::MT_ERROR); continue; }

void DebugConsole::analyseCommand()
{
    pushMessage(currentInputText, Message::MT_LOG);

    std::istringstream parseStream;

    parseStream.str(currentInputText);

    std::string token;

    while(parseStream >> token)
    {
        if(token == "help")
        {

            pushMessage(
                R"(Vangers Debug Console by Ferdinand
Help text syntaxis:
    Command-section:
        Command (Arguments)

Input syntaxis:
    Command-section Command Arguments

    Example:
        player setpos 400 70

Command-sections:
    player - Action with player's VangerUnit:
        setpos2 - Set 2D world position(X,Y)
        setpos3 - Set 3D world position(X,Y,Z)
    help - Print this text in console
    close - Close console window)",
                    Message::MT_LOG
            );

        }
        else if(token == "player")
        {
            VangerUnit& playerVanger = *ActD.Active;
            if(parseStream >> token)
            {
                if(token == "setpos2")
                {
                    int newX, newY;

                    ASSERT_GET_TOKEN(newX);
                    ASSERT_GET_TOKEN(newY);

                    playerVanger.R.x = newX;
                    playerVanger.R.y = newY;
                }
                else if(token == "setpos3")
                {
                    int newX, newY, newZ;

                    ASSERT_GET_TOKEN(newX);
                    ASSERT_GET_TOKEN(newY);
                    ASSERT_GET_TOKEN(newZ);

                    playerVanger.R.x = newX;
                    playerVanger.R.y = newY;
                    playerVanger.R.z = newZ;
                }
            }
        }
        else if(token == "close")
        {
            isOpen = false;
            aciKeyboardLocked = false;
        }
        else
        {
            pushMessage("Unknown token: '" + token + "'", Message::MT_ERROR);
        }
    }
}

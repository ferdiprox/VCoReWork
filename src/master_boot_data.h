#pragma once

#include "lang.h"

#include <string>

enum SPECIAL_AUTOCN_GAME_IDS
{
    AUTOCN_NEW = 0,
    AUTOCN_ANY = -1,
};

namespace mbd
{
    extern Language language; 

    extern bool isAutoconnect;
    extern std::string autoconnectHost;
    extern unsigned short autoconnectPort;
    extern bool isAutoconnectJoinGame;
    extern int autoconnectGameID;
}
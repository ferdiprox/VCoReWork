#include "master_boot_data.h"

/*
        MASTER BOOT DATA

    Storage with startup and runtime data from master boot.
*/

namespace mbd
{
    Language language = ENGLISH;

    bool isAutoconnect = false;
    std::string autoconnectHost;
    unsigned short autoconnectPort;
    bool isAutoconnectJoinGame = false;
    int autoconnectGameID = -1;
}
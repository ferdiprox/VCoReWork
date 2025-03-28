#include "compas_dict.h"

#include "dict_tools.h"

namespace CompasDict
{
    char* Incubator = 0;
    char* Podish = 0;

    char* Repair1 = 0;
    char* Repair2 = 0;
    char* Rigs = 0;
    char* GhOrb = 0;
    char* Broken1 = 0;
    char* Broken2 = 0;
    char* Spiral = 0;

    char* PassGlorx = 0;
    char* PassWeexow = 0;

    char* Ogorod = 0;
    char* Lampasso = 0;
    char* VigBoo = 0;

    char* PassFostral = 0;
    char* PassNecross = 0;
    char* PassXplo = 0;
    char* PassKhox = 0;

    char* Rigs1 = 0;
    char* Rigs2 = 0;

    char* BZone = 0;
    char* ZeePa = 0;

    char* PassBoozeena = 0;
    char* PassArk = 0;

    char* Repair = 0;
    char* Broken = 0;

    char* Spobs = 0;

    char* PassThreall = 0;
    char* PassEarth = 0;
}

void CompasDict::loadLocalization(const std::string& filename)
{
    DICT_LOAD_HEADER();

    GET_LOCAL_STRING(Incubator);
    GET_LOCAL_STRING(Podish);

    GET_LOCAL_STRING(Repair1);
    GET_LOCAL_STRING(Repair2);
    GET_LOCAL_STRING(Rigs);
    GET_LOCAL_STRING(GhOrb);
    GET_LOCAL_STRING(Broken1);
    GET_LOCAL_STRING(Broken2);
    GET_LOCAL_STRING(Spiral);

    GET_LOCAL_STRING(PassGlorx);
    GET_LOCAL_STRING(PassWeexow);

    GET_LOCAL_STRING(Ogorod);
    GET_LOCAL_STRING(Lampasso);
    GET_LOCAL_STRING(VigBoo);

    GET_LOCAL_STRING(PassFostral);
    GET_LOCAL_STRING(PassNecross);
    GET_LOCAL_STRING(PassXplo);
    GET_LOCAL_STRING(PassKhox);

    GET_LOCAL_STRING(Rigs1);
    GET_LOCAL_STRING(Rigs2);

    GET_LOCAL_STRING(BZone);
    GET_LOCAL_STRING(ZeePa);

    GET_LOCAL_STRING(PassBoozeena);
    GET_LOCAL_STRING(PassArk);

    GET_LOCAL_STRING(Repair);
    GET_LOCAL_STRING(Broken);

    GET_LOCAL_STRING(Spobs);

    GET_LOCAL_STRING(PassThreall);
    GET_LOCAL_STRING(PassEarth);
}
#include "aci_dict.h"

#include "../fs/parser.h"

#include "dict_tools.h"

namespace AciDict
{
	char* optionOn = 0;
	char* optionOff = 0;
	
	char* shopUndefinedPrice = 0;
	char* shopPricePrefix = 0;

	char* shopBrokenMechosDescr = 0;

	char* shopMechosEnergyPrm = 0;
	char* shopMechosEnergyRestorePrm = 0;
	char* shopMechosArmorPrm = 0;
	char* shopMechosVelocityPrm = 0;
	char* shopMechosSpiralPrm = 0;
	char* shopMechosAirReservePrm = 0;

	char* shopWeaponDamagePrm = 0;
	char* shopWeaponLoadPrm = 0;
	char* shopWeaponShotsPrm = 0;
	char* shopWeaponBurstPrm = 0;
	
	char* shopDeviceWorkTimePrm = 0;

	char* shopAmmoInPackPrm = 0;

	char* shopNotEnoughCashString = 0;

	char* uiPickupItemsOff = 0;
	char* uiPickupWeaponsOff = 0;

	char* invPutThis = 0;

	char* mpSetupFirstWarePrm = 0;
	char* mpSetupSecondWarePrm = 0;
	char* mpSetupCheckpointsPrm = 0;

	char* saveSlotEmpty = 0;
	char* saveSlotUnnamed = 0;
	char* saveSlotAutosave = 0;

	char* mpGamePlayerWins = 0;
	char* mpGamePlayerLosses = 0;

	char* mpGameRestrictions = 0;
	char* mpGameStatistics = 0;

	char* playerStatLuck = 0;
	char* playerStatDominance = 0;

	char* timeSeconds = 0;
	char* timeMinutes = 0;
	char* timeDay = 0;
}

void AciDict::loadLocalization(const std::string& filename)
{
	DICT_LOAD_HEADER();

    GET_LOCAL_STRING(optionOn);
    GET_LOCAL_STRING(optionOff);

    GET_LOCAL_STRING(shopUndefinedPrice);
	GET_LOCAL_STRING(shopPricePrefix);

	GET_LOCAL_STRING(shopBrokenMechosDescr);

	GET_LOCAL_STRING(shopMechosEnergyPrm);
	GET_LOCAL_STRING(shopMechosEnergyRestorePrm);
	GET_LOCAL_STRING(shopMechosArmorPrm);
	GET_LOCAL_STRING(shopMechosVelocityPrm);
	GET_LOCAL_STRING(shopMechosSpiralPrm);
	GET_LOCAL_STRING(shopMechosAirReservePrm);

	GET_LOCAL_STRING(shopWeaponDamagePrm);
	GET_LOCAL_STRING(shopWeaponLoadPrm);
	GET_LOCAL_STRING(shopWeaponShotsPrm);
	GET_LOCAL_STRING(shopWeaponBurstPrm);
	
	GET_LOCAL_STRING(shopDeviceWorkTimePrm);

	GET_LOCAL_STRING(shopAmmoInPackPrm);

	GET_LOCAL_STRING(shopNotEnoughCashString);

	GET_LOCAL_STRING(uiPickupItemsOff);
	GET_LOCAL_STRING(uiPickupWeaponsOff);

	GET_LOCAL_STRING(invPutThis);

	GET_LOCAL_STRING(mpSetupFirstWarePrm);
	GET_LOCAL_STRING(mpSetupSecondWarePrm);
	GET_LOCAL_STRING(mpSetupCheckpointsPrm);

	GET_LOCAL_STRING(saveSlotEmpty);
	GET_LOCAL_STRING(saveSlotUnnamed);
	GET_LOCAL_STRING(saveSlotAutosave);

	GET_LOCAL_STRING(mpGamePlayerWins);
	GET_LOCAL_STRING(mpGamePlayerLosses);

	GET_LOCAL_STRING(mpGameRestrictions);
	GET_LOCAL_STRING(mpGameStatistics);

	GET_LOCAL_STRING(playerStatLuck);
	GET_LOCAL_STRING(playerStatDominance);

	GET_LOCAL_STRING(timeSeconds);
	GET_LOCAL_STRING(timeMinutes);
    GET_LOCAL_STRING(timeDay);
}

#pragma once

#include <string>

// Dictionary with text of current game language. 
// Used in 'aci' part of code (e.g, src/actint/ascr_fnc.cpp)
namespace AciDict
{
	void loadLocalization(const std::string& filename);

	extern char* optionOn;
	extern char* optionOff;
	
	extern char* shopUndefinedPrice;
	extern char* shopPricePrefix;

	extern char* shopBrokenMechosDescr;

	extern char* shopMechosEnergyPrm;
	extern char* shopMechosEnergyRestorePrm;
	extern char* shopMechosArmorPrm;
	extern char* shopMechosVelocityPrm;
	extern char* shopMechosSpiralPrm;
	extern char* shopMechosAirReservePrm;

	extern char* shopWeaponDamagePrm;
	extern char* shopWeaponLoadPrm;
	extern char* shopWeaponShotsPrm;
	extern char* shopWeaponBurstPrm;
	
	extern char* shopDeviceWorkTimePrm;

	extern char* shopAmmoInPackPrm;

	extern char* shopNotEnoughCashString;

	extern char* uiPickupItemsOff;
	extern char* uiPickupWeaponsOff;

	extern char* invPutThis;

	extern char* mpSetupFirstWarePrm;
	extern char* mpSetupSecondWarePrm;
	extern char* mpSetupCheckpointsPrm;

	extern char* saveSlotEmpty;
	extern char* saveSlotUnnamed;
	extern char* saveSlotAutosave;

	extern char* mpGamePlayerWins;
	extern char* mpGamePlayerLosses;

	extern char* mpGameRestrictions;
	extern char* mpGameStatistics;

	extern char* playerStatLuck;
	extern char* playerStatDominance;

	extern char* timeSeconds;
	extern char* timeMinutes;
	extern char* timeDay;
};

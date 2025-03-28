
/*
		MASTER BOOT

	Initializing Vangers, analysing arguments, saving startup data into master_boot_data.h
*/

#include <iostream>
#include <filesystem>
#if defined(__unix__) || defined(__linux__) || defined(__APPLE__)
#include <locale.h>
#endif

#include "runtime.h"
#include "xstream.h"
#include "xgraph.h"
#include "xerrhandler.h"
#include "lang.h"
#include "sound/hsound.h"
#include "xjoystick.h"

#include "iscreen/iml.h"
#include "math/int_math.h"

#include "sqfont.h"
#include "palette.h"
#include "random.h"
#include "userinput/text_input.h"
#include "locale/compas_dict.h"
#include "locale/aci_dict.h"

#include "master_boot_data.h"

extern int __internal_argc;
extern char** __internal_argv;

// TODOf: need to create some place in code for loading stuff
void LoadingMessage(int flush = 0);

namespace mboot
{

	std::ostream& log()
	{
		return std::cout << "[MBOOT] ";
	}

	void log(const std::string& text)
	{
		log() << text << '\n';
	}

	// RTO Storage
	namespace rtos
	{
		GameQuantRTO *gqObj = 0;
		MainMenuRTO *mmObj = 0;
		EscaveRTO *eObj = 0;
		EscaveOutRTO *eoObj = 0;
		FirstEscaveRTO *fObj = 0;
		FirstEscaveOutRTO *foObj = 0;
		PaletteTransformRTO *pObj = 0;
		LoadingRTO1 *lObj1 = 0;
		LoadSurfaceRTO *lObj2 = 0;
		LoadGameoverRTO *lgoObj = 0;
		ShowImageRTO *siObj = 0;
		ShowAviRTO *saObj = 0;
	}

    void readSqFont(sqFont& fontObject,const std::string& fontFileName)
    {
        XStream inputFile(fontFileName, XS_IN);

		fontObject.init(inputFile);

        inputFile.close();
    }

	std::string startupConfigLine = " STARTUP CONFIGURATION ";

	void printStartupConfigSplitter()
	{
		for(int i = 0; i < startupConfigLine.size(); i++) std::cout << '-';
		std::cout<<'\n';
	}

    void printStartupConfig()
    {
		std::cout << '\n' << startupConfigLine << '\n';

		printStartupConfigSplitter();

		// Configrations print begin

        std::cout << "Game language: ";
        switch(mbd::language)
        {
        default:
            std::cout << "English(?)";
            break;
        case ENGLISH:
            std::cout << "English";
            break;
        case GERMAN:
            std::cout << "German";
            break;
        case RUSSIAN:
            std::cout << "Russian";
            break;
        }
        std::cout << '\n';

        std::cout << "Startup path: " << std::filesystem::current_path().string() << '\n';

		std::cout << "Autoconnect: ";
		if (mbd::isAutoconnect)
		{
			std::cout << "Yes; Data:\n";

			std::cout << "\t Host: \"" << mbd::autoconnectHost<<"\"\n";
			std::cout << "\t Port: " << mbd::autoconnectPort<<'\n';

			std::cout << "\t Joining game: ";

			if (mbd::isAutoconnectJoinGame)
			{
				switch(mbd::autoconnectGameID)
				{
				default:
					std::cout << mbd::autoconnectGameID;
					break;
				case AUTOCN_NEW:
					std::cout << "[NEW]";
					break;
				case AUTOCN_ANY:
					std::cout << "[ANY]";
					break;
				}
			}

			std::cout<<'\n';
		}
		else
		{
			std::cout<<"No\n";
		}

		// End

		printStartupConfigSplitter();
		std::cout << "\n";
	}

	void setupLocale()
	{
#if defined(__unix__) || defined(__linux__) || defined(__APPLE__)
		log() << "Set locale. ";
		char* res = setlocale(LC_NUMERIC, "POSIX");
		std::cout << "Result:" << res << std::endl;
#endif
	}

	void initSound()
	{
		InstallSOUND();
		LoadResourceSOUND("resource/sound/effects/", 0);
		SetSoundVolume(256);
	}

	void initJoystick()
	{
		log() << "Joystick ";

		if (XJoystickInit())
		{
			JoystickMode = JOYSTICK_Joystick;
		}
		else
		{
			std::cout << "not ";
		}

		std::cout << "found\n";
	}

	void initRTOs()
	{
		xtCreateRuntimeObjectTable(RTO_MAX_ID);

		rtos::gqObj = new GameQuantRTO;
		rtos::mmObj = new MainMenuRTO;
		rtos::eObj = new EscaveRTO;
		rtos::eoObj = new EscaveOutRTO;
		rtos::fObj = new FirstEscaveRTO;
		rtos::foObj = new FirstEscaveOutRTO;
		rtos::pObj = new PaletteTransformRTO;
		rtos::lObj1 = new LoadingRTO1;
		rtos::lObj2 = new LoadSurfaceRTO;
		rtos::lgoObj = new LoadGameoverRTO;
		rtos::siObj = new ShowImageRTO;
		rtos::saObj = new ShowAviRTO;
	}

	void initIntroRTO()
	{
		if (lang() == RUSSIAN)
		{
			rtos::saObj->SetNumFiles(3);
		}
		else
		{
			rtos::saObj->SetNumFiles(4);
			rtos::saObj->SetName("resource/video/intro/logo0.avi", 0);
			rtos::saObj->SetName("resource/video/intro/logo1.avi", 1);
			rtos::saObj->SetName("resource/video/intro/logo2.avi", 2);
			rtos::saObj->SetName("resource/video/intro/intro.avi", 3);
		}

		rtos::saObj -> SetNext(RTO_MAIN_MENU_ID);
	}

	void registerRTOs()
	{
		xtRegisterRuntimeObject(rtos::gqObj);
		xtRegisterRuntimeObject(rtos::mmObj);
		xtRegisterRuntimeObject(rtos::eObj);
		xtRegisterRuntimeObject(rtos::eoObj);
		xtRegisterRuntimeObject(rtos::fObj);
		xtRegisterRuntimeObject(rtos::foObj);
		xtRegisterRuntimeObject(rtos::pObj);
		xtRegisterRuntimeObject(rtos::lObj1);
		xtRegisterRuntimeObject(rtos::lObj2);
		xtRegisterRuntimeObject(rtos::lgoObj);
		xtRegisterRuntimeObject(rtos::siObj);
		//xtRegisterRuntimeObject(rtos::saObj);
	}

	void initSteamAPI()
	{
#ifdef _STEAM_API_
		if ( SteamAPI_RestartAppIfNecessary( k_uAppIdInvalid ) ) {
			// if Steam is not running or the game wasn't started through Steam, SteamAPI_RestartAppIfNecessary starts the
			// local Steam client and also launches this game again.

			// Once you get a public Steam AppID assigned for this game, you need to replace k_uAppIdInvalid with it and
			// removed steam_appid.txt from the game depot.

			SDL_Quit();
		}


		// Init Steam CEG
		if (!Steamworks_InitCEGLibrary())
		{
			log("Steamworks_InitCEGLibrary() failed");
			log("Fatal Error, Steam must be running to play this game (InitDrmLibrary() failed).");

			SDL_Quit();
		}

		// Initialize SteamAPI, if this fails we bail out since we depend on Steam for lots of stuff.
		// You don't necessarily have to though if you write your code to check whether all the Steam
		// interfaces are NULL before using them and provide alternate paths when they are unavailable.
		//
		// This will also load the in-game steam overlay dll into your process.  That dll is normally
		// injected by steam when it launches games, but by calling this you cause it to always load,
		// even when not launched via steam.
		if (!SteamAPI_Init())
		{
			log("SteamAPI_Init() failed");
			log("Fatal Error, Steam must be running to play this game (SteamAPI_Init() failed).");

			SDL_Quit();
		}

		// set our debug handler
		//SteamClient()->SetWarningMessageHook( &SteamAPIDebugTextHook );

		// Tell Steam where it's overlay should show notification dialogs, this can be top right, top left,
		// bottom right, bottom left. The default position is the bottom left if you don't call this.
		// Generally you should use the default and not call this as users will be most comfortable with
		// the default position.  The API is provided in case the bottom right creates a serious conflict
		// with important UI in your game.
		SteamUtils()->SetOverlayNotificationPosition( k_EPositionTopRight );
#endif
	}

	void genCosSinTable()
	{
		IntSinIntTable = new int[PiX2];
		IntCosIntTable = new int[PiX2];
		for(int i = 0; i < PiX2; i++)
		{
			IntSinIntTable[i] = round(UNIT * sin(intAng2Real(i)));
			IntCosIntTable[i] = round(UNIT * cos(intAng2Real(i)));
		}
	}

	void processMasterBootData()
	{
		setLang(mbd::language);
	}

    void start()
    {
		// Precompute math
		genCosSinTable();
		ilandPrepare();

		// Init random values
        RNDVAL = 83;

		// Init fonts
        readSqFont(sysfont, "road.fnt");
        readSqFont(zchatfont, "zfont.fnt");

		palTr = new PaletteTransform;

		// Create graphic window
		if (XGR_Init(0)) ErrH.Abort(std::string("Window opening failed! SDL Error buffer: ") + SDL_GetError());

		// Set window loading message
		XGR_Fill(0);
		LoadingMessage(1);

		initSound();

		initJoystick();

		initRTOs();

		// TODOf: revive intro showcase rto because why not
		initIntroRTO();

		registerRTOs();

		initSteamAPI();

		setupLocale();

		text_input::init();

		processMasterBootData();

		CompasDict::loadLocalization("locale/compas_locale" + getLocaleExtension() + ".txt");
		AciDict::loadLocalization("locale/aci_locale" + getLocaleExtension() + ".txt");
    }
}

// Application init call from xtcore.
// This function is first, basic initialization of game.
int xtInitApplication(void)
{
	mboot::log("Vangers master boot started...");

    mboot::printStartupConfig();

    mboot::start();

	return RTO_MAIN_MENU_ID;
}

#define ASSERT_MORE_ARG()	\
	if(i == __internal_argc-1)	\
	{	\
		mboot::log("Invalid parameter usage: '" + currentParameterUsage + "' expected");	\
		break;	\
	}


// Analysing startup arguments from __internal_argc and __internal_argv,
// writing total parameters into master_boot_data.
void xtParseAppArguments(void)
{
	mboot::log("Arguments parse started...");

	// Set it at the beginning of big parameters parsing.
	std::string currentParameterUsage;
	std::string cmdKey;

	for(int i = 1; i < __internal_argc; i++)
	{
		cmdKey = __internal_argv[i];

		if(cmdKey[0] != '-')
		{
			mboot::log("Non-key argument: " + cmdKey);
			continue;
		}

		cmdKey.erase(0, 1);

		if (cmdKey == "lang")
		{
			currentParameterUsage = "-lang [ru|en|ge]";

			ASSERT_MORE_ARG();

			i++;
			std::string langValue = __internal_argv[i];

			// Set language name lowercase, to ignore input text case.
			for(char& c : langValue)
			{
				c = tolower(c);
			}

			if(langValue == "ru")
			{
				mbd::language = RUSSIAN;
			}
			else if(langValue == "en")
			{
				mbd::language = ENGLISH;
			}
			else if(langValue == "ge")
			{
				mbd::language = GERMAN;
			}
			else
			{
				mboot::log("Unknown language name: '" + langValue + "'; expected ru / en / ge .");
			}
        }
		else if (cmdKey == "server")
		{
			currentParameterUsage = "-server hostname";

			ASSERT_MORE_ARG();

			i++;
			mbd::isAutoconnect = true;
			mbd::autoconnectHost = __internal_argv[i];

        }
		else if (cmdKey == "port")
		{
			currentParameterUsage = "-port value";

			ASSERT_MORE_ARG();

			i++;
			mbd::autoconnectPort = (unsigned short)strtol(__internal_argv[i], NULL, 0);

        }
		else if (cmdKey == "game")
		{
			currentParameterUsage = "-game [id|new|any]";

			ASSERT_MORE_ARG();

			i++;
			std::string value = __internal_argv[i];
			mbd::isAutoconnectJoinGame = true;

			if (value == "new")
			{
				mbd::autoconnectGameID = AUTOCN_NEW;
			}
			else if (value == "any")
			{
				mbd::autoconnectGameID = AUTOCN_ANY;
			}
			else
			{
				mbd::autoconnectGameID = (int)strtol(__internal_argv[i], NULL, 0);
			}
        }
		else
		{
            mboot::log("Unknown parameter: '" + cmdKey + "'");
        }
	}

}

include_directories(
	"${PROJECT_SOURCE_DIR}/lib/xtool"
	"${PROJECT_SOURCE_DIR}/lib/xgraph"
	"${PROJECT_SOURCE_DIR}/lib/xsound"
)

option(OLD_SOURCE_STORAGE "Use old set(vangers_SRCS) instead of automatic recursive seeker" OFF)

set(vangers_exe_path "vangers")

if(OLD_SOURCE_STORAGE)
	message("[WARNING] Using old source storage is deprecated...")
	SET(
	vangers_SRCS

		3d/3d_math.cpp
		3d/3dgraph.cpp
		3d/3dobject.cpp
		3d/dynamics.cpp
		3d/optimize.cpp

		actint/aci_scr.cpp
		actint/actint.cpp
		actint/actintml.cpp
		actint/ascr_fnc.cpp
		actint/ascript.cpp
		actint/chtree.cpp
		actint/sscript.cpp

		road.cpp
		master_boot.cpp
		master_boot_data.cpp
		game_surface_disp.cpp 
		backg.cpp
		network.cpp
		palette.cpp
		rle.cpp
		xjoystick.cpp
		xsocket.cpp
		zmod_client.cpp
		camera_data.cpp
		sqfont.cpp
		random.cpp
		dbg_console.cpp

		fs/parser.cpp

		userinput/text_input.cpp

		dast/poly3d.cpp

		iscreen/controls.cpp
		iscreen/hfont.cpp
		iscreen/i_chat.cpp
		iscreen/iextern.cpp
		iscreen/ikeys.cpp
		iscreen/imap_fnc.cpp
		iscreen/iml.cpp
		iscreen/iscr_fnc.cpp
		iscreen/iscreen.cpp
		iscreen/iscript.cpp
		iscreen/ivmap.cpp
		iscreen/script.cpp
		iscreen/smooth.cpp

		particle/bmp2scr.cpp
		particle/deform.cpp
		particle/df.cpp
		particle/light.cpp
		particle/particle.cpp
		particle/partmap.cpp
		particle/pmaptype.cpp

		sound/music.cpp
		sound/sound.cpp

		terra/compress.cpp
		terra/huff1.cpp
		terra/land.cpp
		terra/perpslop.cpp
		terra/siderend.cpp #ASM
		terra/slopskip.cpp
		terra/splay.cpp
		terra/vmap.cpp #ASM

		units/effect.cpp
		units/hobj.cpp
		units/items.cpp
		units/mechos.cpp
		units/moveland.cpp
		units/sensor.cpp
		units/track.cpp

		uvs/diagen.cpp
		uvs/screen.cpp
		uvs/univang.cpp

		math/base_math.cpp
		math/int_math.cpp 

		${WINDOWS_RES}
	)
else()
	set(vangers_SRCS)

	foreach(DIR ".")
		file(GLOB_RECURSE DIR_SOURCES "${DIR}/*.cpp")
		list(APPEND vangers_SRCS ${DIR_SOURCES})
	endforeach()
endif()

if (ANDROID)
	ADD_LIBRARY(${vangers_exe_path} STATIC ${vangers_SRCS}
		$<TARGET_OBJECTS:xtool>
		$<TARGET_OBJECTS:xgraph>
		$<TARGET_OBJECTS:xsound>
	)
else()
	ADD_EXECUTABLE(${vangers_exe_path} ${vangers_SRCS})

	IF(WIN32)
		SET(WIN_LIB
			wsock32
			#-mwindows
			#-Wl,-subsystem,windows
		)
	ENDIF(WIN32)

	TARGET_LINK_LIBRARIES(${vangers_exe_path}
		${SDL2_LIBRARY}
		${OGG_LIBRARY}
		${VORBIS_LIBRARY}
		${VORBISFILE_LIBRARY}
		${CLUNK_LIBRARY}
		${SDL2_NET_LIBRARY}
		${FFMPEG_LIBRARIES}
		${ZLIB_LIBRARIES}
		${OPENGL_LIBRARIES}
		${WIN_LIB}
		${STEAM_LIBS}
		xtool
		xgraph
		xsound
	)
endif(ANDROID)

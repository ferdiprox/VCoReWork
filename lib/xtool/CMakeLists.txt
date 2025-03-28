set(xtool_SRCS)

if(OLD_SOURCE_STORAGE)
	SET(xtool_SRCS
		xtcore.cpp
		xrecorder/xrec.cpp
		port.cpp
		xerrhead.cpp
		xbuffer/xbcnvin.cpp
		xbuffer/xbcnvout.cpp
		xbuffer/xbcore.cpp
		xbuffer/xbsearch.cpp
		xmsgbuffer/xmsgbuf.cpp
		xstream/xscnvin.cpp
		xstream/xscnvout.cpp
		xstream/xscore.cpp
		xstream/xsenlv.cpp
		xstream/xsgetlin.cpp
		xstream/xsinput.cpp
		xstream/xsoutput.cpp
		xstream/xsrdwr.cpp
		xstream/xsserv.cpp
		iniparser/dictionary.c
		iniparser/iniparser.c
		lang.cpp
		xclock.cpp
		convert_buffer.cpp
	)
else()	
	foreach(DIR ".")
		file(GLOB_RECURSE DIR_SOURCES "${DIR}/*.cpp") # Search cpp files
		list(APPEND xtool_SRCS ${DIR_SOURCES})

		file(GLOB_RECURSE DIR_SOURCES "${DIR}/*.c") # Search c libs
		list(APPEND xtool_SRCS ${DIR_SOURCES})
	endforeach()
endif()

IF(DXSTREAM_DEBUG)
	ADD_DEFINITIONS(-DXSTREAM_DEBUG)
ENDIF(DXSTREAM_DEBUG)

INCLUDE_DIRECTORIES(BEFORE .)

if (ANDROID)
	ADD_LIBRARY(xtool OBJECT ${xtool_SRCS})
else()
	ADD_LIBRARY(xtool STATIC ${xtool_SRCS})
	TARGET_LINK_LIBRARIES(xtool ${WIN_DBG})
endif()

TARGET_COMPILE_DEFINITIONS (xtool PUBLIC "-DGIT_COMMIT_HASH=\"${GIT_COMMIT_HASH}\"" "-DGIT_BRANCH=\"${GIT_BRANCH}\"" "-DGITHUB_COMMIT_HASH=\"$ENV{GITHUB_SHA}\"" "-DGITHUB_BRANCH=\"$ENV{GITHUB_REF_NAME}\"")

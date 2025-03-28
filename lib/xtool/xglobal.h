#pragma once

// (WIP) changing convert_buffer usage to std tools like std::to_string
//#define STD_PORT

#ifdef _WIN32
#include <windows.h>
#include <process.h>
#endif

#include <SDL.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <memory>
#include <iostream>

#ifdef STD_PORT

#define _BUFFER_PORT_IN() \
	std::string str = std::to_string(var);	\
	write(str.data(), str.size, 0);	\
	return *this;

#define _STREAM_PORT_IN() \
    std::string str = std::to_string(var);	\
    write(str.data(), str.size);	\
    return *this;

#define _OPERATOR_PORT_OUT() \
    *handler >> var; \
    return *this;

#else

#include "convert_buffer.h"

#endif

#ifdef __WORDSIZE
#else
#if (defined __LP64__)
#define __WORDSIZE = 64
#else
#define __WORDSIZE = 32
#endif
#endif

#ifdef WIN32
#define snprintf sprintf_s
#endif

#include "port.h"
#include "xtcore.h"
//#include "xconsole.h"
//#include "xkey.h"
#include "xerrhandler.h"
#include "xbuffer.h"
#include "xstream.h"
#include "xrec.h"
#include "xcpuid.h"
#include "xmsgbuf.h"
#include "xt_list.h"
#ifdef __cplusplus
extern "C"
{
#endif
#include "iniparser/iniparser.h"
#ifdef __cplusplus
}
#endif


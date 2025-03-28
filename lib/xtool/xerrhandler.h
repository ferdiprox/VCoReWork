#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#ifndef NULL
#define NULL	0L
#endif

#define XERR_USER		0x0001

struct XErrorHandler
{
	const char* prefix;
	const char* postfix;
	std::string log_name;

	std::fstream log_file;

	XErrorHandler();
	~XErrorHandler();

	void Abort(const std::string& message, int code = XERR_USER, int val = -1, std::string subj = "");
	void Log(const char* message);
	void Exit(void);
	void RTC(const char *file,unsigned int line, const char *expr);
};

extern XErrorHandler ErrH;

// Use this macro for after any operation for errors diagnostic
#define XAssert(expr) ErrH.RTC(__FILE__,__LINE__,expr)

void set_signal_handler();

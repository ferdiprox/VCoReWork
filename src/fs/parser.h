#pragma once

#include <string>

#include "xbuffer.h"
#include "xerrhandler.h"

struct Parser : XBuffer
{
	Parser(const std::string& filename, std::string deleteChars = "");

	void searchName(const std::string& name);
	int is_next_name(const char* name);
	int get_int(){ int t; *this >= t; return t; }
	double get_double(){ double t; *this >= t; return t; }
	double quick_get_double();
	char* get_name();
	char* get_string();
};

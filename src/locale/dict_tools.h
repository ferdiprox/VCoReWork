#pragma once

#include "../fs/parser.h"

#define GET_LOCAL_STRING(targetString) \
    inputConfig.searchName(#targetString":");\
    readBuffer = inputConfig.get_name();  \
    targetString = new char[readBuffer.size() + 1]; /* + 1 for null byte at the end */ \
    memcpy(targetString, readBuffer.data(), readBuffer.size()); \
	targetString[readBuffer.size()] = 0; 

#define DICT_LOAD_HEADER() \
    std::string readBuffer; \
    Parser inputConfig(filename);

#pragma once

#include <string>

enum Language {
    ENGLISH = 0,
    RUSSIAN = 1,
    GERMAN = 2,

    LANG_NUM,
};

Language lang();
void setLang(Language lang);

const std::string& getLocaleExtension();
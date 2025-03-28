#include "lang.h"

namespace 
{
    // Used to get a localization dependent file name.
    std::string localeExtensions[LANG_NUM]
    {
        ".en", // English
        ".ru", // Russian
        ".ge", // German
    };
    
    Language _lang = ENGLISH;
}

Language lang() {
    return _lang;
}

void setLang(Language lang) {
    _lang = lang;
}

const std::string& getLocaleExtension()
{
    return localeExtensions[_lang];
}
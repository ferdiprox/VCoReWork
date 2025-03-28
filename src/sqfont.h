#pragma once

#include "xstream.h"

static constexpr int SQ_SYSCOLOR = 256 - 8;
static constexpr int SYSCOLOR = 159;

struct sqFont 
{
	short num;
	unsigned char first,last;
	short sx,sy;
	char** data;

	void init(XStream& sourceFile);
	void draw(int x,int y,unsigned char* s,int fore = SQ_SYSCOLOR,int back = SQ_SYSCOLOR + 5);
    void draw(int x, int y, const std::string& string, int fore = SYSCOLOR, int back = -1) { draw(x,y, (unsigned char*)string.data(), fore, back); }
	void drawtext(int x,int y,char* s,int fore = SQ_SYSCOLOR,int back = SQ_SYSCOLOR + 5);
	void drawchar(int x,int y,int ch,int fore = SQ_SYSCOLOR,int back = SQ_SYSCOLOR + 5);
};

// Main sqFonts in Vangers.
extern sqFont sysfont, zchatfont;
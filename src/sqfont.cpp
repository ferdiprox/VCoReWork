#include "sqfont.h"

#include "xgraph.h"

void sqFont::init(XStream& sourceFile)
{
	sourceFile > num;
	sourceFile > first;
	sourceFile > last;
	sourceFile > sx;
	sourceFile > sy;

	data = new char*[num];

	for(int i = 0; i < num; i++)
	{
		data[i] = new char[sy];

        sourceFile.read(data[i], sy);
	}
}

void sqFont::draw(int x,int y,unsigned char* s,int fore,int back)
{
	while(*s)
	{
		drawchar(x,y,*s,fore,back);
		s++;
		x += sx;	
	}
}

void sqFont::drawtext(int x,int y,char* s,int fore,int back)
{
	char c;
	int i = x;
	while((c = *s) != 0)
    {
		switch(c)
		{
        default:
            drawchar(i,y,*s,fore,back);
            i += sx;
            break;
        case '\n':
            y += sy;
            i = x;
            break;
        case '\t':
            i += 4*sx;
            break;
		}

		s++;
	}
}


void sqFont::drawchar(int x,int y,int ch,int fore,int back)
{
    if(x < 0 || y < 0 || x + sx >= XGR_MAXX || y + sy >= XGR_MAXY) return;

	char *charLines = data[ch];

	int drawX, drawY, m;

	for(drawY = 0; drawY < sy; drawY++)
	{
        char wideData = charLines[drawY];

		for(drawX = 0,m = 1 << sx; drawX < sx; drawX++,m >>= 1)
		{

            if(wideData & m) 
			{
				XGR_SetPixel(x + drawX, y + drawY,fore);
				continue;
			}
			
			if(back != -1) 
			{
				XGR_SetPixel(x + drawX, y + drawY,back);
			}
		}
	}
}

sqFont sysfont, zchatfont;

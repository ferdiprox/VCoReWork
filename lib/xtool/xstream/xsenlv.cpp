#include "xglobal.h"
#include <iostream>
#include <fstream>

std::fstream *open_file(const std::string& name, unsigned f)
{
	std::ios::openmode mode;
	mode = std::ios::binary;
	if (f & XS_IN)
		mode |= std::ios::in;
	if (f & XS_OUT)
		mode |= std::ios::out;
	if (f & XS_APPEND)
		mode |= std::ios::app;

	return new std::fstream(name, mode);
}

bool XStream::open(const std::string& name, unsigned openingFlags)
{
	file_name = name;

	std::fstream *file = open_file(name, openingFlags);
	handler = file;

	if (file->is_open()) {
		fname = name;
		pos = file->tellg();
		eofFlag = 0;
		return 1;
	} 

	if (ErrHUsed)
	{
		std::string errorMessage;

		errorMessage += std::string("File ") + ((openingFlags & XS_IN) ? "opening" : "reading") + " error: ";
		errorMessage += "No such file or directory; ";
		errorMessage += "File name: " + name;
		
		ErrH.Abort(errorMessage);
	} 
	return 0;
}

bool XStream::open(XStream* owner,long s,long ext_sz)
{
	/* Full stream debug
	std::fstream debug("openfile.txt", std::ios::out|std::ios::app);
	if (debug.is_open())
		debug<<"OPEN_XSTREAM "<<owner -> fname<<std::endl;
	debug.close();
	*/
	fname = owner -> fname;
	handler = owner -> handler;
	pos = 0;
	owner -> seek(s,XS_BEG);
	eofFlag = owner -> eof();
	extSize = ext_sz;
	extPos = s;
	return 1;
}

void XStream::close(void)
{	
	if(handler == NULL)
		return;
	
	if (handler->is_open())
		handler->close();

	delete handler;
	handler = NULL;

	//fname = "";
	pos = 0L;
	eofFlag = 1;
	extSize = -1;
	extPos = 0;
}


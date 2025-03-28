#include "xglobal.h"

#ifndef _WIN32
#include <stdlib.h>
#endif

#ifndef STD_PORT

XStream& XStream::operator<= (char var)
{
	char* s = port_itoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (unsigned char var)
{
	char* s = port_itoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (short var)
{
	char* s = port_itoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (unsigned short var)
{
	char* s = port_ltoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (int var)
{
	char* s = port_itoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (unsigned var)
{
	char* s = port_ultoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (long var)
{
	char* s = port_ltoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (unsigned long var)
{
	char* s = port_ultoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (float var)
{
	int len = snprintf(_ConvertBuffer, _CONV_BUFFER_LEN, "%.*g", digits, var);
	write(_ConvertBuffer,len);
	return *this;
}

XStream& XStream::operator<= (double var)
{
	int len = snprintf(_ConvertBuffer, _CONV_BUFFER_LEN, "%.*g", digits, var);
	write(_ConvertBuffer,len);
	return *this;
}

XStream& XStream::operator<= (long double var)
{
	int len = snprintf(_ConvertBuffer, _CONV_BUFFER_LEN, "%.*Lg", digits, var);
	write(_ConvertBuffer,len);
	return *this;
}

#else // STD PORT IMPLEMENTATION

XStream& XStream::operator<= (char var)
{
	_STREAM_PORT_IN();
}

XStream& XStream::operator<= (unsigned char var)
{
	_STREAM_PORT_IN();
}

XStream& XStream::operator<= (short var)
{
	_STREAM_PORT_IN();
}

XStream& XStream::operator<= (unsigned short var)
{
	_STREAM_PORT_IN();
}

XStream& XStream::operator<= (int var)
{
	_STREAM_PORT_IN();
}

XStream& XStream::operator<= (unsigned var)
{
	_STREAM_PORT_IN();
}

XStream& XStream::operator<= (long var)
{
	_STREAM_PORT_IN();
}

XStream& XStream::operator<= (unsigned long var)
{
	_STREAM_PORT_IN();
}

XStream& XStream::operator<= (float var)
{
	_STREAM_PORT_IN();
}

XStream& XStream::operator<= (double var)
{
	_STREAM_PORT_IN();
}

XStream& XStream::operator<= (long double var)
{
	_STREAM_PORT_IN();
}

#endif
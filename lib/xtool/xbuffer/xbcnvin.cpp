#include "xglobal.h"

#ifndef STD_PORT

XBuffer& XBuffer::operator<= (char var)
{
	char* s = port_itoa(var,_ConvertBuffer,radix);
	write(s,strlen(s),0);
	return *this;
}

XBuffer& XBuffer::operator<= (unsigned char var)
{
	char* s = port_itoa(var,_ConvertBuffer,radix);
	write(s,strlen(s),0);
	return *this;
}

XBuffer& XBuffer::operator<= (short var)
{
	char* s = port_itoa(var,_ConvertBuffer,radix);
	write(s,strlen(s),0);
	return *this;
}

XBuffer& XBuffer::operator<= (unsigned short var)
{
	char* s = port_ltoa(var,_ConvertBuffer,radix);
	write(s,strlen(s),0);
	return *this;
}

XBuffer& XBuffer::operator<= (int var)
{
	char* s = port_itoa(var,_ConvertBuffer,radix);
	write(s,strlen(s),0);
	return *this;
}

XBuffer& XBuffer::operator<= (unsigned var)
{
	char* s = port_ultoa(var,_ConvertBuffer,radix);
	write(s,strlen(s),0);
	return *this;
}

XBuffer& XBuffer::operator<= (long var)
{
	char* s = port_ltoa(var,_ConvertBuffer,radix);
	write(s,strlen(s),0);
	return *this;
}

XBuffer& XBuffer::operator<= (long long int var)
{
	char* s = port_ltoa(var,_ConvertBuffer,radix);
	write(s,strlen(s),0);
	return *this;
}

XBuffer& XBuffer::operator<= (unsigned long var)
{
	char* s = port_ultoa(var,_ConvertBuffer,radix);
	write(s,strlen(s),0);
	return *this;
}

XBuffer& XBuffer::operator<= (float var)
{
	int len = snprintf(_ConvertBuffer, _CONV_BUFFER_LEN, "%.*g", digits, var);
	write(_ConvertBuffer,len,0);
	return *this;
}

XBuffer& XBuffer::operator<= (double var)
{
	int len = snprintf(_ConvertBuffer, _CONV_BUFFER_LEN, "%.*g", digits, var);
	write(_ConvertBuffer,len,0);
	return *this;
}

XBuffer& XBuffer::operator<= (long double var)
{
	int len = snprintf(_ConvertBuffer, _CONV_BUFFER_LEN, "%.*Lg", digits, var);
	write(_ConvertBuffer,len,0);
	return *this;
}

#else // STD PORT IMPLEMENTATION

XBuffer& XBuffer::operator<= (char var)
{
	_BUFFER_PORT_IN();
}

XBuffer& XBuffer::operator<= (unsigned char var)
{
	_BUFFER_PORT_IN();
}

XBuffer& XBuffer::operator<= (short var)
{
	_BUFFER_PORT_IN();
}

XBuffer& XBuffer::operator<= (unsigned short var)
{
	_BUFFER_PORT_IN();
}

XBuffer& XBuffer::operator<= (int var)
{
	_BUFFER_PORT_IN();
}

XBuffer& XBuffer::operator<= (unsigned var)
{
	_BUFFER_PORT_IN();
}

XBuffer& XBuffer::operator<= (long var)
{
	_BUFFER_PORT_IN();
}

XBuffer& XBuffer::operator<= (long long int var)
{
	_BUFFER_PORT_IN();
}

XBuffer& XBuffer::operator<= (unsigned long var)
{
	_BUFFER_PORT_IN();
}

XBuffer& XBuffer::operator<= (float var)
{
	_BUFFER_PORT_IN();
}

XBuffer& XBuffer::operator<= (double var)
{
	_BUFFER_PORT_IN();
}

XBuffer& XBuffer::operator<= (long double var)
{
	_BUFFER_PORT_IN();
}

#endif

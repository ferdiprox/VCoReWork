#include "xglobal.h"

#ifndef STD_PORT

XStream& XStream::operator>= (char& var)
{
	int ret = read(_ConvertBuffer,4);
	if(!ret) return *this;
	char* p = _ConvertBuffer;
	p[ret] = ' ';
	var = (char)strtol(p,&p,0);
	seek(p - _ConvertBuffer + 1 - ret,XS_CUR);
	return *this;
}

XStream& XStream::operator>= (unsigned char& var)
{
	int ret = read(_ConvertBuffer,4);
	if(!ret) return *this;
	char* p = _ConvertBuffer;
	p[ret] = ' ';
	var = (unsigned char)strtoul(p,&p,0);
	seek(p - _ConvertBuffer + 1 - ret,XS_CUR);
	return *this;
}

XStream& XStream::operator>= (short& var)
{
	int ret = read(_ConvertBuffer,6);
	if(!ret) return *this;
	char* p = _ConvertBuffer;
	p[ret] = ' ';
	var = (short)strtol(p,&p,0);
	seek(p - _ConvertBuffer + 1 - ret,XS_CUR);
	return *this;
}

XStream& XStream::operator>= (unsigned short& var)
{
	int ret = read(_ConvertBuffer,6);
	if(!ret) return *this;
	char* p = _ConvertBuffer;
	p[ret] = ' ';
	var = (unsigned short)strtoul(p,&p,0);
	seek(p - _ConvertBuffer + 1 - ret,XS_CUR);
	return *this;
}

XStream& XStream::operator>= (int& var)
{
	int ret = read(_ConvertBuffer,16);
	if(!ret) return *this;
	char* p = _ConvertBuffer;
	p[ret] = ' ';
	var = strtol(p,&p,0);
	//std::cout<<"seek - p:"<<(long long)p<<" _ConvertBuffer:"<<(long)_ConvertBuffer<<" ret:"<<var<<" result:"<<p - _ConvertBuffer + 1 - ret<<std::endl;
	seek(p - _ConvertBuffer + 1 - ret,XS_CUR);
	//std::cout<<"Pos:"<<ppos<<std::endl;
	return *this;
}

XStream& XStream::operator>= (unsigned& var)
{
	int ret = read(_ConvertBuffer,16);
	if(!ret) return *this;
	char* p = _ConvertBuffer;
	p[ret] = ' ';
	var = strtoul(p,&p,0);
	seek(p - _ConvertBuffer + 1 - ret,XS_CUR);
	return *this;
}

XStream& XStream::operator>= (long& var)
{
	int ret = read(_ConvertBuffer,16);
	if(!ret) return *this;
	char* p = _ConvertBuffer;
	p[ret] = ' ';
	var = strtol(p,&p,0);
	seek(p - _ConvertBuffer + 1 - ret,XS_CUR);
	return *this;
}

XStream& XStream::operator>= (unsigned long& var)
{
	int ret = read(_ConvertBuffer,16);
	if(!ret) return *this;
	char* p = _ConvertBuffer;
	p[ret] = ' ';
	var = strtoul(p,&p,0);
	seek(p - _ConvertBuffer + 1 - ret,XS_CUR);
	return *this;
}

XStream& XStream::operator>= (double& var)
{
	int ret = read(_ConvertBuffer,_CONV_BUFFER_LEN);
	if(!ret) return *this;
	char* p = _ConvertBuffer;
	p[ret] = ' ';
	var = strtod(p,&p);
	seek(p - _ConvertBuffer + 1 - ret,XS_CUR);
	return *this;
}

XStream& XStream::operator>= (float& var)
{
	int ret = read(_ConvertBuffer,_CONV_BUFFER_LEN);
	if(!ret) return *this;
	char* p = _ConvertBuffer;
	p[ret] = ' ';
	var = (float)strtod(p,&p);
	seek(p - _ConvertBuffer + 1 - ret,XS_CUR);
	return *this;
}

XStream& XStream::operator>= (long double& var)
{
	int ret = read(_ConvertBuffer,_CONV_BUFFER_LEN);
	if(!ret) return *this;
	char* p = _ConvertBuffer;
	p[ret] = ' ';
	var = strtod(p,&p);
	seek(p - _ConvertBuffer + 1 - ret,XS_CUR);
	return *this;
}

#else // STD PORT IMPLEMENTATION 

XStream& XStream::operator>= (char& var)
{
	_OPERATOR_PORT_OUT();
}

XStream& XStream::operator>= (unsigned char& var)
{
	_OPERATOR_PORT_OUT();
}

XStream& XStream::operator>= (short& var)
{
	_OPERATOR_PORT_OUT();
}

XStream& XStream::operator>= (unsigned short& var)
{
	_OPERATOR_PORT_OUT();
}

XStream& XStream::operator>= (int& var)
{
	_OPERATOR_PORT_OUT();
}

XStream& XStream::operator>= (unsigned& var)
{
	_OPERATOR_PORT_OUT();
}

XStream& XStream::operator>= (long& var)
{
	_OPERATOR_PORT_OUT();
}

XStream& XStream::operator>= (unsigned long& var)
{
	_OPERATOR_PORT_OUT();
}

XStream& XStream::operator>= (double& var)
{
	_OPERATOR_PORT_OUT();
}

XStream& XStream::operator>= (float& var)
{
	_OPERATOR_PORT_OUT();
}

XStream& XStream::operator>= (long double& var)
{
	_OPERATOR_PORT_OUT();
}

#endif
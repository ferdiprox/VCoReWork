#include "parser.h"

#include "xstream.h"

Parser::Parser(const std::string& filename, std::string deleteChars) : XBuffer(0,0)
{
	XStream inputFile(filename, XS_IN);

	int fileSize = inputFile.size();

	alloc(fileSize + 1); // +1 byte for null byte at the end
	inputFile.read(buf, fileSize);
	buf[fileSize] = 0;

	if(deleteChars.empty())
    {
		return;
	}

	for(int i = 0; i < fileSize; i++)
	{
		if(deleteChars.find(buf[i]) != std::string::npos)
		{
			buf[i] = ' ';
		}
	}
}

void Parser::searchName(const std::string& name)
{
	if(!search(name))
	{
		ErrH.Abort("Parser: Name not found", XERR_USER, 0, name);
	}
	set(tell() + name.size());
}

int Parser::is_next_name(const char* name)
{
	unsigned int off = tell();
	int log = 0;
	if(search(name)){
		unsigned int off1 = tell() - 1;
		for(unsigned int i = off;i < off1;i++)
			if(!iswspace(buf[i]))
				goto ret;
		log = 1;
		}
ret:
	set(off);
	return log;
}

char* Parser::get_name()
{
	char c;
	unsigned int i,off;
	do{
		if(tell() >= size)
			return 0;
		*this > c;
		}while(iswspace(c));

	off = tell();
	if(c == '"')
		for(i = ++off;i < size;i++){
			if((c = buf[i]) == '"' || (iswspace(c) && c != ' ' && c != '\t')){
				buf[i] = 0;
				break;
				}
			}
	else
		for(i = off;i < size;i++){
			if(iswspace(buf[i])){
				buf[i] = 0;
				break;
				}
		}
	set(++i < size ? i : size);
	return buf + off - 1;
}

char* Parser::get_string()
{
	int i;
	char c;
	do{
		if(tell() >= size)
			return 0;
		*this > c;
		}while(iswspace(c));

	int off = tell();
	for(i = off;i < (int)size;i++){
		if(iswspace(buf[i]) && buf[i] != ' '){
			buf[i] = 0;
			break;
			}
		}
	if(++i < (int)size)
		set(i);
	return buf + off - 1;
}

double Parser::quick_get_double()
{
	 char c,sign = 0;
	 do
		*this > c;
		while(iswspace(c));

	if(c == '-'){
		sign = 1;
		*this > c;
		}
	double val = 0;
	while(iswdigit(c)){
		val  *= 10;
		val += (double)(c - '0');
		*this > c;
		}
	if(c == '.'){
		*this > c;
		double dig = 1;
		while(iswdigit(c)){
			dig  /= 10;
			val += ((double)(c - '0'))*dig;
			*this > c;
			}
		}
	return sign ? -val : val;
}

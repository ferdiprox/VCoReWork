#pragma once

#include <string>

#ifndef NULL
#define NULL	0L
#endif

static constexpr unsigned int XB_DEFSIZE = 256;

#define XB_BEG		0
#define XB_CUR		1
#define XB_END		2

enum XBUFFER_SEARCH_MODE
{
	XB_FORWARD,
	XB_BACKWARD,
	XB_GLOBAL,
};

static constexpr int XB_DEFRADIX = 10;
static constexpr int XB_DEFDIGITS = 8;

struct XBuffer
{
	char* buf;
	unsigned int size;
	unsigned int offset;
	int radix;
	int digits;
	int MakeFree;
	int automatic_realloc;

	XBuffer(unsigned int sz = XB_DEFSIZE)
	{
		alloc(sz);
		radix=XB_DEFRADIX;
		digits=XB_DEFDIGITS;
	}

	XBuffer(void* p,int sz);
	~XBuffer(void){ free(); }

	void SetRadix(int r) { radix = r; }
	void SetDigits(int d) { digits = d; }

	void alloc(unsigned int sz);
	void free(void);
	void fill(char fc = '\0');
	void set(int off,int mode = XB_BEG);
	void init(void){ offset = 0; *buf = 0; }
	bool isEndReached() const { return (offset > size); }

	bool search(const std::string& what, unsigned char mode = XB_FORWARD, bool considerCase = true);
	bool subcompare(const std::string& string, unsigned int at, bool considerCase = true);

	inline unsigned int tell(void) const { return offset; }

	unsigned int read(void* s, unsigned int len);
	unsigned int write(const void* s, unsigned int len, int bin_flag = 1);
	void handleOutOfSize();

	XBuffer& operator< (const char* var);
	XBuffer& operator< (char var) { return write(var); }
	XBuffer& operator< (unsigned char var) { return write(var); }
	XBuffer& operator< (short var) { return write(var); }
	XBuffer& operator< (unsigned short var) { return write(var); }
	XBuffer& operator< (int var ) { return write(var); }
	XBuffer& operator< (unsigned int var) { return write(var); }
	XBuffer& operator< (long var) { return write(var); }
	XBuffer& operator< (unsigned long var) { return write(var); }
	XBuffer& operator< (float var) { return write(var); }
	XBuffer& operator< (double var) { return write(var); }
	XBuffer& operator< (long double var) { return write(var); }

	XBuffer& operator> (char* var);
	XBuffer& operator> (char& var) { return read(var); }
	XBuffer& operator> (unsigned char& var) { return read(var); }
	XBuffer& operator> (short& var) { return read(var); }
	XBuffer& operator> (unsigned short& var) { return read(var); }
	XBuffer& operator> (int& var) { return read(var); }
	XBuffer& operator> (unsigned int& var) { return read(var); }
	XBuffer& operator> (long& var) { return read(var); }
	XBuffer& operator> (unsigned long& var) { return read(var); }
	XBuffer& operator> (float& var) { return read(var); }
	XBuffer& operator> (double& var) { return read(var); }
	XBuffer& operator> (long double& var) { return read(var); }

	XBuffer& operator<= (char);
	XBuffer& operator<= (unsigned char);
	XBuffer& operator<= (short);
	XBuffer& operator<= (unsigned short);
	XBuffer& operator<= (int);
	XBuffer& operator<= (unsigned int);
	XBuffer& operator<= (long);
	XBuffer& operator<= (unsigned long);
	XBuffer& operator<= (long long int);
	XBuffer& operator<= (float);
	XBuffer& operator<= (double);
	XBuffer& operator<= (long double);

	XBuffer& operator>= (char&);
	XBuffer& operator>= (unsigned char&);
	XBuffer& operator>= (short&);
	XBuffer& operator>= (unsigned short&);
	XBuffer& operator>= (int&);
	XBuffer& operator>= (unsigned int&);
	XBuffer& operator>= (long&);
	XBuffer& operator>= (unsigned long&);
	XBuffer& operator>= (float&);
	XBuffer& operator>= (double&);
	XBuffer& operator>= (long double&);

	char* GetBuf() { return buf; }
	char* operator ()(int offs){ return buf + offs; }
	char* operator ()(unsigned int offs){ return buf + offs; }
	XBuffer& operator++(){ offset++; return *this; }
	XBuffer& operator--(){ offset--; return *this; }
	XBuffer& operator+= (int var){ offset+=var; return *this; }
	XBuffer& operator-= (int var){ offset-=var; return *this; }
	XBuffer& operator+= (unsigned int var){ offset += var; return *this; }
	XBuffer& operator-= (unsigned int var){ offset -= var; return *this; }

	char& operator[](int ind){ return buf[ind]; }
	char& operator()(){ return buf[offset]; }

	template<class T> XBuffer& write(const T& var)
	{
		while(offset + sizeof(T) >= size)
		{
			handleOutOfSize();
		}

        (T&)buf[offset] = var;
        offset += sizeof(T);
        return *this;
	}

	template<class T> XBuffer& read(T& var)
	{
		var = (T&)buf[offset];
		offset += sizeof(T);
		return *this;
	}
};

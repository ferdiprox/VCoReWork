#include "rle.h"

#include <cstring>

int RLE_ANALISE(unsigned char* _buf, int len, unsigned char*& out){
	int i = 0;
	int pack_len = 0;
	unsigned char c_len = 0;
	unsigned char* buf = _buf;
	unsigned char *_out = new unsigned char[len*2];
	unsigned char* p = _out;
	unsigned char _ch = *buf++;

	while( i < len) {
		while( (i < len) && (_ch == *buf) &&  (c_len < 127)) {
			c_len++;
			buf++;
			i++;
		}

		if (c_len){
			*p++ = c_len;
			*p++ = _ch;

			_ch = *buf++;

			pack_len += 2;
			c_len = 0;
			i++;
		}

		while( (i < len) && (_ch != *buf) && (c_len < 127)) {
			c_len++;
			_ch = *buf++;
			i++;
		}

		if (c_len){
			*p++ = 128 + (c_len-1);
			memcpy( p, buf - c_len - 1, c_len);
			p += c_len;
			pack_len += c_len + 1;
			c_len = 0;
		}
	}//  end while

	/*G_len += pack_len;
	G_all_len += len;

	fRLE <= G_len < "  ==>  " <= G_all_len < "\n";
	fRLE <= pack_len < "  ==>  " <= len < "\n";
	if ( where ) fRLE < "\n";*/

	out = new unsigned char[pack_len];
	memcpy( out, _out, pack_len);
	/*RLE_UNCODE( _out, len,  out);

	for( i = 0; i < len; i++)
		if (_out[i] != _buf[i] )
			ErrH.Abort("'Bad restore");*/

	delete[] _out;
	
	return pack_len;
}			

void RLE_UNCODE(unsigned char* _buf, int len, unsigned char* out){
	unsigned char* buf = _buf;
	unsigned char c_len = 0;
	unsigned char* p = out;

	int i = 0;
	while( i < len){
		c_len = *p++;

		if (c_len & 128){
			c_len ^= 128;
			memcpy(	buf, p, ++c_len);

			i += c_len;
			p += c_len;
			buf += c_len;
		} else {
			memset(buf, *p++, ++c_len);
			i += c_len;
			buf += c_len;
		}//  end if
	}//  end while
}

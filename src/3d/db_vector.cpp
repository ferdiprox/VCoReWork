#include "db_vector.h"

#include <iostream>

#include "int_vector.h"
#include "db_matrix.h"

/******************************************************************************
			 DB_VECTOR Definition
******************************************************************************/

void DBV::print() {
	std::cout<<x<<" \t"<<y<<" \t"<<z<<"\n";
}

XStream& operator<= (XStream& s,const DBV& v)
{
	s <= v.x < " \t" <= v.y < " \t" <= v.z < "\n";
	return s;
}
XStream& operator>= (XStream& s,DBV& v)
{
	s >= v.x >= v.y >= v.z;
	return s;
}
XStream& operator< (XStream& s,DBV& v)
{
	s.write(&v,sizeof(DBV));
	return s;
}
XStream& operator> (XStream& s,DBV& v)
{
	s.read(&v,sizeof(DBV));
	return s;
}

XBuffer& operator<= (XBuffer& b,const DBV& v)
{
	b <= v.x < " \t" <= v.y < " \t" <= v.z < "\n";
	return b;
}
XBuffer& operator>= (XBuffer& b,DBV& v)
{
	b >= v.x >= v.y >= v.z;
	return b;
}
XBuffer& operator< (XBuffer& b,const DBV& v)
{
	b < v.x < v.y < v.z;
	return b;
}
XBuffer& operator> (XBuffer& b,DBV& v)
{
	b > v.x > v.y > v.z;
	return b;
}

	/* Special 3D functions */
double DBV::angle(const DBV& w) const
{
	double a = vabs()*w.vabs();
	double b = (*this)*w;
	double c = b/a;
	if(fabs(c) >= 1) {
		if(b >= 0) {
			return 0;
		} else {
			return M_PI;
        }
    }
	return acos(c);
}
double DBV::angle(const DBV& v1,const DBV& v2) const
{
	 DBV v = v1 % v2;
	 double val = v1.angle(v2);
	 if((*this)*v < -1e-10)
		val = 2*M_PI - val;
	return val;
}
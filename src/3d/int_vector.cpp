#include "int_vector.h"

#include <iostream>

#include "db_vector.h"
#include "db_matrix.h"

/******************************************************************************
		    VECTOR Definition
******************************************************************************/

void Vector::print() {
	std::cout<<x<<" \t"<<y<<" \t"<<z<<"\n";
}

XStream& operator<= (XStream& s,const Vector& v)
{
	s <= v.x < " \t" <= v.y < " \t" <= v.z < "\n";
	return s;
}
XStream& operator>= (XStream& s,Vector& v)
{
	s >= v.x >= v.y >= v.z;
	return s;
}
XStream& operator< (XStream& s,Vector& v)
{
	s.write(&v,sizeof(Vector));
	return s;
}
XStream& operator> (XStream& s,Vector& v)
{
	s.read(&v,sizeof(Vector));
	return s;
}

XBuffer& operator<= (XBuffer& b,const Vector& v)
{
	b <= v.x < " \t" <= v.y < " \t" <= v.z < "\n";
	return b;
}
XBuffer& operator>= (XBuffer& b,Vector& v)
{
	b >= v.x >= v.y >= v.z;
	return b;
}
XBuffer& operator< (XBuffer& b,const Vector& v)
{
	b < v.x < v.y < v.z;
	return b;
}
XBuffer& operator> (XBuffer& b,Vector& v)
{
	b > v.x > v.y > v.z;
	return b;
}

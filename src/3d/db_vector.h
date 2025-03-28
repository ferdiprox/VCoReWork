#pragma once

#include "xstream.h"
#include "xbuffer.h"

#include "../math/int_math.h"

struct Vector;
struct DBM;

/******************************************************************************
			   DOUBLE VECTOR
******************************************************************************/
struct DBV 
{
	double x;
	double y;
	double z;

		DBV();
		DBV(double u,double v,double t);
		DBV(const DBV& v);
		DBV(const Vector& v);

	double operator [](unsigned int i) const { return ((double*)this)[i % 3]; }					   
	double& operator [](unsigned int i) { return ((double*)this)[i % 3]; }					      

	DBV& operator = (const Vector& v);

	DBV operator- ();

		/* Logical operations */
	int operator () () const;
	int operator ! () const;
	int operator == (const DBV& v) const;
	int operator != (const DBV& v) const;

		/* Norm operations */
	double abs2() const;
	double vabs() const;
	double sum() const;
	DBV& norm(double r);
	DBV get_norm(double r) const;

		/* DBV - DBV operations */
	DBV& operator+= (const DBV& v);
	DBV& operator-= (const DBV& v);
	DBV& operator%= (const DBV& v);       //      Cross product

	DBV operator+ (const DBV& v) const;
	DBV operator- (const DBV& v) const;
	DBV operator% (const DBV& v) const;   //      Cross product
	DBV operator/ (const DBV& v) const;   //      Component-wise division

	DBV& operator*= (const DBV& v);       //      Component-wise multiplication
	DBV& operator/= (const DBV& v);       //      Component-wise division
	double operator* (const DBV& v) const;//      Dot product

		/* DBV - DBM operations */
	DBV& operator*= (const DBM& m);
	DBV operator* (const DBM& m) const;
	friend DBV operator* (const DBM& v, const DBV& m);

		/* Scalar operations */
	DBV& operator*= (double w);
	DBV& operator/= (double w);
	DBV operator* (double w) const;
	DBV operator/ (double w) const;
	friend DBV operator* (double w,const DBV& v);

		/* Shifting operations */
	DBV& operator>>= (int n);
	DBV& operator<<= (int n);

	DBV operator>> (int n) const;
	DBV operator<< (int n) const;

		/* I/O operations */
	void print();
	friend XStream& operator<= (XStream& s,const DBV& v);
	friend XStream& operator>= (XStream& s,DBV& v);
	friend XStream& operator< (XStream& s,DBV& v);
	friend XStream& operator> (XStream& s,DBV& v);

	friend XBuffer& operator<= (XBuffer& b,const DBV& v);
	friend XBuffer& operator>= (XBuffer& b,DBV& v);
	friend XBuffer& operator< (XBuffer& b,const DBV& v);
	friend XBuffer& operator> (XBuffer& b,DBV& v);

		/* Descart - spherical functions */
	inline double psi() const
	{
		return atan2(y,x);
	}
	inline double tetta() const
	{
		double a = vabs();
		if(fabs(z) >= a - DBL_EPS) {
			if(z >= 0) {
				return 0;
			} else {
				return M_PI;
			}
		}
		return acos(z/a);
	}
	inline DBV& spherical(double psi,double tetta,double radius)
	{
		x = radius*sin(tetta);
		y = x*sin(psi);
		x = x*cos(psi);
		z = radius*cos(tetta);
		return *this;
	}

		/* Convertions to & from angular coord systems*/
	DBV& spherical2descart();
	DBV& descart2spherical();
	DBV descart() const;		   // Get descart from spherical
	DBV spherical() const;		   // Get spherical from descart

		/* Special functions */
	double angle(const DBV& v) const;
	double angle(const DBV& v1,const DBV& v2) const;
};

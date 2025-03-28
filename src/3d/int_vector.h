#pragma once

#include "xbuffer.h"
#include "xstream.h"

struct DBV;
struct DBM;

/******************************************************************************
			   INTEGER VECTOR
******************************************************************************/
struct Vector 
{
	int x,y,z;

		Vector(){}
		Vector(int u,int v,int t);
		Vector(const DBV& w);

	int operator [](unsigned int i) const { return ((int*)this)[i % 3]; }					      
	int& operator [](unsigned int i) { return ((int*)this)[i % 3]; }					      

	Vector& operator= (const DBV& w);

	Vector operator- () const;

		/* Logical operations */
	int operator () () const;
	int operator ! () const;
	int operator == (const Vector& v) const;
	int operator != (const Vector& v) const;

		/* Norm operations */
	int abs2() const;
	int vabs() const;
	int sum() const;
	Vector& norm(int r);
	Vector get_norm(int r) const;

		/* Vector - Vector operations */
	Vector& operator+= (const Vector& v);
	Vector& operator-= (const Vector& v);
	Vector& operator%= (const Vector& v); //      Cross product

	Vector operator+ (const Vector& v) const;
	Vector operator- (const Vector& v) const;
	Vector operator% (const Vector& v) const;   //	    Cross product
	int operator* (const Vector& v) const;		//	Dot product

	Vector operator/ (const Vector& v) const;   //	    Component-wise division
	Vector& operator *= (const Vector& v);	//	Component-wise multiplication
	Vector& operator /= (const Vector& v);	//	Component-wise division

		/* Vector - Matrix operations */
	Vector& operator*= (const DBM& m);
	Vector operator* (const DBM& m) const;
	friend Vector operator* (const DBM& v, const Vector& m);

		/* Scalar operations */
	Vector& operator*= (int w);
	Vector& operator/= (int w);
	Vector operator* (int w) const;
	Vector operator/ (int w) const;
	friend Vector operator* (int w,const Vector& v);
	
	Vector& operator*= (double w);
	Vector& operator/= (double w);
	Vector operator* (double w) const;
	Vector operator/ (double w) const;
	friend Vector operator* (double w,const Vector& v);


		/* Shifting operations */
	Vector& operator>>= (int n);
	Vector& operator<<= (int n);

	Vector operator>> (int n) const;
	Vector operator<< (int n) const;

		/* I/O operations */
	void print();
	friend XStream& operator<= (XStream& s,const Vector& v);
	friend XStream& operator>= (XStream& s,Vector& v);
	friend XStream& operator< (XStream& s,Vector& v);
	friend XStream& operator> (XStream& s,Vector& v);

	friend XBuffer& operator<= (XBuffer& b,const Vector& v);
	friend XBuffer& operator>= (XBuffer& b,Vector& v);
	friend XBuffer& operator< (XBuffer& b,const Vector& v);
	friend XBuffer& operator> (XBuffer& b,Vector& v);

		/* Descart - spherical function */
	int psi() const;
	int tetta() const;
	Vector& spherical(int psi,int tetta,int radius);

		/* Convertions to & from angular coord systems*/
	Vector& spherical2descart();
	Vector& descart2spherical();
	Vector descart() const; 	      // Get descart from spherical
	Vector spherical() const;	      // Get spherical from descart

		/* Special function */
	int bitSR() const;
	Vector& rnd(int r);
};

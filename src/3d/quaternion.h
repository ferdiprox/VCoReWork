#pragma once

#include "xstream.h"
#include "xbuffer.h"

struct DBM;
struct DBV;

/******************************************************************************
				Quaternion  Declaration
******************************************************************************/
struct Quaternion {
	double w;
	double x;
	double y;
	double z;

		Quaternion(){}
		Quaternion(double w,double x,double y,double z);	// Simple assignment 
		Quaternion(double theta,DBV u);					// Rotation by theta around u, where u needn't to be unit
		Quaternion(const DBM& m);					// Representation of matrix by quaternion, where ||m|| == 1
		operator DBM();								// Generate corresponding matrix 

	Quaternion operator ~() const;			// Invertion of imaginary parts (x,y,z)
	Quaternion inverse() const;			// q^-1 = ~q/(q*~q)	
	Quaternion operator -() const;		

	void rotation(double& theta,DBV& u) const;
	void Euler(double& phi,double& psi,double& theta) const;

		/* Norm operations */
	double norm2() const;
	double norm() const;
	Quaternion& norm(double s);
	Quaternion get_norm(double s) const;

		/* Quaternion - Quaternion operations */
	Quaternion& operator+= (const Quaternion& q);
	Quaternion& operator-= (const Quaternion& q);
	Quaternion operator+ (const Quaternion& q) const;
	Quaternion operator- (const Quaternion& q) const;
	
	Quaternion& operator%= (const Quaternion& q);       //      Cross product
	Quaternion operator% (const Quaternion& q) const;   //      Cross product
	
	double operator* (const Quaternion& q) const;		//      Dot product

		/* Scalar operations */
	Quaternion& operator*= (double s);
	Quaternion& operator/= (double s);
	Quaternion operator* (double s) const;
	Quaternion operator/ (double s) const;
	friend Quaternion operator* (double s,const Quaternion& q);

		/* I/O operations */
	//friend XConsole& operator<= (XConsole& c,const Quaternion& q);
	void print();

	friend XStream& operator<= (XStream& s,const Quaternion& q);
	friend XStream& operator>= (XStream& s,Quaternion& q);
	friend XStream& operator< (XStream& s,Quaternion& q);
	friend XStream& operator> (XStream& s,Quaternion& q);

	friend XBuffer& operator<= (XBuffer& b,const Quaternion& q);
	friend XBuffer& operator>= (XBuffer& b,Quaternion& q);
	friend XBuffer& operator< (XBuffer& b,const Quaternion& q);
	friend XBuffer& operator> (XBuffer& b,Quaternion& q);

	/* Special function */
	Quaternion& rotate(DBV v);
};

// Spherical linear interpolation
Quaternion Slerp(const Quaternion& A,const Quaternion& B,double t);
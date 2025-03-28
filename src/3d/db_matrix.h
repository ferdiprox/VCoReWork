#pragma once

#include <cstring>

#include "xstream.h"
#include "xbuffer.h"

#include "../math/3dconst.h"
#include "../math/int_math.h"

struct DBV;

/******************************************************************************
			   DOUBLE MATRIX
******************************************************************************/
struct DBM {
	double a[9];

			// Creates I
		DBM();
		DBM(const DBM& m);
		DBM(double a0,double a1,double a2,
		    double a3,double a4,double a5,
		    double a6,double a7,double a8);

			// Rotation around 'axis' (for integer angles)
		DBM(int angle,int axis);
			// Rotation around 'axis' (for real angles)
		DBM(double angle,int axis);
			// Diagonal and Euler-angles-matrix (for real angles)
		DBM(double psi,double tetta,double phi,int mode);
			// Rotation around vector
		DBM(const DBV& v,double angle);
	
	//	Access to elements:
	//	0  1  2		1,1   1,2    1,3    	
	//	3  4  5		2,1   2,2    2,3 
	//	6  7  8		3,1   3,2    3,3 
	double operator [](unsigned int i) const { return a[i]; }					      
	double operator ()(int i,int j) const { i--; j--; return a[i + i + i + j]; }	       
	double& operator [](unsigned int i) { return a[i]; }					      
	double& operator ()(int i,int j){ i--; j--; return a[i + i + i + j]; }	       

	DBM& transpose();
	friend DBM transpose(const DBM& m);

	DBM& operator+= (const DBM& m);
	DBM& operator-= (const DBM& m);
	DBM& operator*= (const DBM& m);
	DBM& operator*= (double w);
	DBM& operator/= (double w);
	DBM& operator+= (double w);
	DBM& operator-= (double w);

	DBM operator+ (const DBM& m) const;
	DBM operator- (const DBM& m) const;
	DBM operator* (const DBM& m) const;
	DBM operator* (double w) const;
	DBM operator/ (double w) const;
	DBM operator+ (double w) const;
	DBM operator- (double w) const;


		/* I/O operations */
	//friend XConsole& operator<= (XConsole& c,const DBM& v);
	void print();
	friend XStream& operator<= (XStream& s,const DBM& v);
	friend XStream& operator>= (XStream& s,DBM& v);
	friend XStream& operator< (XStream& s,DBM& v);
	friend XStream& operator> (XStream& s,DBM& v);

	friend XBuffer& operator<= (XBuffer& b,const DBM& v);
	friend XBuffer& operator>= (XBuffer& b,DBM& v);
	friend XBuffer& operator< (XBuffer& b,const DBM& v);
	friend XBuffer& operator> (XBuffer& b,DBM& v);

	DBV rotation_angles() const;
	double rotation_energy() const;

	double det() const;
	DBM inverse() const;
};

#include "inline/db_matrix.h"
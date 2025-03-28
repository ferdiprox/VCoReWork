#pragma once

/******************************************************************************
			 Double Matrix Definition
******************************************************************************/
inline DBM::DBM()
{
	a[0] = 1; a[1] = 0; a[2] = 0;
	a[3] = 0; a[4] = 1; a[5] = 0;
	a[6] = 0; a[7] = 0; a[8] = 1;
}
inline DBM::DBM(const DBM& m)
{
	a[0] = m[0]; a[1] = m[1]; a[2] = m[2];
	a[3] = m[3]; a[4] = m[4]; a[5] = m[5];
	a[6] = m[6]; a[7] = m[7]; a[8] = m[8];
}
inline DBM::DBM(double a0,double a1,double a2,
	 double a3,double a4,double a5,
	 double a6,double a7,double a8)
{
	a[0] = a0; a[1] = a1; a[2] = a2;
	a[3] = a3; a[4] = a4; a[5] = a5;
	a[6] = a6; a[7] = a7; a[8] = a8;
}
inline DBM::DBM(int angle,int axis)
{
//	------ Calculate Matrix for ROTATE point an angle ------
	double calpha = fCos(angle);
	double salpha = fSin(angle);
	switch(axis){
		case Z_AXIS:
			a[0]   =  calpha; a[1]	 = -salpha; a[2]   = 0;
			a[3]   =  salpha; a[4]	 = calpha;  a[5]   = 0;
			a[6]   = 0;	  a[7]	 = 0;	    a[8]   = 1;
			break;
		case X_AXIS:
			a[0]   =  1;	  a[1]	 =  0;	    a[2]   = 0;
			a[3]   =  0;	  a[4]	 =  calpha; a[5]   = -salpha;
			a[6]   =  0;	  a[7]	 =  salpha; a[8]   = calpha;
			break;
		case Y_AXIS:
			a[0]   = calpha;  a[1]	 =  0;	    a[2]   = salpha;
			a[3]   = 0;	  a[4]	 =  1;	    a[5]   = 0;
			a[6]   = -salpha; a[7]	 =  0;	    a[8]   = calpha;
			break;
		}
}
inline DBM::DBM(double angle,int axis)
{
//	------ Calculate Matrix for ROTATE point an angle ------
	double calpha = cos(angle);
	double salpha = sin(angle);
	switch(axis){
		case Z_AXIS:
			a[0]   =  calpha; a[1]	 = -salpha; a[2]   = 0;
			a[3]   =  salpha; a[4]	 = calpha;  a[5]   = 0;
			a[6]   = 0;	  a[7]	 = 0;	    a[8]   = 1;
			break;
		case X_AXIS:
			a[0]   =  1;	  a[1]	 =  0;	    a[2]   = 0;
			a[3]   =  0;	  a[4]	 =  calpha; a[5]   = -salpha;
			a[6]   =  0;	  a[7]	 =  salpha; a[8]   = calpha;
			break;
		case Y_AXIS:
			a[0]   = calpha;  a[1]	 =  0;	    a[2]   = salpha;
			a[3]   = 0;	  a[4]	 =  1;	    a[5]   = 0;
			a[6]   = -salpha; a[7]	 =  0;	    a[8]   = calpha;
			break;
		}
}

inline DBM& DBM::transpose()
{
	double t;
	t = a[1]; a[1] = a[3]; a[3] = t;
	t = a[2]; a[2] = a[6]; a[6] = t;
	t = a[5]; a[5] = a[7]; a[7] = t;
	return *this;
}
inline DBM transpose(const DBM& m)
{
	return DBM(m[0],m[3],m[6],
			    m[1],m[4],m[7],
			    m[2],m[5],m[8]);
}

inline DBM& DBM::operator+= (const DBM& m)
{
	for(int i = 0;i < 9;i++)
		a[i] += m.a[i];
	return *this;
}
inline DBM& DBM::operator-= (const DBM& m)
{
	for(int i = 0;i < 9;i++)
		a[i] -= m.a[i];
	return *this;
}
inline DBM& DBM::operator*= (const DBM& m)
{
	double t[9];
	t[0] = a[0]*m.a[0] + a[1]*m.a[3] + a[2]*m.a[6];
	t[1] = a[0]*m.a[1] + a[1]*m.a[4] + a[2]*m.a[7];
	t[2] = a[0]*m.a[2] + a[1]*m.a[5] + a[2]*m.a[8];
	t[3] = a[3]*m.a[0] + a[4]*m.a[3] + a[5]*m.a[6];
	t[4] = a[3]*m.a[1] + a[4]*m.a[4] + a[5]*m.a[7];
	t[5] = a[3]*m.a[2] + a[4]*m.a[5] + a[5]*m.a[8];
	t[6] = a[6]*m.a[0] + a[7]*m.a[3] + a[8]*m.a[6];
	t[7] = a[6]*m.a[1] + a[7]*m.a[4] + a[8]*m.a[7];
	t[8] = a[6]*m.a[2] + a[7]*m.a[5] + a[8]*m.a[8];
	memcpy(a,t,sizeof(double)*9);
	return *this;
}
inline DBM& DBM::operator*= (double w)
{
	for(int i = 0;i < 9;i++)
		a[i] *= w;
	return *this;
}
inline DBM& DBM::operator/= (double w)
{
	w = 1/w;
	for(int i = 0;i < 9;i++)
		a[i] *= w;
	return *this;
}
inline DBM& DBM::operator+= (double w)
{
	for(int i = 0;i < 9;i++)
		a[i] += w;
	return *this;
}
inline DBM& DBM::operator-= (double w)
{
	for(int i = 0;i < 9;i++)
		a[i] -= w;
	return *this;
}

inline DBM DBM::operator+ (const DBM& m) const
{
	DBM m1;
	for(int i = 0;i < 9;i++)
		m1.a[i] = a[i] + m.a[i];
	return m1;
}
inline DBM DBM::operator- (const DBM& m) const
{
	DBM m1;
	for(int i = 0;i < 9;i++)
		m1.a[i] = a[i] - m.a[i];
	return m1;
}
inline DBM DBM::operator* (const DBM& m) const
{
	DBM m1;
	m1.a[0] = a[0]*m.a[0] + a[1]*m.a[3] + a[2]*m.a[6];
	m1.a[1] = a[0]*m.a[1] + a[1]*m.a[4] + a[2]*m.a[7];
	m1.a[2] = a[0]*m.a[2] + a[1]*m.a[5] + a[2]*m.a[8];
	m1.a[3] = a[3]*m.a[0] + a[4]*m.a[3] + a[5]*m.a[6];
	m1.a[4] = a[3]*m.a[1] + a[4]*m.a[4] + a[5]*m.a[7];
	m1.a[5] = a[3]*m.a[2] + a[4]*m.a[5] + a[5]*m.a[8];
	m1.a[6] = a[6]*m.a[0] + a[7]*m.a[3] + a[8]*m.a[6];
	m1.a[7] = a[6]*m.a[1] + a[7]*m.a[4] + a[8]*m.a[7];
	m1.a[8] = a[6]*m.a[2] + a[7]*m.a[5] + a[8]*m.a[8];
	return m1;
}
inline DBM DBM::operator* (double w) const
{
	DBM m;
	for(int i = 0;i < 9;i++)
		m.a[i] = a[i]*w;
	return m;
}
inline DBM DBM::operator/ (double w) const
{
	DBM m;
	w = 1/w;
	for(int i = 0;i < 9;i++)
		m.a[i] = a[i]*w;
	return m;
}
inline DBM DBM::operator+ (double w) const
{
	DBM m;
	for(int i = 0;i < 9;i++)
		m.a[i] = a[i] + w;
	return m;
}
inline DBM DBM::operator- (double w) const
{
	DBM m;
	for(int i = 0;i < 9;i++)
		m.a[i] = a[i] - w;
	return m;
}

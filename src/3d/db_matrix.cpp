#include "db_matrix.h"

#include <iostream>

#include "db_vector.h"

/******************************************************************************
			DB_MATRIX Definition
******************************************************************************/
DBM::DBM(double psi,double tetta,double phi,int mode)
{
	switch(mode){
		case DIAGONAL:

			memset(a,0,sizeof(double)*9);

			a[0] = psi;
			a[4] = tetta;
			a[8] = phi;

			break;

		case EULER:

			if(fabs(phi) < DBL_EPS)
			{
				double t1 = cos(psi);
				double t2 = cos(tetta);
				double t4 = sin(psi);
				double t5 = sin(tetta);
				a[0] = t1*t2;  a[1] = -t4;  a[2] = t1*t5;
				a[3] = t4*t2;  a[4] = t1;   a[5] = t4*t5;
				a[6] = -t5;    a[7] = 0.0;  a[8] = t2;
			}
			else
			{
				double t1 = cos(psi);
				double t2 = cos(tetta);
				double t3 = t1*t2;
				double t4 = cos(phi);
				double t6 = sin(psi);
				double t7 = sin(phi);
				double t13 = sin(tetta);
				double t15 = t6*t2;
				a[0] = t3*t4-t6*t7;  a[1] = -t3*t7-t4*t6;  a[2] = t1*t13;
				a[3] = t15*t4+t1*t7; a[4] = -t15*t7+t1*t4; a[5] = t6*t13;
				a[6] = -t13*t4;      a[7] = t13*t7;	   a[8] = t2;
			}

			break;

		case EULER_INV:

			if(fabs(phi) < DBL_EPS)
			{
				double t1 = cos(psi);
				double t2 = cos(tetta);
				double t4 = sin(psi);
				double t6 = sin(tetta);
				a[0]   = t1*t2;   a[1]	 =  t4*t2;  a[2]   = -t6;
				a[3]   = -t4;	  a[4]	 =  t1;     a[5]   = 0;
				a[6]   = t1*t6;   a[7]	 =  t4*t6;  a[8]   = t2;
			}
			else
			{
				double t1 = cos(psi);
				double t2 = cos(tetta);
				double t3 = t1*t2;
				double t4 = cos(phi);
				double t6 = sin(psi);
				double t7 = sin(phi);
				double t10 = t6*t2;
				double t14 = sin(tetta);
				a[0] = t3*t4-t6*t7;  a[1] = t10*t4+t1*t7;  a[2] = -t14*t4;
				a[3] = -t3*t7-t4*t6; a[4] = -t10*t7+t1*t4; a[5] = t14*t7;
				a[6] = t1*t14;	     a[7] = t6*t14;	   a[8] = t2;
			}
			
			break;

		case AROUND_EULER: 
		{
			double t1 = cos(psi);
			double t2 = t1*t1;
			double t3 = cos(tetta);
			double t4 = t3*t3;
			double t6 = cos(phi);
			double t8 = sin(psi);
			double t9 = t8*t8;
			double t11 = sin(tetta);
			double t12 = t11*t11;
			double t17 = t8*t4*t1*t6;
			double t19 = sin(phi);
			double t20 = t9*t3*t19;
			double t22 = t2*t3*t19;
			double t24 = t1*t8*t6;
			double t26 = t1*t12*t8;
			double t28 = t11*t1;
			double t29 = t3*t6;
			double t30 = t28*t29;
			double t31 = t11*t8;
			double t32 = t31*t19;
			double t33 = t28*t3;
			double t41 = t31*t29;
			double t42 = t28*t19;
			double t43 = t31*t3;

			a[0] = t2*t4*t6+t9*t6+t2*t12;
			a[1] = t17-t20-t22-t24+t26;
			a[2] = -t30+t32+t33;
			a[3] = t17+t22+t20-t24+t26;
			a[4] = t9*t4*t6+t2*t6+t9*t12;
			a[5] = -t41-t42+t43;
			a[6] = -t30-t32+t33;
			a[7] = -t41+t42+t43;
			a[8] = t12*t6+t4;

			break;
		}

		case AROUND_VECTOR: 
		{
			DBV v(psi,tetta,phi);

			(*this) = DBM(v.psi(),v.tetta(),v.vabs(),AROUND_EULER);

			break;
		}
	}
}
DBM::DBM(const DBV& dbVector, double angle)
{
	(*this) = DBM(dbVector.psi(), dbVector.tetta(), angle, AROUND_EULER);
}

void DBM::print() {
	std::cout<<a[0]<<" \t"<<a[1]<<" \t"<<a[2]<<"\n";
	std::cout<<a[3]<<" \t"<<a[4]<<" \t"<<a[5]<<"\n";
	std::cout<<a[6]<<" \t"<<a[7]<<" \t"<<a[8]<<"\n";
}

XStream& operator<= (XStream& s,const DBM& m)
{
	s <= m.a[0] < " \t" <= m.a[1] < " \t" <= m.a[2] < "\n";
	s <= m.a[3] < " \t" <= m.a[4] < " \t" <= m.a[5] < "\n";
	s <= m.a[6] < " \t" <= m.a[7] < " \t" <= m.a[8] < "\n";
	return s;
}
XStream& operator>= (XStream& s,DBM& m)
{
	s >= m.a[0] >= m.a[1] >= m.a[2];
	s >= m.a[3] >= m.a[4] >= m.a[5];
	s >= m.a[6] >= m.a[7] >= m.a[8];
	return s;
}
XStream& operator< (XStream& s,DBM& m)
{
	s.write(&m,sizeof(DBM));
	return s;
}
XStream& operator> (XStream& s,DBM& m)
{
	s.read(&m,sizeof(DBM));
	return s;
}

XBuffer& operator<= (XBuffer& b,const DBM& m)
{
	b <= m.a[0] < " \t" <= m.a[1] < " \t" <= m.a[2] < "\n";
	b <= m.a[3] < " \t" <= m.a[4] < " \t" <= m.a[5] < "\n";
	b <= m.a[6] < " \t" <= m.a[7] < " \t" <= m.a[8] < "\n";
	return b;
}
XBuffer& operator>= (XBuffer& b,DBM& m)
{
	b >= m.a[0] >= m.a[1] >= m.a[2];
	b >= m.a[3] >= m.a[4] >= m.a[5];
	b >= m.a[6] >= m.a[7] >= m.a[8];
	return b;
}
XBuffer& operator< (XBuffer& b,const DBM& m)
{
	b < m.a[0] < m.a[1] < m.a[2];
	b < m.a[3] < m.a[4] < m.a[5];
	b < m.a[6] < m.a[7] < m.a[8];
	return b;
}
XBuffer& operator> (XBuffer& b,DBM& m)
{
	b > m.a[0] > m.a[1] > m.a[2];
	b > m.a[3] > m.a[4] > m.a[5];
	b > m.a[6] > m.a[7] > m.a[8];
	return b;
}
double DBM::det() const
{
	return 	a[0]*a[4]*a[8] + a[1]*a[6]*a[5] + a[3]*a[7]*a[2] - a[6]*a[4]*a[2] - a[3]*a[1]*a[8] - a[0]*a[5]*a[7];
}

DBM DBM::inverse() const
{
	double t4 = a[0]*a[4];
	double t6 = a[0]*a[5];
	double t8 = a[1]*a[3];
	double t10 = a[2]*a[3];
	double t12 = a[1]*a[6];
	double t14 = a[2]*a[6];
	double t17 = 1/(t4*a[8]-t6*a[7]-t8*a[8]+t10*a[7]+t12*a[5]-t14*a[4]);

	DBM inv;
	inv.a[0] = (a[4]*a[8]-a[5]*a[7])*t17;
	inv.a[1] = -(a[1]*a[8]-a[2]*a[7])*t17;
	inv.a[2] = -(-a[1]*a[5]+a[2]*a[4])*t17;
	inv.a[3] = -(a[3]*a[8]-a[5]*a[6])*t17;
	inv.a[4] = (a[0]*a[8]-t14)*t17;
	inv.a[5] = -(t6-t10)*t17;
	inv.a[6] = (a[3]*a[7]-a[4]*a[6])*t17;
	inv.a[7] = -(a[0]*a[7]-t12)*t17;
	inv.a[8] = (t4-t8)*t17;
	return inv;
}

DBV DBM::rotation_angles() const
{
	return DBV(
		acos(a[0]/sqrt(sqr(a[0]) + sqr(a[3]) + sqr(a[6]) + DBL_EPS)),
		acos(a[4]/sqrt(sqr(a[1]) + sqr(a[4]) + sqr(a[7]) + DBL_EPS)),
		acos(a[8]/sqrt(sqr(a[2]) + sqr(a[5]) + sqr(a[8]) + DBL_EPS))
		);
}
double DBM::rotation_energy() const
{
	return rotation_angles().vabs();
}

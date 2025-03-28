#include "quaternion.h"

#include <iostream>

#include "db_matrix.h"
#include "db_vector.h"

/******************************************************************************
				Quaternion  Definition
******************************************************************************/
Quaternion::Quaternion(double ww,double xx,double yy,double zz)
{
	w = ww;
	x = xx;
	y = yy;
	z = zz;
}
Quaternion::Quaternion(double theta,DBV u)
{
	theta /= 2;
	w = cos(theta);
	u.norm(sin(theta));
	x = u.x;
	y = u.y;
	z = u.z;
}
Quaternion::Quaternion(const DBM& m)
{
	double a1 = m[0];
	double a2 = m[4];
	double a3 = m[8];
	x = 1 + a1 - a2 - a3;
	y = 1 - a1 + a2 - a3;
	z = 1 - a1 - a2 + a3;
	w = 1 + a1 + a2 + a3;
	if(x < 0)
		x = 0;
	if(y < 0)
		y = 0;
	if(z < 0)
		z = 0;
	if(w < 0)
		w = 0;
	x = sqrt(x)/2;
	y = sqrt(y)/2;
	z = sqrt(z)/2;
	w = sqrt(w)/2;
	if(SIGN(w*x) != SIGN(m[7] - m[5]))
		x = -x;
	if(SIGN(w*y) != SIGN(m[2] - m[6]))
		y = -y;
	if(SIGN(w*z) != SIGN(m[3] - m[1]))
		z = -z;
}
Quaternion::operator DBM()
{
	double t1 = w*w;
	double t2 = z*z;
	double t3 = y*y;
	double t4 = x*x;
	double t6 = w*z;
	double t7 = y*x;
	double t9 = w*y;
	double t10 = z*x;
	double t14 = z*y;
	double t15 = w*x;
	return DBM( t1-t2-t3+t4,	-2.0*t6+2.0*t7,			2.0*t9+2.0*t10,
			2.0*t6+2.0*t7,		-t2+t1-t4+t3,			2.0*t14-2.0*t15,
			-2.0*t9+2.0*t10,	2.0*t14+2.0*t15,	-t3-t4+t1+t2);
}

Quaternion Quaternion::operator ~() const
{
	return Quaternion(w,-x,-y,-z);
}
Quaternion Quaternion::inverse() const
{
	return ~*this/norm2();
}
Quaternion Quaternion::operator -() const
{
	return Quaternion(-w,-x,-y,-z);
}

void Quaternion::rotation(double& theta,DBV& u) const
{
	double w2 = sqr(w);
	u = DBV(x,y,z)/sqrt(1 - w2);
	theta = acos(2*w2 - 1);
}
void Quaternion::Euler(double& phi,double& psi,double& theta) const
{
	double a = sqrt(1 - sqr(w));
	if(a < DBL_EPS){
		phi = psi = theta = 0;
		return;
		}
	theta = acos(z/a);
	phi = 2*acos(w);
	psi = atan2(y,x);
}

	/* Norm operations */
double Quaternion::norm2() const
{
	return w*w + x*x + y*y + z*z;
}
double Quaternion::norm() const
{
	return sqrt(w*w + x*x + y*y + z*z);
}

Quaternion& Quaternion::norm(double s)
{
	double k = s/norm();
	w *= k;
	x *= k;
	y *= k;
	z *= k;
	return *this;
}
Quaternion Quaternion::get_norm(double s) const
{
	double k = s/norm();
	return Quaternion(w* k,x*k,y*k,z*k);
}
	/* Quaternion - Quaternion operations */
Quaternion& Quaternion::operator+= (const Quaternion& q)
{
	w += q.w;
	x += q.x;
	y += q.y;
	z += q.z;
	return *this;
}
Quaternion& Quaternion::operator-= (const Quaternion& q)
{
	w -= q.w;
	x -= q.x;
	y -= q.y;
	z -= q.z;
	return *this;
}
Quaternion Quaternion::operator+ (const Quaternion& q) const
{
	return Quaternion(w + q.w,x + q.x,y + q.y,z + q.z);
}
Quaternion Quaternion::operator- (const Quaternion& q) const
{
	return Quaternion(w - q.w,x - q.x,y - q.y,z - q.z);
}

Quaternion& Quaternion::operator%= (const Quaternion& q)
{
	*this = *this % q;
	return *this;
}	
Quaternion Quaternion::operator% (const Quaternion& q) const
{
	return Quaternion(
			w*q.w-x*q.x-y*q.y-z*q.z,
			w*q.x+q.w*x+y*q.z-z*q.y,
			w*q.y+q.w*y+z*q.x-x*q.z,
			w*q.z+q.w*z+x*q.y-y*q.x);
}


double Quaternion::operator* (const Quaternion& q) const
{
	return w*q.w + x*q.x + y*q.y + z*q.z;
}

	/* Scalar operations */
Quaternion& Quaternion::operator*= (double s)
{
	w *= s;
	x *= s;
	y *= s;
	z *= s;
	return *this;
}
Quaternion& Quaternion::operator/= (double s)
{
	s = 1/s;
	w *= s;
	x *= s;
	y *= s;
	z *= s;
	return *this;
}
Quaternion Quaternion::operator* (double s) const
{
	return Quaternion(w*s,x*s,y*s,z*s);
}
Quaternion Quaternion::operator/ (double s) const
{
	s = 1/s;
	return Quaternion(w*s,x*s,y*s,z*s);
}
Quaternion operator* (double s,const Quaternion& q)
{
	return Quaternion(q.w*s,q.x*s,q.y*s,q.z*s);
}
Quaternion Slerp(const Quaternion& A,const Quaternion& B,double t)
{
	double pre_theta = A*B;
	if (fabs(pre_theta) > 1.0) {
		return A;
	}

	double theta = acos(pre_theta);
	double sin_theta = sin(theta);
	if(fabs(sin_theta) < DBL_EPS) {
		return A;
	}

	sin_theta = 1/sin_theta;
	return A*(sin(theta*(1 - t))*sin_theta) + B*(sin(theta* t)*sin_theta);
}

void Quaternion::print() {
	std::cout<<w<<" \t\t"<<x<<" \t"<<y<<" \t"<<z<<"\n";
}

XStream& operator<= (XStream& s,const Quaternion& q)
{
	s <= q.w < " \t\t"  <= q.x < " \t" <= q.y < " \t" <= q.z < "\n";
	return s;
}
XStream& operator>= (XStream& s,Quaternion& q)
{
	s >= q.w >= q.x >= q.y >= q.z;
	return s;
}
XStream& operator< (XStream& s,Quaternion& q)
{
	s.write(&q,sizeof(Quaternion));
	return s;
}
XStream& operator> (XStream& s,Quaternion& q)
{
	s.read(&q,sizeof(Quaternion));
	return s;
}

XBuffer& operator<= (XBuffer& b,const Quaternion& q)
{
	b <= q.w < " \t\t"  <= q.x < " \t" <= q.y < " \t" <= q.z < "\n";
	return b;
}
XBuffer& operator>= (XBuffer& b,Quaternion& q)
{
	b >= q.w >= q.x >= q.y >= q.z;
	return b;
}
XBuffer& operator< (XBuffer& b,const Quaternion& q)
{
	b < q.w < q.x < q.y < q.z;
	return b;
}
XBuffer& operator> (XBuffer& b,Quaternion& q)
{
	b > q.w > q.x > q.y > q.z;
	return b;
}

Quaternion& Quaternion::rotate(DBV v)
{
	v *= 0.5;
        w += -x*v.x-y*v.y-z*v.z;
	x += w*v.x-z*v.y+y*v.z;
	y += w*v.y-x*v.z+z*v.x;
	z += w*v.z-y*v.x+x*v.y;
	norm(1);
	return *this;
}
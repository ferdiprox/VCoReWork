#pragma once

/******************************************************************************
			 DB_VECTOR Definition
******************************************************************************/
inline DBV::DBV()
{
	x = y = z = 0;
}
inline DBV::DBV(double u,double v,double t)
{
	x = u;
	y = v;
	z = t;
}
inline DBV::DBV(const DBV& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
inline DBV::DBV(const Vector& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
inline DBV& DBV::operator = (const Vector& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return	*this;
}

inline DBV DBV::operator- ()
{
	return DBV(-x,-y,-z);
}

	/* Logical operations */
inline int DBV::operator () () const
{
	return fabs(x) > DBL_EPS || fabs(y) > DBL_EPS || fabs(z) > DBL_EPS;
}
inline int DBV::operator ! () const
{
	return fabs(x) < DBL_EPS && fabs(y) < DBL_EPS && fabs(z) < DBL_EPS;
}
inline int DBV::operator == (const DBV& v) const
{
	return fabs(x - v.x) < DBL_EPS &&
	       fabs(y - v.y) < DBL_EPS &&
	       fabs(z - v.z) < DBL_EPS;
}
inline int DBV::operator != (const DBV& v) const
{
	return fabs(x - v.x) > DBL_EPS ||
	       fabs(y - v.y) > DBL_EPS ||
	       fabs(z - v.z) > DBL_EPS;
}

	/* Norm operations */
inline double DBV::abs2() const
{
	return x*x + y*y + z*z;
}
inline double DBV::vabs() const
{
	return sqrt(x*x + y*y + z*z);
}
inline double DBV::sum() const
{
	return fabs(x) + fabs(y) + fabs(z);
}
inline DBV& DBV::norm(double r)
{
	double a = vabs();
	if(a > DBL_EPS){
		r /= a;
		x = x*r;
		y = y*r;
		z = z*r;
		}
	return *this;
}
inline DBV DBV::get_norm(double r) const
{
	double a = vabs();
	if(a > DBL_EPS){
		r /= a;
		return DBV(x*r, y*r, z*r);
		}
	else
		return DBV(0,0,0);
}

	/* DBV - DBV operations */
inline DBV& DBV::operator+= (const DBV& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
inline DBV& DBV::operator-= (const DBV& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
inline DBV& DBV::operator%= (const DBV& v)
{
	double xx = y*v.z - z*v.y;
	double yy = z*v.x - x*v.z;
	z = x*v.y - y*v.x;
	x = xx;
	y = yy;
	return *this;
}

inline DBV DBV::operator+ (const DBV& v) const
{
	return DBV(x + v.x, y + v.y, z + v.z);
}
inline DBV DBV::operator- (const DBV& v) const
{
	return DBV(x - v.x, y - v.y, z - v.z);
}
inline DBV DBV::operator% (const DBV& v) const
{
	return DBV(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}
inline DBV DBV::operator/ (const DBV& v) const
{
	return DBV(x/v.x, y/v.y, z/v.z);
}
inline DBV& DBV::operator*= (const DBV& v)
{
	x *= v.x; y *= v.y; z *= v.z;
	return *this;
}
inline DBV& DBV::operator/= (const DBV& v)
{
	x /= v.x; y /= v.y; z /= v.z;
	return *this;
}
inline double DBV::operator* (const DBV& v) const
{
	return x*v.x + y*v.y + z*v.z;
}

	/* Scalar operations */
inline DBV& DBV::operator*= (double w)
{
	x *= w;
	y *= w;
	z *= w;
	return *this;
}
inline DBV& DBV::operator/= (double w)
{
	w = 1/w;
	x *= w;
	y *= w;
	z *= w;
	return *this;
}
inline DBV DBV::operator* (double w) const
{
	return DBV(x*w, y*w, z*w);
}
inline DBV DBV::operator/ (double w) const
{
	w = 1/w;
	return DBV(x*w, y*w, z*w);
}
inline DBV operator* (double w,const DBV& v)
{
	return DBV(v.x*w, v.y*w, v.z*w);
}

	/* DBV - Matrix operation */
inline DBV& DBV::operator*= (const DBM& m)
{
	double xx = m.a[0]*x + m.a[1]*y + m.a[2]*z;
	double yy = m.a[3]*x + m.a[4]*y + m.a[5]*z;
	z = m.a[6]*x + m.a[7]*y + m.a[8]*z;
	x = xx;
	y = yy;
	return *this;
}
inline DBV DBV::operator* (const DBM& m) const
{
	return DBV (m.a[0]*x + m.a[1]*y + m.a[2]*z,
		     m.a[3]*x + m.a[4]*y + m.a[5]*z,
		     m.a[6]*x + m.a[7]*y + m.a[8]*z);
}
inline DBV operator* (const DBM& m, const DBV& v)
{
	return DBV (m.a[0]*v.x + m.a[1]*v.y + m.a[2]*v.z,
		     m.a[3]*v.x + m.a[4]*v.y + m.a[5]*v.z,
		     m.a[6]*v.x + m.a[7]*v.y + m.a[8]*v.z);
}

	/* Shifting operations */
inline DBV& DBV::operator>>= (int n)
{
	double a = 1/(double)(1 << n);
	x *= a;
	y *= a;
	z *= a;
	return *this;
}
inline DBV& DBV::operator<<= (int n)
{
	double a = 1 << n;
	x *= a;
	y *= a;
	z *= a;
	return *this;
}
inline DBV DBV::operator>> (int n) const
{
	double a = 1/(double)(1 << n);
	return DBV(x*a, y*a, z*a);
}
inline DBV DBV::operator<< (int n) const
{
	double a = 1 << n;
	return DBV(x*a, y*a, z*a);
}

inline DBV& DBV::spherical2descart()
{
	double xx = z*sin(y);
	double yy = xx*sin(x);
	xx *= cos(x);
	z = z*cos(y);
	x = xx;
	y = yy;
	return *this;
}
inline DBV& DBV::descart2spherical()
{
	double p = atan2(y,x);
	double r = vabs();
	double t = acos(z/r);
	x = p;
	y = t;
	z = r;
	return *this;
}
inline DBV DBV::descart() const
{
	double xx = z*sin(y);
	return DBV(
			xx*cos(x),
			xx*sin(x),
			z*cos(y)
			);
}
inline DBV DBV::spherical() const
{
	DBV v;
	v.x    = atan2(y,x);
	v.z = vabs();
	v.y  = acos(z/v.z);
	return v;
}
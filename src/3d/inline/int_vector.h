#pragma once

/******************************************************************************
		Inline Vector Funtion definition
******************************************************************************/
inline Vector::Vector(int u,int v,int t)
{
	x = u;
	y = v;
	z = t;
}

inline Vector::Vector(const DBV& w)
{
	x = round(w.x);
	y = round(w.y);
	z = round(w.z);
}

inline Vector& Vector::operator= (const DBV& w)
{
	x = round(w.x);
	y = round(w.y);
	z = round(w.z);
	return *this;
}

inline Vector Vector::operator- () const
{	    
	return Vector(-x,-y,-z);
}

	/* Logical operations */
inline int Vector::operator () () const
{
	return x || y || z;
}

inline int Vector::operator ! () const
{
	return !x && !y && !z;
}

inline int Vector::operator == (const Vector& v) const
{
	return x == v.x && y == v.y && z == v.z;
}

inline int Vector::operator != (const Vector& v) const
{
	return x != v.x || y != v.y || z == v.z;
}

	/* Norm operations */
inline int Vector::abs2() const
{
	return x*x + y*y + z*z;
}

inline int Vector::vabs() const
{
	return (int)sqrt((double)x*x + y*y + z*z);
}

inline int Vector::sum() const
{
	return abs(x) + abs(y) + abs(z);
}

inline Vector& Vector::norm(int r)
{
	int a = vabs();
	if(a){
		x = x*r/a;
		y = y*r/a;
		z = z*r/a;
		}
	return *this;
}

inline Vector Vector::get_norm(int r) const
{
	int a = vabs();
	if(a)
		return Vector(x*r/a, y*r/a, z*r/a);
	else
		return Vector(0,0,0);
}

	/* Vector - Vector operations */
inline Vector& Vector::operator+= (const Vector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline Vector& Vector::operator-= (const Vector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline Vector& Vector::operator%= (const Vector& v)
{
	int xx = y*v.z - z*v.y;
	int yy = z*v.x - x*v.z;
	z = x*v.y - y*v.x;
	x = xx;
	y = yy;
	return *this;
}

inline Vector Vector::operator+ (const Vector& v) const
{
	return Vector(x + v.x, y + v.y, z + v.z);
}

inline Vector Vector::operator- (const Vector& v) const
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

inline Vector Vector::operator% (const Vector& v) const
{
	return Vector(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

inline Vector Vector::operator/ (const Vector& v) const
{
	return Vector(x/v.x, y/v.y, z/v.z);
}

inline Vector& Vector::operator*= (const Vector& v)
{
	x *= v.x; y *= v.y; z *= v.z;
	return *this;
}

inline Vector& Vector::operator/= (const Vector& v)
{
	x /= v.x; y /= v.y; z /= v.z;
	return *this;
}

inline int Vector::operator* (const Vector& v) const
{
	return x*v.x + y*v.y + z*v.z;
}

	/* Scalar operations */
inline Vector& Vector::operator*= (int w)
{
	x *= w;
	y *= w;
	z *= w;
	return *this;
}

inline Vector& Vector::operator/= (int w)
{
	double d = 1/(double)w;
	x = round(x*d);
	y = round(y*d);
	z = round(z*d);
	return *this;
}

inline Vector Vector::operator* (int w) const
{
	return Vector(x*w, y*w, z*w);
}

inline Vector Vector::operator/ (int w) const
{
	double d = 1/(double)w;
	return Vector(round(x*d), round(y*d), round(z*d));
}

inline Vector operator* (int w,const Vector& v)
{
	return Vector(v.x*w, v.y*w, v.z*w);
}

inline Vector& Vector::operator*= (double w)
{
	x = round(x*w);
	y = round(y*w);
	z = round(z*w);
	return *this;
}

inline Vector& Vector::operator/= (double w)
{
	w = 1/w;
	x = round(x*w);
	y = round(y*w);
	z = round(z*w);
	return *this;
}

inline Vector Vector::operator* (double w) const
{
	return Vector(round(x*w), round(y*w), round(z*w));
}

inline Vector Vector::operator/ (double w) const
{
	w = 1/w;
	return Vector(round(x*w), round(y*w), round(z*w));
}

inline Vector operator* (double w,const Vector& v)
{
	return Vector(round(v.x*w), round(v.y*w), round(v.z*w));
}

	/* Shifting operations */
inline Vector& Vector::operator>>= (int n)
{
	x >>= n;
	y >>= n;
	z >>= n;
	return *this;
}

inline Vector& Vector::operator<<= (int n)
{
	x <<= n;
	y <<= n;
	z <<= n;
	return *this;
}

inline Vector Vector::operator>> (int n) const
{
	return Vector(x >> n, y >> n, z >> n);
}

inline Vector Vector::operator<< (int n) const
{
	return Vector(x << n, y << n, z << n);
}

	/* Descart - spherical function */
inline int Vector::psi() const
{
	return Atan2(y,x);
}

inline int Vector::tetta() const
{
	return ArcCos(z,vabs());
}

inline Vector& Vector::spherical(int psi,int tetta,int radius)
{
	double xy = radius*fSin(tetta);
	x = round(xy*fCos(psi));
	y = round(xy*fSin(psi));
	z = round(radius*fCos(tetta));
	return *this;
}

inline Vector& Vector::spherical2descart()
{
	double xy = z*fSin(y);
	int yy = round(xy*fSin(x));
	x = round(xy*fCos(x));	// ! x is the same as x
	z = round(z*fCos(y));
	y = yy;
	return *this;
}

inline Vector& Vector::descart2spherical()
{
	int p = Atan2(y,x);
	int r = vabs();
	int t = ArcCos(z,r);
	x = p;
	y = t;
	z = r;
	return *this;
}

inline Vector Vector::descart() const
{
	double xy = z*fSin(y);
	return Vector(
			round(xy*fCos(x)),
			round(xy*fSin(x)),
			round(z*fCos(y))
			);
}

inline Vector Vector::spherical() const
{
	Vector v;
	v.x    = Atan2(y,x);
	v.z = vabs();
	v.y  = ArcCos(z,v.z);
	return v;
}

	/* Vector - Matrix operations */
inline Vector& Vector::operator*= (const DBM& m)
{
	int xx = round(m.a[0]*x + m.a[1]*y + m.a[2]*z);
	int yy = round(m.a[3]*x + m.a[4]*y + m.a[5]*z);
	z = round(m.a[6]*x + m.a[7]*y + m.a[8]*z);
	x = xx;
	y = yy;
	return *this;
}

inline Vector Vector::operator* (const DBM& m) const
{
	return Vector(
		round(m.a[0]*x + m.a[1]*y + m.a[2]*z),
		round(m.a[3]*x + m.a[4]*y + m.a[5]*z),
		round(m.a[6]*x + m.a[7]*y + m.a[8]*z));
}

inline Vector operator* (const DBM& m,const Vector& v)
{
	return Vector(
		round(m.a[0]*v.x + m.a[1]*v.y + m.a[2]*v.z),
		round(m.a[3]*v.x + m.a[4]*v.y + m.a[5]*v.z),
		round(m.a[6]*v.x + m.a[7]*v.y + m.a[8]*v.z));
}

	/* Special function */
inline int Vector::bitSR() const
{
	return max(::bitSR(x),::bitSR(y),::bitSR(z));
}
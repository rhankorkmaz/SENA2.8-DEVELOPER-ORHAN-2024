
#include "Shengming.h"
#include <math.h>

//-----------------------------------------------------------------------------
// Vector2
//-----------------------------------------------------------------------------
// construction

Vector2::Vector2(float fX, float fY)
{
	x = fX;
	y = fY;
}
Vector2::Vector2(const float* afTuple)
{
	x = afTuple[0];
	y = afTuple[1];
}
Vector2::Vector2(const Vector2& rkV)
{
	x=rkV.x;
	y=rkV.y;
}

// casting
Vector2::operator float* ()
{
	return &x;
}

Vector2::operator const float* () const
{
	return &x;
}

// arithmetic operations
Vector2 Vector2::operator+ (const Vector2& rkV) const
{
	return Vector2(x+rkV.x, y+rkV.y);
}
Vector2 Vector2::operator- (const Vector2& rkV) const
{
	return Vector2(x-rkV.x, y-rkV.y);
}
Vector2 Vector2::operator* (float fScalar) const
{
	return Vector2(x*fScalar, y*fScalar);
}
Vector2 Vector2::operator/ (float fScalar) const
{
	if (fScalar == 0.f)
	{
		return Vector2(Math::MAX_REAL, Math::MAX_REAL);
	}
	else
	{
		float fInvScalar = 1.f/fScalar;
		return Vector2(x*fInvScalar, y*fInvScalar);
	}
}

// unary operators
Vector2 Vector2::operator+ () const
{
	return *this;
}
Vector2 Vector2::operator- () const
{
	return Vector2(-x, -y);
}

// arithmetic updates
Vector2& Vector2::operator+= (const Vector2& rkV)
{
	x+=rkV.x;
	y+=rkV.y;
	return *this;
}
Vector2& Vector2::operator-= (const Vector2& rkV)
{
	x-=rkV.x;
	y-=rkV.y;
	return *this;
}
Vector2& Vector2::operator*= (float fScalar)
{
	x*=fScalar;
	y*=fScalar;
	return *this;
}
Vector2& Vector2::operator/= (float fScalar)
{
	if (fScalar == 0.f)
	{
		x=Math::MAX_REAL;
		y=Math::MAX_REAL;
	}
	else
	{
		float fInvScalar = 1.f/fScalar;

		x*=fInvScalar;
		y*=fInvScalar;
	}
	return *this;
}

Vector2 operator * ( float fScalar, const Vector2 & rkV )
{
	return Vector2(fScalar*rkV.x, fScalar*rkV.y);
}

bool Vector2::operator == ( const Vector2& rkV) const
{
	return x==rkV.x && y==rkV.y;
}
bool Vector2::operator != ( const Vector2& rkV) const
{
	return x!=rkV.x || y!=rkV.y;
}

//-----------------------------------------------------------------------------
// Vector3
//-----------------------------------------------------------------------------
// construction
Vector3::Vector3(float fX, float fY, float fZ)
{
	x = fX;
	y = fY;
	z = fZ;
}
Vector3::Vector3(const float* afTuple)
{
	x = afTuple[0];
	y = afTuple[1];
	z = afTuple[2];
}
Vector3::Vector3(const Vector3& rkV)
{
	x=rkV.x;
	y=rkV.y;
	z=rkV.z;
}

// casting
Vector3::operator float* ()
{
	return &x;
}

Vector3::operator const float* () const
{
	return &x;
}

// arithmetic operations
Vector3 Vector3::operator+ (const Vector3& rkV) const
{
	return Vector3(x+rkV.x, y+rkV.y, z+rkV.z);
}
Vector3 Vector3::operator- (const Vector3& rkV) const
{
	return Vector3(x-rkV.x, y-rkV.y, z-rkV.z);
}
Vector3 Vector3::operator* (float fScalar) const
{
	return Vector3(x*fScalar, y*fScalar, z*fScalar);
}
Vector3 Vector3::operator/ (float fScalar) const
{
	if (fScalar == 0.f)
	{
		return Vector3(Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL);
	}
	else
	{
		float fInvScalar = 1.f/fScalar;
		return Vector3(x*fInvScalar, y*fInvScalar, z*fInvScalar);
	}
}

// unary operators
Vector3 Vector3::operator+ () const
{
	return *this;
}
Vector3 Vector3::operator- () const
{
	return Vector3(-x, -y, -z);
}

// arithmetic updates
Vector3& Vector3::operator+= (const Vector3& rkV)
{
	x+=rkV.x;
	y+=rkV.y;
	z+=rkV.z;
	return *this;
}
Vector3& Vector3::operator-= (const Vector3& rkV)
{
	x-=rkV.x;
	y-=rkV.y;
	z-=rkV.z;
	return *this;
}
Vector3& Vector3::operator*= (float fScalar)
{
	x*=fScalar;
	y*=fScalar;
	z*=fScalar;
	return *this;
}
Vector3& Vector3::operator/= (float fScalar)
{
	if (fScalar == 0.f)
	{
		x=Math::MAX_REAL;
		y=Math::MAX_REAL;
		z=Math::MAX_REAL;
	}
	else
	{
		float fInvScalar = 1.f/fScalar;

		x*=fInvScalar;
		y*=fInvScalar;
		z*=fInvScalar;
	}
	return *this;
}

Vector3 operator * ( float fScalar, const Vector3 & rkV )
{
	return Vector3(fScalar*rkV.x, fScalar*rkV.y, fScalar*rkV.z);
}

bool Vector3::operator == ( const Vector3& rkV) const
{
	return x==rkV.x && y==rkV.y && z==rkV.z;
}
bool Vector3::operator != ( const Vector3& rkV) const
{
	return x!=rkV.x || y!=rkV.y || z!=rkV.z;
}


//-----------------------------------------------------------------------------
// Plane
//-----------------------------------------------------------------------------

Plane::Plane( const float* pf )
{
	a = pf[0];
	b = pf[1];
	c = pf[2];
	d = pf[3];
}

Plane::Plane( float fa, float fb, float fc, float fd )
{
	a = fa;
	b = fb;
	c = fc;
	d = fd;
}


// casting

Plane::operator float* ()
{
	return (float *) &a;
}


Plane::operator const float* () const
{
	return (const float *) &a;
}


// assignment operators

Plane& Plane::operator *= ( float f )
{
	a *= f;
	b *= f;
	c *= f;
	d *= f;
	return *this;
}

Plane& Plane::operator /= ( float f )
{
	float fInv = 1.f / f;
	a *= fInv;
	b *= fInv;
	c *= fInv;
	d *= fInv;
	return *this;
}


// unary operators
Plane Plane::operator + () const
{
	return *this;
}

Plane Plane::operator - () const
{
	return Plane(-a, -b, -c, -d);
}


// binary operators
Plane Plane::operator * ( float f ) const
{
	return Plane(a * f, b * f, c * f, d * f);
}

Plane Plane::operator / ( float f ) const
{
	float fInv = 1.0f / f;
	return Plane(a * fInv, b * fInv, c * fInv, d * fInv);
}

Plane operator * (float f, const Plane& p )
{
	return Plane(f * p.a, f * p.b, f * p.c, f * p.d);
}

bool Plane::operator == ( const Plane& p ) const
{
	return a == p.a && b == p.b && c == p.c && d == p.d;
}

bool Plane::operator != ( const Plane& p ) const
{
	return a != p.a || b != p.b || c != p.c || d != p.d;
}
Vector3 const * Plane::Normal()const
{
	return (Vector3 const *)(void const *)(&a);
}

//-----------------------------------------------------------------------------
// Matrix2
//-----------------------------------------------------------------------------
// construction
Matrix2::Matrix2( const float * pf)
{
	m[0][0] = pf[0];
	m[0][1] = pf[1];
	m[1][0] = pf[2];
	m[1][1] = pf[3];
}
Matrix2::Matrix2( const Matrix2 & rhs)
{
	m[0][0] = rhs.m[0][0];
	m[0][1] = rhs.m[0][1];
	m[1][0] = rhs.m[1][0];
	m[1][1] = rhs.m[1][1];
}
Matrix2::Matrix2( float _11, float _12
				 , float _21, float _22)
{
	m[0][0] = m[0][0];
	m[0][1] = m[0][1];
	m[1][0] = m[1][0];
	m[1][1] = m[1][1];
}


// access grants
float& Matrix2::operator () ( int Row, int Col )
{
	return m[Row][Col];
}
float Matrix2::operator () ( int Row, int Col ) const
{
	return m[Row][Col];
}

// casting operators
Matrix2::operator float* ()
{
	return &m[0][0];
}
Matrix2::operator const float* () const
{
	return &m[0][0];
}

// assignment operators
Matrix2& Matrix2::operator *= ( const Matrix2& mat )
{
	Matrix2Multiply(this, this, &mat);
	return *this;
}
Matrix2& Matrix2::operator += ( const Matrix2& mat)
{
	m[0][0] += mat.m[0][0]; m[0][1] += mat.m[0][1];
	m[1][0] += mat.m[1][0]; m[1][1] += mat.m[1][1];
	return *this;
}
Matrix2& Matrix2::operator -= ( const Matrix2& mat)
{
	m[0][0] -= mat.m[0][0]; m[0][1] -= mat.m[0][1];
	m[1][0] -= mat.m[1][0]; m[1][1] -= mat.m[1][1];
	return *this;
}
Matrix2& Matrix2::operator *= ( float f )
{
	m[0][0] *= f; m[0][1] *= f;
	m[1][0] *= f; m[1][1] *= f;
	return *this;
}

Matrix2& Matrix2::operator /= ( float f )
{
	if(f == float(0.0))
	{
		m[0][0] = m[0][1] = Math::MAX_REAL;
		m[1][0] = m[1][1] = Math::MAX_REAL;
	}
	else
	{
		float fInv = 1.0f / f;
		m[0][0] *= fInv; m[0][1] *= fInv;
		m[1][0] *= fInv; m[1][1] *= fInv;
	}
	return *this;
}
// unary operators
Matrix2 Matrix2::operator + () const
{
	return *this;
}
Matrix2 Matrix2::operator - () const
{
	return Matrix2( -m[0][0], -m[0][1],
		-m[1][0], -m[1][1]);
}

// binary operators
Matrix2 Matrix2::operator * ( const Matrix2& mat) const
{
	Matrix2 matT;
	Matrix2Multiply(&matT, this, &mat);
	return matT;
}
Matrix2 Matrix2::operator + ( const Matrix2& mat) const
{
	return Matrix2(m[0][0] + mat.m[0][0], m[0][1] + mat.m[0][1],
		m[1][0] + mat.m[1][0], m[1][1] + mat.m[1][1]);
}
Matrix2 Matrix2::operator - ( const Matrix2& mat) const
{
	return Matrix2(m[0][0] - mat.m[0][0], m[0][1] - mat.m[0][1],
		m[1][0] - mat.m[1][0], m[1][1] - mat.m[1][1]);
}
Matrix2 Matrix2::operator * ( float f ) const
{
	return Matrix2(m[0][0] * f, m[0][1] * f,
		m[1][0] * f, m[1][1] * f);
}
Matrix2 Matrix2::operator / ( float f) const
{
	if(f != float(0.0))
	{
		float fInv = 1.0f / f;
		return Matrix2( m[0][0] * fInv, m[0][1] * fInv,
			m[1][0] * fInv, m[1][1] * fInv);
	}
	else
	{
		return Matrix2( Math::MAX_REAL, Math::MAX_REAL,
			Math::MAX_REAL, Math::MAX_REAL);
	}
}

Matrix2 operator * ( float f, const Matrix2& mat)
{
	return Matrix2(mat.m[0][0] * f, mat.m[0][1] * f,
		mat.m[1][0] * f, mat.m[1][1] * f);
}

bool Matrix2::operator == ( const Matrix2& mat) const
{
	return ( m[0][0] == mat.m[0][0] && m[0][1] == mat.m[0][1] 
	&& m[1][0] == mat.m[1][0] && m[1][1] == mat.m[1][1] );
}
bool Matrix2::operator != ( const Matrix2& mat) const
{
	return ( m[0][0] != mat.m[0][0] || m[0][1] != mat.m[0][1] 
	|| m[1][0] != mat.m[1][0] || m[1][1] != mat.m[1][1] );
}
//-----------------------------------------------------------------------------
// Vector2
//-----------------------------------------------------------------------------
float Vec2Length(Vector2 const * v)
{
	return sqrtf(v->x * v->x + v->y * v->y);
}
float Vec2LengthSq(Vector2 const * v)
{
	return (v->x * v->x + v->y * v->y);
}
float Vec2Dot(Vector2 const * v1, Vector2 const * v2)
{
	return (v1->x * v2->x + v1->y * v2->y);
}
float Vec2Cross(Vector2 const * v1, Vector2 const * v2)
{
	return v1->x * v2->y - v1->y * v2->x;
}
Vector2 * Vec2Normalize(Vector2 * out, Vector2 const * v)
{
	float fLength = Vec2Length(v);

	if (fLength > Math::ZERO_TOLERANCE)
	{
		float fInvLength = 1.f/fLength;
		out->x = v->x * fInvLength;
		out->y = v->y * fInvLength;
	}
	else
	{
		out->x = 
			out->y = 0.f;
	}

	return out;
}
Vector2 * Vec2Transform(Vector2 * out, Vector2 const * v, Matrix2 const * m)
{
	Vector2 t;
	t.x = v->x*m->m[0][0] + v->y*m->m[1][0];
	t.y = v->x*m->m[0][1] + v->y*m->m[1][1];
	*out = t;

	return out;
}

//-----------------------------------------------------------------------------
// Vector3
//-----------------------------------------------------------------------------
float Vec3Length(Vector3 const * v)
{
	return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}
float Vec3LengthSq(Vector3 const * v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z);
}
float Vec3Dot(Vector3 const * v1, Vector3 const * v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}
Vector3 * Vec3Cross(Vector3 * out, Vector3 const * v1, Vector3 const * v2)
{
	Vector3 v;

	v.x = v1->y * v2->z - v1->z * v2->y;
	v.y = v1->z * v2->x - v1->x * v2->z;
	v.z = v1->x * v2->y - v1->y * v2->x;

	*out = v;
	return out;
}
Vector3 * Vec3Normalize(Vector3 * out, Vector3 const * v)
{
	float fLength = Vec3Length(v);

	if (fLength > Math::ZERO_TOLERANCE)
	{
		float fInvLength = 1.f/fLength;
		out->x = v->x * fInvLength;
		out->y = v->y * fInvLength;
		out->z = v->z * fInvLength;
	}
	else
	{
		out->x =
			out->y =
			out->z = 0.f;
	}

	return out;
}
Vector3 * Vec3Transform(Vector3 * out, Vector3 const * v, Matrix2 const * m)
{
	Vector2 t;
	t.x = v->x*m->m[0][0] + v->y*m->m[1][0];
	t.y = v->x*m->m[0][1] + v->y*m->m[1][1];

	out->x = t.x;
	out->y = t.y;

	return out;
}

//-----------------------------------------------------------------------------
// Plane
//-----------------------------------------------------------------------------
float PlaneDistance(Plane const * p, Vector3 const * v)
{
	return Vec3Dot( p->Normal(), v ) - p->d;
}

Vector3 * PlaneIntersectLine(Vector3 * out, Plane const * p, Vector3 const * from, Vector3 const * to)
{
	Vector3 dir = (*to) - (*from);
	Vec3Normalize(&dir, &dir);

	float dot = Vec3Dot(&dir, p->Normal());
	if(float(fabs(dot)) > Math::ZERO_TOLERANCE)
	{
		float dist = PlaneDistance(p, from);
		float len = dist / ( -dot );

		*out = dir*len;
		return out;
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------------------
// Matrix2
//-----------------------------------------------------------------------------
Matrix2* Matrix2Multiply(Matrix2* out, Matrix2 const * m1, Matrix2 const * m2)
{
	Matrix2 t;
	t.m[0][0] = m1->m[0][0] * m2->m[0][0] + m1->m[0][1] * m2->m[1][0];
	t.m[0][1] = m1->m[0][0] * m2->m[0][1] + m1->m[0][1] * m2->m[1][1];
	t.m[1][0] = m1->m[1][0] * m2->m[0][0] + m1->m[1][1] * m2->m[1][0];
	t.m[1][0] = m1->m[1][0] * m2->m[0][1] + m1->m[1][1] * m2->m[1][1];

	*out = t;
	return out;
}
Matrix2* Mat2Scale(Matrix2* out, float s)
{
	out->m[0][0] = out->m[1][1] = s;
	out->m[0][1] = out->m[1][0] = float(0.0);

	return out;
}
Matrix2* Mat2Rotation(Matrix2* out, float radian)
{
	out->m[0][0] = float(cos(radian));	out->m[0][1] = float(sin(radian));
	out->m[1][0] = -out->m[0][1];			out->m[1][1] = out->m[0][0];

	return out;
}
Matrix2* Mat2Inverse(Matrix2 * out, float * out_det, Matrix2 const * in)
{
	const float det = in->m[0][0]*in->m[1][1] - in->m[0][1]*in->m[1][0];
	if(out_det)
		*out_det = det;

	if(float(fabs(det)) > Math::ZERO_TOLERANCE)
	{
		Matrix2 tmp(*in);
		const float invsDet = 1.f/det;

		out->m[0][0] =  tmp.m[1][1]*invsDet;	out->m[0][1] = -tmp.m[0][1]*invsDet;
		out->m[1][0] = -tmp.m[1][0]*invsDet;	out->m[1][1] =  tmp.m[0][0]*invsDet;
	}
	else
	{
		out->m[0][0] = out->m[0][1] = out->m[1][0] = out->m[1][1] = 0.f;
	}

	return out;
}

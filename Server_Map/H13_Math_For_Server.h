
#ifndef H013_MATH_FOR_SERVER_H
#define H013_MATH_FOR_SERVER_H

#include <math.h>

namespace Math
{
	// common constants
	const float EPSILON =  1.192092896e-07F ;
	const float ZERO_TOLERANCE = 1e-06f;
	const float MAX_REAL = 3.402823466e+38F;
	const float PI = 3.14159265358979323846f;
	const float TWO_PI = 2.0f*Math::PI;
	const float HALF_PI = 0.5f*Math::PI;
	const float INV_PI = 1.0f/Math::PI;
	const float INV_TWO_PI = 1.0f/Math::TWO_PI;
	const float DEG_TO_RAD = Math::PI/180.0f;
	const float RAD_TO_DEG = 180.0f/Math::PI;
};


struct Vector2
{
	float x,y;

	// construction
	Vector2(){};
	Vector2(float fX, float fY);
	Vector2(const float* afTuple);
	Vector2(const Vector2& rkV);

	// casting
	operator float* ();
	operator const float* () const;

	// arithmetic operations
	Vector2 operator+ (const Vector2& rkV) const;
	Vector2 operator- (const Vector2& rkV) const;
	Vector2 operator* (float fScalar) const;
	Vector2 operator/ (float fScalar) const;

	// unary operators
	Vector2 operator+ () const;
	Vector2 operator- () const;

	// arithmetic updates
	Vector2& operator+= (const Vector2& rkV);
	Vector2& operator-= (const Vector2& rkV);
	Vector2& operator*= (float fScalar);
	Vector2& operator/= (float fScalar);

	friend Vector2 operator * ( float, const Vector2& );

	bool operator == ( const Vector2& ) const;
	bool operator != ( const Vector2& ) const;
};

struct Vector3
{
	float x,y,z;

	// construction
	Vector3 (){};  // uninitialized
	Vector3 (float fX, float fY, float fZ);
	Vector3 (const float* afTuple);
	Vector3 (const Vector3& rkV);

	// casting
	operator float* ();
	operator const float* () const;

	// arithmetic operations
	Vector3 operator+ (const Vector3& rkV) const;
	Vector3 operator- (const Vector3& rkV) const;
	Vector3 operator* (float fScalar) const;
	Vector3 operator/ (float fScalar) const;

	// unary operators
	Vector3 operator+ () const;
	Vector3 operator- () const;

	// arithmetic updates
	Vector3& operator+= (const Vector3& rkV);
	Vector3& operator-= (const Vector3& rkV);
	Vector3& operator*= (float fScalar);
	Vector3& operator/= (float fScalar);

	friend Vector3 operator * ( float, const Vector3& );

	bool operator == ( const Vector3& ) const;
	bool operator != ( const Vector3& ) const;

};


struct Plane
{
	float a,b,c,d;

	Plane() {}
	Plane( const float* );
	Plane( float fa, float fb, float fc, float fd );

	// casting
	operator float* ();
	operator const float* () const;

	// assignment operators
	Plane& operator *= ( float );
	Plane& operator /= ( float );

	// unary operators
	Plane operator + () const;
	Plane operator - () const;

	// binary operators
	Plane operator * ( float ) const;
	Plane operator / ( float ) const;

	friend Plane operator * ( float, const Plane& );

	bool operator == ( const Plane& ) const;
	bool operator != ( const Plane& ) const;

	// util
	Vector3 const * Normal()const;
};


struct Matrix2
{
	float m[2][2];

	// construction
	Matrix2() {};
	Matrix2( const float * );
	Matrix2( const Matrix2 & );
    Matrix2( float _11, float _12,
           float _21, float _22);

	// access grants
	float& operator () ( int Row, int Col );
	float  operator () ( int Row, int Col ) const;

	// casting operators
	operator float* ();
	operator const float* () const;

	// assignment operators
	Matrix2& operator *= ( const Matrix2& );
	Matrix2& operator += ( const Matrix2& );
	Matrix2& operator -= ( const Matrix2& );
	Matrix2& operator *= ( float );
	Matrix2& operator /= ( float );

	// unary operators
	Matrix2 operator + () const;
	Matrix2 operator - () const;

	// binary operators
	Matrix2 operator * ( const Matrix2& ) const;
	Matrix2 operator + ( const Matrix2& ) const;
	Matrix2 operator - ( const Matrix2& ) const;
	Matrix2 operator * ( float ) const;
	Matrix2 operator / ( float ) const;

	friend Matrix2 operator * ( float, const Matrix2& );

	bool operator == ( const Matrix2& ) const;
	bool operator != ( const Matrix2& ) const;
};

//-----------------------------------------------------------------------------
// Vector2
//-----------------------------------------------------------------------------
float Vec2Length(Vector2 const * v);
float Vec2LengthSq(Vector2 const * v);
float Vec2Dot(Vector2 const * v1, Vector2 const * v2);
float Vec2Cross(Vector2 * out, Vector2 const * v1, Vector2 const * v2);
Vector2 * Vec2Normalize(Vector2 * out, Vector2 const * v);
Vector2 * Vec2Transform(Vector2 * out, Vector2 const * v, Matrix2 const * m);

//-----------------------------------------------------------------------------
// Vector3
//-----------------------------------------------------------------------------
float Vec3Length(Vector3 const * v);
float Vec3LengthSq(Vector3 const * v);
float Vec3Dot(Vector3 const * v1, Vector3 const * v2);
Vector3 * Vec3Cross(Vector3 * out, Vector3 const * v1, Vector3 const * v2);
Vector3 * Vec3Normalize(Vector3 * out, Vector3 const * v);
Vector3 * Vec3Transform(Vector3 * out, Vector3 const * v, Matrix2 const * m);

//-----------------------------------------------------------------------------
// Plane
//-----------------------------------------------------------------------------
float PlaneDistance(Plane const * p, Vector3 const * v);
Vector3 * PlaneIntersectLine(Vector3 * out, Plane const * p, Vector3 const * from, Vector3 const * to);

//-----------------------------------------------------------------------------
// Matrix2
//-----------------------------------------------------------------------------
Matrix2* Matrix2Multiply(Matrix2* out, Matrix2 const * m1, Matrix2 const * m2);
Matrix2* Mat2Scale(Matrix2* out, float s);
Matrix2* Mat2Rotation(Matrix2* out, float radian);
Matrix2* Mat2Inverse(Matrix2 * out, float * out_det, Matrix2 const * in);

#endif	//H013_MATH_FOR_SERVER_H

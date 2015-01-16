#pragma once
//-------------------------------------------------------------------------------------------------------------------------------
// Math
//
// Defines super quick and useful math functions including vectors and matrices.
//-------------------------------------------------------------------------------------------------------------------------------

#include <assert.h>
#include <math.h>

namespace HE
{
	//-----------------------------------------------------------------------------------------------------------------------
	// SECTION: FUNCTIONS
	//-----------------------------------------------------------------------------------------------------------------------

	// Wikipedia: Fast inverse square root used for calculating vector normals.
	// Fun fact - Originally implemented in Quake III Arena
	float FastInverseSquareRoot(const float number);

	//-----------------------------------------------------------------------------------------------------------------------
	// SECTION: CLASSES
	//-----------------------------------------------------------------------------------------------------------------------

	class BitVector8
	{
	private:
		char bits;

	public:
		BitVector8() : bits(0) {}

		void Clear() { bits = 0; }
		bool GetBit(const int index) const  { return (bits & (1 << index)) > 0; }
		void SetBit(const int index)		{ bits |= (1 << index); }
		void ClearBit(const int index)		{ bits &= (~(1 << index)); }
		void ToggleBit(const int index)		{ bits ^= (1 << index); }
	};

	class BitVector16
	{
	private:
		short bits;

	public:
		BitVector16() : bits(0) {}

		void Clear() { bits = 0; }
		bool GetBit(const int index) const	{ return (bits & (1 << index)) > 0; }
		void SetBit(const int index)		{ bits |= (1 << index); }
		void ClearBit(const int index)		{ bits &= (~(1 << index)); }
		void ToggleBit(const int index)		{ bits ^= (1 << index); }
	};

	class BitVector32
	{
	private:
		int bits;

		BitVector32() : bits(0) {}

		void Clear() { bits = 0; }
		bool GetBit(const int index) const	{ return (bits & (1 << index)) > 0; }
		void SetBit(const int index)		{ bits |= (1 << index); }
		void ClearBit(const int index)		{ bits &= (~(1 << index)); }
		void ToggleBit(const int index)		{ bits ^= (1 << index); }
	};
	
	class BitVector64
	{
	private:
		long long bits;

		BitVector64() : bits(0) {}

		void Clear() { bits = 0; }
		bool GetBit(const int index) const	{ return (bits & (1i64 << index)) > 0; }
		void SetBit(const int index)		{ bits |= (1i64 << index); }
		void ClearBit(const int index)		{ bits &= (~(1i64 << index)); }
		void ToggleBit(const int index)		{ bits ^= (1i64 << index); }
	};
	
	/*
	class Vector2f
	{
	public:
		// public x, y for fast access

		float x, y;

		//----------------------------------------------------------------------------
		// Construction
		//----------------------------------------------------------------------------

		Vector2f() : x(0.0f), y(0.0f) {}
		Vector2f(const float _x, const float _y) : x(_x), y(_y) {}
		Vector2f(const Vector2f& other) : x(other.x), y(other.y) {}

		//----------------------------------------------------------------------------
		// Transformations
		//----------------------------------------------------------------------------

		// Normalize this vector.
		void Normalize() { float inverseSquareRoot = FastInverseSquareRoot(LengthSquared()); x *= inverseSquareRoot; y *= inverseSquareRoot; }
		// Return a new normalized vector with the same direction as this.
		Vector2f NewNormalized() const { float inverseSquareRoot = FastInverseSquareRoot(LengthSquared()); return Vector2f(x * inverseSquareRoot, y * inverseSquareRoot); }

		//----------------------------------------------------------------------------
		// Properties
		//----------------------------------------------------------------------------

		// no Length() implemented to discourage its usage for performance
		float LengthSquared() const { return ((x * x) + (y * y)); }
		float Direction() const { return atan2(y, x); }

		//----------------------------------------------------------------------------
		// Unary Arithmetic
		//----------------------------------------------------------------------------

		Vector2f operator - () const { return Vector2f(-x, -y); }

		//----------------------------------------------------------------------------
		// Arithmetic
		//----------------------------------------------------------------------------

		Vector2f operator + (Vector2f const& other) const { return Vector2f(x + other.x, y + other.y); }
		Vector2f operator - (Vector2f const& other) const { return Vector2f(x - other.x, y - other.y); }
		Vector2f operator * (const float scalar) const { return Vector2f(x * scalar, y * scalar); }
		Vector2f operator / (const float scalar) const { assert(scalar != 0.0f && "Attempting divide by zero in HE::Vector2f::operator/"); return Vector2f(x / scalar, y / scalar); }

		Vector2f operator + (Vector2f const *const pOther) const { return Vector2f(x + pOther->x, y + pOther->y); }
		Vector2f operator - (Vector2f const *const pOther) const { return Vector2f(x - pOther->x, y - pOther->y); }

		float Dot(Vector2f const& other) const { return ((x * other.x) + (y * other.y)); }
		float Dot(Vector2f const *const pOther) const { return ((x * pOther->x) + (y * pOther->y)); }

		//----------------------------------------------------------------------------
		// Comparison
		//----------------------------------------------------------------------------

		bool operator < (Vector2f const& other) const { return (LengthSquared() < other.LengthSquared()); }
		bool operator > (Vector2f const& other) const { return (LengthSquared() > other.LengthSquared()); }
		bool operator <= (Vector2f const& other) const { return (LengthSquared() <= other.LengthSquared()); }
		bool operator >= (Vector2f const& other) const { return (LengthSquared() >= other.LengthSquared()); }
		bool operator == (Vector2f const& other) const { return ((x == other.x) && (y == other.y)); }
		bool operator != (Vector2f const& other) const { return ((x != other.x) || (y != other.y)); }

		bool operator < (Vector2f const *const pOther) const { return (LengthSquared() < pOther->LengthSquared()); }
		bool operator > (Vector2f const *const pOther) const { return (LengthSquared() > pOther->LengthSquared()); }
		bool operator <= (Vector2f const *const pOther) const { return (LengthSquared() <= pOther->LengthSquared()); }
		bool operator >= (Vector2f const *const pOther) const { return (LengthSquared() >= pOther->LengthSquared()); }
		bool operator == (Vector2f const *const pOther) const { return ((x == pOther->x) && (y == pOther->y)); }
		bool operator != (Vector2f const *const pOther) const { return ((x != pOther->x) || (y != pOther->y)); }

		bool OrthogonalTo(Vector2f const& other) { return (Dot(other) < 0.01f); }
		bool OrthogonalTo(Vector2f const *const pOther) { return (Dot(pOther) < 0.01f); }

		// a.AngleBetween(b) = a.Direction() - b.Direction()
		float AngleBetween(Vector2f const& other) const { return (Direction() - other.Direction()); }
		// a.AngleBetween(b) = a.Direction() - b.Direction()
		float AngleBetween(Vector2f const *const pOther) const { return (Direction() - pOther->Direction()); }

		//----------------------------------------------------------------------------
		// Assignment
		//----------------------------------------------------------------------------

		Vector2f& operator = (Vector2f const& other) { x = other.x; y = other.y; return (*this); }
		Vector2f& operator = (Vector2f const *const pOther) { x = pOther->x; y = pOther->y; return (*this); }

		//----------------------------------------------------------------------------
		// Compound Assignment
		//----------------------------------------------------------------------------

		Vector2f& operator += (Vector2f const& other) { x += other.x; y += other.y; return (*this); }
		Vector2f& operator -= (Vector2f const& other) { x -= other.x; y -= other.y; return (*this); }
		Vector2f& operator *= (const float scalar) { x *= scalar; y *= scalar; return (*this); }
		Vector2f& operator /= (const float scalar) { assert(scalar != 0.0f && "Attempting divide by zero in HE::Vector2f::operator/="); x /= scalar; y /= scalar; return (*this); }

		Vector2f& operator += (Vector2f const *const pOther) { x += pOther->x; y += pOther->y; return (*this); }
		Vector2f& operator -= (Vector2f const *const pOther) { x -= pOther->x; y -= pOther->y; return (*this); }
	};

	class Vector3f
	{
	public:
		// public x, y, z for fast access

		float x, y, z;

		//----------------------------------------------------------------------------
		// Construction
		//----------------------------------------------------------------------------

		Vector3f() : x(0.0f), y(0.0f), z(0.0f) {}
		Vector3f(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) {}

		//----------------------------------------------------------------------------
		// Transformations
		//----------------------------------------------------------------------------

		// Normalize this vector.
		void Normalize() { float inverseSquareRoot = FastInverseSquareRoot(LengthSquared()); x *= inverseSquareRoot; y *= inverseSquareRoot; z *= inverseSquareRoot; }
		// Return a new normalized vector with the same direction as this.
		Vector3f NewNormalized() const { float inverseSquareRoot = FastInverseSquareRoot(LengthSquared()); return Vector3f(x * inverseSquareRoot, y * inverseSquareRoot, z * inverseSquareRoot); }

		//----------------------------------------------------------------------------
		// Properties
		//----------------------------------------------------------------------------

		// no Length() implemented to discourage its usage for performance
		float LengthSquared() const { return ((x * x) + (y * y) + (z * z)); }
		float ThetaDirection() const { return atan2(y, x); }
		float PhiDirection() const { assert(0 && "HE::Vector3f::PhiDirection() not implemented."); }

		//----------------------------------------------------------------------------
		// Unary Arithmetic
		//----------------------------------------------------------------------------

		Vector3f operator - () const { return Vector3f(-x, -y, -z); }

		//----------------------------------------------------------------------------
		// Arithmetic
		//----------------------------------------------------------------------------

		Vector3f operator + (Vector2f const& other) const { return Vector3f(x + other.x, y + other.y, z); }
		Vector3f operator - (Vector2f const& other) const { return Vector3f(x - other.x, y - other.y, z); }

		Vector3f operator + (Vector3f const& other) const { return Vector3f(x + other.x, y + other.y, z + other.z); }
		Vector3f operator - (Vector3f const& other) const { return Vector3f(x - other.x, y - other.y, z - other.z); }
		Vector3f operator * (const float scalar) const { return Vector3f(x * scalar, y * scalar, z * scalar); }
		Vector3f operator / (const float scalar) const { assert(scalar != 0.0f && "Attempting divide by zero in Vector3f::operator/"); return Vector3f(x / scalar, y / scalar, z / scalar); }

		Vector3f operator + (Vector2f const *const pOther) const { return Vector3f(x + pOther->x, y + pOther->y, z); }
		Vector3f operator - (Vector2f const *const pOther) const { return Vector3f(x - pOther->x, y - pOther->y, z); }

		Vector3f operator + (Vector3f const *const pOther) const { return Vector3f(x + pOther->x, y + pOther->y, z + pOther->z); }
		Vector3f operator - (Vector3f const *const pOther) const { return Vector3f(x - pOther->x, y - pOther->y, z - pOther->z ); }

		float Dot(Vector3f const& other) const { return ((x * other.x) + (y * other.y) + (z * other.z)); }
		float Dot(Vector3f const *const pOther) const { return ((x * pOther->x) + (y * pOther->y) + (z * pOther->z)); }

		Vector3f Cross(const Vector3f& other) const { return Vector3f((y * other.z) - (z * other.y), (z * other.x) - (x * other.z), (x * other.y) - (y * other.x)); }

		//----------------------------------------------------------------------------
		// Comparison
		//----------------------------------------------------------------------------

		bool operator < (Vector3f const& other) const { return (LengthSquared() < other.LengthSquared()); }
		bool operator > (Vector3f const& other) const { return (LengthSquared() > other.LengthSquared()); }
		bool operator <= (Vector3f const& other) const { return (LengthSquared() <= other.LengthSquared()); }
		bool operator >= (Vector3f const& other) const { return (LengthSquared() >= other.LengthSquared()); }
		bool operator == (Vector3f const& other) const { return ((x == other.x) && (y == other.y)); }
		bool operator != (Vector3f const& other) const { return ((x != other.x) || (y != other.y)); }

		bool operator < (Vector3f const *const pOther) const { return (LengthSquared() < pOther->LengthSquared()); }
		bool operator > (Vector3f const *const pOther) const { return (LengthSquared() > pOther->LengthSquared()); }
		bool operator <= (Vector3f const *const pOther) const { return (LengthSquared() <= pOther->LengthSquared()); }
		bool operator >= (Vector3f const *const pOther) const { return (LengthSquared() >= pOther->LengthSquared()); }
		bool operator == (Vector3f const *const pOther) const { return ((x == pOther->x) && (y == pOther->y) && (z == pOther->z)); }
		bool operator != (Vector3f const *const pOther) const { return ((x != pOther->x) || (y != pOther->y) || (z != pOther->z)); }

		bool OrthogonalTo(Vector3f const& other) { return (Dot(other) < 0.01f); }
		bool OrthogonalTo(Vector3f const *const pOther) { return (Dot(pOther) < 0.01f); }

		// a.AngleBetween(b) = a.Direction() - b.Direction()
		//float AngleBetween(Vector3f const& other) const { return (Direction() - other.Direction()); }
		// a.AngleBetween(b) = a.Direction() - b.Direction()
		//float AngleBetween(Vector3f const *const pOther) const { return (Direction() - pOther->Direction()); }

		//----------------------------------------------------------------------------
		// Assignment
		//----------------------------------------------------------------------------

		Vector3f& operator = (Vector3f const& other) { x = other.x; y = other.y; z = other.z; return (*this); }
		Vector3f& operator = (Vector3f const *const pOther) { x = pOther->x; y = pOther->y; z = pOther->z; return (*this); }

		//----------------------------------------------------------------------------
		// Compound Assignment
		//----------------------------------------------------------------------------

		Vector3f& operator += (Vector2f const& other) { x += other.x; y += other.y; return (*this); }
		Vector3f& operator -= (Vector2f const& other) { x -= other.x; y -= other.y; return (*this); }

		Vector3f& operator += (Vector3f const& other) { x += other.x; y += other.y; z += other.z; return (*this); }
		Vector3f& operator -= (Vector3f const& other) { x -= other.x; y -= other.y; z -= other.z; return (*this); }
		Vector3f& operator *= (const float scalar) { x *= scalar; y *= scalar; z *= scalar; return (*this); }
		Vector3f& operator /= (const float scalar) { assert(scalar != 0.0f && "Attempting divide by zero in Vector3f::operator/="); x /= scalar; y /= scalar; z /= scalar; return (*this); }

		Vector3f& operator += (Vector2f const *const pOther) { x += pOther->x; y += pOther->y; return (*this); }
		Vector3f& operator -= (Vector2f const *const pOther) { x -= pOther->x; y -= pOther->y; return (*this); }

		Vector3f& operator += (Vector3f const *const pOther) { x += pOther->x; y += pOther->y; z += pOther->z; return (*this); }
		Vector3f& operator -= (Vector3f const *const pOther) { x -= pOther->x; y -= pOther->y; z -= pOther->z; return (*this); }
	};

	class Vector4f
	{
	public:
		// public x, y, z, w for fast access

		float x, y, z, w;

		//----------------------------------------------------------------------------
		// Construction
		//----------------------------------------------------------------------------

		Vector4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		Vector4f(const float _x, const float _y, const float _z, const float _w) : x(_x), y(_y), z(_z), w(_w) {}

		//----------------------------------------------------------------------------
		// Transformations
		//----------------------------------------------------------------------------

		// Normalize this vector.
		void Normalize() { float inverseSquareRoot = FastInverseSquareRoot(LengthSquared()); x *= inverseSquareRoot; y *= inverseSquareRoot; z *= inverseSquareRoot; w *= inverseSquareRoot; }
		// Return a new normalized vector with the same direction as this.
		Vector4f NewNormalized() const { float inverseSquareRoot = FastInverseSquareRoot(LengthSquared()); return Vector4f(x * inverseSquareRoot, y * inverseSquareRoot, z * inverseSquareRoot, w * inverseSquareRoot); }

		//----------------------------------------------------------------------------
		// Properties
		//----------------------------------------------------------------------------

		// no Length() implemented to discourage its usage for performance
		float LengthSquared() const { return ((x * x) + (y * y) + (z * z) + (w * w)); }

		//----------------------------------------------------------------------------
		// Unary Arithmetic
		//----------------------------------------------------------------------------

		Vector4f operator - () const { return Vector4f(-x, -y, -z, -w); }

		//----------------------------------------------------------------------------
		// Arithmetic
		//----------------------------------------------------------------------------

		Vector4f operator + (Vector4f const& other) const { return Vector4f(x + other.x, y + other.y, z + other.z, w + other.w); }
		Vector4f operator - (Vector4f const& other) const { return Vector4f(x - other.x, y - other.y, z - other.z, w - other.w); }
		Vector4f operator * (const float scalar) const { return Vector4f(x * scalar, y * scalar, z * scalar, w * scalar); }
		Vector4f operator / (const float scalar) const { assert(scalar != 0.0f && "Attempting divide by zero in Vector4f::operator/"); return Vector4f(x / scalar, y / scalar, z / scalar, w / scalar); }

		Vector4f operator + (Vector4f const *const pOther) const { return Vector4f(x + pOther->x, y + pOther->y, z + pOther->z, w + pOther->w); }
		Vector4f operator - (Vector4f const *const pOther) const { return Vector4f(x - pOther->x, y - pOther->y, z - pOther->z, w - pOther->w); }

		float Dot(Vector4f const& other) const { return ((x * other.x) + (y * other.y) + (z * other.z) + (w * other.w)); }
		float Dot(Vector4f const *const pOther) const { return ((x * pOther->x) + (y * pOther->y) + (z * pOther->z) + (w * pOther->w)); }

		//----------------------------------------------------------------------------
		// Comparison
		//----------------------------------------------------------------------------

		bool operator < (Vector4f const& other) const { return (LengthSquared() < other.LengthSquared()); }
		bool operator > (Vector4f const& other) const { return (LengthSquared() > other.LengthSquared()); }
		bool operator <= (Vector4f const& other) const { return (LengthSquared() <= other.LengthSquared()); }
		bool operator >= (Vector4f const& other) const { return (LengthSquared() >= other.LengthSquared()); }
		bool operator == (Vector4f const& other) const { return ((x == other.x) && (y == other.y)); }
		bool operator != (Vector4f const& other) const { return ((x != other.x) || (y != other.y)); }

		bool operator < (Vector4f const *const pOther) const { return (LengthSquared() < pOther->LengthSquared()); }
		bool operator > (Vector4f const *const pOther) const { return (LengthSquared() > pOther->LengthSquared()); }
		bool operator <= (Vector4f const *const pOther) const { return (LengthSquared() <= pOther->LengthSquared()); }
		bool operator >= (Vector4f const *const pOther) const { return (LengthSquared() >= pOther->LengthSquared()); }
		bool operator == (Vector4f const *const pOther) const { return ((x == pOther->x) && (y == pOther->y) && (z == pOther->z) && (w == pOther->w)); }
		bool operator != (Vector4f const *const pOther) const { return ((x != pOther->x) || (y != pOther->y) || (z != pOther->z) || (w != pOther->w)); }

		bool OrthogonalTo(Vector4f const& other) { return (Dot(other) < 0.01f); }
		bool OrthogonalTo(Vector4f const *const pOther) { return (Dot(pOther) < 0.01f); }

		// a.AngleBetween(b) = a.Direction() - b.Direction()
		//float AngleBetween(Vector4f const& other) const { return (Direction() - other.Direction()); }
		// a.AngleBetween(b) = a.Direction() - b.Direction()
		//float AngleBetween(Vector4f const *const pOther) const { return (Direction() - pOther->Direction()); }

		//----------------------------------------------------------------------------
		// Assignment
		//----------------------------------------------------------------------------

		Vector4f& operator = (Vector4f const& other) { x = other.x; y = other.y; z = other.z; w = other.w; return (*this); }
		Vector4f& operator = (Vector4f const *const pOther) { x = pOther->x; y = pOther->y; z = pOther->z; w = pOther->w; return (*this); }

		//----------------------------------------------------------------------------
		// Compound Assignment
		//----------------------------------------------------------------------------

		Vector4f& operator += (Vector4f const& other) { x += other.x; y += other.y; z += other.z; w += other.w; return (*this); }
		Vector4f& operator -= (Vector4f const& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return (*this); }
		Vector4f& operator *= (const float scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return (*this); }
		Vector4f& operator /= (const float scalar) { assert(scalar != 0.0f && "Attempting divide by zero in Vector4f::operator/="); x /= scalar; y /= scalar; z /= scalar; w /= scalar; return (*this); }

		Vector4f& operator += (Vector4f const *const pOther) { x += pOther->x; y += pOther->y; z += pOther->z; w += pOther->w; return (*this); }
		Vector4f& operator -= (Vector4f const *const pOther) { x -= pOther->x; y -= pOther->y; z -= pOther->z; w -= pOther->w; return (*this); }
	};
	*/
}
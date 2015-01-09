#pragma once
//----------------------------------------------------------------------------------------------------------------
// Geometry2D
//
// Declares basic 2-dimensional shapes. Useful for meshing.
//----------------------------------------------------------------------------------------------------------------

#include <vector>
#include <algorithm>

#include "..\Utilities\HEMath.h"

namespace HE
{
	class Rectangle
	{
	protected:
		Vector3f topLeft, topRight, bottomRight, bottomLeft;

	public:
		Rectangle();

		Rectangle(const Vector3f& _topLeft, const Vector3f& _bottomRight);

		Rectangle(const Rectangle& other);
		Rectangle& operator=(const Rectangle& other);

		Vector3f TopLeft() const { Vector3f copy(topLeft); return copy; }
		Vector3f TopRight() const { Vector3f copy(topRight); return copy; }
		Vector3f BottomRight() const { Vector3f copy(bottomRight); return copy; }
		Vector3f BottomLeft() const { Vector3f copy(bottomLeft); return copy; }

		Vector3f CalculateCenter();

		void Translate(const float x, const float y) { Translate(Vector2f(x, y)); }
		void Translate(const Vector2f& term);
		void SetOrientation(const float _orientation);
	};

	class Polygon
	{
	protected:
		std::vector<Vector3f> verts;

	public:
		Polygon(const std::vector<Vector3f> points) { assert(points.size() > 2 && "A polygon must be at least 3 points."); verts = points; }
		Polygon(const Polygon& other) { InitFromOther(other); }
		Polygon& operator=(const Polygon& other) { verts.clear(); InitFromOther(other); }

		Vector3f& operator[](const unsigned int index) { return verts[index]; }
		const Vector3f& operator[](const unsigned int index) const { return verts[index]; }
		size_t Size() const { return verts.size(); }

		bool IsPointInsidePolygon(const float x, const float y) const;
		bool IsPointInsidePolygon(const Vector3f& point) const { return IsPointInsidePolygon(point.x, point.y); }

		bool IsColliding(const Polygon& other) const;

	private:
		void InitFromOther(const Polygon& other) { for (unsigned int i = 0; i < other.Size(); i++) verts.push_back(other[i]); }
	};
}
#pragma once
//----------------------------------------------------------------------------------------------------------------
// Geometry2D
//
// Declares basic 2-dimensional shapes. Useful for meshing.
//----------------------------------------------------------------------------------------------------------------

#include <vector>
#include <algorithm>
#include <glm.hpp>

#include "..\Utilities\HEMath.h"

namespace HE
{
	class Rectangle
	{
	protected:
		glm::vec2 topLeft, topRight, bottomRight, bottomLeft;

	public:
		// equivalent to Rectangle(glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 0.0f))
		Rectangle();
		Rectangle(const glm::vec2& _topLeft, const glm::vec2& _bottomRight);

		Rectangle(const Rectangle& other);
		Rectangle& operator=(const Rectangle& other);

		glm::vec2 TopLeft() const { glm::vec2 copy(topLeft); return copy; }
		glm::vec2 TopRight() const { glm::vec2 copy(topRight); return copy; }
		glm::vec2 BottomRight() const { glm::vec2 copy(bottomRight); return copy; }
		glm::vec2 BottomLeft() const { glm::vec2 copy(bottomLeft); return copy; }

		void Translate(const float x, const float y) { Translate(glm::vec2(x, y)); }
		void Translate(const glm::vec2& term) { topLeft += term; topRight += term; bottomRight += term; bottomLeft += term; }

		glm::vec2 CalculateCenter();

		bool IsPointInsideRectangle(const glm::vec2& point);
	};

	class Polygon
	{
	protected:
		std::vector<glm::vec2> verts;

	public:
		Polygon(const std::vector<glm::vec2>& points) { assert(points.size() > 2 && "A polygon must be at least 3 points."); verts = points; }
		Polygon(const Polygon& other) { InitFromOther(other); }
		Polygon& operator=(const Polygon& other) { verts.clear(); InitFromOther(other); }

		glm::vec2& operator[](const unsigned int index) { return verts[index]; }
		const glm::vec2& operator[](const unsigned int index) const { return verts[index]; }
		size_t Size() const { return verts.size(); }

		bool IsPointInsidePolygon(const float x, const float y) const;
		bool IsPointInsidePolygon(const glm::vec2& point) const { return IsPointInsidePolygon(point.x, point.y); }

		bool IsColliding(const Polygon& other) const;

	private:
		void InitFromOther(const Polygon& other) { for (unsigned int i = 0; i < other.Size(); i++) verts.push_back(other[i]); }
	};
}
#pragma once
//------------------------------------------------------------------------------------------
// Physics2D
//
// An interface for a physics object.
//------------------------------------------------------------------------------------------

#include <glm.hpp>
#include <vector>

#include "..\Geometry\HEGeometry2D.h"
#include "..\Utilities\HEMisc.h"

namespace HE
{
	class iCollidable
	{
	protected:
		Polygon collisionMesh;

	public:
		explicit iCollidable(const Polygon _collisionMesh) : collisionMesh(_collisionMesh) {}
		iCollidable(iCollidable const& other) : collisionMesh(other.GetCollisionMesh()) {}
		iCollidable& operator=(iCollidable const& other) { collisionMesh = other.GetCollisionMesh(); }

		Polygon GetCollisionMesh() const { return Polygon(collisionMesh); }
		void SetCollisionMesh(const Polygon newCollisionMesh) { collisionMesh = newCollisionMesh; }

		virtual void IsColliding(iCollidable const& other) { collisionMesh.IsColliding(other.GetCollisionMesh()); }
		virtual void OnCollide(std::vector<iCollidable *const> const& collisionObjects, const float deltaMilliseconds) = 0;
	};

	class Physics2DBase : public iCollidable, private Uncopyable
	{
	protected:
		float mass;
		float coefficientOfFriction;

		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec2 acceleration;

		float orientation;
		float angularVelocity;
		float angularAcceleration;

	public:
		explicit Physics2DBase(const Polygon _collisionMesh,
							   const float _mass = 0.0f,
							   const float _coefficientOfFriction = 0.0f,
							   const glm::vec2 _position = glm::vec2(0.0f, 0.0f),
							   const glm::vec2 _velocity = glm::vec2(0.0f,0.0f),
							   const glm::vec2 _acceleration = glm::vec2(0.0f,0.0f),
							   const float _orientation = 0.0f, 
							   const float _angularVelocity = 0.0f,
							   const float _angularAcceleration = 0.0f) :
			iCollidable(_collisionMesh),
			mass(_mass),
			coefficientOfFriction(_coefficientOfFriction),
			position(_position),
			velocity(_velocity),
			acceleration(_acceleration),
			orientation(_orientation),
			angularVelocity(_angularVelocity),
			angularAcceleration(_angularAcceleration)
		{}

		virtual float GetMass()							 const { return mass; }
		virtual float GetCoefficientOfFriction()         const { return coefficientOfFriction; }
		virtual glm::vec2 GetPosition()				     const { return glm::vec2(position); }
		virtual glm::vec2 GetVelocity()                  const { return glm::vec2(velocity); }
		virtual glm::vec2 GetAcceleration()              const { return glm::vec2(acceleration); }
		virtual float GetOrientation()			         const { return orientation; }
		virtual float GetAngularVelocity()				 const { return angularVelocity; }
		virtual float GetAngularAcceleration()			 const { return angularAcceleration; }

		virtual void SetMass(const float newMass)									  { mass = newMass; }
		virtual void SetCoefficientOfFriction(float newCoefficientOfFriction)		  { coefficientOfFriction = newCoefficientOfFriction; }
		virtual void SetPosition(glm::vec2 const& newPosition)						  { position = newPosition; }
		virtual void SetOrientation(const float newOrientation)						  { orientation = newOrientation; }
		virtual void SetVelocity(glm::vec2 const& newVelocity)                        { velocity = newVelocity; }
		virtual void SetAcceleration(glm::vec2 const& newAcceleration)                { acceleration = newAcceleration; }

		virtual void Translate(glm::vec2 const& translation) { position += translation; }
		virtual void Rotate(const float rotation)            { orientation += rotation; }

		virtual void GetTransformationMatrix(glm::mat3x3& out) const;

		virtual void OnUpdate(const float deltaMilliseconds);
		virtual void OnCollide(std::vector<iCollidable *const> const& collisionObjects, const float deltaMilliseconds) override;
	};
}
#pragma once
//--------------------------------------------------------------------------------------------------------------------------------------
// Actor
//
// Basic data for game actors
//--------------------------------------------------------------------------------------------------------------------------------------

namespace HE
{
	class Actor
	{
		class ActorPiece
		{
			//protected:
			// attributes list
			// physics handler
		};

	protected:
		unsigned int id;
		// ActorPiece list

	public:
		Actor(unsigned int _id) { id = _id; }
	};
}
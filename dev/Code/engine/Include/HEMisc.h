#pragma once

//----------------------------------------------------------------------------------------------------------
// Misc
//
// Defines some useful macros, functions and classes.
//----------------------------------------------------------------------------------------------------------

#define SAFE_DELETE(x) if(x) delete x; x = NULL;
#define SAFE_DELETE_ARRAY(x) if (x) delete[] x; x = NULL;

namespace HE
{
	class Uncopyable
	{
	protected:
		Uncopyable() {}
		~Uncopyable() {}

	private:
		Uncopyable(const Uncopyable&);
		Uncopyable& operator=(const Uncopyable&);
	};
}
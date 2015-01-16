#pragma once

//-----------------------------------------------------------------------------------------------------
// InputHandler
//
// Senses input from a keyboard. Mouse and joypad functionality may be added later.
//-----------------------------------------------------------------------------------------------------

#include <assert.h>
#include <string>
#include <SFML/Window.hpp>
#include <HEEventManager.h>
#include <HEMisc.h>

class InputHandler : private HE::Uncopyable
{
private:
	static bool instantiated;

public:
	InputHandler() { assert(!instantiated); instantiated = true; }

	void OnUpdate();
};

bool InputHandler::instantiated = false;
#pragma once

//-------------------------------------------------------------------------------------------------------
// Ships
//-------------------------------------------------------------------------------------------------------

#include <string>
#include <map>

#include "..\Scripting\Code\ShipParser.h"

class BasicShip
{
protected:
	std::string name;
	std::map<std::string, std::string> attributes;
	std::string imageFileName;

public:
	BasicShip() : name(""), imageFileName("") {}


	std::string Name() const { return name; }
	std::string TryGetAttribute(std::string attribName) { if (attributes.find(attribName) == attributes.end()) return NULL; else return attributes[attribName]; }
	std::string ImageFileName() const { return imageFileName; }
};
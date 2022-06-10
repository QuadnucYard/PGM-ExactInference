#pragma once
#include "factordef.h"

namespace pgm {

	struct Variable
	{
		fid_t id;
		fid_t numValues;
		std::string name;
		std::string abbr;
	};

	using VariableList = std::vector<Variable>;

}
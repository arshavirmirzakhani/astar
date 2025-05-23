#pragma once
#include "../global.h"

#include <cassert>
#include <sol/sol.hpp>

class ScriptEngine {

      public:
	ScriptEngine();
	~ScriptEngine();

	std::string script;
	void run();

	template <class Archive> void serialize(Archive& archive) { archive(script); }
};

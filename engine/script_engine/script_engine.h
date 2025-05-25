#pragma once
#include "../global.h"
#include <cassert>
#include <sol/sol.hpp>

class ScriptEngine {

      public:
	ScriptEngine();
	~ScriptEngine();

	sol::state lua_engine;

	void run(sol::state lua_engine);

	template <class Archive> void serialize(Archive& archive) { archive(script); }
};

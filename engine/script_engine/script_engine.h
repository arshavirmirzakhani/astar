#pragma once
#include "../global.h"

#include <cassert>
#include <sol/sol.hpp>

class ScriptEngine {

      public:
	ScriptEngine(/* args */);
	~ScriptEngine();

	std::string script;

	sol::state lua_engine;
	void run();
};

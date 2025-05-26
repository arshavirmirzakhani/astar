#include "script_engine.h"

ScriptEngine::ScriptEngine() {}
ScriptEngine::~ScriptEngine() {}

void ScriptEngine::run(sol::state lua_engine) { this->lua_engine.script("main()"); }

void ScriptEngine::expose_keycodes_as_constants(sol::state& lua, const std::unordered_map<std::string, KEY_CODE>& map) {
	for (const auto& [name, key] : map) {
		this->lua_engine[name] = key;
	}
}